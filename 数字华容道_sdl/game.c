#include "game.h"

//定时器回调
//运行并绘制当前房间
void gameRun(int data)
{
 cls(0xff,0xff,0xff);
 runCurRoom();
 drawCurRoom();
 ref(0,0,SW,SH);
}

//入口函数
int init()
{
 cls(255,255,255);
 setscrsize(640,640*SH/SW);
 
 //初始化定时器
 GM.timer=
 getRes("GM.timer",tTim)->id;
 timerstart(GM.timer,100,0,gameRun,1);
 
 GM.rmHome = NULL;
 GM.rmMenu = NULL;
 
 gotoMenu();

 //刷新屏幕
 ref(0,0,SW,SH);
 return 0;
}

//event函数
int event(int type,int p1,int p2)
{
	drawRect(0,0,SCRW,SCRW,0x50303030);
	ref(0,0,SCRW,SCRH);
 if(_room->event!=NULL)
 	_room->event(type,p1,p2);
 return 0;
}

//应用暂停
int pause()
{
 return 0;
}

//应用恢复
int resume()
{
 return 0;
}

//退出函数
int exitApp()
{
 freeRes();
 return 0;
}

