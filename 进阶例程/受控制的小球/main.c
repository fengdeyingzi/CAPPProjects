/*******************
*����С��*���ߣ�С�
********************/

#include <base.h>
#include <graphics.h>

/**********
�Զ���ͷ�ļ�*
***********/
#include "ball.h"
#include "event.h"

Ball ball;

void start()
{
  /*��ʼ��С������*/
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



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
  /****************************
  *�������£��������ͷž��ᴥ��С��*
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

//Ӧ����ͣ������������̨���Ϊ���ɼ�ʱ����ô˺���
int pause()
{
    return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
int resume()
{
    return 0;
}
 