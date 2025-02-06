

#ifndef _ARRAY_H_
#define _ARRAY_H_

typedef struct
{
 int *array;  //���黺��
 int len;  //���ó���
 int size;  //�����ڴ泤��
} _ARRAY;


//��������
_ARRAY *array_create()
{
 _ARRAY *array=malloc(sizeof(_ARRAY));
 array->size=1024;
 array->len=0;
 array->array=malloc(array->size*4);
 return array;
};

//������ĩβ���һ����Ϣ
int array_append(_ARRAY *array,int num)
{
 int size;
 int *data;
 if(array->size<=array->len)
 {
  size=array->size+1024;
  data=malloc(size*4);
  memcpy(data,array->array,array->size);
  free(array->array);
  array->array=data;
  array->size=size;
 }
 array->array[array->len++]=num;
 
 return 0;
}
//�ı�����Ŀ��ó���(����ʹ��)
int array_setlen(_ARRAY *array,int len)
{
 array->len=len;
 
 return 0;
}

//ɾ��������һ����Ϣ
int array_delete(_ARRAY *array, int offset)
{
 memmove(array->array+offset,array->array+offset+1,array->len-offset-1);
 array->len--;
 return 0;
}

//�޸�������һ����Ϣ
int array_set(_ARRAY *array,int offset,int num)
{
 array->array[offset]=num;
 return 0;
}

//��ȡ������һ����Ϣ
int array_get(_ARRAY *array,int offset)
{
 if(offset<array->len)
 return array->array[offset];
 return 0;
}
//����
int array_free(_ARRAY *array)
{
 free(array->array);
 free(array);
 return 0;
}















#endif
