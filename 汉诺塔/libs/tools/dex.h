#ifndef DEX_H
#define DEX_H
#include "../api/android.h"

typedef struct
{
 int loader;
 int class;
 int obj;
}_DEX;

//创建插件
//参数：插件文件名，插件类名
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
   printf("找不到class \n");
  }
 }
 else
 {
  printf("loader null \n");
 }
 return dex;
}

//向插件传递数据
//手动释放内存
char*dex_put(_DEX*dex,char*text)
{
 return dex_putString(dex->obj,text);
}

//释放插件
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
  dtext("该版本不支持dex扩展",0,0,255,255,255,0,1);
  ref(0,0,SCRW,SCRH);
  sleep(2000);
  exit();
 }
}

#endif

