#ifndef _GAME_H_
#define _GAME_H_

#include "baozha.h"
#include "array.h"
#include "map.h"
#include "zidan.h"
#include "hero.h"
#include "plan.h"


typedef struct
{
 int32 time; //时间
 _HERO *hero;
 _PLAN *plan;
 int32 bitmap_map;
 int32 bitmap_baozha;
 _BAOZHA *baozha;
 _ARRAY *array_baozha;
 _MAP *map;
 _ARRAY *array_zidan;
 _ARRAY *array_plan;
 int32 scene;
 int32 bitmap_hero;
 int32 bitmap_plan1;
 int32 bitmap_plan2;
 int32 bitmap_plan3;
 int32 bitmap_plan4;
 int32 bitmap_plan5;
} _GAME;


//创建游戏
_GAME *game_create()
{
 _GAME *game=malloc(sizeof(_GAME));
 memset(game,0,sizeof(_GAME));
 printf("读取图片 \n");
 game->bitmap_hero= readBitmapFromAssets("hero1.png");
 game->bitmap_plan1=readBitmapFromAssets("plane0.png");
 game->bitmap_plan2=readBitmapFromAssets("plane3.png");
 game->bitmap_plan3=readBitmapFromAssets("plane20.png");
 game->bitmap_plan4=readBitmapFromAssets("plane40.png");
 game->bitmap_plan5=readBitmapFromAssets("plane41.png");
 printf("创建主角 \n");
 game->hero = hero_create(game->bitmap_hero);
 
 printf("创建地图 \n");
 game->bitmap_map=readBitmapFromAssets("bg_01.png");
 //地图
 game->map=map_create(game->bitmap_map);
 
 //子弹
 game->array_zidan=array_create();
 //敌机
 game->array_plan=array_create();
 //爆炸
 game->bitmap_baozha = readBitmapFromAssets("guang.png");
 game->array_baozha = array_create();
 game->baozha = bao_create(game->bitmap_baozha);
 
 
 game->plan = plan_create(game->bitmap_plan1, game->bitmap_plan2, game->bitmap_plan3, game->bitmap_plan4, game->bitmap_plan5);
 hero_setxy(game->hero,SCRW/2,SCRH*3/4);
 
 printf("游戏场景 \n");
 
 return game;
};

//设置关卡
int game_setScene(_GAME *game,int32 type)
{
 game->scene=type;
 return 0;
}

int isDown;
int hx,hy;
//event事件
int game_event(_GAME *game,int type,int p1,int p2)
{
 if(type==MS_DOWN)
 {
  hx=p1;
  hy=p2;
  if(hero_isImpact(game->hero,p1,p2))
  {
   isDown=TRUE;
  }
  else isDown = FALSE;
 }
 else if(type==MS_MOVE)
 {
  if(isDown)
  hero_move(game->hero,p1-hx,p2-hy);
  hx=p1;
  hy=p2;
 }
 else if(type==MS_UP)
 {
  isDown = FALSE;
 }
 
 if(type==KY_UP)
 {
  if(p1==_BACK)
  {
   win_set(WIN_MAIN);
  }
 }
 
 return 0;
}
//销毁当前场景
int game_sceneDestory(_GAME *game)
{
 
 return 0;
}
//飞机运行事件
int game_run(_GAME *game)
{
 _ZIDAN *zidan;
 _PLAN *plan;
 _BAOZHA *baozha;
 printf("gamerun \n");
 int i,j;
 int power;
 game->time++;
 //地图
 map_move(game->map);
 //创建子弹
 if(game->time%8==0)
 {
  zidan=hero_createZidan(game->hero);
  //printf("创建zidan %d\n",game->array_zidan->len);
  array_append(game->array_zidan,(int)zidan);
 }
 
 //飞机运行
 for(i=0;i<array_getlen(game->array_plan);i++)
 {
  plan= (void*)array_get(game->array_plan,i);
  plan_run(plan);
 }
 
 //创建飞机
 if(game->time%50==0)
 {
  plan = plan_copy(game->plan);
  array_append(game->array_plan, (int)plan);
  plan_setxy(plan,rand()%SCRW,0);
  //printf("飞机数量%d \n",game->array_plan->len);
 }
 
 //子弹运行
 //子弹销毁
 //子弹与敌机碰撞
 for(i=0;i<array_getlen(game->array_zidan);i++)
 {
  zidan=(void*)array_get(game->array_zidan,i);
  z_run(zidan);
  if(z_isDestory(zidan))
  {
   array_delete(game->array_zidan,i);
   //printf("销毁子弹%d \n", array_getlen(game->array_zidan));
   z_distory(zidan);
  }
  else
  {
   power=z_getPower(zidan);
   for(j=0;j<array_getlen(game->array_plan);j++)
   {
    plan=(void*)array_get(game->array_plan,j);
   if(plan_impact(plan,z_getx(zidan),z_gety(zidan)))
    {
     //打中飞机
     plan_subtractHp(plan,z_getPower(zidan));
     z_setDistory(zidan,0);
    }
   }
  }
 }
 
 //销毁飞机
 for(i=0;i<array_getlen(game->array_plan);i++)
 {
 plan=(void*)array_get(game->array_plan,i);
 if(plan_getHp(plan)<=0)
 {
  //从数组中删除
  array_delete(game->array_plan,i);

  //添加爆炸效果
  baozha = bao_copy(game->baozha);
  array_append(game->array_baozha, (int)baozha);
  bao_setxy(baozha, plan_getx(plan),plan_gety(plan));
    //释放
  plan_free(plan);
 }
 }
 //爆炸运行/销毁爆炸特效
 for(i=0;i<array_getlen(game->array_baozha);i++)
 {
  baozha = (void*)array_get(game->array_baozha,i);
  bao_run(baozha);
  if(bao_isDestory(baozha))
  {
   bao_free(baozha);
   array_delete(game->array_baozha,i);
  }
 }
 
 
 
 return 0;
}
//我方子弹运行 并检测子弹与飞机的碰撞
//敌方子弹运行 并检测碰撞
int game_zidanRun(_GAME *game)
{
 
 return 0;
}


