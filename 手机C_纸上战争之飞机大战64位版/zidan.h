#ifndef _ZIDAN_H_
#define _ZIDAN_H_

#include <ex_math.h>

enum
{
 ZIDAN_COMMON, //普通
 ZIDAN_ROCKET, //火箭
 ZIDAN_FOLLOW, //跟踪
 ZIDAN_LASER  //跟踪
};

typedef struct
{
 int32 bitmap; //图片
 int32 sprite; //精灵
 int type; //子弹类型
 int x;
 int y; //显示坐标
 int w;
 int h;
 int ux;
 int uy; //计算坐标(为了增加精确度，是实际坐标的10倍)
 int v;//速度
 int direction; //方向
 int hp; //生命值
 int lv; //等级(和威力有关)
 int power; //攻击力
} _ZIDAN;

#ifdef TCC
extern void z_setType(_ZIDAN *zidan, int type);
#endif


//创建子弹 参数：bitmap 子弹类型
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

//设置子弹坐标
void z_setxy(_ZIDAN *zidan, int x,int y)
{
 zidan->x=x;
 zidan->y=y;
 zidan->ux=x*10;
 zidan->uy=y*10;
 sp_setxy(zidan->sprite,x-(zidan->w)/2,y-(zidan->h)/2);
}
//设置子弹方向
void z_setDirection(_ZIDAN *zidan, int direction)
{
 zidan->direction=direction;
 
}
//设置子弹速度
void z_setv(_ZIDAN *zidan, int v)
{
 zidan->v=v*10;
 
}

//设置子弹等级
void z_setlv(_ZIDAN *zidan, int lv)
{
 zidan->lv=lv;
 
}

//获取子弹hp
int z_getHp(_ZIDAN *zidan)
{
 return zidan->hp;
}

//获取子弹坐标
int z_getx(_ZIDAN *zidan)
{
 return zidan->x;
}

int z_gety(_ZIDAN *zidan)
{
 return zidan->y;
}


//获取子弹攻击力
int z_getPower(_ZIDAN *zidan)
{
 return zidan->power;
}

//检测子弹是否被销毁
int z_isDestory(_ZIDAN *zidan)
{
 if(zidan->hp<=0)
 return TRUE;
 else
 return FALSE;
}

//设置子弹类型
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

//子弹升级
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

//复制一颗子弹
_ZIDAN *z_copy(_ZIDAN *zidan)
{
 _ZIDAN *temp = malloc(sizeof(_ZIDAN));
 memcpy(temp,zidan,sizeof(_ZIDAN));
 temp->sprite=sp_copy(zidan->sprite);
 return temp;
};


//子弹移动
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
//画子弹
void z_draw(_ZIDAN *zidan)
{
 sp_draw(zidan->sprite,NULL);
 
}

//子弹爆炸
void z_blast(_ZIDAN *zidan)
{
 sp_setAction(zidan->sprite,1);
}

//设置子弹在n秒后销毁
void z_setDistory(_ZIDAN *zidan,int hp)
{
 zidan->hp=hp;
}

//销毁子弹
void z_distory(_ZIDAN *zidan)
{
 sp_free(zidan->sprite);
 free(zidan);
}

#endif