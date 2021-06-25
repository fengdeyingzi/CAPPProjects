//加载系统头文件base.h
#include <base.h>
#include <android.h>
#include "button.h"

//声明按钮
button *btn_exit,*btn_start;

//记录文字宽高
int fontw,fonth;
#define FONT 1

 void draw()
{
    cls(255,255,255);
    dtext("按钮点击事件",0,0,50,50,50,0,FONT);
    dtext("by：风的影子",0,fonth+4,50,50,50,0,FONT);
    //将按钮绘制到屏幕上
    button_draw(btn_exit);
    button_draw(btn_start);
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
 //检测文字大小
 textwh("子",0,FONT,&fontw,&fonth);
 
 //初始化按钮，新建两个按钮
 //new_button参数分别是 按钮文字 按钮x坐标 y坐标 宽度 高度 
 btn_start=new_button("开始",0,SCRH-(fonth+10), fontw*4+10 ,fonth+10 );
 btn_exit=new_button("退出",SCRW-(fontw*4+10),SCRH-(fonth+10), fontw*4+10, fonth+10);
 //显示
 draw();
 
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
            exitapp();
            break;
        case _MENU:
            break;
        }
    }
    //判断触屏事件
    if(type == MS_UP)
    {
     if(button_impact(btn_start, p1, p2))
     {
      toast("你点中了开始按钮",0);
     }
     if(button_impact(btn_exit,p1,p2))
     {
      toast("感谢测试^o^",0);
      exitapp();
     }
     
    }

    return 0;
}

void exitapp()
{
 button_free(btn_start);
 button_free(btn_exit);
 exit();
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
 