
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "array.h"
#include "readtext.h"
#include "map.h"
#include "hero.h"

typedef struct
{
 int type; //���˵����� 0Ģ�� 1�ڹ�
 int x; //���˳��ֵ�λ��
 int y; //���˳��ֵ�����
 int direction; //�˶�����
 int sprite; //����
} _ENEMY;



typedef struct
{
 int load; //����
 int size; //��������
 int bitmap_mogu;
 int bitmap_turtle;
 int bitmap_flower;
 _ARRAY *enemys; //���е���
} _EN_TASK;

typedef struct
{
 int bitmap;
 int width;
 int height;
 int itemw;
 int itemh;
 int *sprite;
 int *data;
 _EN_TASK *en_task;
 int world;
 int camera;
 } _TILED;


//��ʼ�����е���
void *en_create(char *filename)
{
 _EN_TASK *task=malloc(sizeof(_EN_TASK));
 memset(task,0,sizeof(_EN_TASK));
 printf("����bitmap\n");
 task->bitmap_mogu=readBitmapFromAssets("mogu.png");
 task->bitmap_turtle=readBitmapFromAssets("turtle.png");
 task->bitmap_flower=readBitmapFromAssets("flower.png");
 
 
 _ENEMY *en=NULL;
 
 _ARRAY *array=array_create();
 task->enemys=array;
 char *text=text_readFromAssets(filename);
 char c;
 int type=0;
 printf("ѭ����ȡ��������\n");
 while(c=*text)
 {
  switch(type)
  {
   case 0:
   if(en==NULL)
   en=malloc(sizeof(_ENEMY));
   if(c>='0' && c<='9')
   {
    en->type=atoi(text);
    switch(en->type)
    {
     case 0: //Ģ��
     en->sprite = sp_read("mogu.sprite",task->bitmap_mogu);
     sp_setDraw(en->sprite,0);
     break;
     case 1: //Ѽ��
     en->sprite= sp_read("turtle.sprite",task->bitmap_turtle);
     sp_setDraw(en->sprite,0);
     break;
     case 2: //ʳ�˻�
     en->sprite= sp_read("flower.sprite",task->bitmap_flower);
     sp_setDraw(en->sprite,0);
     break;
     
    }
    type=1;
   }
   break;
   case 1:
   if(c==':')
   {
    type=2;
   }
   else if(c=='\n')
   {
    type=0;
   }
   break;
   case 2:
   if(c>='0' && c<='9')
   {
    en->x=atoi(text);
    type=3;
   }
   else if(c=='\n')
   {
    type=0;
   }
   break;
   case 3:
   if(c==' ')
   {
    type=4;
   }
   else if(c=='\n')
   {
    type=0;
   }
   break;
   case 4:
   if(c>='0' && c<='9')
   {
    en->y=atoi(text);
    sp_setxy(en->sprite,en->x*20,en->y*20);
    if(en->type==2)
    sp_move(en->sprite,10,0);
    type=5;
   }
   else if(c=='\n')
   {
    type=0;
   }
   break;
   case 5:
   if(c=='\n')
   {
   array_append(array,(int)en);
   en=NULL;
   task->size++;
   type=0;
   }
   break;
  }
  
  text++;
 }
 if(en!=NULL)
 {
 array_append(array,(int)en);
 task->size++;
 }
 printf("�����ɹ�\n");
 
 return task;
};

//�����е�����ӵ�������
int en_addWorld(_EN_TASK *task,int world)
{
 for(int i=0;i<task->size;i++)
 {
  _ENEMY *en=(void*)array_get(task->enemys,i);
 world_addSprite(world,en->sprite);
 }
 return 0;
}


//�жϵ����Ƿ���Լ���
int en_load(_EN_TASK *task,int x)
{
 _ENEMY *en=NULL;
 if(task->load>=task->size)
 return FALSE;
 en=(void*)array_get(task->enemys,task->load);
 if(x>en->x)
 {
 sp_setDraw(en->sprite,1);
 task->load++;
 if(task->load>=task->size)
 task->load=task->size;
 }
 
 return TRUE;
}

//�����˶��¼�
int en_run(_EN_TASK *task, _TILED *tiled,_HERO* hero)
{
 for(int i=0;i<task->load;i++)
 {
  _ENEMY *en=(void*)array_get(task->enemys,i);
  int sx= sp_getx(en->sprite);
  int sy= sp_gety(en->sprite);
  if(sp_isDraw(en->sprite) && sp_getAction(en->sprite)!=1)
  {
  switch(en->type)
   {
   case 0:
   case 1:
  if(en->direction==0)
    {
    sx--;
    //����Ƿ�ײ������
   if(tiled_getDataCoor(tiled,sx,sy))
    en->direction=1;
    //����Ƿ�����ȥ
   if(!tiled_getDataCoor(tiled,sx,sy+20))
    {
    en->direction=1;
    }
    }
   else 
    {
    sx++;
      //����Ƿ�ײ������
   if(tiled_getDataCoor(tiled,sx+19,sy))
    en->direction=0;
    //����Ƿ�����ȥ
   if(!tiled_getDataCoor(tiled,sx+20,sy+20))
     {
     en->direction=0;
     }
    }
   
   
  break;
  case 2:
  if(en->direction==0) //����
   {
  sy--;
  if(sy<en->y*20-32)
  {
   en->direction=2;

  
  }
   }
  else if(en->direction==1)
   {
  sy++;
  if(sy>en->y*20) en->direction=2;
   }
   else
   {
      //�������ʳ�˻��ܽ�����ôʳ�˻�����
  int sp_len=hero->x-sx;
  if(sp_len>26 || sp_len< -26)
  {
   if(sy>en->y*20) en->direction=0;
   else
   en->direction=1;
  }
   }
  
   } //switch
   sp_setxy(en->sprite,sx,sy);
   //��������ײ
   
   if(sp_crash(en->sprite,hero->sprite) && sp_getAction(en->sprite)!=1)
   {
    if(en->type==2)
    {
    
    hero->hp--;
    }
    else 
    {
     if(hero->isjump && hero->hv>0)
     {
      hero->hv=-8;
     sp_setAction(en->sprite,1);
     }
     else
     hero->hp--;
    }
   }
  } //if
  
 } //for
 
 return 0;
}


//���ٵ���
int en_free(_EN_TASK *task)
{
 //����bitmap
 bitmapFree(task->bitmap_mogu);
 bitmapFree(task->bitmap_flower);
 bitmapFree(task->bitmap_turtle);
 //���پ���
 for(int i=0;i<task->size;i++)
 {
  _ENEMY *en=(void*)array_get(task->enemys,i);
  sp_free(en->sprite);
   //���ٵ���
  free(en);
 }

 
 //��������
 array_free(task->enemys);
 //����task
 free(task);
 return 0;
}




#endif







