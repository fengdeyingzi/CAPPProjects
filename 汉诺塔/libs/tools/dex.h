#ifndef DEX_H
#define DEX_H
#include "../api/android.h"

typedef struct
{
 int loader;
 int class;
 int obj;
}_DEX;

//�������
//����������ļ������������
void*dex_create(char*filename,char*classname)
{
 _DEX*dex = malloc(sizeof(_DEX));
 memset(dex,0,sizeof(_DEX));
 
 dex->loader = loadDex(filename);
 if(dex->loader!=0)
 {
  printf("%d \n",dex->loader);
  dex->class = loadClass(dex->loader,classname);
  
  if(dex->class!=0)
  {
   dex->obj = runClass(dex->class);
  }
  else
  {
   printf("�Ҳ���class \n");
  }
 }
 else
 {
  printf("loader null \n");
 }
 return dex;
}

//������������
//�ֶ��ͷ��ڴ�
char*dex_put(_DEX*dex,char*text)
{
 return dex_putString(dex->obj,text);
}

//�ͷŲ��
int dex_free(_DEX*dex)
{
 free(dex);
 return 0;
}

void dexVersion()
{
 printf("run dex \n");
 if(_VERSION<3100||(_VERSION>=3170&&_VERSION<=3180))
 {
  cls(0,0,0);
  dtext("�ð汾��֧��dex��չ",0,0,255,255,255,0,1);
  ref(0,0,SCRW,SCRH);
  sleep(2000);
  exit();
 }
}

#endif

