//����ϵͳͷ�ļ�base.h
#include <base.h>
#include "exb.h"
#include "li.h"

int timer;
_LI *li;


void logoc(int32 data)
{
 
 static int time=0;
 drawRect(0,0,SCRW,SCRH,0x20000000);
 //cls(0,0,0);
 dtext("���Ӱ�� ��Ʒ",0,30,240,240,240,0,1);
 li_run(li);
 li_draw(li);
 
 time++;
 if(time>60)
 {
  time=0;
  li_setColor(li,rand()%0xffffff);
 }
 
 ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
 setscrsize(480,480*SCRH/SCRW);
   timer=timercreate();
   li=li_create(SCRW/2,SCRH/2);
   li_setColor(li,0x60a0f0);
   
   logoc(0);
   #ifdef TCC
   timerstart(timer,30,1,logoc,TRUE); 
   #else
   timerstart(timer,30,1,"logoc",TRUE); 
   #endif
    return 0;
}




//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            // exitApp();
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(type==MS_MOVE)
    {
     li_setxy(li,p1,p2);
     
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
 
 
 
int exitApp()
{
 li_free(li);
 timerdel(timer);
 return 0;
}


