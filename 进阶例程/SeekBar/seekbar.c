//加载系统头文件base.h
#include <base.h>
#include <android.h>

  void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}
int seekbar;

//入口函数，程序启动时开始执行
int init()
{
    setContextView("seekbar.xml");
    seekbar=findViewById(10);
    if(seekbar!=0)
    {
    //设置SeekBar的最大值
    seekBar_setMax(seekbar,100);
    //设置SeekBar的进度
    seekBar_setProgress(seekbar,50);
    }
    int i=seekBar_getProgress(seekbar);
    
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
          int i=seekBar_getOffset(seekbar);
    printf(" %d ",i);
            break;
        }
    }
    
    //SeekBar的滑动事件
    if(type==23)
    {
     printf("seekBar滑动");
     int id= p1;
     printf(" id:%d pos:%d\n",p1,p2);
    }
    else if(type==24)
    {
     printf("seekBar开始滑动\n");
     
    }
    
    else if(type==25)
    {
     printf("seekBar结束滑动\n");
     
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
 