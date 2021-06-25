//加载系统头文件base.h
#include <base.h>
#include <android.h>
#include "zip.h"
#include "String.h"

#define ZIPFILE "C/读取zip信息/魔法兽司.zip"


 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}

ZIPHEAD *ziphead;

//入口函数，程序启动时开始执行
int init()
{
int dx=0,dy=0;
    //调用函数helloworld
    helloworld();
    
    setscrsize(320,480);
    cls(45,185,230);
    printf("%d",sizeof(ZIPHEAD));
    //ziphead=malloc(100);
    char text[300];
    char text2[300];
    //读取zip头信息
    ziphead=readziphead(ZIPFILE);
    if(ziphead==NULL)
    {
     toast("读取失败",0);
    }
    //显示
    sprintf(text,"文件头：%x",ziphead->head);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    sprintf(text,"解压缩所需版本：%d", ziphead->version);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    sprintf(text,"通用比特标志位：%d", ziphead->bit_flag);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    sprintf(text,"压缩方式：%d",ziphead->method);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    
    
    
    sprintf(text,"%s",ziphead->filename);
    UTF8ToUni(text, text2, 300);
    dtext(text2, dx,dy,240,240,240,1,1);
    dy+=30;
    sprintf(text,"文件名长：%d",ziphead->filename_len);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    
    sprintf(text,"扩展段长：%d",ziphead->field_len);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    ref(0,0,SCRW,SCRH);
    return 0;
}

void u2(char *text)
{
 char temp;
 int i=0;
 temp=text[i];
 text[i]=text[i+1];
 text[i+1]=temp;
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exitapp();
            break;
        case _MENU:
            break;
        }
    }

    return 0;
}

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause()
{
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
    return 0;
}
 
int exitapp()
{
 if(ziphead!=NULL)
 free(ziphead);
 exit();
}