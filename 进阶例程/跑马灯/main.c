//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>
#include <graphics.h>
#include <exb.h>
#include <ex_math.h>

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(40,90,240);
    //������
   // dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}
int timer;
int R;
//��ں�������������ʱ��ʼִ��
int init()
{
    //���ú���helloworld
    helloworld();
    R=0;
    timer=timercreate();
    timerstart(timer,100,2,"logoc",TRUE);
    
    return 0;
}
void logoc(int data)
{
 drawRect(0,0,SCRW,SCRH,0x504060f0);
 drawCirs(SCRW/2,SCRH/2,SCRW/3,R);
 ref(0,0,SCRW,SCRH);
 R+=36;
 
}

//��������Բ�����������ĵ� �뾶 ����
void drawCirs(int x,int y,int r,int R)
{
 int x1,y1,r1;
 int x2,y2,r2;
 //�����Բ����
 x1=x-r/2;
 y1=y;
 r1=r/2;
 x2=x+r/2;
 y2=y;
 r2=r/2;
 //�����ת����
 toSpin(x,y,r1,r1,R, &x1,&y1);
 toSpin(x,y,r2,r2,180+R, &x2,&y2);
 
 //��Բ
// drawCir(x1,y1,r1,0xfff0f0f0);
// drawCir(x2,y2,r2,0xff202020);
 //��СԲ
 drawCir(x1,y1,r1/5,0xff000000 + rand()%0xffffff);
 drawCir(x2,y2,r2/5,0xff000000 + rand()%0xffffff);
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
        exitapp();
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


int exitapp()
{
 timerdel(timer);
 return 0;
}
 