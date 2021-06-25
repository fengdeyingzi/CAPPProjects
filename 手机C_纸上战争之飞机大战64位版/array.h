

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

//������ָ��λ�����һ����Ϣ
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

//��ȡ���鳤��
int array_getlen(_ARRAY *array)
{
 return array->len;
}

//ɾ��������һ����Ϣ
int array_delete(_ARRAY *array, int offset)
{
 if(array->len>0)
 {
 memmove(array->array+offset,array->array+offset+1,(array->len-offset)*4);
 array->len--;
 }
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

//��С��������
/*
��shell��ϣ��������
shell����һ���� shell ����������1969�귢���ġ������Ȱ����k(k>=1)���Ǽ���Ԫ���ź�������Сkֵ��һ��ȡ��һ�룩��������ֱ��k=1ʱ���������������������������룺
*/
void shell(int *a,int n)
{
int i,j,k,x;
k=n/2; /*���ֵ*/
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
k/=2; /*��С���ֵ*/
}
}
int array_shell(_ARRAY *array)
{
 shell(array->array,array->len);
 return 0;
}
//�ɴ�С����
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
   if(data[i]<data[j])//����
   {
    temp=data[i];
    data[i]=data[j];
    data[j]=temp;
   }
  }
 }
 return 0;
}

//�����鱣��Ϊָ���ļ�
int array_save(_ARRAY *array,char *filename)
{
 remove(filename);
 int f;
 f=open(filename,2+8);
 write(f,array->array,array->len*4);
 close(f);
}
//��ָ���ļ���ȡ����
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
//����
int array_free(_ARRAY *array)
{
 free(array->array);
 free(array);
 return 0;
}















#endif
