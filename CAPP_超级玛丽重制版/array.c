
#include "base.h"
#include "array.h"


//创建数组
_ARRAY *array_create()
{
 _ARRAY *array=malloc(sizeof(_ARRAY));
 array->size=1024;
 array->len=0;
 array->array=malloc(array->size*sizeof(int32));
 return array;
};

//在数组末尾添加一条信息
int array_append(_ARRAY *array,int32 num)
{
 int size;
 int32 *data;
 if(array->size<=array->len)
 {
  size=array->size+1024;
  data=malloc(size*sizeof(int32));
  memcpy(data,array->array,array->size);
  free(array->array);
  array->array=data;
  array->size=size;
 }
 array->array[array->len++]=num;

 return 0;
}
//改变数组的可用长度(谨慎使用)
int array_setlen(_ARRAY *array,int len)
{
 array->len=len;

 return 0;
}

//删除数组上一个信息
int array_delete(_ARRAY *array, int offset)
{
 memmove(array->array+offset,array->array+offset+1,array->len-offset-1);
 array->len--;
 return 0;
}

//修改数组上一个信息
int array_set(_ARRAY *array,int offset,int32 num)
{
 array->array[offset]=num;
 return 0;
}

//获取数组上一条信息
int32 array_get(_ARRAY *array,int offset)
{
 if(offset<array->len)
  return array->array[offset];
 return 0;
}
//销毁
int array_free(_ARRAY *array)
{
 free(array->array);
 free(array);
 return 0;
}












