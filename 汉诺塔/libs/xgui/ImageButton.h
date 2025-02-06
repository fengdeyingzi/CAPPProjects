#ifndef XGUI_IMAGEBUTTON_H
#define XGUI_IMAGEBUTTON_H
#include "graphics.h"
#include "ex_math.h"
#include "./bitmap.h"

typedef struct
{
 char*name;//控件名字
 int id;//按钮id
 int type;//按钮状态，按下1，释放0，隐藏-1
 int isshow;//是否显示 不显示时将不会执行点击事件
 int isdown;//是否按下
 int x;//按钮位置x
 int y;//按钮位置y
 int w;//按钮宽度
 int h;//按钮高度
 int bitmap;//bitmap句柄
 int blend_color;//混合颜色
 int img_mode;//图片显示模式 0正常 1自适应 2填充整个控件
 int32 timer;//回调定时器
 int draw_mode;//刷新模式
 
 void*onclick;//函数回调
 int click_mode;//回调模式 -1不回调 0仅一次 1多次
}ImageButton;

//创建图片控件
void*img_create(char*filename,int x,int y,int w,int h);
//获取id
int img_getid(ImageButton*img);
//绘制控件
void img_draw(ImageButton*img);
//判断控件是否显示
int img_isshow(ImageButton*img);
//显示控件
void img_show(ImageButton*img);
//隐藏控件
void img_hide(ImageButton*img);
//设置混合颜色
void img_setBlendColor(ImageButton*img,int color);
//设置图片显示模式 0正常 1自适应 2填充
void img_setmode(ImageButton*img,int mode);
//获取显示模式
int img_getmode(ImageButton*img);
//设置点击事件
void img_setonclick(ImageButton*img,void*click);
//控件event事件
int img_event(ImageButton*img,int type,int p1,int p2);
//释放图片控件
void img_free(ImageButton*img);


//创建图片控件
void*img_create(char*filename,int x,int y,int w,int h)
{
 ImageButton*img = malloc(sizeof(ImageButton));
 memset(img,0,sizeof(ImageButton));
 img->name = "ImageButton";
 if(strlen(filename)>9&&strncmp(filename,"assets://",9)==0)
 	img->bitmap = readBitmapFromAssets(filename+9);
 else
 	img->bitmap = readBitmap(filename);
 img->blend_color = 0xffffffff;
 img->x = x;
 img->y = y;
 img->w = w;
 img->h = h;
 img->isshow = 1;
 img->img_mode = 1;
 img->draw_mode = 1;
 img->click_mode = 0;
 img->timer = timercreate();
 return img;
}

//设置id
void img_setid(ImageButton*img,int id)
{
 img->id = id;
}

//设置混合颜色
void img_setBlendColor(ImageButton*img,int color)
{
 img->blend_color = color;
 img_draw(img);
 ref(img->x,img->y,img->w,img->h);
}

//获取id
int img_getid(ImageButton*img)
{
 return img->id;
}


//绘制控件
void img_draw(ImageButton*img)
{
 int bit = bitmap_blend(img->bitmap,img->blend_color);
 
 //0正常 1自适应 2填充
 int x,y;
 int w = bitmap_getw(bit);
 int h = bitmap_geth(bit);
 int dx,dy,dw,dh;
 if(img->isshow)
 {
  if(img->img_mode==0)
  {
   x = img->x+(img->w-w)/2;
   y = img->y+(img->h-h)/2;
   drawBitmap(bit,x,y);
   ref(img->x,img->y,img->w,img->h);
  }
  
  if(img->img_mode==1)
  {
   //判断宽高比
   if(w*1000/h>img->w*1000/img->h)
   {
    dw = img->h*w/h;
    dh = img->h;
    dx = img->x+(img->w-dw)/2;
    dy = img->y+(img->h-dh)/2;
    //以高度作为适配
    drawBitmapEx(bit,dx,dy,dw,dh,0,0,w,h);
   }
   else
   {
    //以宽度作为适配
    dw = img->w;
    dh = img->w*h/w;
    dx = img->x+(img->w-dw)/2;
    dy = img->y+(img->h-dh)/2;
    drawBitmapEx(bit,dx,dy,dw,dh,0,0,w,h);
   }
  }
  if(img->img_mode==2)
  {
   drawBitmapEx(bit,img->x,img->y,img->w,img->h,0,0,w,h);
  }
 }
 bitmapFree(bit);
}

//判断控件是否显示
int img_isshow(ImageButton*img)
{
 return img->isshow;
}

//显示控件
void img_show(ImageButton*img)
{
 img->isshow = 1;
 if(img->draw_mode==1)
 {
  img_draw(img);
  ref(img->x,img->y,img->w,img->h);
 }
}
//隐藏控件
void img_hide(ImageButton*img)
{
 img->isshow = 0;
}

//设置图片显示模式 0正常 1自适应 2填充
void img_setmode(ImageButton*img,int mode)
{
 img->img_mode = mode;
}

//获取显示模式
int img_getmode(ImageButton*img)
{
 return img->img_mode;
}

//设置点击事件
void img_setonclick(ImageButton*img,void*click)
{
 img->onclick = click;
}

//控件event事件
int img_event(ImageButton*img,int type,int p1,int p2)
{
 if(img->isshow)
 {
  if(type==MS_DOWN)
  {
   if(isPointCollRect(p1,p2,img->x,img->y,img->w,img->h))
   {
    img->isdown = 1;
    
    if(img->click_mode>0)
    	if(img->onclick!=NULL)
    	timerstart(img->timer,1,img->id,img->onclick,0);
    
    if(img->draw_mode==0)
    {
     img_draw(img);
     ref(img->x,img->y,img->w,img->h);
    }
   }
  }
  
  if(type==MS_UP)
  {
   if(img->isdown)
   {
    img->isdown = 0;
    
    if(img->click_mode>-1)
    	if(img->onclick!=NULL)
    	timerstart(img->timer,1,img->id,img->onclick,0);
    
    if(img->draw_mode==0)
    {
     img_draw(img);
     ref(img->x,img->y,img->w,img->h);
    }
   }
  }
 }
 return 0;
}

//释放图片控件
void img_free(ImageButton*img)
{
 if(img->bitmap)
 {
  bitmapFree(img->bitmap);
  img->bitmap = 0;
 }
 if(img->timer)
 {
  timerstop(img->timer);
  timerdel(img->timer);
  img->timer = 0;
 }
 free(img);
}

#endif
