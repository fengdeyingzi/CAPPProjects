/*******************
*控制小球*作者：小蟀
********************/

#include <base.h>
#include <graphics.h>

/**********
自定义头文件*
***********/
#include "ball.h"
#include "event.h"

Ball ball;

void start()
{
  /*初始化小球数据*/
  ball.x=100;
  ball.y=100;
  ball.dx=10;
  ball.dy=10;
  ball.r=30;
  ball.color=0xff556688;
  draw();
}

int init()
{
  start();
  return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
  /****************************
  *触屏按下，滑动，释放均会触发小球*
  *****************************/
  if(MS_DOWN == type||MS_MOVE == type||MS_UP == type)
  {
    ballEvent(type,p1,p2);
  }
  
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
 