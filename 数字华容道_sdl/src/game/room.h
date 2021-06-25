#ifndef _ROOM_H_
#define _ROOM_H_
#include "../def.h"
#include "../api/base.h"
#include "./object.h"
#include "./objsen.h"
#include "./camera.h"

typedef void(*RmFun)(void*ob);
typedef void(*RmEve)(int type,int p1,int p2);

//房间定义
typedef struct room
{
 //所有obj
 ObjSen*sen;
 //摄像机
 Cam cam;
 
 //速度宽高
 int sp;
 int tim;
 int w;
 int h;
 
 //创建退出函数
 RmFun create;
 RmFun draw;
 RmFun exit;
 RmEve event;
}Room;

//当前房间
extern Room*_room;

//创建房间
extern Room*newRoom(int w,int h,int sp);

//房间跳转
extern void gotoRoom(Room*rm);

//添加obj
extern void roomAddObj(Room*rm,Obj*obj);

extern void drawRoom(Room*rm);
extern void drawCurRoom();

//运行房间
extern void runRoom(Room*rm);

//运行当前房间
extern void runCurRoom();

//退出房间
extern void exitRoom(Room*rm);

#endif


