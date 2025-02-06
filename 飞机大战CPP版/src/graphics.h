#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include "base.h"
/*
手机C编译模式头文件 graphics.h
最后修改于 2021-06-04
*/

#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

//结构体 枚举
enum
{
_JPG=0,
_PNG=1,
_BMP16=2
};


typedef struct
{
unsigned int width; //宽度
unsigned int height; //高度
unsigned int stride;
int format; //格式
unsigned int flags; // 0 for now
void *ptr; //缓存
} BITMAPINFO;



//定义函数指针
typedef int32 (*CREATEBITMAP)(int w,int h);
typedef int32 (*READBITMAP)(char *filename);
typedef int32 (*READBITMAPFROMASSETS)(char *filename);
typedef int32 (*CLIPBITMAP)(int32 b,int32 x,int32 y,int32 w,int32 h);
typedef void (*DRAWBITMAP)(int32 b,int32 x,int32 y);
typedef void (*DRAWBITMAPFLIP)(int32 b,int x,int y,int bx,int by,int bw,int bh);
typedef 
void (*DRAWBITMAPEX)(int32 b,int x,int y,int w,int h,int tx,int ty,int tw,int th);
typedef void (*DRAWBITMAPROTATE)(int32 b,int scrx,int scry, int bx, int by, int r, int color);
typedef void (*DRAWRECT)(int x,int y,int w,int h,int32 color);

typedef void (*DRAWCIR)(int x,int y,int r,int32 color);
typedef int32 (*DRAWBITMAPOLD)(int32 di, int32 buf,  int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy);
typedef int32 (*BITMAPFREE)(int32 b);
typedef int (*BITMAPGETINFO)(int32 b,BITMAPINFO *info);
typedef int32 (*SAVEBITMAP)(int32 b,char* filename, int type, int load);
typedef int32 (*DRAWBITMAPEXB)(int32 bitmap, int x,int y, int origin_x,int origin_y, int zoom_h, int zoom_v, int rotate, int color);
typedef int32 (*DRAWBITMAPEXC)(int32 bitmap, int x,int y,int cw,int ch,int bx,int by,int bw,int bh,float origin_x,float origin_y, int rotate,int alpha);


//定义指针变量
extern CREATEBITMAP createBitmap;
extern READBITMAP readBitmap;
extern READBITMAPFROMASSETS readBitmapFromAssets;
extern CLIPBITMAP clipBitmap;
extern DRAWBITMAP drawBitmap;
extern DRAWBITMAPFLIP drawBitmapFlip;
extern DRAWBITMAPEX drawBitmapEx;
extern DRAWBITMAPROTATE drawBitmapRotate;
extern DRAWRECT drawRect;

extern DRAWCIR drawCir;
extern DRAWBITMAPOLD drawBitmapOld;
extern BITMAPFREE bitmapFree;
extern BITMAPGETINFO bitmapGetInfo;

extern SAVEBITMAP saveBitmap;
extern DRAWBITMAPEXB drawBitmapExb;
extern DRAWBITMAPEXC drawBitmapExc;


#ifdef __cplusplus
}
#endif






#endif