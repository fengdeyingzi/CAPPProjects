#ifndef _BITMAP_H_
#define _BITMAP_H_
#include <graphics.h>

//��ȡbitmap���
int bitmap_getw(int bitmap)
{
 int w=0;
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap,info);
 w=info->width;
 return w;
}

//��ȡbitmap�߶�
int bitmap_geth(int bitmap)
{
 int h=0;
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap,info);
 h=info->height;
 return h;
}



#endif
