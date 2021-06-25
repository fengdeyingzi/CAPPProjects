/****************
*旋转的太极：作者:小蟀
*****************/
#include <base.h>
#include <graphics.h>
#include <ex_math.h>

typedef struct
{
  int x;
  int y;
}Point;


/***************
*点绕点旋转
*返回一个点
****************/
void* go(Point* p,Point* p1,Point* p2,int angle)
{
  toSpin(p1->x,p1->y,p2->x,p2->y,angle,&p->x,&p->y);
  return p;
}

/*************
*绘制圆的函数
*定时器函数
*************/
void draw(int data)
{
  cls(0,0,0);
  Point temp;
  
  /*空心外围圆*/
  drawCir(t1.x,t1.y,200,0xfffffffff);
  drawCir(t1.x,t1.y,199,0xff000000);
  
  /*旋转的半圆*/
  drawCir(p1.x,p1.y,100,0xffffffff);
  drawCir(p1.x,p1.y,99,0xff000000);
  go(&temp,&t1,&t2,angle+1);
  drawCir(temp.x,temp.y,100,0xff000000);

  drawCir(p2.x,p2.y,100,0xffffffff);
  drawCir(p2.x,p2.y,99,0xff000000);
  go(&temp,&t1,&t2,angle+181);
  drawCir(temp.x,temp.y,100,0xff000000);

  
  /*旋转的小圆*/
  drawCir(p1.x,p1.y,data,0xffffffff);
  drawCir(p2.x,p2.y,data,0xffffffff);
  
  ref(0,0,SCRW,SCRH);
}

/***************
*圆的运动函数
*定时器函数
****************/
void run(int data)
{
  if(angle>=360)
    angle=0;
  go(&p1,&t1,&t2,angle);
  go(&p2,&t1,&t2,angle+180);
  angle++;
}


/*旋转的圆心，以及旋转半径，旋转后的点*/
Point t1,t2,p1,p2;
int angle=0;

/*定时器句柄*/
int runT,drawT;

//入口函数，程序启动时开始执行
int init()
{
    t1.x=200;
    t1.y=200;
    t2.x=100;
    t2.y=100;
    
    /*初始化定时器*/
     runT=timercreate();
    drawT=timercreate();
    
    /*开启定时器*/
    timerstart(runT,10,0,"run",1);
    timerstart(drawT,10,20,"draw",1);
    
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
            timerdel(drawT);
            timerdel(runT);
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
 