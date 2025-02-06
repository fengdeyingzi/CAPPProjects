//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <graphics.h>

//��ṹ��
typedef struct
{
 //����
 int x;
 int y;
 
 //�ٶ�
 int dx;
 int dy;
 
 //�뾶
 int r;
 
 //��ɫ
 int32 color;
}Ball;

//���˶���ʱ��
int32 rtimer;

//������
Ball b[30];

//�������˶�
void ballRun(Ball *ball)
{
 //����
 ball->y+=ball->dy;
 ball->x+=ball->dx;
 
 //�ж�
 if(ball->y>=SCRH)
 {
   ball->y=0;
   
   //����
   if(ball->dy<50)
      ball->dy+=2;
   else
      ball->dy=rand()%10+5;
   
   //�ָ�
   ball->color=0xff00ffff;
 }
 
 if(ball->x<=0)
    ball->dx=-ball->dx;  
 
 if(ball->x>=SCRW)
   ball->dx=-ball->dx; 
 
}

//���˶���ʱ������
void ballRunTimer(int data)
{
  printf("ball..\r\n");
 //�������˶�
 int i;
 for(i=0;i<sizeof(b)/sizeof(Ball);i++)
   ballRun(&b[i]);
 
 //�жϷɻ�
 int n=plan.x/(SCRW/(sizeof(b)/sizeof(Ball)));
 
 if(plan.y<=b[n].y)
 if(plan.y>=b[n].y-plan.h)
 {
   b[n].color=0xffff0000;
   b[n].dy=0;
 }
 
 //���һ����
 if(n>0)
 if(plan.y<=b[n-1].y)
 if(plan.y>=b[n-1].y-plan.h)
 {
   b[n-1].color=0xffff0000;
   b[n-1].dy=0;
 }
 
 //�ұ�һ����
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

//��ʼ����
void runStart()
{
 rtimer=timercreate();
 timerstart (rtimer,30,10,ballRunTimer,1);  
}

//��������
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




