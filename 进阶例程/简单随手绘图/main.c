#include <base.h>

/*绘制小块矩形*/
void draw(int x,int y)
{
  drect(x,y,5,5,100,100,100);
  ref(0,0,SCRW,SCRH);
}

int init()
{
    
  return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(MS_DOWN == type)
    {
      cls(0,0,0);
    }
    
    if(MS_MOVE == type)
    {
      draw(p1,p2);
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
 