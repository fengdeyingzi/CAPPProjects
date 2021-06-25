#include "../api/base.h"
#include "../api/ex_math.h"
#include "./object.h"

//创建obj
Obj*newObj(int x,int y,Spr*spr)
{
 Obj*obj = malloc(sizeof(Obj));
 obj->x = x;
 obj->y = y;
 obj->spr = spr;
 obj->mask = spr;
 obj->mask_show = FALSE;
 obj->act = 0;
 
 obj->img = 0;
 obj->img_sp = 100;
 obj->_img_tim = getuptime();
 
 obj->xsca = FALSE;
 obj->ysca = FALSE;
 obj->view = TRUE;
 
 obj->sp = 0;
 obj->dir = 0;
 obj->sta = 0;
 obj->group = 0;
 
 obj->step = _defStep;
 obj->coll = NULL;
 obj->draw = NULL;
 int i;
 for( i = 0;i<10;i++)
 	obj->data[i] = -1;
 
 //getScaSpr(spr,TRUE,TRUE);
 //getScaSpr(spr,TRUE,FALSE);
 //getScaSpr(spr,FALSE,TRUE);
// getScaSpr(spr,FALSE,FALSE);
 
 return obj;
}

//设置分组
void setObjGroup(Obj*obj,int group)
{
 obj->group = group;
}

//默认step
void _defStep(void*ob)
{
 Obj*obj = (Obj*)ob;
 int x = obj->x+obj->sp*100;
 int y = obj->y;
 toSpin(obj->x,obj->y,
  obj->sp*100,obj->sp*100,
  obj->dir,&x,&y);
 obj->x+=(x-obj->x)/100;
 obj->y+=(y-obj->y)/100;
}

//追踪x,y，用于制作追踪导弹
//xy坐标，r每帧旋转角度
void _follObj(Obj*obj,int x,int y,int r)
{
 //获取目标角度
 int radi = 
 getRadiam(obj->x,obj->y,x,y);
 //计算差值
 int rr = obj->dir-radi;
 if(rr!=0)
 	obj->dir-=rr/abs(rr)*r;
 _defStep(obj);
}

//运行obj
void runObj(Obj*obj)
{
 if(obj==NULL)
 	return;
 if(getuptime()-obj->_img_tim>
   obj->img_sp)
 {
  if(obj->spr!=NULL)
  {
   setSprActId(obj->spr,
    obj->act);
   setSprImgId(obj->spr,
    obj->img);
   runSpr(obj->spr);
   obj->img = obj->spr->
   act[obj->spr->ind].ind;
  }
  if(obj->step!=NULL)
  {
   (*obj->step)(obj);
  }
  obj->_img_tim = getuptime();
 }
 
 
 //obj->act=obj->spr->ind;
}

void drawObjPos(Obj*obj,int x,int y)
{
 if(obj==NULL)
 	return;
 if(obj->view)
 {
  setSprActId(obj->spr,obj->act);
  setSprImgId(obj->spr,obj->img);
  drawSpr(obj->spr,x,y);
  if(obj->mask!=NULL)
  	if(obj->mask_show)
  	drawSpr(obj->mask,x,y);
 }
}

//绘制obj
void drawObj(Obj*obj)
{
 drawObjPos(obj,obj->x,obj->y);
}

void drawObjCam(Obj*obj,Cam*cam)
{
 drawObjPos(obj,
  obj->x-cam->x,obj->y-cam->y);
}

void _defDraw(void*ob)
{
 Obj*obj = ob;
 if(obj->view)
 	drawObj(obj);
}

//碰撞检测,不检测碰撞组
int _objCollObj(Obj*obj1,Obj*obj2)
{
 Spr*spr1 = obj1->mask;
 Spr*spr2 = obj2->mask;
 
 int x1 = obj1->x-spr1->x;
 int y1 = obj1->y-spr1->y;
 int x2 = obj2->x-spr2->x;
 int y2 = obj2->y-spr2->y;
 
 return isCollRect(x1,y1,
  spr1->w,spr1->h,
  x2,y2,
  spr2->w,spr2->h);
}

//点与obj碰撞
int _posCollObj(int x,int y,Obj*obj)
{
 Spr*spr = obj->mask;
 int x1 = obj->x-spr->x;
 int y1 = obj->y-spr->y;
 
 return isPointCollRect(x,y,
  x1,y1,spr->w,spr->h);
}

//矩形与obj碰撞
int _rectCollObj(int x,int y,int w,int h,Obj*obj)
{
 Spr*spr = obj->mask;
 int x1 = obj->x-spr->x;
 int y1 = obj->y-spr->y;
 
 return isCollRect(x,y,w,h,
  x1,y1,spr->w,spr->h);
}

//释放obj
void freeObj(Obj*obj)
{
 free(obj);
}

