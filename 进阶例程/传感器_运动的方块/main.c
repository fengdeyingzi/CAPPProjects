//加载系统头文件base.h
#include <base.h>
#include <exb.h>

MOTION_ACC *acc;
char text[300];

//定时器，控制方块移动
int timer;
//方块的坐标
int rx,ry;

//保存传感器坐标参数
int sensor_x,sensor_y;


//方块移动定时器
void logoc(int data)
{
 move(-sensor_x,sensor_y);
 draw_rect(rx,ry);
 
}

//移动方块坐标
int move(int movex,int movey)
{
 rx+=movex/10;
 ry+=movey/10;
 if(rx<0)rx=0;
 if(rx>SCRW-50)rx=SCRW-50;
 if(ry<0)ry=0;
 if(ry>SCRH-50)ry=SCRH-50;
 return 0;
}

//绘制方块
 void draw_rect(int x,int y)
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画矩形
    drect(x,y,50,50,240,240,240);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
   
    if( _VERSION<2200)
    {
     cls(0,0,0);
     dtext("手机C语言版本过低，请升级",0,30,255,50,50,0,1);
     
     ref(0,0,SCRW,SCRH);
     return -1;
    }
    
    sensorOn();
    sensorStart(1);
    timer=timercreate();
    timerstart(timer, 100, 2, "logoc", TRUE);
   logoc(0);
    
    return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
        sensorOff();
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(type==18)
    {
     acc=(void*)p2;
     sensor_x=acc->x;
     sensor_y=acc->y;
     /*
     draw_rect(acc->x,-acc->y);
     sprintf(text,"%d %d %d\n",acc->x,acc->y,acc->z);
     
     dtext(text,0,0,20,255,20,0,1);
     ref(0,0,SCRW,SCRH);
     */
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
 