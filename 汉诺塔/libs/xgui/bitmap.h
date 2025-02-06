#ifndef _BITMAP_H_
#define _BITMAP_H_
#include "graphics.h"

#define MAKERGBA(r,g,b,a)((r<<24)|(g<<16)|(b<<8)|a)
#define MAKEABGR(a,b,g,r)((a<<24)|(b<<16)|(g<<8)|r)
#define MAKEARGB(a,r,g,b)((a<<24)|(r<<16)|(g<<8)|b)
#define MAKECOLOR(r,g,b)((r<<16)|(g<<8)|b)

//��ȡbitmap���
int bitmap_getw(int bitmap)
{
 int w = 0;
 BITMAPINFO*info = malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap,info);
 w = info->width;
 free(info);
 return w;
}

//��ȡbitmap�߶�
int bitmap_geth(int bitmap)
{
 int h = 0;
 BITMAPINFO*info = malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap,info);
 h = info->height;
 free(info);
 return h;
}

//��ȡbitmap��һ�����ص���ɫ abgr��ʽ
int bitmap_getPix(BITMAPINFO *info, int x,int y)
{
 int *ptr=info->ptr;
 return *(ptr + info->width*y+x);
}


//����bitmap��һ�����ص���ɫ abgr��ʽ
int bitmap_setPix(BITMAPINFO *info, int x,int y,int color)
{
 int *ptr=info->ptr;
 *(ptr + info->width*y+x)=color;
 return 0;
}


//�����ɫargb 0xff ff ff ff
//��bitmap��Ⱦ��ָ����ɫ��������Ⱦ���bitmap
int bitmap_blend(int bitmap,int color)
{
 int r = (color>>16)&0xff;
 int g = (color>>8)&0xff;
 int b = color&0xff;
 int br,bg,bb,alpha;
 color = color<<8;
 BITMAPINFO*info = malloc(sizeof(BITMAPINFO));
 BITMAPINFO*temp_info = malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap,info);
 int temp_bitmap = createBitmap(info->width,info->height);
 bitmapGetInfo(temp_bitmap,temp_info);
 int ix,iy;
 for(iy = 0;iy<info->height;iy++)
 {
  for(ix = 0;ix<info->width;ix++)
  {
   int pix = bitmap_getPix(info,ix,iy);
   br = (pix)&0xff;
   bg = (pix>>8)&0xff;
   bb = (pix>>16)&0xff;
   alpha = (pix>>24)&0xff;
   //��ȡƽ��ֵ
   int ap = (br+bg+bb)/3;
   //�ϳ���Ⱦɫ
   br = r*ap/0xff;
   bg = g*ap/0xff;
   bb = b*ap/0xff;
   //����
   bitmap_setPix(temp_info,ix,iy,MAKEABGR(alpha,bb,bg,br));
  }
 }
 free(info);
 free(temp_info);
 return temp_bitmap;
}




#endif
