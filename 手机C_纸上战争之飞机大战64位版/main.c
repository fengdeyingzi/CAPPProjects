//加载系统头文件base.h
#include <base.h>
#include <android.h>
#include <graphics.h>

#include "rclist.h"
#include "win.h"
#include "sprite_write.h"
#include "menu.h"
#include "game.h"

extern void logoc(int data);

 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}

MENU *menu;
_GAME *game;
int32 timer;
int32 rc;

//入口函数，程序启动时开始执行
int init()
{
 win=WIN_MAIN;
    //调用函数helloworld
    setscrsize(480,480*SCRH/SCRW);
    helloworld();
    printf("%s\n","测试");
    rc = rc_read("res_lang0.rc",30);
    //printf_mapsprite(32,32,32,32);
    win_set(WIN_MAIN);
    printf("%s\n","win_set ok");
    menu = menu_create();
    printf("%s\n","...");
    menu_draw(menu);
    printf("%s\n","测试");
    timer=timercreate();
    #ifdef TCC
    timerstart(timer,30,1,logoc,1);
    #else
    timerstart(timer,30,1,"logoc",1);
    #endif
    
    return 0;
}

void logoc(int data)
{
 if(win==WIN_MAIN)
 {
 menu_draw(menu);
 }
 if(win==WIN_GAME)
 {
  game_run(game);
 game_drawAll(game);
 }
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
 /*
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
        exitApp();
            exit();
            return 0;
        case _MENU:
            break;
        }
    }
    */
    
    if(win==WIN_MAIN)
    menu_event(menu,type,p1,p2);
    else if(win==WIN_GAME)
    game_event(game,type,p1,p2);
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
 if(win==WIN_MAIN)
 {
  menu_free(menu);
 }
 else if(win==WIN_GAME)
 {
  game_free(game);
 }
 timerstop(timer);
 timerdel(timer);
 rc_free(rc);
return 0;
}

 