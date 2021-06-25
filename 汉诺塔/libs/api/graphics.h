#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include "./base.h"
//结构体 枚举
enum
{
_JPG=0,
_PNG=1,
_BMP16=2
};

typedef struct
{
uint32 width; //宽度
uint32 height; //高度
uint32 stride;
int32 format; //格式
uint32 flags; // 0 for now
void *ptr; //缓存
} BITMAPINFO;

//定义函数指针
typedef int (*CREATEBITMAP)(int w,int h);
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
typedef int32 (*DRAWBITMAPOLD)(int di, int buf,  int32 x, int32 y, int32 w, int32 h, int32 sx, int32 sy);
typedef int32 (*BITMAPFREE)(int32 b);
typedef int (*BITMAPGETINFO)(int b,BITMAPINFO *info);
typedef int32 (*SAVEBITMAP)(int32 b,char* filename, int type, int load);


//定义指针变量
CREATEBITMAP createBitmap;
READBITMAP readBitmap;
READBITMAPFROMASSETS readBitmapFromAssets;
CLIPBITMAP clipBitmap;
DRAWBITMAP drawBitmap;
DRAWBITMAPFLIP drawBitmapFlip;
DRAWBITMAPEX drawBitmapEx;
DRAWBITMAPROTATE drawBitmapRotate;
DRAWRECT drawRect;

DRAWCIR drawCir;
DRAWBITMAPOLD drawBitmapOld;
BITMAPFREE bitmapFree;
BITMAPGETINFO bitmapGetInfo;

SAVEBITMAP saveBitmap;


//add方法
int graphics_add(char* name,void* ptr)
{
 if(!strcmp(name, "createBitmap"))
 {
 createBitmap=ptr;
 }
 else if(!strcmp(name, "readBitmap"))
 {
 readBitmap=ptr;
 }
 else if(!strcmp(name, "readBitmapFromAssets"))
 {
 readBitmapFromAssets=ptr;
 }
 else if(!strcmp(name, "clipBitmap"))
 {
 clipBitmap=ptr;
 }
 else if(!strcmp(name, "drawBitmap"))
 {
 drawBitmap=ptr;
 }
 else if(!strcmp(name, "drawBitmapFlip"))
 {
 drawBitmapFlip=ptr;
 }
 else if(!strcmp(name, "drawBitmapEx"))
 {
 drawBitmapEx=ptr;
 }
 else if(!strcmp(name, "drawBitmapRotate"))
 {
 drawBitmapRotate=ptr;
 }
 else if(!strcmp(name, "drawRect"))
 {
 drawRect=ptr;
 }
 
 if(!strcmp(name, "drawCir"))
 {
 drawCir=ptr;
 }
 else if(!strcmp(name, "drawBitmapOld"))
 {
 drawBitmapOld=ptr;
 }
 else if(!strcmp(name, "bitmapFree"))
 {
 bitmapFree=ptr;
 }
 else if(!strcmp(name, "bitmapGetInfo"))
 {
 bitmapGetInfo=ptr;
 }
 else if(!strcmp(name, "saveBitmap"))
 {
 saveBitmap=ptr;
 }
 
 return 0;
}









#endif