//主角运行 并检测主角与敌机的碰撞 检测道具与主角的碰撞
int game_heroRun(_GAME *game)
{
 
 return 0;
}

//道具下落事件
int game_resource(_GAME *game)
{
 
 return 0;
}
//绘制所有场景
int game_drawAll(_GAME *game)
{
 int i;
_ZIDAN *zidan;
 _PLAN *plan;
_BAOZHA *baozha;
printf("draw \n");
  //显示地图
 map_draw(game->map);
 //显示飞机
 hero_draw(game->hero);

 //画背景
 
 //画主角
 
 //画敌机
 for(i=0;i<array_getlen(game->array_plan);i++)
 {
  plan= (void*)array_get(game->array_plan,i);
  plan_draw(plan);
  //printf("显示飞机%d %d \n",plan->x,plan->y);
 }
 //printf("绘制敌机完成 \n");
 //画子弹
 for(i=0;i<array_getlen(game->array_zidan);i++)
 {
  zidan=(void*)array_get(game->array_zidan,i);
  z_draw(zidan);
 }
 //画爆炸
 for(i=0;i<array_getlen(game->array_baozha);i++)
 {
  baozha = (void*)array_get(game->array_baozha,i);
  bao_draw(baozha);
 }
  //刷新
 ref(0,0,SCRW,SCRH);
 return 0;
}

//释放
int game_free(_GAME *game)
{
 int i;
 _PLAN *plan;
 //释放地图
 map_free(game->map);
 bitmapFree(game->bitmap_map);
 //释放主角
 hero_free(game->hero);
 bitmapFree(game->bitmap_hero);
 //爆炸
 bitmapFree(game->bitmap_baozha);
 for(i=0;i<array_getlen(game->array_baozha);i++)
 {
  bao_free((void*)array_get(game->array_baozha,i));
 }
 array_free(game->array_baozha);
 //释放飞机
 bitmapFree(game->bitmap_plan1);
 bitmapFree(game->bitmap_plan2);
 bitmapFree(game->bitmap_plan3);
 bitmapFree(game->bitmap_plan4);
 bitmapFree(game->bitmap_plan5);
 //释放子弹
 for(i=0;i<array_getlen(game->array_zidan);i++)
 {
  z_distory((void*)array_get(game->array_zidan,i));
 }
 array_free(game->array_zidan);
 
 //释放敌机
 for(i=0;i<array_getlen(game->array_plan);i++)
 {
  plan= (void*)array_get(game->array_plan,i);
  plan_free(plan);
  //printf("显示飞机%d %d \n",plan->x,plan->y);
 }
 array_free(game->array_plan);
 //释放道具
 return 0;
}












#endif