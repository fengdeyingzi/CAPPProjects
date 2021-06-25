//加载系统头文件base.h
#include <base.h>
#include <exb.h>
#include <graphics.h>
//加载自定义头文件
#include "uptime.h"

setpadtype(2);

//入口函数，程序启动时开始执行
int init()
{

  
  getTime();
  cls(240,240,240);
  ref(0,0,500,500);
  getTime();
   
 int32 bitmap= readBitmapFromAssets ("1.png");
BITMAPINFO picinfo;
bitmapGetInfo(bitmap,&picinfo);
 printf("图片宽度：%d 高度：%d",picinfo.width,picinfo.height);
drawBitmap(bitmap,0,0);
bitmapFree(bitmap);
    ref(0,0,SCRW,SCRH);
    return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        //按下返回键，就退出
        case _SRIGHT:
            exit();
            break;
        case _1:
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
 