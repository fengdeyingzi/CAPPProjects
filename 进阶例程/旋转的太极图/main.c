/****************
*��ת��̫��������:С�
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
*���Ƶ���ת
*����һ����
****************/
void* go(Point* p,Point* p1,Point* p2,int angle)
{
  toSpin(p1->x,p1->y,p2->x,p2->y,angle,&p->x,&p->y);
  return p;
}

/*************
*����Բ�ĺ���
*��ʱ������
*************/
void draw(int data)
{
  cls(0,0,0);
  Point temp;
  
  /*������ΧԲ*/
  drawCir(t1.x,t1.y,200,0xfffffffff);
  drawCir(t1.x,t1.y,199,0xff000000);
  
  /*��ת�İ�Բ*/
  drawCir(p1.x,p1.y,100,0xffffffff);
  drawCir(p1.x,p1.y,99,0xff000000);
  go(&temp,&t1,&t2,angle+1);
  drawCir(temp.x,temp.y,100,0xff000000);

  drawCir(p2.x,p2.y,100,0xffffffff);
  drawCir(p2.x,p2.y,99,0xff000000);
  go(&temp,&t1,&t2,angle+181);
  drawCir(temp.x,temp.y,100,0xff000000);

  
  /*��ת��СԲ*/
  drawCir(p1.x,p1.y,data,0xffffffff);
  drawCir(p2.x,p2.y,data,0xffffffff);
  
  ref(0,0,SCRW,SCRH);
}

/***************
*Բ���˶�����
*��ʱ������
****************/
void run(int data)
{
  if(angle>=360)
    angle=0;
  go(&p1,&t1,&t2,angle);
  go(&p2,&t1,&t2,angle+180);
  angle++;
}


/*��ת��Բ�ģ��Լ���ת�뾶����ת��ĵ�*/
Point t1,t2,p1,p2;
int angle=0;

/*��ʱ�����*/
int runT,drawT;

//��ں�������������ʱ��ʼִ��
int init()
{
    t1.x=200;
    t1.y=200;
    t2.x=100;
    t2.y=100;
    
    /*��ʼ����ʱ��*/
     runT=timercreate();
    drawT=timercreate();
    
    /*������ʱ��*/
    timerstart(runT,10,0,"run",1);
    timerstart(drawT,10,20,"draw",1);
    
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
 