
#include "base.h"

int x,y;

/*

一个简单的画图程序
by：风的影子

*/


int init()
{
cls(240,240,240);
ref(0,0,SCRW,SCRH);
return 0;
}

int event(int msg,int p1,int p2)
{
if(msg==KY_UP)
  {
    if(p1==_BACK)
    {exit();}
    if(p1==_MENU)
    {init();}
  }
  if(MS_DOWN==msg)
    {x=p1; y=p2;}
  if(MS_MOVE==msg)
  {
    dline(x,y,p1,p2,15,45,200);
x=p1; y=p2;
  }
ref(0,0,SCRW,SCRH);
return 0;
}                                                                                                                                        

int pause()
{
 return 0;
}

int resume()
{
 return 0;
}
