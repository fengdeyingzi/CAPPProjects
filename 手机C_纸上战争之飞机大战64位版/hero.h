#ifndef _HERO_H_
#define _HERO_H_
#include "zidan.h"
#include <ex_game.h>

typedef struct
{
 int32 bitmap;
 int32 bitmap_zidan;
 int32 sprite;
 int x;
 int y;
 int lv;
 int hp;
 _ZIDAN *zidan;
} _HERO;


//创建主角 参数：精灵，子弹
_HERO *hero_create(int bitmap)
{
 int32 sprite;
 int32 bitmap_zidan=readBitmapFromAssets("zidan.png");
 printf("hero 创建子弹 \n");
 _ZIDAN *zidan=z_create(bitmap_zidan,1);
 _HERO *hero = malloc(sizeof(_HERO));
 memset(hero,0,sizeof(_HERO));
 hero->zidan = zidan;
 hero->bitmap=bitmap;
 hero->bitmap_zidan=bitmap_zidan;
 //hero->bitmap=readBitmapFromAssets("hero1.png");
 printf("hero 创建精灵 \n");
 hero->sprite=sp_read("hero1.sprite",hero->bitmap);
 printf("精灵读取完成 \n");
 hero->hp=100;
 hero->lv=1;
 
 hero->zidan=zidan;
 //设置子弹
 printf("设置子弹 \n");
 z_setv(hero->zidan,8);
 printf("设置子弹完成 \n");
 z_setDirection(hero->zidan,270);
 printf("设置方向 \n");
 hero_setxy(hero,0,0);
 printf("主角创建完成 \n");
 return hero;
};

//绘制
void hero_draw(_HERO *hero)
{
 sp_draw(hero->sprite,NULL);
}
//检测主角是否被按下
int hero_isImpact(_HERO *hero,int x,int y)
{
 return sp_impact(hero->sprite,x,y);
}

//获取子弹
_ZIDAN *hero_getZidan(_HERO *hero)
{
 return hero->zidan;
};

//发射一颗子弹
_ZIDAN *hero_createZidan(_HERO *hero)
{
 _ZIDAN *zidan=z_copy(hero->zidan);
 z_setxy(zidan,hero->x,hero->y);
 return zidan;
};

//设置主角坐标
void hero_setxy(_HERO *hero,int x,int y)
{
 
 hero->x=x;
 hero->y=y;
 printf("hero 精灵 \n");
 sp_setxy(hero->sprite, x-32,y-2);
 printf("精灵设置完成 \n");
}
//获取主角坐标
int hero_getx(_HERO *hero)
{
 return hero->x;
}

int hero_gety(_HERO *hero)
{
 return hero->y;
}

//主角移动
void hero_move(_HERO *hero,int x,int y)
{
 hero->x+=x;
 hero->y+=y;
 sp_move(hero->sprite,x,y);
}
//释放
int hero_free(_HERO *hero)
{
 //bitmapFree(hero->bitmap);
 sp_free(hero->sprite);
 z_distory(hero->zidan);
 free(hero);
 return 0;
}

#endif

