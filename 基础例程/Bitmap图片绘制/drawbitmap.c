#include <base.h>
#include <graphics.h>

/***************************
头文件：graphics.h
从安装包assets目录读取bitmap
并绘制到屏幕上
****************************/

 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    
    //从assets目录读取bitmap
    int32 bitmap = readBitmapFromAssets ("1.png");
    
    //绘制bitmap
    drawBitmap(bitmap, 0, 0);
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
 