
#ifndef _PLAN_H_
#define _PLAN_H_

#include <graphics.h>
#include <ex_game.h>
//敌机

typedef struct
{
 int32 sprite;
 int32 sprite_1; //敌机精灵缓存
 int32 sprite_2;
 int32 sprite_3;
 int32 sprite_4;
 int32 sprite_5;
 int x; //显示坐标
 int y;
 int w;
 int h;
 int ux; //计算坐标(是显示坐标的10倍)
 int uy;
 int v; //速度
 int hp; //生命值
 int lv; //等级
 int32 time; //运行时间
 int direction; //方向
 
} _PLAN;

//创建敌机
_PLAN *plan_create(int32 bitmap_1,int32 bitmap_2,int32 bitmap_3,int32 bitmap_4,int32 bitmap_5)
{
 _PLAN *plan = malloc(sizeof(_PLAN));
 memset(plan,0,sizeof(_PLAN));
 int sprite_1,sprite_2,sprite_3,sprite_4,sprite_5;
 sprite_1=sp_read("plane0.sprite",bitmap_1);
 sprite_2=sp_read("plane3.sprite",bitmap_2);
 sprite_3=sp_read("plane20.sprite",bitmap_3);
 sprite_4=sp_read("plane40.sprite",bitmap_4);
 sprite_5=sp_read("plane41.sprite",bitmap_5);
 plan->sprite_1 = sprite_1;
 plan->sprite_2 = sprite_2;
 plan->sprite_3 = sprite_3;
 plan->sprite_4 = sprite_4;
 plan->sprite_5 = sprite_5;
 plan->sprite=sprite_1;
 plan->v=100;
 plan->direction=90;
 plan->hp=30;
 return plan;
};

//复制一个飞机
_PLAN *plan_copy(_PLAN *plan)
{
 _PLAN *temp=malloc(sizeof(_PLAN));
 memcpy(temp,plan,sizeof(_PLAN));
 
 temp->sprite_1=sp_copy(plan->sprite_1);
 temp->sprite_2=sp_copy(plan->sprite_2);
 temp->sprite_3=sp_copy(plan->sprite_3);
 temp->sprite_4=sp_copy(plan->sprite_4);
 temp->sprite_5=sp_copy(plan->sprite_5);
 temp->sprite=temp->sprite_1;
 return temp;
};

//消耗生命值
void plan_subtractHp(_PLAN *plan, int num)
{
 plan->hp-=num;
}

//获取生命值
int plan_getHp(_PLAN *plan)
{
 return plan->hp;
}

int plan_getx(_PLAN *plan)
{
 return plan->x+sp_getWidth(plan->sprite)/2;
}

int plan_gety(_PLAN *plan)
{
 return plan->y+sp_getHeight(plan->sprite)/2;
}

//设置敌机类型
int plan_setType(_PLAN *plan,int type)
{
 switch(type)
 {
  case 0:
  plan->sprite=sprite_1;
  
  break;
  case 1:
  plan->sprite=sprite_1;
  break;
  
  case 2:
  plan->sprite=sprite_2;
  break;
  case 3:
  plan->sprite=sprite_3;
  break;
  
  case 4:
  plan->sprite=sprite_4;
  break;
  
  case 5:
  plan->sprite=sprite_5;
  break;
  
 }
 plan->w=sp_getWidth(plan->sprite);
  plan->h=sp_getHeight(plan->sprite);
 return 0;
}

//设置速度
void plan_setv(_PLAN *plan,int v)
{
 plan->v=v*10;
}

//设置xy
void plan_setxy(_PLAN *plan,int x,int y)
{
 plan->x=x;
 plan->y=y;
 plan->ux=x*10;
 plan->uy=y*10;
 sp_setxy(plan->sprite,x,y);
}

//飞机运行
void plan_run(_PLAN *plan)
{
 if(plan->hp>0)
 {
 toSpin(plan->ux,plan->uy,plan->v,plan->v,plan->direction, &(plan->ux),&(plan->uy));
 plan->x=plan->ux/10;
 plan->y=plan->uy/10;
 sp_setxy(plan->sprite,plan->x,plan->y);
 plan->time++;
 }
 if(plan->y>SCRH)
 plan->hp=0;
}

//画飞机
void plan_draw(_PLAN *plan)
{
 sp_draw(plan->sprite,NULL);
 //drect(plan->x,plan->y,30,30,240,240,240);
}

//飞机是否点中
int plan_impact(_PLAN *plan,int x,int y)
{
 return sp_impact(plan->sprite,x,y);
}


//销毁
int plan_free(_PLAN *plan)
{
 sp_free(plan->sprite_1);
 sp_free(plan->sprite_2);
 sp_free(plan->sprite_3);
 sp_free(plan->sprite_4);
 sp_free(plan->sprite_5);
 
 free(plan);
return 0;
}

#endif
