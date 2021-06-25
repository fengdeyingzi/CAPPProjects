#ifndef GAME_H
#define GAME_H
//声明游戏内结构，函数等
#include "def.h"

//游戏变量
struct _game
{
 int32 timer;//全局定时器
 
 _FNT *fnt;//全局字体
 Room*rmHome;//主页
 Room*rmMenu;//菜单
}GM;

//rmHome 主页
extern int NUM;
extern void homeCreate(void*rm);
extern void homeDraw(void *rm);
extern void homeEvent(int type,int p1,int p2);
extern int gotoHome();

//rmMenu 菜单
extern void menuCreate(void*rm);
extern void menuDraw(void *rm);
extern void menuEvent(int type,int p1,int p2);
extern int gotoMenu();





#endif

