#ifndef _FNT_H_
#define _FNT_H_

#include "base.h"
#include "graphics.h"
#include "android.h"
#include "exb.h"

/*
fnt字体加载头文件
风的影子

影子俱乐部网站：www.yzjlb.net
手机C论坛：bbs.yzjlb.net
手机C交流QQ群：370468001

*/

typedef struct
{
    int id;     //un编号
    int x;      //字体在图片上的x坐标
    int y;      //字体在图片上的y坐标
    int width;  //字宽
    int height; //字高
    int xoffset;
    int yoffset;
} _FONT;

typedef struct
{
    int bitmap;     //图片
    int lineHeight; //行高
    int base;       //字体大小
    int scaleW;     //图片宽度
    int scaleH;     //图片高度
    _FONT **font;
    int size;

} _FNT;
void fnt_drawline(_FNT *fnt, char *text, int x, int y);

//创建结构体，加载字体文件
//参数：图片名 fnt文件名
void *fnt_create(char *imgname, char *fntname)
{
    _FNT *fnt = malloc(sizeof(_FNT));
    memset(fnt, 0, sizeof(_FNT));
    fnt->bitmap = readBitmapFromAssets(imgname);
    printf("读取图片\n");
    int len = 0;
    char *temp = readFileFromAssets(fntname, &len);
    printf("%s\n", "读取文本");
    if (len <= 0)
        printf("读取文件失败%s\n", fntname);
    char *text = malloc(len + 1);
    memcpy(text, temp, len);
    *(text + len) = 0;
    free(temp);
    char c = 0;
    int line = 1;
    char *key = NULL;
    //int start=0;
    char *value = NULL;
    int type = 0;
    int linetype = 0;
    int tempi = 0;
    _FONT *font = malloc(sizeof(_FONT));
    memset(font, 0, sizeof(_FONT));
    int i = 0;
    for (i = 0; i < len; i++)
    {
        c = *(text + i);
        if (c == '\n')
            line++;
    }
    fnt->font = malloc(line * 4);
    memset(fnt->font, 0, line * 4);
    fnt->size = line;
    //fnt->bitmap = readBitmapFromAssets(imgname);

    for (i = 0; i < len; i++)
    {
        c = *(text + i);
        switch (type)
        {
        case 0: //解析key
            if (c >= 'a' && c <= 'z')
            {
                //start = i;
                key = text + i;
                type = 1;
                if (strncmp(key, "info", 4) == 0)
                    linetype = 0;
                if (strncmp(key, "page", 4) == 0)
                    linetype = 1;
                if (strncmp(key, "common", 6) == 0)
                    linetype = 2;
                if (strncmp(key, "chars", 5) == 0)
                    linetype = 3;
                if (strncmp(key, "char ", 5) == 0)
                    linetype = 4;
            }
            else if (c == '\n')
            {
                type = 0;
            }
            break;
        case 1: //解析阶段
            if (c == ' ')
            {
                type = 2;
                key = text + i + 1;
            }
            if (c == '\n')
                type = 0;
            break;
        case 2: //寻找az 解析key
            if (c >= 'a' && c <= 'z')
            {
                type = 3;
                key = text + i;
                //printf("key=%c\n",c);
            }
            else if (c == '\n')
            {
                if (linetype == 4)
                {
                    _FONT *font_temp = malloc(sizeof(_FONT));
                    memset(font_temp, 0, sizeof(_FONT));
                    font_temp->id = font->id;
                    font_temp->x = font->x;
                    font_temp->y = font->y;
                    font_temp->width = font->width;
                    font_temp->height = font->height;
                    fnt->font[tempi++] = font_temp;
                    //printf("添加一个文字：%d\n",font->id);
                }
                type = 0;
            }
            break;
        case 3: //=
            if (c == '=')
            {
                //start=i;
                value = text + i + 1;
                type = 4;
            }
            else if (c == ' ')
            {
                type = 0;
            }
            else if (c == '\n')
            {
                type = 0;
            }
            break;
        case 4: //空格
            if (c == '"')
            {
                type = 5;
            }
            else if (c >= '0' && c <= '9')
            {
                value = text + i;
                type = 2;
                //char textt[30];
                //strncpy(textt,key,5);
                //printf("key:%s\n",textt);
                if (strncmp(key, "size", 4) == 0)
                {
                    fnt->base = atoi(value);
                    fnt->lineHeight = fnt->base * 14 / 12;
                    printf("size:%d\n", fnt->base);
                }

                if (strncmp(key, "lineHeight", 10) == 0)
                {
                    //fnt->base = atoi(value);
                }
                if (strncmp(key, "scaleW", 6) == 0)
                {
                    fnt->scaleW = atoi(value);
                }
                if (strncmp(key, "scaleH", 6) == 0)
                {
                    fnt->scaleH = atoi(value);
                }

                if (strncmp(key, "id", 2) == 0)
                {
                    font->id = atoi(value);
                    // printf("id:%d\n", font->id);
                }
                if (strncmp(key, "x=", 2) == 0)
                {
                    font->x = atoi(value);
                }
                if (strncmp(key, "y=", 2) == 0)
                {
                    font->y = atoi(value);
                }
                if (strncmp(key, "width", 5) == 0)
                {
                    font->width = atoi(value);
                }
                if (strncmp(key, "height", 6) == 0)
                {
                    //printf("height=%d\n",atoi(value));
                    font->height = atoi(value);
                }
            }
            else if (c == ' ')
            {
                type = 0;
            }
            else if (c == '\n')
            {
                type = 0;
            }
            break;
        case 5: //"
            if (c == '"')
            {
                type = 2;
            }
            break;
        }
    }

    free(font);
    free(text);
    return fnt;
}

