
#include <base.h>
#include <graphics.h>
#include <android.h>
#include <ex_math.h>
#include "exb.h"


typedef struct
{
 float x; //坐标
 float y; //坐标
 int r;
 float speed_x;  //横向运动值
 float speed_y;   //纵向运动值
 int hp; //生命
 int color;
 int alpha; //透明度
} _POINT;


typedef struct
{
 _POINT *point;
 int x;
 int y; //粒子发生点 坐标
 int r; //宽度
 int v;
 int size; //粒子数量
 int birth; //出生量
 int speed; //粒子递减量
 int hp; //生命
 int color; //颜色 rgb值
} _LI;



//创建粒子
_LI *li_create(int x,int y)
{
 _LI *li = malloc(sizeof(_LI));
 li->x=x;
 li->y=y;
 li->r=2;
 li->v=1;
 li->speed=1;
 li->hp= 500;
 li->birth=20;
 li->size=10000;
 li->point = malloc(sizeof(_POINT)*li->size);
 memset(li->point,0,sizeof(_POINT)*li->size);
 li->color=0xffffff;
 
 return li;
};

//粒子运动
int li_run(_LI *li)
{
 //生成粒子
 int i;
 int size=0;
 for(i=0;i<li->size;i++)
 {
 if(li->point[i].hp<=0)
  {
   _POINT *point=&(li->point[i]);
  li->point[i].hp=li->hp;
  li->point[i].x=li->x;
  li->point[i].y=li->y;
  li->point[i].alpha=255;
  li->point[i].color=li->color | rand()%0xffffff;
  li->point[i].r=li->r;
  li->point[i].speed_x=-3+rand()%6;
  li->point[i].speed_y=-3+rand()%6;
  int x,y;
  toSpin(0,0, li->v*100, li->v*100, rand()%360, &x,&y);
  point->speed_x=((float)x)/100;
  point->speed_y=((float)y)/100;
  size++;
  if(size>=li->birth) break;
  }
 }
 
 //运动
 for(i=0;i<li->size;i++)
 {
  _POINT *point=&(li->point[i]);
  point->x+=point->speed_x;
  point->y+=point->speed_y;
  point->hp--;
  point->alpha-=li->speed;
  if(point->alpha<0)
  point->alpha=0;
 }
 
 return 0;
}

//设置粒子速度
int li_setV(_LI *li)
{
 
 
 return 0;
}

//设置粒子透明度递减量
int li_setSpeed(_LI *li, int speed)
{
 li->speed=speed;
 
 return 0;
}
//设置粒子生成角度


//设置粒子生命
int li_setHp(_LI *li, int hp)
{
 li->hp=hp;
 
 return 0;
}

//设置粒子数量
int li_setSize(_LI *li, int size)
{
 li->size=size;
 return 0;
}

//设置粒子坐标
int li_setxy(_LI *li,int x,int y)
{
 li->x=x;
 li->y=y;
 return 0;
}

//设置粒子颜色
int li_setColor(_LI *li, int color)
{
 li->color=color;
 return 0;
}

//显示粒子
int li_draw(_LI *li)
{
 int i;
 for(i=0;i<li->size;i++)
 {
  _POINT *point= &(li->point[i]);
  if(point->hp>0)
  drawCir(point->x,point->y,point->r, (point->alpha<<24) | point->color);
 }
 
 return 0;
}



//删除粒子
int li_free(_LI *li)
{
 free(li->point);
 free(li);
 return 0;
}











































