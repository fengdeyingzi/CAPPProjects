

#ifndef _ARRAY_H_
#define _ARRAY_H_

typedef struct
{
 int *array;  //数组缓存
 int len;  //可用长度
 int size;  //数组内存长度
} _ARRAY;


//创建数组
_ARRAY *array_create()
{
 _ARRAY *array=malloc(sizeof(_ARRAY));
 array->size=1024;
 array->len=0;
 array->array=malloc(array->size*4);
 return array;
};

//在数组指定位置添加一条信息
int array_add(_ARRAY *array,int index,int num)
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
 memmove(array->array+index,array->array+index+1,(array->len-index)*4);
 array->len++;
 
 return 0;
}

//在数组末尾添加一条信息
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
//改变数组的可用长度(谨慎使用)
int array_setlen(_ARRAY *array,int len)
{
 array->len=len;
 
 return 0;
}

//获取数组长度
int array_getlen(_ARRAY *array)
{
 return array->len;
}

//删除数组上一个信息
int array_delete(_ARRAY *array, int offset)
{
 if(array->len>0)
 {
 memmove(array->array+offset,array->array+offset+1,(array->len-offset)*4);
 array->len--;
 }
 return 0;
}

//修改数组上一个信息
int array_set(_ARRAY *array,int offset,int num)
{
 array->array[offset]=num;
 return 0;
}

//获取数组上一条信息
int array_get(_ARRAY *array,int offset)
{
 if(offset<array->len)
 return array->array[offset];
 return 0;
}

//由小到大排序
/*
“shell（希尔）法”
shell法是一个叫 shell 的美国人与1969年发明的。它首先把相距k(k>=1)的那几个元素排好序，再缩小k值（一般取其一半），再排序，直到k=1时完成排序。下面让我们来分析其代码：
*/
void shell(int *a,int n)
{
int i,j,k,x;
k=n/2; /*间距值*/
while(k>=1) {
for(i=k;i<n;i++) {
x=a[i];
j=i-k;
while(j>=0&&x<a[j]) {
a[j+k]=a[j];
j-=k;
}
a[j+k]=x;
}
k/=2; /*缩小间距值*/
}
}
int array_shell(_ARRAY *array)
{
 shell(array->array,array->len);
 return 0;
}
//由大到小排序
int array_shell2(_ARRAY *array)
{
 int *data=array->array;
 int len=array->len;
 int i,j;
 int temp;
 for(i=0;i<len;i++)
 {
  
  for(j=i+1;j<len;j++)
  {
   if(data[i]<data[j])//交换
   {
    temp=data[i];
    data[i]=data[j];
    data[j]=temp;
   }
  }
 }
 return 0;
}

//将数组保存为指定文件
int array_save(_ARRAY *array,char *filename)
{
 remove(filename);
 int f;
 f=open(filename,2+8);
 write(f,array->array,array->len*4);
 close(f);
}
//从指定文件读取数组
_ARRAY *array_read(char *filename)
{
 _ARRAY *array;
 int f;
 int len=getlen(filename);
 
 f=open(filename,1+8);
 if(f>0)
 {
  array=array_create();
  if(array->size>len)
  array->len=len;
  else
  {
   array->size=len;
   free(array->array);
   array->array=malloc(array->size*4);
  }
 read(f,array->array,len);
 close(f);
 }
 return array;
};
//销毁
int array_free(_ARRAY *array)
{
 free(array->array);
 free(array);
 return 0;
}















#endif
