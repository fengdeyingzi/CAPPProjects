//加载系统头文件base.h
#include <base.h>
#include "android.h"
#include "SeekBar.h"

 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}

void onstart(int id)
{
 printf("%s id=%d 进度:%d\n","滑动开始",id,seek_getProgress(seekBar));
 
 //draw_main();
 //printf("点\n");
// return 0;
 }
 

void onpos(int id)
{
 printf("%s id=%d 进度=%d\n","滑动",id,seek_getProgress(seekBar));
 
 //draw_main();
 //printf("点\n");
// return 0;
 }
 
 
void onstop(int id)
{
 printf("%s id=%d 进度=%d\n","滑动结束",id,seek_getProgress(seekBar));
 
 //draw_main();
 //printf("点\n");
// return 0;
 }

typedef struct
{
 char *name;
} CH;

SeekBar *seekBar;


//绘制画面
void draw_main()
{
    cls(240,240,240);
    //绘制按钮
    seek_draw(seekBar);
    
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
 
}


//入口函数，程序启动时开始执行
int init()
{
 int DECVIDE_WIDTH=0;
 int DECVIDE_HEIGHT=0;
 if(SCRW<SCRH)
 {
  DECVIDE_WIDTH=720;
  DECVIDE_HEIGHT = 720*SCRH/SCRW;
 }
 else
 {
  DECVIDE_WIDTH=720;
  DECVIDE_HEIGHT = 720*SCRW/SCRH;
 }
 
 
 
 setscrsize(720,720*DECVIDE_HEIGHT/DECVIDE_WIDTH);
    //创建SekBar
    seekBar = seek_create(50,50,720-100,100);
    
    //设置SeekBar进度
    seek_setProgress(seekBar, 30);
    seek_setMax(seekBar,100);
    seek_onStartTrackingTouch(seekBar,"onstart");
    seek_onProgressChanged(seekBar,"onpos");
    seek_onStopTrackingTouch(seekBar,"onstop");
    
    
    CH *ch = (void*)seekBar;
    printf("%s\n", ch->name);
    //设置id
    seek_setid(seekBar,1);
    
    
    draw_main();
    return 0;
}

void exit_free()
{
 seek_free(seekBar);
 
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{
 //监听event事件
 seek_event(seekBar,type,p1,p2);
 
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
        exit_free();
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
 printf("pause\n");
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
 printf("resume\n");
    return 0;
}
 