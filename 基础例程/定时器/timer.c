#include <base.h>

//定时器句柄
int32 timer;

//用来统计定时器执行次数
int a=0;


void timerCD(int data)
{
    char text[20];
    sand(getuptime());
    cls(255,255,255);
    //将a的值转换成字符串
    sprintf (text, "%d", a);
    //绘制文字到屏幕上
    dtext (text, 10, 10, 20, 20, 20, 0, 2);
    
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
    //输出printf
    printf("timer,data=%d,a=%d\r\n",data,a++);
    
}


int init(void)
{
 
    //创建定时器
    timer=timercreate();
    //启动定时器 参数分别是：定时器句柄，定时器时长，定时器回调data，定时器回调函数，是否循环
    timerCD(0);
    timerstart (timer, 1000, 1234, "timerCD", TRUE);
    
    return 0;
}

int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
    {
        switch(p1)
        {
         //按返回键退出
        case _BACK:
            exitapp();
            break;
        case _1:
            break;
        case _2:
            break;
        }
    }

    return 0;
}

int pause(void)
{
    return 0;
}

int resume(void)
{
    return 0;
}

int exitapp(void)
{
    //退出时删除定时器
    timerdel(timer);
    
    exit();
    return 0;
}