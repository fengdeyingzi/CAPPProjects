#ifndef _OBJSEN_H_
#define _OBJSEN_H_
#include "../api/base.h"
#include "./object.h"
#include "./camera.h"

//obj链表
typedef struct _oSen
{
 Obj*obj;
 struct _oSen*next;
}ObjSen;

//绘制ObjSen内obj
extern void drawSenObj(ObjSen*link);
extern void drawSenObjCam(ObjSen*link,Cam*cam);
//向ObjSen添加obj
extern void addSenObj(ObjSen*link,Obj*obj);

//运行ObjSen
extern void runObjSen(ObjSen*link);

//检测ObjSen碰撞
void collAllSenObj(ObjSen*link);
extern void collSenObj(ObjSen*link,Obj*obj);
Obj*pointSenObj(ObjSen*link,
 int x,int y);
//检测链接中数目
int getSenObjNum(ObjSen*link,int group);
//删除ObjSen内一个obj
extern void delSenOne(ObjSen**link,Obj*obj);

//删除ObjSen内全部obj
extern void delSenAll(ObjSen*link);

#endif

