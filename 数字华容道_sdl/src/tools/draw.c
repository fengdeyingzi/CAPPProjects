
#include "../api/base.h"
#include "../api/graphics.h"
#include "./draw.h"

//绘制圆环
void drawCirCir(int x,int y,int r1,int r2,int color,int ii,int radi)
{
 int dx,dy;
 //计算圆半径
 int r = (r2-r1)/2;
 //循环绘制
 int i;
 for( i = 0;i<ii;i++)
 {
  dx = x+r;
  dy = y;
  toSpin(x,y,r1+r,r1+r,
   i*radi/ii,&dx,&dy);
  drawCir(dx,dy,r,color);
 }
}


/**************
*用圆绘制粗斜线
*起点坐标：x,y
*倾斜角度：radi
*线的长度：size
*圆的大小：r
*线的颜色：color
***************/
int drawCirLine(int x,int y,int radi,int size,int r,int color)
{
 int cx,cy;
 int i;
 //循环取值
 for( i = 0;i<size;i++)
 {
  cx = x;
  cy = y-i;
  //旋转
  toSpin(x,y,i,i,radi,&cx,&cy);
  //绘制
  drawCir(cx,cy,r,color);
 }
 return 0;
}


/**************
*用圆绘制粗斜线
*起点坐标：x1,y1
*终点坐标：x2,y2
*圆的大小：r
*线的颜色：color
***************/
int drawCirLine2(int x1,int y1,int x2,int y2,int r,int color)
{
 //取长度值
 int size = 
 getLineSize(x1,y1,x2,y2);
 //取弧度值
 int radi = 
 getRadiam(x1,y1,x2,y2);
 //循环取值
 drawCirLine(x1,y1,
  radi,size,r,color);
 return 0;
}

//获取bitmap上一个像素的颜色 abgr格式
int bitmap_getPix(_BITMAPINFO *info, int x,int y)
{
 int *ptr=info->ptr;
 return *(ptr + info->width*y+x);
}


//设置bitmap上一个像素的颜色 abgr格式
int bitmap_setPix(_BITMAPINFO *info, int x,int y,int color)
{
 int *ptr=info->ptr;
 *(ptr + info->width*y+x)=color;
 return 0;
}

int bitmap_getWidth(int32 bit)
{
 _BITMAPINFO info;
 bitmapGetInfo(bit,&info);
 return info.width;
}

int bitmap_getHeight(int32 bit)
{
 _BITMAPINFO info;
 bitmapGetInfo(bit,&info);
 return info.height;
}



//翻转bitmap，返回翻转后的bitmap
// int32 bitmap_turn(int bitmap,int left, int up)
// {
//  int ix,iy;
//  _BITMAPINFO*info = malloc(sizeof(_BITMAPINFO));
//  bitmapGetInfo(bitmap,info);
 
//  //左右翻转 上下翻转
//  int temp_bitmap = createBitmap(info->width,info->height);
//  _BITMAPINFO*temp_info = malloc(sizeof(_BITMAPINFO));
//  bitmapGetInfo(temp_bitmap,temp_info);
//  for(iy = 0;iy<info->height;iy++)
//  {
//   for(ix = 0;ix<info->width;ix++)
//   {
//    int pix = bitmap_getPix(info,ix,iy);
//    bitmap_setPix(temp_info,(left==TRUE)?(info->width-ix):ix,(up==TRUE)?(info->height-iy):iy, pix);
//   }
//  }
 
//  free(info);
//  free(temp_info);
//  return temp_bitmap;
// }

