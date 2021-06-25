
#ifndef _BITMAP_H_
#define _BITMAP_H_

/*
bitmap处理函数
作者：风的影子

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
uint32 width; //宽度
uint32 height; //高度
uint32 stride;
int32 format; //格式
uint32 flags; // 0 for now
void *ptr; //缓存
} BITMAPINFO;
*/

typedef struct
{
 uint8 r;
 uint8 g;
 uint8 b;
 uint8 a;
} _ARGB;


//获取bitmap信息
void bitmap_getInfo(int bitmap, BITMAPINFO *info)
{
 bitmapGetInfo(bitmap,info);
 
}

//获取bitmap上一个像素的颜色 abgr格式
int bitmap_getPix(BITMAPINFO *info, int x,int y)
{
 int *ptr=info->ptr;
 return *(ptr + info->width*y+x);
}


//设置bitmap上一个像素的颜色 abgr格式
int bitmap_setPix(BITMAPINFO *info, int x,int y,int color)
{
 int *ptr=info->ptr;
 *(ptr + info->width*y+x)=color;
 return 0;
}


//获取bitmap上一个像素的颜色 ARGB结构体 返回值为原图片缓存指针
_ARGB* bitmap_getARGB(BITMAPINFO *info, int x,int y)
{
 _ARGB *ptr=info->ptr;
 if(x<0 || y<0 || x>=info->width || y>=info->height)
 return ptr;
 else
 return (ptr + info->width*y+x);
}


//设置bitmap上一个像素的颜色 ARGB结构体
int bitmap_setARGB(BITMAPINFO *info, int x,int y,_ARGB *argb)
{
 _ARGB *ptr=info->ptr;
 *(ptr + info->width*y+x)=*argb;
 return 0;
}

//获取bitmap宽度
int bitmap_getWidth(BITMAPINFO *info)
{
 return info->width;
}

//获取bitmap高度
int bitmap_getHeight(BITMAPINFO *info)
{
 return info->height;
}

//将bitmap渲染成指定颜色，返回渲染后的bitmap
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
   //获取平均值
   int ap= (br+bg+bb)/3;
   //合成渲染色
   br= r * ap/0xff;
   bg= g * ap/0xff;
   bb= b * ap/0xff;
   //生成
   bitmap_setPix(temp_info,ix,iy,MAKEABGR(alpha,bb,bg,br));
  }
 }
 free(info);
 free(temp_info);
 return temp_bitmap;
}

//将bitmap替换成指定颜色，但不替换透明度，返回处理后的bitmap
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
   
   //生成
   bitmap_setARGB(temp_info,ix,iy,pix);
  }
 }
 free(info);
 free(temp_info);
 return temp_bitmap;
}


//复制一张bitmap
int bitmap_copy(int bitmap)
{
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 BITMAPINFO *temp_info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap, info);
 //创建一张新图片
 int temp_bitmap= createBitmap(info->width,info->height);
 bitmapGetInfo(temp_bitmap, temp_info);
 
 int len=info->width*info->height;
 memcpy(temp_info->ptr,info->ptr,len*4);
 free(info);
 free(temp_info);
 return temp_bitmap;
}


//将比bitmap按指定大小缩放，返回缩放后的bitmap
int bitmap_ex(int bitmap,int w,int h)
{
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 BITMAPINFO *temp_info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap, info);
 //创建一张新图片
 int temp_bitmap= createBitmap(w,h);
 bitmapGetInfo(temp_bitmap, temp_info);
 //遍历原图片，获取点赋值到新的图片上
 int ix,iy;
 int *ptr=info->ptr;
 int *temp_ptr=temp_info->ptr;

 for(ix=0;ix<temp_info->width;ix++)
 for(iy=0;iy<temp_info->height;iy++)
 {
  //获取点
  int point= ptr[(iy*info->height/temp_info->height)*info->width + (ix*info->width/temp_info->width)];
  temp_ptr[iy*temp_info->width + ix]=point;
  
 }
 
 
 free(info);
 free(temp_info);
 
 return temp_bitmap;
}

//修改bitmap整体透明度，生成新的bitmap
int bitmap_createAlpha(int bitmap,uint8 alpha)
{
 
 BITMAPINFO *info= malloc(sizeof(BITMAPINFO));
 BITMAPINFO *temp_info= malloc(sizeof(BITMAPINFO));
 bitmapGetInfo(bitmap, info);
 //创建一张新图片
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


//透明覆盖绘制算法，将一张bitmap图片透明度信息绘制到另一张bitmap图片上
int bitmap_drawAlphaOld(BITMAPINFO *bitmap,BITMAPINFO *buf,int x,int y)
{
 int ix=x,iy=y,x_max=x+buf->width,y_max=y+buf->height;
 
// if(ix<0)ix=0;
// if(iy<0)iy=0;
 if(x_max>bitmap->width)x_max=bitmap->width;
 if(y_max>bitmap->height)y_max=bitmap->height;
 //绘制点
 _ARGB *bitmap_argb=bitmap->ptr;
 _ARGB *buf_argb=buf->ptr;
 for(int bx=0;bx<buf->width;bx++)
 for(int by=0;by<buf->height;by++)
 {
  //在图片范围内
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


//在bitmap上绘制线性渐变色
//参数：bitmapinfo结构体，渐变起始颜色，渐变末尾颜色，渐变角度



//在bitmap上绘制角度渐变
//参数：bitmapinfo，渐变起始颜色，渐变末尾位置，渐变起始角度


//颜色填充
//填充x y处的颜色为指定颜色


//颜色替换
//将bitmap上x y处的颜色替换成指定颜色


//位移
//将bitmap位移指定坐标，返回位移后的bitmap
//参数：横向位移量，纵向位移量


//模糊
//将bitmap图像变模糊

//镜像，返回镜像后的bitmap
//参数：横向镜像/纵向镜像


//旋转bitmap，返回旋转后的bitmap
//参数：旋转90度/180度/270度


//圆角
//为bitmap添加圆角效果

//画点


//画线

//画透明度


//画矩形
//参数，bitmapinfo，x坐标，坐标，宽度，高度

//画圆
//参数：bitmapinfo，x坐标，y坐标，长度


//画扇形
//参数：bitmapinfo，x坐标，y坐标，半径，


#endif

