//加载系统头文件base.h
#include <base.h>
#include <graphics.h>

//球结构体
typedef struct
{
 //坐标
 int x;
 int y;
 
 //速度
 int dx;
 int dy;
 
 //半径
 int r;
 
 //颜色
 int32 color;
}Ball;

//球运动定时器
int32 rtimer;

//球数组
Ball b[30];

//单个球运动
void ballRun(Ball *ball)
{
 //向下
 ball->y+=ball->dy;
 ball->x+=ball->dx;
 
 //判断
 if(ball->y>=SCRH)
 {
   ball->y=0;
   
   //加速
   if(ball->dy<50)
      ball->dy+=2;
   else
      ball->dy=rand()%10+5;
   
   //恢复
   ball->color=0xff00ffff;
 }
 
 if(ball->x<=0)
    ball->dx=-ball->dx;  
 
 if(ball->x>=SCRW)
   ball->dx=-ball->dx; 
 
}

//球运动定时器函数
void ballRunTimer(int data)
{
  printf("ball..\r\n");
 //球数组运动
 int i;
 for(i=0;i<sizeof(b)/sizeof(Ball);i++)
   ballRun(&b[i]);
 
 //判断飞机
 int n=plan.x/(SCRW/(sizeof(b)/sizeof(Ball)));
 
 if(plan.y<=b[n].y)
 if(plan.y>=b[n].y-plan.h)
 {
   b[n].color=0xffff0000;
   b[n].dy=0;
 }
 
 //左边一个球
 if(n>0)
 if(plan.y<=b[n-1].y)
 if(plan.y>=b[n-1].y-plan.h)
 {
   b[n-1].color=0xffff0000;
   b[n-1].dy=0;
 }
 
 //右边一个球
 if(n<sizeof(b)/sizeof(Ball)-1)
 if(plan.y<=b[n+1].y)
 if(plan.y>=b[n+1].y-plan.h)
 {
   b[n+1].color=0xffff0000;
   b[n+1].dy=0;
 } 
    
}

void drawBall(Ball *ball)
{
 drawCir(ball->x,ball->y,ball->r,ball->color);
}

//开始运行
void runStart()
{
 rtimer=timercreate();
 timerstart (rtimer,30,10,ballRunTimer,1);  
}

//结束运行
void ballRunEnd()
{
 timerdel(rtimer);
}

int initBall()
{
    printf("initBall..\r\n");
    sand(getuptime());
    printf("initBall.. uptime\r\n");
    int i;
    for(i=0;i<sizeof(b)/sizeof(Ball);i++)
    {
      b[i].x=i*SCRW/(sizeof(b)/sizeof(Ball))+SCRW/(2*(sizeof(b)/sizeof(Ball)));
      b[i].y=0;
  
      b[i].dx=0;
      b[i].dy=rand()%10+10;
         
      b[i].r=20;
      
      b[i].color=0xff00ffff;
    } 
    runStart();
    return 0;
}




