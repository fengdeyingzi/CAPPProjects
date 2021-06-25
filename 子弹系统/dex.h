#ifndef _DEX_H_
#define _DEX_H_

typedef struct
{
 int32 loader;
 int32 class;
 int32 obj;
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
  printf("loadClass\n");
  if(dex->class!=0)
  {
      printf("runClass\n");
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

#endif


