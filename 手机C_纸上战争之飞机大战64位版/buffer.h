#include <base.h>
#include <ex_game.h>
#include "array.h"
typedef struct
{
 _ARRAY *array_bitmap;
 _ARRAY *array_sprite;
 _ARRAY *array_camera;
 _ARRAY *array_world;
 _ARRAY *array_data;
} _BUFFER;


//���������
_BUFFER *buf_create()
{
 _BUFFER *buf = malloc(sizeof(_BUFFER));
 memset(buf,0,sizeof(_BUFFER));
 buf->array_bitmap=array_create();
 buf->array_sprite=array_create();
 buf->array_camera=array_create();
 buf->array_world=array_create();
 buf->array_data=array_create();
 
 return buf;
}
//���bitmap
int buf_addBitmap(_BUFFER *buf,int bitmap)
{
 array_append(buf->array_bitmap,bitmap);
 return 0;
}
//��Ӿ���
int buf_addSprite(_BUFFER *buf,int sprite)
{
 array_append(buf->array_sprite,sprite);
 return 0;
}


//�������
int buf_addWorld(_BUFFER *buf,int world)
{
 array_append(buf->array_world,world);
 return 0;
}
//��������
int buf_addCamera(_BUFFER *buf,int camera)
{
 array_append(buf->array_camera,camera);
 return 0;
}

//���malloc������ڴ�
int buf_addData(_BUFFER *buf,void *data)
{
 array_append(buf->array_data,(int)data);
 return 0;
}

//�ͷţ��������ڴ��ͷ�
int buf_free(_BUFFER *buf)
{
 int i;
 //�ͷ�bitmap
 for(i=0;i<array_getlen(buf->array_bitmap);i++)
 {
  bitmapFree(array_get(buf->array_bitmap,i));
 }
 array_free(buf->array_bitmap);
 
 //�ͷ�sprite
 for(i=0;i<array_getlen(buf->array_sprite;i++)
 {
  sp_free(array_get(buf->array_sprite,i);
 }
 array_free(buf->array_sprite);
 
 //�ͷ������
 for(i=0;i<array_getlen(buf->array_camera;i++)
 {
  ca_free(array_get(buf->array_camera,i);
 }
 array_free(buf->array_camera);
 
 //�ͷ�����
 for(i=0;i<array_getlen(buf->array_world;i++)
 {
  world_free(array_get(buf->array_world),i);
 }
 array_free(buf->array_world);
 
 //�ͷ�data
 for(i=0;i<array_getlen(buf->array_data;i++)
 {
  world_free(array_get(buf->array_data),i);
 }
 array_free(buf->array_data);
 
 return 0;
}




