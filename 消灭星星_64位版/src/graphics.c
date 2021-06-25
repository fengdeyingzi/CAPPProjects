

#include "base.h"
#include "graphics.h"

/*
�ֻ�C����ģʽͷ�ļ� graphics.h
����޸��� 2019-11-24
*/


#ifdef __cplusplus
#include <iostream>
extern "C"{ //��Ϊcpp�ļ�Ĭ�϶����˸ú�),�����C���Է�ʽ���б���
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

//����ָ�����
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




//add����
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



