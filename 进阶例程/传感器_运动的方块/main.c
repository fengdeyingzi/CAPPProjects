//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <exb.h>

MOTION_ACC *acc;
char text[300];

//��ʱ�������Ʒ����ƶ�
int timer;
//���������
int rx,ry;

//���洫�����������
int sensor_x,sensor_y;


//�����ƶ���ʱ��
void logoc(int data)
{
 move(-sensor_x,sensor_y);
 draw_rect(rx,ry);
 
}

//�ƶ���������
int move(int movex,int movey)
{
 rx+=movex/10;
 ry+=movey/10;
 if(rx<0)rx=0;
 if(rx>SCRW-50)rx=SCRW-50;
 if(ry<0)ry=0;
 if(ry>SCRH-50)ry=SCRH-50;
 return 0;
}

//���Ʒ���
 void draw_rect(int x,int y)
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    drect(x,y,50,50,240,240,240);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
   
    if( _VERSION<2200)
    {
     cls(0,0,0);
     dtext("�ֻ�C���԰汾���ͣ�������",0,30,255,50,50,0,1);
     
     ref(0,0,SCRW,SCRH);
     return -1;
    }
    
    sensorOn();
    sensorStart(1);
    timer=timercreate();
    timerstart(timer, 100, 2, "logoc", TRUE);
   logoc(0);
    
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
        sensorOff();
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(type==18)
    {
     acc=(void*)p2;
     sensor_x=acc->x;
     sensor_y=acc->y;
     /*
     draw_rect(acc->x,-acc->y);
     sprintf(text,"%d %d %d\n",acc->x,acc->y,acc->z);
     
     dtext(text,0,0,20,255,20,0,1);
     ref(0,0,SCRW,SCRH);
     */
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
 