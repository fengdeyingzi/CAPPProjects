//加载系统头文件base.h
#include <base.h>
#include <graphics.h>

 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
    cls(0,0,0);
    crect(40,40,150,50,20,0xff4080ff);
    ref(0,0,SCRW,SCRH);
    
    return 0;
}

//画圆角矩形，参数分别是：x,y坐标,宽度，高度，圆角半径，十六进制颜色
void crect(int x,int y,int w,int h,int r,int color)
{
 drawRect(x,y+r,w,h-2*r,color|0xff000000);
 drawRect(x+r,y,w-2*r,h, color|0xff000000);
 drawCir(x+r,y+r,r,color|0xff000000);
 drawCir(x+w-r, y+r,r,color|0xff000000);
 drawCir(x+r,y+h-r,r,color|0xff000000);
 drawCir(x+w-r,y+h-r, r, color|0xff000000);
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{
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
 