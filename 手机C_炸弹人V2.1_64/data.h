
/*
��Ϸ��ͼ���ݿ�

���ߣ����Ӱ��

*/


#include "map.h"
//1 ���� 2 3 4�� 5 6Ģ�� 7ľ׮
int data1[20*20]=
{
 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 8, 7, 7, 7, 7, 8, 8, 8, 
8, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 4, 5, 5, 5, 5, 0, 0, 3, 
3, 0, 3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 
8, 0, 2, 3, 0, 0, 0, 3, 2, 0, 0, 0, 3, 0, 3, 0, 0, 12,0, 3, 
3, 0, 0, 3, 0, 2, 0, 0, 2, 3, 3, 0, 0, 0, 2, 0, 0, 12,0, 8, 
8, 0, 0, 14,0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 3, 12,0, 3, 
3, 0, 0, 2, 2, 2, 3, 0, 12,12,0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 
8, 0, 5, 0, 7, 0, 5, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 5, 3, 
4, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 7, 0, 2, 2, 2, 2, 0, 0, 8, 
3, 0, 2, 2, 3, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 
3, 0, 3, 3, 3, 0, 5, 0, 2, 0, 5, 0, 5, 0, 5, 0, 2, 0, 0, 8, 
4, 0, 0, 0, 0, 0, 0, 0, 5, 0, 13,0, 5, 0, 0, 2, 0, 3, 0, 3, 
3, 0, 2, 3, 2, 3, 2, 0, 5, 0, 5, 0, 5, 7, 2, 3, 0, 2, 0, 4, 
3, 0, 0, 0, 0, 2, 0, 0, 5, 0, 5, 0, 5, 0, 0, 2, 0, 3, 0, 3, 
4, 2, 0, 0, 2, 3, 2, 0, 0, 7, 0, 0, 0, 3, 0, 3, 0, 2, 15,15,
4, 2, 0, 0, 0, 3, 0, 0, 0, 0, 0, 2, 2, 3, 0, 0, 0, 0, 0, 15,
6, 2, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2, 3, 0, 0, 0, 0, 6, 12,
6, 2, 2, 0, 7, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 3, 3, 0, 7, 12,
6, 2, 2, 0, 0, 0, 2, 2, 5, 0, 0, 0, 2, 2, 2, 2, 3, 0, 0, 12,
3, 16,16,16,16,13,3, 3, 3, 4, 3, 4, 3, 12,12,12,12,12,12,12,
 
};
int data1_back[20*20]=
{
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1
 
 
 
};

typedef struct 
{
 int32 bitmap;
 int32 map;
 int32 map_back;
 int32 world;
 int32 world_back;
 int32 sprite;
 int32 sprite_back;
 int32 camera;
} _DATA;



//���ص�ͼ ����data
_DATA *data_load(int num)
{
 _DATA *map_data;
 map_data=malloc(sizeof(_DATA));
 
 map_data->bitmap=readBitmapFromAssets("ld2.png");
 printf("��ȡbitmap\n");
 map_data->bitmap=readBitmapFromAssets("ld2.png");
 map_data->sprite=sp_read("ld2.sprite",map_data->bitmap);
 map_data->sprite_back=sp_read("ld.sprite",map_data->bitmap);
 printf("��ȡ����\n");
 

 if(num==1)
 {
  map_data->map= map_create(data1,map_data->sprite,20,20);
  map_data->map_back=map_create(data1_back,map_data->sprite_back,20,20);
  printf("������ͼ\n");
 }
 map_data->world=world_create();
 map_data->world_back=world_create();
 map_data->camera=ca_create(0,0,400,400);
 
 
 world_setCamera(map_data->world,map_data->camera);
 world_setCamera(map_data->world_back,map_data->camera);
 printf("���������%d %d\n",map_data->world==(int)map_data->world,map_data->map==map_data->map);
 map_addWorld(map_data->world,map_data->map);
 map_addWorld(map_data->world_back,map_data->map_back);
 printf("����ͼ��ӵ�������\n");
 return map_data;
};

//��ȡ��ǰ��ͼ
long data_getMap(_DATA *map_data)
{
 return map_data->map;
}

//�ͷŵ�ͼ
int data_free(_DATA *map_data)
{
 if(map_data!=NULL)
 {
  map_free(map_data->map);
  map_free(map_data->map_back);
  sp_free(map_data->sprite);
  sp_free(map_data->sprite_back);
  bitmapFree(map_data->bitmap);
  world_free(map_data->world);
  world_free(map_data->world_back);
  ca_free(map_data->camera);
 }
 free(map_data);
 return 0;
}

