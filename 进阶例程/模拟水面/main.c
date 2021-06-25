//加载系统头文件base.h
#include <base.h>
#include <graphics.h>
#include <ex_math.h>
#include "water.h"


WATERS *was;
int timer;

int init()
{
    int i;
    was=wa_create();
    setscrsize(480,480*SCRH/SCRW);
    for(i=0;i<SCRW;i+=5)
    {
     wa_add(was,i,100,rand()%20,i+rand()%30);
    }
    
    timer=timercreate();
    timerstart(timer,50,1,"logoc",TRUE);
    
    
    return 0;
}

void logoc(int data)
{
 drawRect(0,0,SCRW,SCRH,0x30a0c1f1);
 wa_draw(was);
 wa_run(was);
 ref(0,0,SCRW,SCRH);
 
}


//event函数，接收消息事件
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
 
 
 int exitapp()
 {
  wa_free(was);
  return 0;
 }