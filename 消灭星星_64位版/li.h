
#ifndef _LI_H_
#define _LI_H_
#include <base.h>
#include <graphics.h>
#include <android.h>
#include <ex_math.h>



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
 int32 bitmap; //粒子图片
 int x;
 int y; //粒子发生点 坐标
 int r; //宽度
 int v; //速度
 int min_v; //最小速度
 int size; //粒子数量
 int birth; //出生量
 int speed; //粒子递减量
 int hp; //生命
 int color; //颜色 rgb值
 int coreColor; //核心颜色
 int isRandColor; //是否产生随机颜色
 int isDirection; //是否有方向
 int direction;//风向
 int isFirst; //是否只生成一次
 int time; //粒子运行时间
} _LI;



//创建粒子
_LI *li_create(int x,int y)
{
 _LI *li = malloc(sizeof(_LI));
 li->x=x;
 li->y=y;
 li->r=5;
 li->v=2;
 li->min_v=4;
 li->bitmap=0;
 li->isRandColor=FALSE;
 li->speed=20;
 li->isDirection=FALSE;
 li->direction=270;
 li->hp= 20;
 li->birth=6;
 li->size=400;
 li->time=0;
 li->point = malloc(sizeof(_POINT)*li->size);
 memset(li->point,0,sizeof(_POINT)*li->size);
 li->color=0xffffff;
 li->coreColor=0xffffff;
 
 return li;
};

int li_start(_LI *li)
{
 memset(li->point,0,sizeof(_POINT)*li->size);
 
 return 0;
}

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
   //判断是否为第一次生成
   if((point->x!=0) && (point->y!=0) && li->isFirst) break;

  point->hp=li->hp;
  point->x=li->x;
  point->y=li->y;
  point->alpha=255;
  int alpha=point->alpha;
  point->color=li->color;
  if(li->isRandColor)
  point->color|=rand()%0xffffff;
  point->r=li->r;
  point->speed_x=-3+rand()%6;
  point->speed_y=-3+rand()%6;
  int x,y;
  int v=( (rand()%(li->v - li->min_v+1)) +li->min_v)*100+10;
 // printf("%d\n",v);
  toSpin(0,0, v, v, rand()%360, &x,&y);
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
  int x,y;
  int v=200;
  if(li->isDirection)
  {
   toSpin(0,0, v, v, li->direction, &x,&y);
   point->speed_x+=((float)x)/100;
  point->speed_y+=((float)y)/100;
  }
  point->hp--;
  point->alpha-=li->speed;
  if(point->alpha<0)
  point->alpha=0;
 }
 
 li->time++;
 
 return 0;
}
//设置粒子速度
int li_setV(_LI *li,int v)
{
 
 li->v=v;
 return 0;
}

//设置粒子只生成一次
int li_setFirst(_LI *li)
{
 li->isFirst=TRUE;
 return 0;
}

//设置粒子图片
int li_setBitmap(_LI *li, int bitmap)
{
 li->bitmap= bitmap;
 return 0;
}

//设置粒子只生成一次

//获取粒子播放时间
int li_getTime(_LI *li)
{
 
 return li->time;
}



//设置粒子透明度递减量量
int li_setSpeed(_LI *li, int speed)
{
 li->speed=speed;
 
 return 0;
}

//设置粒子生成角度
int li_setDirection(_LI *li, int direction)
{
  li->isDirection=TRUE;
  li->direction=direction;
return 0;
}


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
 if(li->point) free(li->point);
 li->point = malloc(sizeof(_POINT)*li->size);
 memset(li->point,0,sizeof(_POINT)*li->size);
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
 int r,g,b;
 
 //如果是图片
 if(li->bitmap)
 {
  for(i=0;i<li->size;i++)
  {
   _POINT *point= &(li->point[i]);
   if( point->hp>0 )
   drawBitmapRotate(li->bitmap, point->x,point->y,0,0, 0, point->alpha);
  }
  
 }
 else
 {
 for(i=0;i<li->size;i++)
 {
  _POINT *point= &(li->point[i]);
   if(point->hp>0 && point->x>=0 &&point->x<SCRW && point->y>=0 && point->y<SCRH)
   {
   r= (point->color>>16) & 0xff;
   g= (point->color>>8) & 0xff;
   b= (point->color)&0xff;
   r= r+(255-r)*point->alpha/255;
   g= g+(255-g)*point->alpha/255;
   b= b+(255-b)*point->alpha/255;
  drawCir(point->x,point->y,point->r, (point->alpha<<24) | (r<<16) | (g<<8) | b); 
//  drawCir(point->x,point->y,point->r/2,  (point->alpha<<24) | point->color);
  //dpoint(point->x,point->y,point->color);
  }
 }
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












#endif






























