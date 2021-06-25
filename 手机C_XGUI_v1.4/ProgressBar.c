//加载系统头文件base.h
#include <base.h>
#include "android.h"
#include "ProgressBar.h"

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
 printf("%s id=%d 进度:%d\n","滑动开始",id,pos_getProgress(seekBar));
 
 //draw_main();
 //printf("点\n");
// return 0;
 }
 

void onpos(int id)
{
 printf("%s id=%d 进度=%d\n","滑动",id,pos_getProgress(seekBar));
 
 //draw_main();
 //printf("点\n");
// return 0;
 }
 
 
void onstop(int id)
{
 printf("%s id=%d 进度=%d\n","滑动结束",id,pos_getProgress(seekBar));
 
 //draw_main();
 //printf("点\n");
// return 0;
 }

typedef struct
{
 char *name;
} CH;

ProgressBar *seekBar;


//绘制画面
void draw_main()
{
    cls(240,240,240);
    //绘制按钮
    pos_draw(seekBar);
    
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
    cls(240,240,240);
    ref(0,0,SCRW,SCRH);
    //创建SekBar
    seekBar = pos_create(50,50,720-100,100);
    
    //设置SeekBar进度
    pos_setProgress(seekBar, 30);
    pos_setMax(seekBar,100);
    /*
    for(int i=0;i<=10;i++)
    {
     pos_setProgress(seekBar, 10*i);
     sleep(100);
    }
    */
    
    
    CH *ch = (void*)seekBar;
    printf("%s\n", ch->name);
    //设置id
    pos_setid(seekBar,1);
    
    
    draw_main();
    return 0;
}

void exit_free()
{
 pos_free(seekBar);
 
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{
 //监听event事件
 pos_event(seekBar,type,p1,p2);
 
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