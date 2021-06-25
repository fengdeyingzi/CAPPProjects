/*
点击屏幕触发对话
*/

#include <base.h>
#include <exb.h>

#include "rpgsen.h"

Rpgsen r;
int flag_into = 0;
int tt;

int init()
{
 setscrsize(540,540*SCRH/SCRW);
 rpgsenInit(&r);
 rpgsenRead(&r, "1.rpgsen");
 tt = timercreate();
 timerstart(tt, 100,0,"helloworld", 1);
 return 0;
}

void helloworld(int data)
{
 cls(180, 190, 180);
 rpgsenDraw(&r);
 char s[100];
 sprintf(s, "flag:%d sumNow:%d trigger:%d", flag_into, r.sumNow, r.triggerSumNow );
 setTextSize(1, 20);
 dtext( s, 0, 0, 0, 0, 0, 0, 1);
 ref(0, 0, 540, 960);
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{

 if(flag_into == 0 )
 {
  if(MS_UP == type)
  {
   flag_into = 1;
   rpgsenInto(&r);
  }
 }
 else
 {
  flag_into = rpgsenEvent(&r, type, p1,p2);
 }
 if(KY_UP == type && p1 == _BACK)
 {
  rpgsenDispose(&r);
  exit();
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
 