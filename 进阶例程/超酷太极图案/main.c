
/************************
*太极图案**作者：风的影子
*************************/
#include <base.h>
#include <android.h>
#include <graphics.h>
#include <exb.h>
#include <ex_math.h>


int timer;
int R;
//入口函数，程序启动时开始执行
int init()
{
    cls(255,255,255);
    R=0;
    timer=timercreate();
    timerstart(timer,50,2,"logoc",TRUE);
    
    return 0;
}

void logoc(int data)
{
// drawRect(0,0,SCRW,SCRH,0x08f0f0f0);
 drawCirs(SCRW/2,SCRH/2,SCRW/3,R);
 ref(0,0,SCRW,SCRH);
 R+=5;
}

//绘制两个圆，参数：中心点 半径 弧度
void drawCirs(int x,int y,int r,int R)
{
 int x1,y1,r1;
 int x2,y2,r2;
 //求出两圆坐标
 x1=x-r/2;
 y1=y;
 r1=r/2;
 x2=x+r/2;
 y2=y;
 r2=r/2;
 //求出旋转坐标
 toSpin(x,y,r1,r1,R, &x1,&y1);
 toSpin(x,y,r2,r2,180+R, &x2,&y2);
 
 //画圆
 drawCir(x1,y1,r1,0xfff0f0f0);
 drawCir(x2,y2,r2,0xff202020);
 //画小圆
 drawCir(x1,y1,r1/3,0xff305060);
 drawCir(x2,y2,r2/3,0xffa0c0f0);
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
 timerdel(timer);
 return 0;
}
 