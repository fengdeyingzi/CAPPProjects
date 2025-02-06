//加载系统头文件base.h
#include <base.h>
#include <graphics.h>
#include <stdlib.h>
#include "plan.h"

#include "eme.h"
#include "timer.h"
#include "check.h"

//结束游戏
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
    
    //初始化飞机，开始绘制飞机，子弹开始运动
    initPlan(&plan);   
    printf("init Plan...\r\n");
    startDrawPlan();
    printf("start draw...\r\n");
    startRayRun();
    
    //检测
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


//event函数，接收消息事件
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
 

int mrc_exitApp()
{
	return 0;
}