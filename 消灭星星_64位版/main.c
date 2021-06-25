//加载系统头文件base.h
#include <base.h>
#include <android.h>
#include "star.h"
#include "bitmap.h"
#include "coding.h"
#include "li.h"
#include "fps.h"

/*
手机C版消灭星星 

添加粒子效果
星星运动效果

风的影子 制作

*/

FPS *fps;
_STARS *star;
int32 timer=0;
int32 view_title;
int32 view_fen;
int isExit = 0;
void logoc(int data);
int exitApp();


//星星初始化
int star_init()
{
fps= fps_create();
printf("%s\n","find");
view_title = findViewById(1);
printf("%s\n","find2");
view_fen= findViewById(10); 
printf("%s\n","find 3");
star=star_create(0,SCRH-640,10,10);
printf("%s\n","star_init");
 star_setview(star,view_fen );
    star_draw(star);
   // star_free(star);
    ref(0,0,SCRW,SCRH);
    printf("刷新屏幕\n");
    if(timer==0)
    {
    timer=timercreate();
    printf("启动定时器\n");
    timerstart( timer,30,1,logoc,1);
    printf("%s\n","启动成功");
    }
 return 0;
}

//入口函数，程序启动时开始执行
int init()
{
 toast("风的影子 作品",0);
 printf("启动游戏\n");
 setContextView("text.xml");
    cls(0,0,0);
    setscrsize(640,640*SCRH/SCRW);
    printf("%s\n","测试");
   
   
   
    star_init();
    return 0;
}

void logoc(int data)
{
printf("%s\n","logoc");
 cls(0,0,0);
 char text[40];
 printf("%s\n","fps_run");
fps_run(fps);
printf("%s\n","star_run");
 star_run(star);
 printf("%s\n","star_draw");
 star_draw(star);
 if(star_getTime(star)==60)
  {
   setVisibility(view_title,8);
  }
 if(star_isNoImpact(star))
 {
  //printf("exitapp\n");
  exitApp();
  //printf("star_init\n");
  star_init();
  //printf("setText\n");
   view_setText(view_title,"\x60\x6d\x55\x9c\x8f\xc7\x51\x73\x0\x0");
  setVisibility(view_title,0);
  
 }
 
//printf("fps_get\n");
 sprintf(text,"fps:%d\n\0",fps_get(fps));
//printf("dtext\n");
 dtext (text,SCRW/2,0,240,240,240,0,0);
//printf("ref\n"); 
 // printf("timer\n");
 ref(0,0,SCRW,SCRH);
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exitApp(); 
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    star_event(star,type,p1,p2);

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
 
 
 
int exitApp()
{
if(isExit==0){
printf("%s\n","exitApp");
printf("%s\n","star_free");
 star_free(star);
 printf("%s\n","fps_free");
 fps_free(fps);
 
 timerdel(timer);
 timer=0;
 isExit = 1;
 }
return 0;
}


