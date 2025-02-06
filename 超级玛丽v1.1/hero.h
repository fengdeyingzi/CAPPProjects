#ifndef _HERO_H_
#define _HERO_H_

#include <base.h>
#include <ex_game.h>

typedef struct
{
 int action; //���ﶯ��
 int x; // x����
 int y; // y����
 int hp; //����
 int isjump; //�Ƿ�����
 int isColak; //�Ƿ�����
 int colak_time; //����ʱ��
 int iskey; //�Ƿ�����Ծ��
 int wv; //�����ٶ�
 int hv; //�����ٶ�
 int bitmap;
 int sprite; //����
} _HERO;

enum
{
 HERO_STAND, //��ֹ
 HERO_RUN, //�˶�
 HERO_JUMP, //��
 HERO_DOWN, //�¶�
 HERO_DIE =7 //����
 };

//��������
void *hero_create(char *filename,char *bitmapname)
{
 _HERO *hero=malloc(sizeof(_HERO));
 memset(hero,0,sizeof(_HERO));
 hero->bitmap= readBitmapFromAssets(bitmapname);
 hero->sprite= sp_read(filename,hero->bitmap);
 hero->hp=1;
 return hero;
}

//��������λ��
int hero_setxy(_HERO *hero,int x, int y)
{
 hero->x=x;
 hero->y=y;
 sp_setxy(hero->sprite,x,y);
 return 0;
}
//�����˶��¼�
void hero_run(_HERO *hero)
{
 int sprite=hero->sprite;
 int hero_action=hero->action;
 int isjump=hero->isjump;
 int iskey=hero->iskey;
 //printf("�ж������Ƿ�����\n");
 if(hero->hp<=0)
 {
  hero_action=HERO_DIE;
 }
 //printf("��������\n");
 if(hero_action==HERO_DIE)
 {
  hero->y+=4;
 }
 else
 {
    //�жϰ���
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
 //printf("�����Ծ\n");
 
 
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
  //�ж��Ƿ��䵽����
  
 }
 else
 {
  hero->iskey=0;
 }
 //printf("����\n");
 //��������
 hero->hv++;
 if(hero->hv>=6)hero->hv=6;
 hero->y+=hero->hv;
 //�жϽ���ײ
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
  //�ж�ͷ���Ƿ�ײ��ǽ
  if (tiled_getData(tiled,(hero->x+1)/20,(hero->y)/20) || tiled_getData(tiled,(hero->x+19)/20,(hero->y)/20))
  if(hero->hv<0)
  hero->hv=-hero->hv;
 }
 }
if(hero_action!=sp_getAction(sprite)) sp_setAction(sprite,hero_action);
 sp_setxy(sprite,hero->x,hero->y);
 hero->action=hero_action;
 hero->isjump=isjump;
 //printf("���Ǽ������\n");
}

//��������״̬
void hero_setType(_HERO *hero,int type)
{
 hero->type= type;
 sp_setAction(hero->sprite,type);
}

//������������
//�������Ƿ���������ʱ��ms
void hero_setColak(_HERO *hero,int isColak,int time)
{
 hero->isColak= isColak;
 hero->colak_time=time;
}

//��������
int hero_free(_HERO *hero)
{
 //���پ���
 sp_free(hero->sprite);
 //����bitmap
 bitmapFree(hero->bitmap);
 //����hero
 free(hero);
 return 0;
}





#endif







