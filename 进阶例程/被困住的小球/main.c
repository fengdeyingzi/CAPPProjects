/*********************
*运动的小球*作者：小蟀
**********************/

/*基础函数库*/
#include <base.h>

/*绘图函数库*本例中用于绘制小球*/
#include <graphics.h>


/*小球结构体*用于储存小球的信息*/
typedef struct
{
  int x;
  int y;
  int dx;  //用于控制小球横向移动
  int dy;  //用于控制小球纵向移动
  int r;
  int32 color;
}Ball;


/*小球结构体对象（真正的球）*/
Ball ball;

/*绘图函数*本例中用于绘制小球并刷新屏幕*/
void draw(int data)
{
  /*********************************
  *drawCir函数共四个参数* x,y,r,color*
  ****x,y代表圆的圆心，r代表圆的半径****
  ********color代表绘制圆的颜色*******
  *********************************/
  /*指定颜色清屏*/
  cls(0,0,0);
  
  drawCir(ball.x,ball.y,ball.r,ball.color);
  
  /*刷新一个矩形区域* SCRW,SCRH分别代表屏幕宽，高*/
  ref(0,0,SCRW,SCRH);
}

void run(int data)
{
  /*运动起来啦*/
  ball.x+=ball.dx;
  ball.y+=ball.dy;
  
  /*************
  *到边界了咋办?**
  **************/
  
  /*左*/
  if(ball.x<=ball.r)
  {
     ball.x=ball.r;
     /*换方向咯*/
     ball.dx=-ball.dx;
  }
  
  /*右*/
  if(ball.x>=SCRW-ball.r)
  {
     ball.x=SCRW-ball.r;
     /*换方向咯*/
     ball.dx=-ball.dx;
  }
  
  /*上*/
  if(ball.y<=ball.r)
  {
     ball.y=ball.r;
     /*换方向咯*/
     ball.dy=-ball.dy;
  }
  
  /*下*/
  if(ball.y>=SCRH-ball.r)
  {
     ball.y=SCRH-ball.r;
     /*换方向咯*/
     ball.dy=-ball.dy;
  }
  
}


/*定义全局定时器用于定时绘制小球和刷新屏幕*/
/*定义全局定时器用于控制小球的运动*/
int drawT , runT;

int init()
{
  /*初始化小球数据*/
  ball.x=100;
  ball.y=100;
  ball.dx=10;
  ball.dy=10;
  ball.r=30;
  ball.color=0xff556688;
  
  /*初始化定时器*/
  drawT=timercreate();
   runT=timercreate();
  
  /*************************************
  *启动定时器*共5个参数 t,time,data,f,loop*
  **定时器句柄，时间，数据，函数名，是否循环**
  **************************************/
  timerstart(runT,30,0,"run",1);
  timerstart(drawT,30,0,"draw",1);

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
            /*退出前别忘了销毁定时器*/
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
 