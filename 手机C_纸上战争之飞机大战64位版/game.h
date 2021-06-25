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
 int32 time; //ʱ��
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


//������Ϸ
_GAME *game_create()
{
 _GAME *game=malloc(sizeof(_GAME));
 memset(game,0,sizeof(_GAME));
 printf("��ȡͼƬ \n");
 game->bitmap_hero= readBitmapFromAssets("hero1.png");
 game->bitmap_plan1=readBitmapFromAssets("plane0.png");
 game->bitmap_plan2=readBitmapFromAssets("plane3.png");
 game->bitmap_plan3=readBitmapFromAssets("plane20.png");
 game->bitmap_plan4=readBitmapFromAssets("plane40.png");
 game->bitmap_plan5=readBitmapFromAssets("plane41.png");
 printf("�������� \n");
 game->hero = hero_create(game->bitmap_hero);
 
 printf("������ͼ \n");
 game->bitmap_map=readBitmapFromAssets("bg_01.png");
 //��ͼ
 game->map=map_create(game->bitmap_map);
 
 //�ӵ�
 game->array_zidan=array_create();
 //�л�
 game->array_plan=array_create();
 //��ը
 game->bitmap_baozha = readBitmapFromAssets("guang.png");
 game->array_baozha = array_create();
 game->baozha = bao_create(game->bitmap_baozha);
 
 
 game->plan = plan_create(game->bitmap_plan1, game->bitmap_plan2, game->bitmap_plan3, game->bitmap_plan4, game->bitmap_plan5);
 hero_setxy(game->hero,SCRW/2,SCRH*3/4);
 
 printf("��Ϸ���� \n");
 
 return game;
};

//���ùؿ�
int game_setScene(_GAME *game,int32 type)
{
 game->scene=type;
 return 0;
}

int isDown;
int hx,hy;
//event�¼�
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
//���ٵ�ǰ����
int game_sceneDestory(_GAME *game)
{
 
 return 0;
}
//�ɻ������¼�
int game_run(_GAME *game)
{
 _ZIDAN *zidan;
 _PLAN *plan;
 _BAOZHA *baozha;
 printf("gamerun \n");
 int i,j;
 int power;
 game->time++;
 //��ͼ
 map_move(game->map);
 //�����ӵ�
 if(game->time%8==0)
 {
  zidan=hero_createZidan(game->hero);
  //printf("����zidan %d\n",game->array_zidan->len);
  array_append(game->array_zidan,(int)zidan);
 }
 
 //�ɻ�����
 for(i=0;i<array_getlen(game->array_plan);i++)
 {
  plan= (void*)array_get(game->array_plan,i);
  plan_run(plan);
 }
 
 //�����ɻ�
 if(game->time%50==0)
 {
  plan = plan_copy(game->plan);
  array_append(game->array_plan, (int)plan);
  plan_setxy(plan,rand()%SCRW,0);
  //printf("�ɻ�����%d \n",game->array_plan->len);
 }
 
 //�ӵ�����
 //�ӵ�����
 //�ӵ���л���ײ
 for(i=0;i<array_getlen(game->array_zidan);i++)
 {
  zidan=(void*)array_get(game->array_zidan,i);
  z_run(zidan);
  if(z_isDestory(zidan))
  {
   array_delete(game->array_zidan,i);
   //printf("�����ӵ�%d \n", array_getlen(game->array_zidan));
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
     //���зɻ�
     plan_subtractHp(plan,z_getPower(zidan));
     z_setDistory(zidan,0);
    }
   }
  }
 }
 
 //���ٷɻ�
 for(i=0;i<array_getlen(game->array_plan);i++)
 {
 plan=(void*)array_get(game->array_plan,i);
 if(plan_getHp(plan)<=0)
 {
  //��������ɾ��
  array_delete(game->array_plan,i);

  //��ӱ�ըЧ��
  baozha = bao_copy(game->baozha);
  array_append(game->array_baozha, (int)baozha);
  bao_setxy(baozha, plan_getx(plan),plan_gety(plan));
    //�ͷ�
  plan_free(plan);
 }
 }
 //��ը����/���ٱ�ը��Ч
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
//�ҷ��ӵ����� ������ӵ���ɻ�����ײ
//�з��ӵ����� �������ײ
int game_zidanRun(_GAME *game)
{
 
 return 0;
}


//�������� �����������л�����ײ �����������ǵ���ײ
int game_heroRun(_GAME *game)
{
 
 return 0;
}

//���������¼�
int game_resource(_GAME *game)
{
 
 return 0;
}
//�������г���
int game_drawAll(_GAME *game)
{
 int i;
_ZIDAN *zidan;
 _PLAN *plan;
_BAOZHA *baozha;
printf("draw \n");
  //��ʾ��ͼ
 map_draw(game->map);
 //��ʾ�ɻ�
 hero_draw(game->hero);

 //������
 
 //������
 
 //���л�
 for(i=0;i<array_getlen(game->array_plan);i++)
 {
  plan= (void*)array_get(game->array_plan,i);
  plan_draw(plan);
  //printf("��ʾ�ɻ�%d %d \n",plan->x,plan->y);
 }
 //printf("���Ƶл���� \n");
 //���ӵ�
 for(i=0;i<array_getlen(game->array_zidan);i++)
 {
  zidan=(void*)array_get(game->array_zidan,i);
  z_draw(zidan);
 }
 //����ը
 for(i=0;i<array_getlen(game->array_baozha);i++)
 {
  baozha = (void*)array_get(game->array_baozha,i);
  bao_draw(baozha);
 }
  //ˢ��
 ref(0,0,SCRW,SCRH);
 return 0;
}

//�ͷ�
int game_free(_GAME *game)
{
 int i;
 _PLAN *plan;
 //�ͷŵ�ͼ
 map_free(game->map);
 bitmapFree(game->bitmap_map);
 //�ͷ�����
 hero_free(game->hero);
 bitmapFree(game->bitmap_hero);
 //��ը
 bitmapFree(game->bitmap_baozha);
 for(i=0;i<array_getlen(game->array_baozha);i++)
 {
  bao_free((void*)array_get(game->array_baozha,i));
 }
 array_free(game->array_baozha);
 //�ͷŷɻ�
 bitmapFree(game->bitmap_plan1);
 bitmapFree(game->bitmap_plan2);
 bitmapFree(game->bitmap_plan3);
 bitmapFree(game->bitmap_plan4);
 bitmapFree(game->bitmap_plan5);
 //�ͷ��ӵ�
 for(i=0;i<array_getlen(game->array_zidan);i++)
 {
  z_distory((void*)array_get(game->array_zidan,i));
 }
 array_free(game->array_zidan);
 
 //�ͷŵл�
 for(i=0;i<array_getlen(game->array_plan);i++)
 {
  plan= (void*)array_get(game->array_plan,i);
  plan_free(plan);
  //printf("��ʾ�ɻ�%d %d \n",plan->x,plan->y);
 }
 array_free(game->array_plan);
 //�ͷŵ���
 return 0;
}












#endif