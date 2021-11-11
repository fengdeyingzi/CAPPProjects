

#include "base.h"
#include "graphics.h"

/*
手机C编译模式头文件 graphics.h
最后修改于 2019-11-24
*/


#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

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
DRAWBITMAPEXB drawBitmapExb;
DRAWBITMAPEXC drawBitmapExc;




//add方法
int graphics_add(char* name,void* ptr)
{
 if(!strcmp(name, "createBitmap"))
 {
 createBitmap=(CREATEBITMAP)ptr;
 }
 else if(!strcmp(name, "readBitmap"))
 {
 readBitmap=(READBITMAP)ptr;
 }
 else if(!strcmp(name, "readBitmapFromAssets"))
 {
 readBitmapFromAssets=(READBITMAPFROMASSETS)ptr;
 }
 else if(!strcmp(name, "clipBitmap"))
 {
 clipBitmap=(CLIPBITMAP)ptr;
 }
 else if(!strcmp(name, "drawBitmap"))
 {
 drawBitmap=(DRAWBITMAP)ptr;
 }
 else if(!strcmp(name, "drawBitmapFlip"))
 {
 drawBitmapFlip=(DRAWBITMAPFLIP)ptr;
 }
 else if(!strcmp(name, "drawBitmapEx"))
 {
 drawBitmapEx=(DRAWBITMAPEX)ptr;
 }
 else if(!strcmp(name, "drawBitmapRotate"))
 {
 drawBitmapRotate=(DRAWBITMAPROTATE)ptr;
 }
 else if(!strcmp(name, "drawRect"))
 {
 drawRect=(DRAWRECT)ptr;
 }
 
 if(!strcmp(name, "drawCir"))
 {
 drawCir=(DRAWCIR)ptr;
 }
 else if(!strcmp(name, "drawBitmapOld"))
 {
 drawBitmapOld=(DRAWBITMAPOLD)ptr;
 }
 else if(!strcmp(name, "bitmapFree"))
 {
 bitmapFree=(BITMAPFREE)ptr;
 }
 else if(!strcmp(name, "bitmapGetInfo"))
 {
 bitmapGetInfo=(BITMAPGETINFO)ptr;
 }
 else if(!strcmp(name, "saveBitmap"))
 {
 saveBitmap=(SAVEBITMAP)ptr;
 }
 else if(!strcmp(name, "drawBitmapExb")){
  drawBitmapExb = (DRAWBITMAPEXB)ptr;
 }
 else if(!strcmp(name,"drawBitmapExc")){
  drawBitmapExc = (DRAWBITMAPEXC)ptr;
 }
 
 return 0;
}





#ifdef __cplusplus
}
#endif



