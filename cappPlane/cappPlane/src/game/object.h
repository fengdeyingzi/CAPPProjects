#ifndef _OBJ_H_
#define _OBJ_H_
#include "../api/base.h"
#include "./sprite.h"

//步函数
typedef void (*ObjStep)(void *ob);
typedef void (*ObjDraw)(void *ob);
typedef void (*ObjColl)(void *self, void *other);

//obj结构体
typedef struct
{
	int x;
	int y;

	Spr *spr;		 //精灵id
	int act;		 //动作id
	int img;		 //图片id
	int img_sp;		 //更新速度
	int32 _img_tim;	 //上次更新时间

	int view;  //可视

	int sp;	 //运动速度方向
	int dir;

	int group;	//碰撞组

	//回调函数
	ObjStep step;  //步函数
	ObjColl coll;  //碰撞函数
	ObjDraw draw;  //绘制函数

	//对外存数据
	int32 data[5];	//用来存数据
} Obj;

//所有obj
typedef struct _oSen {
	Obj *obj;
	struct _oSen *next;
} ObjSen;

extern ObjSen *_objSen;

/**
 * 创建Obj
 * @param x 坐标x
 * @param y 坐标y
 * @param spr 精灵
 * @returns Obj指针
 */
extern Obj *newObj(int x, int y, Spr *spr);

/**
 * 设置Obj的id
 * @param x 坐标x
 * @param y 坐标y
 * @param spr 精灵
 * @returns 无
 */
extern void setObjGroup(Obj *obj, int id);

//添加obj
extern void _addObj(Obj *obj);

//绘制obj
extern void _drawObj(Obj *obj);

extern void _defDraw(void *ob);

/**
 * 绘制所有obj
 * @returns 无
 */
extern void drawObj();

//运行obj
extern void _runObj(Obj *obj);

/**
 * 运行所有Obj
 * @returns 无
 */
extern void runObj();

//默认step
extern void _defStep(void *ob);

//追踪obj
extern void _follObj(Obj *obj, int x, int y, int r);

//检测一个obj碰撞
extern void collAllObj(Obj *obj);

//碰撞检测,不检测碰撞组
extern int _objCollObj(Obj *obj1, Obj *obj2);

//点与obj碰撞
extern int _posCollObj(int x, int y, Obj *obj);

//矩形与obj碰撞
extern int _rectCollObj(int x, int y, int w, int h, Obj *obj);

//释放obj
extern void _freeObj(Obj *obj);

//删除一个obj
extern void delOneObj(Obj *obj);

//删除obj
extern void delObj();

#endif