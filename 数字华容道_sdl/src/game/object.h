#ifndef _OBJ_H_
#define _OBJ_H_
#include "../api/base.h"
#include "./sprite.h"
#include "./camera.h"

//步函数
typedef void(*ObjStep)(void*ob);
typedef void(*ObjDraw)(void*ob);
typedef void(*ObjColl)(void*self,void*other);

//obj结构体
typedef struct
{
 int x;
 int y;
 
 Spr*spr;//精灵id
 Spr*mask;//遮罩精灵
 int mask_show;
 int act;//动作id
 int img;//图片id
 int img_sp;//更新速度
 int _img_tim;//上次更新时间
 
 int xsca;//翻转精灵
 int ysca;
 
 int view;//可视
 
 int sp;//运动速度方向
 int dir;
 int sta;
 
 int group;//碰撞组
 
 //回调函数
 ObjStep step;//步函数
 ObjColl coll;//碰撞函数
 ObjDraw draw;//绘制函数
 
 int data[10];
}Obj;

//创建obj
extern Obj*newObj(int x,int y,Spr*spr);
//设置id
extern void setObjGroup(Obj*obj,int id);
//添加obj
extern void _addObj(Obj*obj);
//绘制obj
extern void drawObjPos(Obj*obj,int x,int y);
extern void drawObj(Obj*obj);
extern void drawObjCam(Obj*obj,Cam*cam);
extern void _defDraw(void*ob);
//运行obj
extern void runObj(Obj*obj);
//默认step
extern void _defStep(void*ob);
//追踪obj
extern void _follObj(Obj*obj,int x,int y,int r);
//碰撞检测,不检测碰撞组
extern int _objCollObj(Obj*obj1,Obj*obj2);
//点与obj碰撞
extern int _posCollObj(int x,int y,Obj*obj);
//矩形与obj碰撞
extern int _rectCollObj(int x,int y,int w,int h,Obj*obj);
//释放obj
extern void freeObj(Obj*obj);

#endif
