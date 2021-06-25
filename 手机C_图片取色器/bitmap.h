
#ifndef _BITMAP_H_
#define _BITMAP_H_

/*
bitmap������
���ߣ����Ӱ��

*/

#include <base.h>
#include <graphics.h>
#define MAKERGBA(r,g,b,a) ((r<<24) | (g<<16) | (b<<8) | a)

#define MAKEABGR(a,b,g,r) ((a<<24) | (b<<16) | (g<<8) | r)



#define MAKEARGB(a,r,g,b) ((a<<24) | (r<<16) | (g<<8) | b)

#define MAKECOLOR(r,g,b) ((r<<16) | (g<<8) | b)

/*
typedef struct?
{
uint32 width; //���
uint32 height; //�߶�
uint32 stride;
int32 format; //��ʽ
uint32 flags; // 0 for now
void *ptr; //����
} BITMAPINFO;
*/

typedef struct
{
 uint8 r;
 uint8 g;
 uint8 b;
 uint8 a;
} _ARGB;


//��ȡbitmap��Ϣ
void bitmap_getInfo(int bitmap, BITMAPINFO *info)
{
 bitmapGetInfo(bitmap,info);
 
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


//��ȡbitmap��һ�����ص���ɫ ARGB�ṹ�� ����ֵΪԭͼƬ����ָ��
_ARGB* bitmap_getARGB(BITMAPINFO *info, int x,int y)
{
 _ARGB *ptr=info->ptr;
 if(x<0 || y<0 || x>=info->width || y>=info->height)
 return ptr;
 else
 return (ptr + info->width*y+x);
}


//����bitmap��һ�����ص���ɫ ARGB�ṹ��
int bitmap_setARGB(BITMAPINFO *info, int x,int y,_ARGB *argb)
{
 _ARGB *ptr=info->ptr;
 *(ptr + info->width*y+x)=*argb;
 return 0;
}

//��ȡbitmap���
int bitmap_getWidth(BITMAPINFO *info)
{
 return info->width;
}

//��ȡbitmap�߶�
int bitmap_getHeight(BITMAPINFO *info)
{
 return info->height;
}

//��bitmap��Ⱦ��ָ����ɫ��������Ⱦ���bitmap
int bitmap_drawColor(int bitmap,int color)
{
 int r=(color>>16) & 0xff;
 int g=(color>>8) & 0xff;
 int b=color & 0xff;
 int br,bg,bb,alpha;
 color = color<<8;
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 BITMAPINFO *temp_info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap, info);
 int temp_bitmap= createBitmap(info->width,info->height);
 bitmapGetInfo(temp_bitmap, temp_info);
 int ix,iy;
 for(iy=0;iy<info->height;iy++)
 {
  for(ix=0;ix<info->width;ix++)
  {
   int pix = bitmap_getPix(info,ix,iy);
   br=(pix) & 0xff;
   bg=(pix>>8) & 0xff;
   bb=(pix>>16) & 0xff;
   alpha=(pix>>24) & 0xff;
   //��ȡƽ��ֵ
   int ap= (br+bg+bb)/3;
   //�ϳ���Ⱦɫ
   br= r * ap/0xff;
   bg= g * ap/0xff;
   bb= b * ap/0xff;
   //����
   bitmap_setPix(temp_info,ix,iy,MAKEABGR(alpha,bb,bg,br));
  }
 }
 free(info);
 free(temp_info);
 return temp_bitmap;
}

//��bitmap�滻��ָ����ɫ�������滻͸���ȣ����ش�����bitmap
int bitmap_exColor(int bitmap,int color)
{
 int r=(color>>16) & 0xff;
 int g=(color>>8) & 0xff;
 int b=color & 0xff;
 printf("%d %d %d\n",r,g,b);
 int br,bg,bb,alpha;
 color = color<<8;
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 BITMAPINFO *temp_info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap, info);
 int temp_bitmap= createBitmap(info->width,info->height);
 bitmapGetInfo(temp_bitmap, temp_info);
 int ix,iy;
 for(iy=0;iy<info->height;iy++)
 {
  for(ix=0;ix<info->width;ix++)
  {
   _ARGB *pix = bitmap_getARGB(info,ix,iy);
   pix->r=(uint8)r;
   pix->g=(uint8)g;
   pix->b=(uint8)b;
   
   //����
   bitmap_setARGB(temp_info,ix,iy,pix);
  }
 }
 free(info);
 free(temp_info);
 return temp_bitmap;
}


