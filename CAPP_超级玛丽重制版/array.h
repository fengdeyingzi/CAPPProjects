

#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "base.h"

typedef struct
{
    int32 *array;  //数组缓存
    int len;  //可用长度
    int size;  //数组内存长度
} _ARRAY;


//创建数组
_ARRAY *array_create();
//在数组末尾添加一条信息
int array_append(_ARRAY *array,int32 num);

//改变数组的可用长度(谨慎使用)
int array_setlen(_ARRAY *array,int len);

//删除数组上一个信息
int array_delete(_ARRAY *array, int offset);

//修改数组上一个信息
int array_set(_ARRAY *array,int offset,int32 num);

//获取数组上一条信息
int32 array_get(_ARRAY *array,int offset);

//销毁
int array_free(_ARRAY *array);







#endif
