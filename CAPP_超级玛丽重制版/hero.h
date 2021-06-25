#ifndef _HERO_H_
#define _HERO_H_

#include "base.h"
#include "ex_game.h"
#include "map.h"
#include "enemy.h"

typedef struct
{
    int type; //状态
    int action; //人物动作
    int x; // x坐标
    int y; // y坐标
    int hp; //生命
    int isjump; //是否悬空
    int isColak; //是否隐身
    int colak_time; //隐身时间
    int iskey; //是否按下跳跃键
    int wv; //横向速度
    int hv; //纵向速度
    int bitmap;
    int sprite; //精灵
} _HERO;

enum
{
    HERO_STAND, //静止
    HERO_RUN, //运动
    HERO_JUMP, //跳
    HERO_DOWN, //下蹲
    HERO_DIE =7 //死亡
};

extern int itemw;///图块大小
extern int camera;
extern struct TILED_LA *tiled;

//创建主角
void *hero_create(char *filename,char *bitmapname)
{
 _HERO *hero=malloc(sizeof(_HERO));
 memset(hero,0,sizeof(_HERO));
 hero->bitmap= readBitmapFromAssets(bitmapname);
 hero->sprite= sp_read(filename,hero->bitmap);
 hero->hp=1;
 return hero;
}

//设置主角位置
int hero_setxy(_HERO *hero,int x, int y)
{
 hero->x=x;
 hero->y=y;
 sp_setxy(hero->sprite,x,y);
 return 0;
}
//主角运动事件
void hero_run(_HERO *hero)
{
 int sprite=hero->sprite;
 int hero_action=hero->action;
 int isjump=hero->isjump;
 int iskey=hero->iskey;
 //printf("判断主角是否死亡\n");
 if(hero->hp<=0)
 {
  hero_action=HERO_DIE;
 }
 //printf("加载主角\n");
 if(hero_action==HERO_DIE)
 {
  hero->y+=4;
 }
 else
 {
  //判断按键
  if(getkeypressed(_LEFT)==0)
  {
   if(hero_action==HERO_STAND && !isjump)
   {
    hero_action=HERO_RUN;
   }

   hero->x-=4;
   if(tiled_getData(tiled,hero->x/itemw,hero->y/itemw)) hero->x+=4;
   if(hero->x<0)hero->x=0;
   if(hero->x<ca_getx(camera))
    hero->x+=4;

  }
  else if(getkeypressed(_RIGHT)==0)
  {
   if(hero_action==HERO_STAND && !isjump)
   {
    hero_action=HERO_RUN;
   }
   hero->x+=4;
   if(tiled_getData(tiled,(hero->x+itemw-1)/itemw,hero->y/itemw)) hero->x-=4;
  }
  else
  {
   if(hero_action==HERO_RUN)
   {
    hero_action=HERO_STAND;
   }
  }
  //printf("检测跳跃\n");


  if(getkeypressed(_POUND)==0)
  {

   if(hero_action!=HERO_JUMP && !iskey && !isjump)
   {
    hero->iskey=1;
    hero_action=HERO_JUMP;
    isjump=1;
   }
   if(hero->iskey)
   {
    if(hero->iskey==1)
     hero->hv-=8;
    if(hero->iskey==3)
     hero->hv-=8;
    hero->iskey++;
   }
   //判断是否落到地上

  }
  else
  {
   hero->iskey=0;
  }
  //printf("下落\n");
  //重力下落
  hero->hv++;
  if(hero->hv>=6)hero->hv=6;
  hero->y+=hero->hv;
  //判断脚碰撞
  if (tiled_getData(tiled,(hero->x+1)/20,(hero->y+19)/20) || tiled_getData(tiled,(hero->x+19)/20,(hero->y+19)/20))
  {
   hero->y-=hero->y%itemw;
   if(hero_action==HERO_JUMP)
   {
    hero_action=HERO_STAND;
   }
   isjump=0;
   if(hero->hv>0)
    hero->hv=0;
  }
  else
  {
   isjump=1;
   //判断头部是否撞到墙
   if (tiled_getData(tiled,(hero->x+1)/20,(hero->y)/20) || tiled_getData(tiled,(hero->x+19)/20,(hero->y)/20))
    if(hero->hv<0)
     hero->hv=-hero->hv;
  }
 }
 if(hero_action!=sp_getAction(sprite)) sp_setAction(sprite,hero_action);
 sp_setxy(sprite,hero->x,hero->y);
 hero->action=hero_action;
 hero->isjump=isjump;
 //printf("主角加载完成\n");
}

//设置主角状态
void hero_setType(_HERO *hero,int type)
{
 hero->type= type;
 sp_setAction(hero->sprite,type);
}

//设置主角隐身
//参数：是否隐身，隐身时间ms
void hero_setColak(_HERO *hero,int isColak,int time)
{
 hero->isColak= isColak;
 hero->colak_time=time;
}

//销毁主角
int hero_free(_HERO *hero)
{
 //销毁精灵
 sp_free(hero->sprite);
 //销毁bitmap
 bitmapFree(hero->bitmap);
 //销毁hero
 free(hero);
 return 0;
}





#endif