//����һ��bitmap
int bitmap_copy(int bitmap)
{
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 BITMAPINFO *temp_info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap, info);
 //����һ����ͼƬ
 int temp_bitmap= createBitmap(info->width,info->height);
 bitmapGetInfo(temp_bitmap, temp_info);
 
 int len=info->width*info->height;
 memcpy(temp_info->ptr,info->ptr,len*4);
 free(info);
 free(temp_info);
 return temp_bitmap;
}


//����bitmap��ָ����С���ţ��������ź��bitmap
int bitmap_ex(int bitmap,int w,int h)
{
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 BITMAPINFO *temp_info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap, info);
 //����һ����ͼƬ
 int temp_bitmap= createBitmap(w,h);
 bitmapGetInfo(temp_bitmap, temp_info);
 //����ԭͼƬ����ȡ�㸳ֵ���µ�ͼƬ��
 int ix,iy;
 int *ptr=info->ptr;
 int *temp_ptr=temp_info->ptr;

 for(ix=0;ix<temp_info->width;ix++)
 for(iy=0;iy<temp_info->height;iy++)
 {
  //��ȡ��
  int point= ptr[(iy*info->height/temp_info->height)*info->width + (ix*info->width/temp_info->width)];
  temp_ptr[iy*temp_info->width + ix]=point;
  
 }
 
 
 free(info);
 free(temp_info);
 
 return temp_bitmap;
}

//�޸�bitmap����͸���ȣ������µ�bitmap
int bitmap_createAlpha(int bitmap,uint8 alpha)
{
 
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 BITMAPINFO *temp_info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap, info);
 //����һ����ͼƬ
 int temp_bitmap= bitmap_copy(bitmap);
 bitmapGetInfo(temp_bitmap, temp_info);

 int ix,iy;
 int i;
 _ARGB *argb=temp_info->ptr;
 for(i=0;i<info->width*info->height;i++)
 {
  argb->a= ((int)argb->a)*alpha/255;
  argb++;
 }
 
 free(info);
 free(temp_info);
 
 return temp_bitmap;
}


//͸�����ǻ����㷨����һ��bitmapͼƬ͸������Ϣ���Ƶ���һ��bitmapͼƬ��
int bitmap_drawAlphaOld(BITMAPINFO *bitmap,BITMAPINFO *buf,int x,int y)
{
 int ix=x,iy=y,x_max=x+buf->width,y_max=y+buf->height;
 
// if(ix<0)ix=0;
// if(iy<0)iy=0;
 if(x_max>bitmap->width)x_max=bitmap->width;
 if(y_max>bitmap->height)y_max=bitmap->height;
 //���Ƶ�
 _ARGB *bitmap_argb=bitmap->ptr;
 _ARGB *buf_argb=buf->ptr;
 for(int bx=0;bx<buf->width;bx++)
 for(int by=0;by<buf->height;by++)
 {
  //��ͼƬ��Χ��
  if((bx+ix < bitmap->width)&&(by+iy < bitmap->height))
  {
  _ARGB *di=bitmap_argb+(iy+by)*bitmap->width + (ix+bx);
  _ARGB *src=buf_argb+by*buf->width + bx;
  if(di->a<src->a)
  di->a=src->a;
  }
  
 }
 
 
 return 0;
}


//��bitmap�ϻ������Խ���ɫ
//������bitmapinfo�ṹ�壬������ʼ��ɫ������ĩβ��ɫ������Ƕ�



//��bitmap�ϻ��ƽǶȽ���
//������bitmapinfo��������ʼ��ɫ������ĩβλ�ã�������ʼ�Ƕ�


//��ɫ���
//���x y������ɫΪָ����ɫ


//��ɫ�滻
//��bitmap��x y������ɫ�滻��ָ����ɫ


//λ��
//��bitmapλ��ָ�����꣬����λ�ƺ��bitmap
//����������λ����������λ����


//ģ��
//��bitmapͼ���ģ��

//���񣬷��ؾ�����bitmap
//������������/������


//��תbitmap��������ת���bitmap
//��������ת90��/180��/270��


//Բ��
//Ϊbitmap���Բ��Ч��

//����


//����

//��͸����


//������
//������bitmapinfo��x���꣬���꣬��ȣ��߶�

//��Բ
//������bitmapinfo��x���꣬y���꣬����


//������
//������bitmapinfo��x���꣬y���꣬�뾶��


#endif

