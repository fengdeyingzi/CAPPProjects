/**********************
**绘制五子棋盘**作者小蟀**
***********************/
#include <base.h>

/*定义棋盘宽度*/
#define nX 12
#define nY 17
#define W  SCRW/nX
#define H  SCRH/nY

typedef struct
{
  int x;
  int y;
  int w;
  int h;
}Line;

Line mapX[nX];
Line mapY[nY];

void initMap()
{
  int i;
  /*线数据*/
  for(i=0;i<nY;i++)
  {
    mapY[i].x=W/2;
    mapY[i].y=i*H+H/2;
    mapY[i].w=SCRW-W;
    mapY[i].h=2;
  }
  
  for(i=0;i<nX;i++)
  {
    mapX[i].x=i*W+W/2;
    mapX[i].y=H/2;
    mapX[i].w=2;
    mapX[i].h=SCRH-H;
  }
  
}

void drawMap()
{
  cls(255,255,255);
  int r=0,g=0,b=0,i;
  
  for(i=0;i<nY;i++)
  {
    /*绘制横线*/
    drect(mapY[i].x,mapY[i].y,mapY[i].w,mapY[i].h,r,g,b);
  }
  
  for(i=0;i<nX;i++)
  {
    /*绘制竖线*/
    drect(mapX[i].x,mapX[i].y,mapX[i].w,mapX[i].h,r,g,b);
  }
  
  ref(0,0,SCRW,SCRH);
}

int init()
{
  /*设置屏幕分辨率*/
  setscrsize(600,600*SCRH/SCRW);
  
  initMap();
  drawMap();
  return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exit();
            break;
        case _MENU:
            break;
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
 