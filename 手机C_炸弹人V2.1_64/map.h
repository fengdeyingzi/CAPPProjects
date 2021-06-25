
#ifndef _MAP_H_
#define _MAP_H_
/*
�����ͼ
ÿ��ͼ�鶼��һ������
��������ӵ������У��Դ�����ʾ��ͼ
�ŵ㣺������2.5d��ͼ��ͼ�����ȸ�
ȱ�㣺�Ƚ�ռ�ڴ�
����Ϸר��

���Ӱ�� ��д
*/
#include <base.h>
#include <graphics.h>





typedef struct
{
 int *data;//Դ����
 int32 *sp_data; //��ͼ������ͼ��
 int32 sprite; //ԭʼ��������
 int w;
 int h;
 int itemw;
 int itemh;
} _MAP;



//������ͼ
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
   //���þ��鶯��֮���ٸ���һ��
   sp_setAction(sprite,map->data[iy*map->w+ix]);
   sp_setxy(sprite, ix*itemw,iy*itemh-1);

   map->sp_data[iy*map->w+ix]=sp_copy(sprite);
   
  }
 }
  return (long)map;
 }
 

//����ͼ��ӵ�������
int map_addWorld(int32 world,int32 map)
{
 _MAP *_map=(void*)map;
 int ix,iy;
 int sp;
 printf("map_addWorld\n");
 int itemw=sp_getWidth(_map->sprite);
 int itemh=sp_getHeight(_map->sprite);
 printf("��ʼ���ͼ��\n");
 for(iy=0;iy<_map->h;iy++)
 {
  for(ix=0;ix<_map->w;ix++)
  {
   //����ͼ�еľ�����ӵ�������
   //printf("��ӵ�������%d\n",iy*_map->w+ix);
   world_addSprite(world,_map->sp_data[iy*_map->w+ix]);
  }
 }
 return 0;
}


//���ݵ�ͼ����ƥ�侫������
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

//��ȡ��ͼ��ָ��λ�õ�����
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



//���ٵ�ͼ
int map_free(int32 id)
{
 _MAP *map=(void*)id;
 //���ٵ�ͼ�е�ͼ��
 int i;
 for(i=0;i<map->w*map->h;i++)
 sp_free(map->sp_data[i]);
 free(map);
 return 0;
}


//




#endif

