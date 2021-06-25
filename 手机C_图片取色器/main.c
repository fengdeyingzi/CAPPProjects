//加载系统头文件base.h
#include <base.h>
#include <graphics.h>
#include <android.h>
#include "bitmap.h"

/*
荧光画板
作者：风的影子
运行有些卡

*/




int exitApp();
void draw();
void drawColor(int bitmap,BITMAPINFO *bitmap_info,int x,int y);


 void helloworld()
{
    //用指定颜色清除屏幕
    cls(240,240,240);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}

int bitmapx;
int paint;
BITMAPINFO *bitmap_info,*paint_info;
int gbx,gby;
int setColor(int color);
//入口函数，程序启动时开始执行
int init()
{
 
    //调用函数helloworld
    helloworld();
    setContextView("main.xml");
     
    bitmapx=readBitmapFromAssets("bird0_2.png");
    
    bitmap_info=malloc(sizeof(BITMAPINFO));
    
    
     
    
    
        bitmap_getInfo(bitmapx,bitmap_info);
    
    
    
    
    setTitle("取色器\0");
    setscrsize(260,260*SCRH/SCRW);
     drawColor(bitmapx,bitmap_info,0,0);
    toast("风的影子 作品",0);
    return 0;
}

//显示画面
void draw()
{
  cls(200,200,200);
  drawBitmap(bitmapx,0,0);
  //drawBitmap(paint,0,0);
 // drect(0,0,paint_info->width,paint_info->height,0,0,0);
  ref(0,0,SCRW,SCRH);
}

//显示取色器
void drawColor(int bitmap,BITMAPINFO *bitmap_info,int x,int y)
{
 _ARGB *argb=bitmap_getARGB(bitmap_info,x,y);
 char text[300];
 sprintf(text,"0x%02x%02x%02x%02x r=%d g=%d b=%d",argb->a,argb->r,argb->g,argb->b,argb->r,argb->g,argb->b);
 int w,h;
 textwh(text,0,1,&w,&h);
 cls(40,40,40);
 
 drawBitmap(bitmap,0,0);
 dline(x,0,x,SCRH,20,240,20);
 dline(0,y,SCRW,y,20,240,20);
 dtext(text,0,SCRH-h-SCRH/10,0,255,0,0,1);
 ref(0,0,SCRW,SCRH);
}

//设置画笔颜色
int setColor(int color)
{
 int buf=bitmap_exColor(paint,color);
 int bitmap_buf=bitmap_exColor(bitmapx,color);
 bitmapFree(paint);
 bitmapFree(bitmapx);
 paint = buf;
 bitmapx=bitmap_buf;
  
  bitmap_getInfo(buf,paint_info);
  bitmap_getInfo(bitmap_buf,bitmap_info);
  for(int ix=0;ix<bitmap_info->width;ix++)
  for(int iy=0;iy<bitmap_info->height;iy++)
  {
   _ARGB *argb=bitmap_getARGB(bitmap_info,ix,iy);
  
  }
  
  
 return buf;
}


int bitmap_drawPaint(BITMAPINFO *bitmap_info,BITMAPINFO *paint_info,int x1,int y1,int x2,int y2)
{
 	int x, y, dx, dy, c1, c2, err, swap = 0;
 int left = paint_info->width/2;
 int top = paint_info->height/2;
	/*   
	if (x1 < 0 || x1 >= MR_SCREEN_W || x2 < 0 || x2 >= MR_SCREEN_W ||
	y1 < 0 || y1 >= MR_SCREEN_H || y2 < 0 || y2 >= MR_SCREEN_H)
	return;
	*/

	dx = x2 - x1; dy = y2 - y1;
	if (((dx < 0) ? -dx : dx) < ((dy < 0) ? -dy : dy))
	{
		swap = 1;                       /* take the long way        */
		x = x1; x1 = y1; y1 = x;
		x = x2; x2 = y2; y2 = x;
	}
	if (x1 > x2)
	{
		x = x1; x1 = x2; x2 = x;        /* always move to the right */
		y = y1; y1 = y2; y2 = y;
	}

	dx = x2 - x1; dy = y2 - y1;
	c1 = dy * 2; dy = 1;
	if (c1 < 0)
	{
		c1 = -c1;
		dy = -1;
	}
	err = c1 - dx; c2 = err - dx;
	x = x1; y = y1;
	while (x <= x2)
	{
		bitmap_drawAlphaOld(bitmap_info,paint_info,(swap?y:x)-left,(swap?x:y)-top);
  //drawBitmap(paint,(swap?y:x)-left,(swap?x:y)-top);
		x++;
		if (err < 0)
			err += c1;
		else
		{
			y += dy;
			err += c2;
		}
	}
//ref(0,0,SCRW,SCRH);
  draw();
 return 0;
}

int hx,hy;
//event函数，接收消息事件
int event(int type, int p1, int p2)
{
 char *path;
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            #ifndef JNI
            exitApp();
            #endif
            exit();
            break;
        case _MENU:
            break;
        }
    }

  if(type==MS_DOWN)
  {
   hx=p1;
   hy=p2;
   drawColor(bitmapx,bitmap_info,p1,p2);
  }
  

   else if(type== MS_MOVE)
   {
    drawColor(bitmapx,bitmap_info,p1,p2);
    hx=p1;
    hy=p2;
    
   }
   else if(type==VIEW_UP)
   {
    if(p1==1)
    {
     fv_init(0);
     fv_settype(".jpg|.JPG|.PNG|.png|.bmp|.BMP|.GIF|.gif",TRUE);
     fv_begin("");
     
    }
    
   }
   
  else if(type==10)
  {
   if(p1==DLG_OK)
   {
   path = (char*)fv_getpath();
   printf("%s\n",path);
   int temp=readBitmap(path);
   fv_end();
   if(temp!=0)
   {
    bitmapFree(bitmapx);
    
    bitmapx=temp;
    bitmap_getInfo(bitmapx,bitmap_info);
    if(bitmap_info->width <200 && bitmap_info->width<200)
    setscrsize(240,240*SCRH/SCRW);
    else if(bitmap_info->width>bitmap_info->height)
    setscrsize(bitmap_info->width,bitmap_info->width * SCRH/SCRW);
    else 
    setscrsize(bitmap_info->height*SCRW/SCRH,bitmap_info->height);
    drawColor(bitmapx,bitmap_info,p1,p2);
   }
   }
  }
  

    return 0;
}

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause()
{
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
    return 0;
}
 
 int exitApp()
 {
  free(bitmap_info);
  
  bitmapFree(bitmapx);
  
  return 0;
 }