//加载系统头文件base.h
#include <base.h>
#include <android.h>
#include <graphics.h>

 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    //dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}

int list;
int bitmap;
//入口函数，程序启动时开始执行
int init()
{
    //调用函数helloworld
    helloworld();
    
    bitmap = readBitmapFromAssets("icon_music.png");
    //加载布局
    setContextView("list.xml");
    //获取listView控件
    list=findViewById(100);
    //向listView中添加项目
    for(int i=0;i<10;i++)
    list_add(list,0,bitmap,"\x98\xce\x76\x84\x5f\x71\x5b\x50\x0\x0","\x66\x2f\x59\x29\x62\x4d\x0\x0");
   // printf("%d",list);
    //刷新listView
    list_notifyData(list);
    
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
        bitmapFree(bitmap);
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(type==19)//ListView的event事件
    {
     int id=view_getId(list);
     //printf(" p1=%d p2=%d\n",p1,p2);
     if(id==p1)
     {
      //删除一项内容
     list_remove(list,p2);
     //刷新listView
     list_notifyData(list);
     }
    }

printf("%d %d %d \n",type,p1,p2);
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
 