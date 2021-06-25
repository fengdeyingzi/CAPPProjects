//加载系统头文件base.h
#include <base.h>
#include <android.h>
#include "keytime.h"

/*
按住屏幕不放
弹出toast

作者：风的影子
本公子是无所不能的～
*/

int keytime;

 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "长按事件例子", 0, 0, 255, 255, 255, 0, 1);
    
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
    //调用函数helloworld
    helloworld();
    toast("屏幕长按例子",0);
    toast("本公子是无所不能的～",0);
    //创建事件
    keytime=key_create();
    //设置长按时间
    key_settime(keytime,2000);
    
    return 0;
}
int exitapp()
{
 key_free(keytime);
 exit();
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
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(type==MS_DOWN)
    {
     //开始长按事件
     key_start(keytime);
    }
    else if(type==MS_UP)
    {
     key_stop(keytime);
    }
    //接收长按事件
    if(type==(int)keytime)
    {
     toast("长按事件启动",0);
     dtext("长按事件启动",0,50,240,0,0,0,1);
     ref(0,0,SCRW,SCRH);
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
 
 