/*********************
*�˶���С��*���ߣ�С�
**********************/

/*����������*/
#include <base.h>

/*��ͼ������*���������ڻ���С��*/
#include <graphics.h>


/*С��ṹ��*���ڴ���С�����Ϣ*/
typedef struct
{
  int x;
  int y;
  int dx;  //���ڿ���С������ƶ�
  int dy;  //���ڿ���С�������ƶ�
  int r;
  int32 color;
}Ball;


/*С��ṹ�������������*/
Ball ball;

/*��ͼ����*���������ڻ���С��ˢ����Ļ*/
void draw(int data)
{
  /*********************************
  *drawCir�������ĸ�����* x,y,r,color*
  ****x,y����Բ��Բ�ģ�r����Բ�İ뾶****
  ********color�������Բ����ɫ*******
  *********************************/
  /*ָ����ɫ����*/
  cls(0,0,0);
  
  drawCir(ball.x,ball.y,ball.r,ball.color);
  
  /*ˢ��һ����������* SCRW,SCRH�ֱ������Ļ����*/
  ref(0,0,SCRW,SCRH);
}

void run(int data)
{
  /*�˶�������*/
  ball.x+=ball.dx;
  ball.y+=ball.dy;
  
  /*************
  *���߽���զ��?**
  **************/
  
  /*��*/
  if(ball.x<=ball.r)
  {
     ball.x=ball.r;
     /*������*/
     ball.dx=-ball.dx;
  }
  
  /*��*/
  if(ball.x>=SCRW-ball.r)
  {
     ball.x=SCRW-ball.r;
     /*������*/
     ball.dx=-ball.dx;
  }
  
  /*��*/
  if(ball.y<=ball.r)
  {
     ball.y=ball.r;
     /*������*/
     ball.dy=-ball.dy;
  }
  
  /*��*/
  if(ball.y>=SCRH-ball.r)
  {
     ball.y=SCRH-ball.r;
     /*������*/
     ball.dy=-ball.dy;
  }
  
}


/*����ȫ�ֶ�ʱ�����ڶ�ʱ����С���ˢ����Ļ*/
/*����ȫ�ֶ�ʱ�����ڿ���С����˶�*/
int drawT , runT;

int init()
{
  /*��ʼ��С������*/
  ball.x=100;
  ball.y=100;
  ball.dx=10;
  ball.dy=10;
  ball.r=30;
  ball.color=0xff556688;
  
  /*��ʼ����ʱ��*/
  drawT=timercreate();
   runT=timercreate();
  
  /*************************************
  *������ʱ��*��5������ t,time,data,f,loop*
  **��ʱ�������ʱ�䣬���ݣ����������Ƿ�ѭ��**
  **************************************/
  timerstart(runT,30,0,"run",1);
  timerstart(drawT,30,0,"draw",1);

  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            /*�˳�ǰ���������ٶ�ʱ��*/
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
 