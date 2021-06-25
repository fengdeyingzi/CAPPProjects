/*************************************
*自绘按钮的按下与抬起效果**作者:小蟀*******
*此例程只做简单示例，深度研究请看SGL,tWin**
*************************************/

#include <base.h>
#include <button.h>
#include <ex_math.h>

/*按钮被按下*/
void down(int x,int y)
{
  if(isPointCollRect(x,y,b->x,b->y,b->w,b->h)==TRUE)
  {
    b->isDown=1;
  }
  else
  {
    b->isDown=0;
  }
  drawBtn(b);
}

void up()
{
  b->isDown=0;
  drawBtn(b);
}

Btn* b;

int init()
{
  cls(0,0,0);
   
  b=newBtn(100,200,100,50);
  drawBtn(b);
  
  ref(0,0,SCRW,SCRH);
  return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(MS_DOWN == type)
    {
      down(p1,p2);
    }
    
    if(MS_UP == type)
    {
      up();
    }
    
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
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
 