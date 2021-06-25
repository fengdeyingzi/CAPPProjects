#include "../api/base.h"
#include "../api/graphics.h"
#include "../tools/fnt.h"
#include "../game/sprite.h"
#include "../game/object.h"

#include "./res.h"

char* readFile(char*file)
{
 int fp=open(file,4|8);
 if(fp!=0)
 {
  int len=getlen(file);
  char*text=
  malloc(sizeof(char)*len+1);
  memset(text,'\0',len+1);
  read(fp,text,len);
  return text;
 }
 return NULL;
}

char*resTypeStr[]={
 "图片","字体","声音",
 "定时器","字符串",
 "精灵","JSON","Object"
 };
 
//载入资源
void*loadRes(char*path,ResType type)
{
 printf("loadRes%d：%s:%s\n",
  ResList.num-1,
  resTypeStr[type],path);
 
 char*text=NULL,*sprStr=NULL;
 Res*res = 
 &(ResList.res[ResList.num-1]);
 switch(type)
 {
  //图片
  case tImg:
  res->type = type;
  res->path = 
  getRes(path,tStr)->path;
  if(res->path[0]=='/')
  res->id = 
  readBitmapFromAssets(path+1);
  else
  res->id = 
  readBitmapFromAssets(path);
  if(res->id<=0)
  {
   //读取sd卡图片
   res->id=readBitmap(path);
   if(res->id<=0)
    return NULL;
  }
  break;
  
  //字体
  case tFnt:
  text = malloc(
  sizeof(char)*strlen(path));
  int len = strlen(path);
  strcpy(text,path);
  text[len-1] = 'g';
  text[len-2] = 'n';
  text[len-3] = 'p';
  res->id = 
  (int32)fnt_create(text,path);
  res->type = type;
  res->path = 
  getRes(path,tStr)->path;
  free(text);
  break;
  
  //定时器
  case tTim:
  res->id = timercreate();
  res->type = type;
  res->path = 
  getRes(path,tStr)->path;
  break;
  
  //字符串
  case tStr:
  text = malloc(
  sizeof(char)*strlen(path)+sizeof(char));
  memset(text,
  '\0',strlen(path)+sizeof(char));
  strcpy(text,path);
  res->type = type;
  strcpy(text,path);
  res->path = text;
  res->id = (int32)text;
  break;
  
  //精灵
  case tSpr:
  res->id = (int32)
  loadSprFile(path);
  res->type = type;
  res->path = 
  getRes(path,tStr)->path;
  break;
 
  //Json
  case tJsn:
  sprStr = 
  readFileFromAssets(path,&len);
  if(len<=0)
  sprStr=readFile(path);
  //解析精灵文件 
  if(sprStr!=NULL)
  {
   res->id = (int32)
   cJSON_Parse(sprStr);
   res->type = type;
   res->path = 
   getRes(path,tStr)->path;
  }
  free(sprStr);
  break;
  
  case tObj:
  
  break;
  
  default:
  break;
 }
 return res;
}

void freeOneRes(Res*res,
 ResType type)
{
 Res*res2 = NULL;
  int i;
 //遍历资源
 if(ResList.num>0)
 	for( i = 0;
   i<ResList.num;i++)
 {
  res2 = &(ResList.res[i]);
  //资源已载入
  if(res->type==type)
  if(strcmp(res->path,
     res2->path)==0)
  {
   printf("释放资源%d:%s\n",i,res2->path);
   switch(res2->type)
   {
    //图片
    case tImg:
    bitmapFree(res2->id);
    break;
    
    //字体
    case tFnt:
    fnt_free((_FNT*)(res2->id));
    break;
    
    //定时器
    case tTim:
    timerstop(res2->id);
    timerdel(res2->id);
    break;
    
    //精灵
    case tSpr:
    free((Spr*)(res2->id));
    break;
    
    //Json
    case tJsn:
    cJSON_Delete(
     (cJSON*)res2->id);
    break;
    
    case tStr:
    return;
    break;
    
    case tObj:
    
    break;
    
    default:
    break;
   }
   int j;
   for( j = i;
     j<ResList.num-1;j++)
   {
    ResList.res[j] = 
    ResList.res[j+1];
   }
   ResList.num--;
   return;
   break;
  }
 }
 //资源未载入
 printf("释放资源失败：%s\n",
  res2->path);
 //返回资源
 return;
}

//释放资源资源
void freeRes()
{
 //遍历Res
 Res*res;
 int i;
 for( i = 0;i<ResList.num;i++)
 {
  res = &(ResList.res[i]);
  printf("freeRes%d\n",i);
  switch(res->type)
  {
   //图片
   case tImg:
   bitmapFree(res->id);
   break;
   
   //字体
   case tFnt:
   fnt_free((_FNT*)(res->id));
   break;
   
   //定时器
   case tTim:
   timerstop(res->id);
   timerdel(res->id);
   break;
   
   //精灵
   case tSpr:
   free((Spr*)(res->id));
   break;
   
   
   //Json
   case tJsn:
   cJSON_Delete(
    (cJSON*)res->id);
   break;
   
   case tStr:
   free(res->path);
   break;
   
   case tObj:
   
   break;
   
   default:
   break;
  }
 }
}

//获取资源
Res*getRes(char*path,ResType type)
{
 Res*res = NULL;
 int i;
 //遍历资源
 if(ResList.num>0)
 	for( i = 0;i<ResList.num;i++)
 {
  res = &(ResList.res[i]);
  //资源已载入
  if(res->type==type)
  	if(strcmp(path,res->path)==0)
  {
   return res;
   break;
  }
 }
 //资源未载入
 ResList.num++;
 res = loadRes(path,type);
 if(res==NULL)
 {
  ResList.num--;
  capp_exit();
 }
 //返回资源
 return res;
}


