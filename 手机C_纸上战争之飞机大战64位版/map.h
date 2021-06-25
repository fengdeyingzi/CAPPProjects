
#ifndef _MAP_H_
#define _MAP_H_


typedef struct
{
 int32 bitmap;
 int item_w;
 int item_h;
 int x;
 int y;
} _MAP;

//创建背景
_MAP *map_create(int32 bitmap)
{
 _MAP *map = malloc(sizeof(_MAP));
 memset(map,0,sizeof(_MAP));
 map->bitmap=bitmap;
 map->x=0;
 map->y=0;
 return map;
};


//绘制地图
void map_draw(_MAP *map)
{
 int i=0;
 int ix=map->x;
 int iy=map->y;
 for(i=0;i<6;i++)
 {
  drawBitmap(map->bitmap,ix,iy);
  iy+=270;
 }
}
//地图运动事件
void map_move(_MAP *map)
{
 map->y+=5;
 if(map->y>0)
 map->y-=270;
}
//释放地图
int map_free(_MAP *map)
{
 free(map);
 return 0;
}

#endif

