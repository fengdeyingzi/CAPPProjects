//加载系统头文件base.h
#include <base.h>
#include <android.h>

/*
xml布局可以方便的管理程序界面，提高开发速度
手机c也支持xml布局
将xml文件放到工程的assets目录下，然后通过setContextView函数加载布局。
更多功能请参见API文档：android.h

手机C自带一个方便的xml编辑器，易UI，使用方法请参见菜单>帮助与支持。
*/







//入口函数，程序启动时开始执行
int init()
{
    //调用setContextView函数加载布局
    setContextView("main.xml");
    
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
    
    if(type==VIEW_UP)
    {
     if(p1==1)
     {
      toast("你点击了按钮1",0);
     }
     if(p1==2)
     {
      toast("你点击了按钮2",0);
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
 