#ifndef _ZIDAN_H_
#define _ZIDAN_H_

#include <ex_math.h>

enum
{
 ZIDAN_COMMON, //��ͨ
 ZIDAN_ROCKET, //���
 ZIDAN_FOLLOW, //����
 ZIDAN_LASER  //����
};

typedef struct
{
 int32 bitmap; //ͼƬ
 int32 sprite; //����
 int type; //�ӵ�����
 int x;
 int y; //��ʾ����
 int w;
 int h;
 int ux;
 int uy; //��������(Ϊ�����Ӿ�ȷ�ȣ���ʵ�������10��)
 int v;//�ٶ�
 int direction; //����
 int hp; //����ֵ
 int lv; //�ȼ�(�������й�)
 int power; //������
} _ZIDAN;

#ifdef TCC
extern void z_setType(_ZIDAN *zidan, int type);
#endif


//�����ӵ� ������bitmap �ӵ�����
_ZIDAN *z_create(int32 bitmap,int type)
{
 _ZIDAN *zidan = malloc(sizeof(_ZIDAN));
 memset(zidan,0,sizeof(_ZIDAN));
 zidan->type=type;
// zidan->bitmap=readBitmapFromAssets("zidan.png");
 zidan->bitmap=bitmap;
 zidan->sprite=sp_read("zidan.sprite",zidan->bitmap);
 zidan->w=10;
 zidan->h=31;
 zidan->hp=100;
 zidan->power=20;
 z_setType(zidan,1);
 
 return zidan;
};

//�����ӵ�����
void z_setxy(_ZIDAN *zidan, int x,int y)
{
 zidan->x=x;
 zidan->y=y;
 zidan->ux=x*10;
 zidan->uy=y*10;
 sp_setxy(zidan->sprite,x-(zidan->w)/2,y-(zidan->h)/2);
}
//�����ӵ�����
void z_setDirection(_ZIDAN *zidan, int direction)
{
 zidan->direction=direction;
 
}
//�����ӵ��ٶ�
void z_setv(_ZIDAN *zidan, int v)
{
 zidan->v=v*10;
 
}

//�����ӵ��ȼ�
void z_setlv(_ZIDAN *zidan, int lv)
{
 zidan->lv=lv;
 
}

//��ȡ�ӵ�hp
int z_getHp(_ZIDAN *zidan)
{
 return zidan->hp;
}

//��ȡ�ӵ�����
int z_getx(_ZIDAN *zidan)
{
 return zidan->x;
}

int z_gety(_ZIDAN *zidan)
{
 return zidan->y;
}


//��ȡ�ӵ�������
int z_getPower(_ZIDAN *zidan)
{
 return zidan->power;
}

//����ӵ��Ƿ�����
int z_isDestory(_ZIDAN *zidan)
{
 if(zidan->hp<=0)
 return TRUE;
 else
 return FALSE;
}

//�����ӵ�����
void z_setType(_ZIDAN *zidan, int type)
{
 zidan->type=type;
 switch(type)
 {
  case 1:
  zidan->v=600;
  zidan->direction=270;
  break;
  case 2:
  zidan->v=400;
  zidan->direction=270;
  break;
  case 3:
  zidan->v=400;
  zidan->direction=270;
  break;
  
  case 4:
  zidan->v=400;
  zidan->direction=270;
  break;
  
 }
}

//�ӵ�����
int z_upgrade(_ZIDAN *zidan)
{
 if(zidan->lv<6)
 {
 zidan->lv++;
 zidan->power=zidan->lv*20;
 return TRUE;
 }
 else
 return 0;
}

//����һ���ӵ�
_ZIDAN *z_copy(_ZIDAN *zidan)
{
 _ZIDAN *temp = malloc(sizeof(_ZIDAN));
 memcpy(temp,zidan,sizeof(_ZIDAN));
 temp->sprite=sp_copy(zidan->sprite);
 return temp;
};


//�ӵ��ƶ�
void z_run(_ZIDAN *zidan)
{
 if(zidan->hp>0)
 {
 toSpin(zidan->ux,zidan->uy,zidan->v,zidan->v,zidan->direction, &(zidan->ux),&(zidan->uy));
 zidan->x=zidan->ux/10;
 zidan->y=zidan->uy/10;
 
 zidan->hp--;
 sp_setxy(zidan->sprite,zidan->x-zidan->w/2,zidan->y-zidan->h/2);
 }
}
//���ӵ�
void z_draw(_ZIDAN *zidan)
{
 sp_draw(zidan->sprite,NULL);
 
}

//�ӵ���ը
void z_blast(_ZIDAN *zidan)
{
 sp_setAction(zidan->sprite,1);
}

//�����ӵ���n�������
void z_setDistory(_ZIDAN *zidan,int hp)
{
 zidan->hp=hp;
}

//�����ӵ�
void z_distory(_ZIDAN *zidan)
{
 sp_free(zidan->sprite);
 free(zidan);
}

#endif