//显示单行文字
void fnt_drawline(_FNT *fnt, char *text, int x, int y)
{
    char *untemp = ex_coding(text, strlen(text), "UTF-8", "UTF-16LE");
    unsigned short *un = (unsigned short *)untemp;
    int ix = x;
    int iy = y;
    int id = 0;
    int len = wstrlen(untemp) / 2;
    int isdraw = 0;
    int n = 0;
    int i = 0;
    for (n = 0; n < len; n++)
    {
        id = un[n];
        isdraw = 0;
        //printf("绘制%x\n",id);
        for (i = 0; i < fnt->size; i++)
        {
            if (fnt->font[i] != NULL)
            {
                if (id == 0x0a)
                {
                    ix = x;
                    iy += fnt->lineHeight;
                    //printf("iy:%d\n",iy);
                    isdraw = 1;
                    break;
                }
                else if (fnt->font[i]->id == id)
                {
                    isdraw = 1;
                    //else
                    {
                        drawBitmapFlip(fnt->bitmap, ix, iy, fnt->font[i]->width, fnt->font[i]->height, fnt->font[i]->x, fnt->font[i]->y);
                        ix += fnt->font[i]->width;
                    }
                }
            }
        }
        if (!isdraw)
        {
            printf("绘制失败 id:%d\n", id);
            if (id < 128)
                ix += fnt->base / 2;
            else
                ix += fnt->base;
        }
    }
}

//显示多行文字
void fnt_drawrect(_FNT *fnt, char *text, int x, int y, int w, int h)
{
}

//显示单个文字 参数：文字编号
void fnt_draw(_FNT *fnt, int id, int x, int y)
{
    int i = 0;
    printf("绘制单个文字：%d", id);
    for (i = 0; i < fnt->size; i++)
    {
        printf("%d\n", i);
        if (fnt->font[i]->id == id)
        {
            printf("绘制x=%d y=%d w=%d h=%d\n", fnt->font[i]->x, fnt->font[i]->y, fnt->font[i]->width, fnt->font[i]->height);
            drawBitmapFlip(fnt->bitmap, x, y, fnt->font[i]->width, fnt->font[i]->height, fnt->font[i]->x, fnt->font[i]->y);
        //     printf("绘制x=%d y=%d w=%d h=%d\n", fnt->font[i]->x, fnt->font[i]->y, fnt->font[i]->width, fnt->font[i]->height);
            return;
        }
    }
}

//获取指定文字的宽度
int fnt_getW(_FNT *fnt, int id)
{
    int i = 0;
    for (i = 0; i < fnt->size; i++)
    {
        if (fnt->font[i]->id == id)
        {
            return fnt->font[i]->width;
        }
    }
    return fnt->base;
}

//检测文字是否在字体中存在
//返回值：TRUE/FALSE
int fnt_check(_FNT *fnt, int id)
{
    int i = 0;
    for (i = 0; i < fnt->size; i++)
    {
        if (fnt->font[i]->id == id)
        {
            return TRUE;
        }
    }
    return FALSE;
}
//释放字体
int fnt_free(_FNT *fnt)
{
    int i = 0;
    for (i = 0; i < fnt->size; i++)
    {
        if (fnt->font[i] != NULL)
            free(fnt->font[i]);
    }
    bitmapFree(fnt->bitmap);
    free(fnt);
    return 0;
}

#endif
