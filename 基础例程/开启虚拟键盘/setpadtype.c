//加载系统头文件base.h
#include <base.h>
#include <exb.h>
/*
setpadtype 函数 
开启虚拟键盘，目前支持以下键盘
0 没有任何按键
1 全键键盘
2 游戏键盘 做游戏专用
3 只有方向键 确定键 返回键
*/


 void helloworld()
{
    //开启虚拟键盘
    setpadtype(3);
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "虚拟键盘示例", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
    
}


//入口函数，程序启动时开始执行
int init()
{
    //调用函数helloworld
    helloworld();
    
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
            
            setpadtype(0);
            ref(0 ,0 ,SCRW, SCRH);
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
 