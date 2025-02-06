//加载系统头文件base.h
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
 dtext("风的影子 作品",0,30,240,240,240,0,1);
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


//入口函数，程序启动时开始执行
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




//event函数，接收消息事件
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
 
 
 
int exitApp()
{
 li_free(li);
 timerdel(timer);
 return 0;
}


