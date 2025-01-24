#ifndef _PICTURE_H_
#define _PICTURE_H_

#include "rectflip.h"


//画面 包含图片矩形区域(用于显示图片)和显示位置
typedef struct _PICTURE
{
 RECTFLIP *rect[30];//矩形区域
 int size; //矩形块数量
} PICTURE;

//新建一张空白画面
PICTURE *pic_new();

//创建一张画面 参数：矩形区域，矩形块数量，
/*
PICTURE *pic_create(RECTFLIP *rects,int size)
{
 PICTURE *pic=malloc(sizeof(PICTURE));
// pic->rect=rects;
 pic->size=size;
 
 return pic;
};
*/

//给画面添加一个裁剪区域
int pic_add(PICTURE *picture, RECTFLIP *rect);

//显示一张画面，参数：bitmap，画面结构体，屏幕坐标
void pic_draw(int bitmap,PICTURE *pic,int x,int y);

PICTURE *pic_copy(PICTURE *pic);


//销毁画面
int pic_free(PICTURE *pic);

//释放画面



#endif
