//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <graphics.h>
#include <stdlib.h>
#include "plan.h"

#include "eme.h"
#include "timer.h"
#include "check.h"

//������Ϸ
void over()
{
  endAllTimer();
  delPlan(&plan);
  delEme();
  exit(); 
}

int init()
{
    cls(0,0,0);
    printf("start...\r\n");
    setscrsize(800,800*SCRH/SCRW);        
    
    //��ʼ���ɻ�����ʼ���Ʒɻ����ӵ���ʼ�˶�
    initPlan(&plan);   
    printf("init Plan...\r\n");
    startDrawPlan();
    printf("start draw...\r\n");
    startRayRun();
    
    //���
    startCheckRun();
    printf("check...\r\n");
    
    int i;
    for(i=0;i<EmeN;i++)
    { 
       initEme(&emeN[i]);
    }
 
    ref(0,0,SCRW,SCRH);
      
    return 0;
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(MS_MOVE==type)
    {
      planRun(&plan,p1,p2);
    }
    
    if(MS_UP==type)
    {
      //planRun(&plan,plan.x,plan.y);
    }
    
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK
:
            over();
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
 

int mrc_exitApp()
{
	return 0;
}