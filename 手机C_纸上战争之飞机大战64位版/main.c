//����ϵͳͷ�ļ�base.h
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
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

MENU *menu;
_GAME *game;
int32 timer;
int32 rc;

//��ں�������������ʱ��ʼִ��
int init()
{
 win=WIN_MAIN;
    //���ú���helloworld
    setscrsize(480,480*SCRH/SCRW);
    helloworld();
    printf("%s\n","����");
    rc = rc_read("res_lang0.rc",30);
    //printf_mapsprite(32,32,32,32);
    win_set(WIN_MAIN);
    printf("%s\n","win_set ok");
    menu = menu_create();
    printf("%s\n","...");
    menu_draw(menu);
    printf("%s\n","����");
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



//event������������Ϣ�¼�
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

//Ӧ����ͣ������������̨���Ϊ���ɼ�ʱ����ô˺���
int pause()
{
    return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
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

 