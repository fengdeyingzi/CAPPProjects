
#ifndef _MAP_H_
#define _MAP_H_
/*
世界地图
每个图块都是一个精灵
将精灵添加到世界中，以此来显示地图
优点：可以做2.5d地图，图块灵活度高
缺点：比较占内存
做游戏专用

风的影子 编写
*/
#include <base.h>
#include <graphics.h>





typedef struct
{
 int *data;//源数据
 int32 *sp_data; //地图中所有图块
 int32 sprite; //原始精灵数据
 int w;
 int h;
 int itemw;
 int itemh;
} _MAP;



//创建地图
 long map_create(int *data,int32 sprite,int w,int h)
 {
  _MAP *map=malloc(sizeof(_MAP));
  map->data=data;
  map->sp_data=malloc(w*h*sizeof(int));
  map->sprite=sprite;
  map->w=w;
  map->h=h;
  int itemw=sp_getWidth(sprite);
int itemh=sp_getHeight(sprite);
  map->itemw=itemw;
  map->itemh=itemh;
  int ix,iy;
   for(iy=0;iy<map->h;iy++)
 {
  for(ix=0;ix<map->w;ix++)
  {
   //设置精灵动作之后再复制一份
   sp_setAction(sprite,map->data[iy*map->w+ix]);
   sp_setxy(sprite, ix*itemw,iy*itemh-1);

   map->sp_data[iy*map->w+ix]=sp_copy(sprite);
   
  }
 }
  return (long)map;
 }
 

//将地图添加到世界中
int map_addWorld(int32 world,int32 map)
{
 _MAP *_map=(void*)map;
 int ix,iy;
 int sp;
 printf("map_addWorld\n");
 int itemw=sp_getWidth(_map->sprite);
 int itemh=sp_getHeight(_map->sprite);
 printf("开始添加图块\n");
 for(iy=0;iy<_map->h;iy++)
 {
  for(ix=0;ix<_map->w;ix++)
  {
   //将地图中的精灵添加到世界中
   //printf("添加到世界中%d\n",iy*_map->w+ix);
   world_addSprite(world,_map->sp_data[iy*_map->w+ix]);
  }
 }
 return 0;
}


//根据地图重新匹配精灵坐标
void map_setXY(int32 sprite,int itemw,int itemh)
{
 int x=sp_getx(sprite);
 int y=sp_gety(sprite);
 int dx=x%itemw;
 int dy=y%itemh;
 x=x/itemw*itemw;
 y=y/itemh*itemh;
 if(dx>itemw/2)x+=itemw;
 if(dy>itemh/2)y+=itemh;
 
 sp_setxy(sprite,x,y);
}

//获取地图上指定位置的数据
int map_getData(int32 id,int x,int y)
{
 _MAP *map=(void*)id;
 //int ix=x/map->itemw;
 //int iy=y/map->itemh;
 // if(x<0 || x>=map->w || y<0 || y>=map->h)return -1;
 if(x<0 ||  y<0 || x>=map->w || y>=(map->h))return -1;
 return map->data[(y*map->w) + x];
}

int map_setData(int32 id,int x,int y,int type)
{
 _MAP *map=(void*)id;
  map->data[y*map->w + x]=type;
  sp_setAction(map->sp_data[y*map->w + x],0);
  return 0;
}



//销毁地图
int map_free(int32 id)
{
 _MAP *map=(void*)id;
 //销毁地图中的图块
 int i;
 for(i=0;i<map->w*map->h;i++)
 sp_free(map->sp_data[i]);
 free(map);
 return 0;
}


//




#endif

