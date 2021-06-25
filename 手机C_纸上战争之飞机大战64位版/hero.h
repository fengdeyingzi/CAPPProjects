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


//�������� ���������飬�ӵ�
_HERO *hero_create(int bitmap)
{
 int32 sprite;
 int32 bitmap_zidan=readBitmapFromAssets("zidan.png");
 printf("hero �����ӵ� \n");
 _ZIDAN *zidan=z_create(bitmap_zidan,1);
 _HERO *hero = malloc(sizeof(_HERO));
 memset(hero,0,sizeof(_HERO));
 hero->zidan = zidan;
 hero->bitmap=bitmap;
 hero->bitmap_zidan=bitmap_zidan;
 //hero->bitmap=readBitmapFromAssets("hero1.png");
 printf("hero �������� \n");
 hero->sprite=sp_read("hero1.sprite",hero->bitmap);
 printf("�����ȡ��� \n");
 hero->hp=100;
 hero->lv=1;
 
 hero->zidan=zidan;
 //�����ӵ�
 printf("�����ӵ� \n");
 z_setv(hero->zidan,8);
 printf("�����ӵ���� \n");
 z_setDirection(hero->zidan,270);
 printf("���÷��� \n");
 hero_setxy(hero,0,0);
 printf("���Ǵ������ \n");
 return hero;
};

//����
void hero_draw(_HERO *hero)
{
 sp_draw(hero->sprite,NULL);
}
//��������Ƿ񱻰���
int hero_isImpact(_HERO *hero,int x,int y)
{
 return sp_impact(hero->sprite,x,y);
}

//��ȡ�ӵ�
_ZIDAN *hero_getZidan(_HERO *hero)
{
 return hero->zidan;
};

//����һ���ӵ�
_ZIDAN *hero_createZidan(_HERO *hero)
{
 _ZIDAN *zidan=z_copy(hero->zidan);
 z_setxy(zidan,hero->x,hero->y);
 return zidan;
};

//������������
void hero_setxy(_HERO *hero,int x,int y)
{
 
 hero->x=x;
 hero->y=y;
 printf("hero ���� \n");
 sp_setxy(hero->sprite, x-32,y-2);
 printf("����������� \n");
}
//��ȡ��������
int hero_getx(_HERO *hero)
{
 return hero->x;
}

int hero_gety(_HERO *hero)
{
 return hero->y;
}

//�����ƶ�
void hero_move(_HERO *hero,int x,int y)
{
 hero->x+=x;
 hero->y+=y;
 sp_move(hero->sprite,x,y);
}
//�ͷ�
int hero_free(_HERO *hero)
{
 //bitmapFree(hero->bitmap);
 sp_free(hero->sprite);
 z_distory(hero->zidan);
 free(hero);
 return 0;
}

#endif

