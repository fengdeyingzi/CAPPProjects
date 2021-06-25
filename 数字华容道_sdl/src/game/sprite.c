#include "./sprite.h"

#include "../api/ex_math.h"
#include "../tools/res.h"
#include "../tools/draw.h"

//创建翻转spr
int32 getScaImg(Spr*spr,int xsca,int ysca)
{
 Act* act=NULL;
 Pic* pic= NULL;
 int32 bit=
 getRes(spr->file,tImg)->id;
 int w=bitmap_getWidth(bit);
 int h=bitmap_getHeight(bit);
 //创建图片
 int32 nbit=
 createBitmap(w,h);
 //遍历Spr
 int i,j;
 for( i=0;i<spr->act_num;i++)
 {
  act=&spr->act[i];
  for( j=0;
   j<act->pic_num;j++)
  {
   pic=&act->pic[j];
   //裁剪生成图片
   int tbit=
   clipBitmap(bit,pic->px,
   pic->py,pic->pw,pic->ph);
   int fbit=
  //  bitmap_turn(tbit,xsca,ysca);
   //绘制翻转图片
   drawBitmapOld(nbit,fbit,
   pic->px,pic->py,
   pic->pw,pic->ph,0,0);
   //释放图片内存
   bitmapFree(tbit);
   bitmapFree(fbit);
  }
 }
 return nbit;
}

//复制spr内容
Spr*copySpr(Spr*spr)
{
 Spr*nspr=malloc(sizeof(Spr));
 nspr->x=spr->x;
 nspr->y=spr->y;
 nspr->w=spr->w;
 nspr->h=spr->h;
 nspr->ind=spr->ind;
 nspr->act_num=spr->act_num;
 nspr->file=spr->file;
 nspr->xca_file=spr->xca_file;
 nspr->yca_file=spr->yca_file;
 nspr->cca_file=spr->cca_file;
 
 Act*act,*nact;
 Pic*pic,*npic;
 int i;
 for( i=0;i<spr->act_num;i++)
 {
  act=&spr->act[i];
  nact=&nspr->act[i];
  nact->ind=act->ind;
  nact->pic_num=act->pic_num;
  nact->name=act->name;
int j;
  for( j=0;
   j<act->pic_num;j++)
  {
   pic=&act->pic[j];
   npic=&nact->pic[j];
   npic->px=pic->px;
   npic->py=pic->py;
   npic->pw=pic->pw;
   npic->ph=pic->ph;
  }
 }
 return nspr;
}

//获取翻转的spr
Spr*getScaSpr(Spr*spr,int xsca,int ysca)
{
 Spr*nspr=NULL;
 if(FALSE==xsca&&FALSE==ysca)
 {
  return spr;
 }
 else if(xsca==TRUE&&ysca==TRUE)
 {
  if(spr->cca_file==NULL)
  spr->cca_file=
  getScaSprPath(spr,xsca,ysca);
  nspr=(Spr*)getRes(
  spr->cca_file,tSpr)->id;
 }
 else if(xsca==TRUE)
 {
  if(spr->xca_file==NULL)
  spr->xca_file=
  getScaSprPath(spr,xsca,ysca);
  nspr=(Spr*)getRes(
  spr->xca_file,tSpr)->id;
 }
 else if(ysca==TRUE)
 {
  if(spr->yca_file==NULL)
  spr->yca_file=
  getScaSprPath(spr,xsca,ysca);
  nspr=(Spr*)getRes(
  spr->yca_file,tSpr)->id;
 }
 //不允许再翻转
 nspr->cca_file=nspr->file;
 nspr->xca_file=nspr->file;
 nspr->yca_file=nspr->file;
 return nspr;
}

//获取翻转spr路径
char*getScaSprPath(Spr*spr,int xsca,int ysca)
{
 char file[100];
 Spr*nspr=copySpr(spr);
 memset(file,'\0',100);
 //不翻转精灵
 if(xsca==FALSE&&ysca==FALSE)
 {
  return spr->file;
 }
 //上下左右翻转
 else if(xsca==TRUE&&ysca==TRUE)
 {
  nspr->x=nspr->w-nspr->x;
  nspr->y=nspr->h-nspr->y;
  if(spr->cca_file!=NULL)
  return spr->cca_file;
 }
 //左右翻转
 else if(xsca==TRUE)
 {
  nspr->x=nspr->w-nspr->x;
  if(spr->xca_file!=NULL)
  return spr->xca_file; 
 }
 //上下翻转
 else if(ysca==TRUE)
 {
  nspr->y=nspr->h-nspr->y;
  if(spr->yca_file!=NULL)
  return spr->yca_file;
 }
 //翻转精灵
 int time=getuptime();
 sprintf(file,"capp/.cache/%d.png",time);
 //保存png
 int nbit=
 getScaImg(spr,xsca,ysca);
 saveBitmap(nbit,
 file, _PNG, 100);
 nspr->file=
 getRes(file,tStr)->path;
 //保存spr
 sprintf(file,"capp/.cache/%d.spr",time);
 saveSpr(nspr,file);
 //释放并返回
 free(nspr);
 return getRes(file,tStr)->path;
}

//运行精灵
void runSpr(Spr*spr)
{
 if(spr==NULL)
  return ;
 Act*act = &(spr->act[spr->ind]);
 act->ind++;
 act->ind = 
 act->ind%act->pic_num;
}

//旋转绘制
void drawSprAngle(Spr*spr,int x2,int y2,int roat)
{
 /*
 if(spr==NULL)
 {
  printf("Spr绘制失败\n");
  return ;
 }
 int x=x2-spr->x;
 int y=y2-spr->y;
 
 int32 bit = 
 getRes(spr->file,tImg)->id;
 Act*act = &(spr->act[spr->ind]);
 Pic*pic = &(act->pic[act->ind]);
 
 int rImg=
 createBitmap(pic->pw,pic->ph);
 drawBitmapOld(rImg,bit, 0, 0,
 pic->pw, pic->ph, 
 pic->px, pic->py);

 drawBitmapRotate(rImg,x2,y2, 
 spr->x,spr->y,
 roat-90,0xffffffff);


 bitmapFree(rImg);*/
}

//绘制精灵
void drawSpr(Spr*spr,int x2,int y2)
{
 if(spr==NULL)
 {
  printf("Spr绘制失败\n");
  return ;
 }
 Res*res=getRes(spr->file,tImg);
 if(res==NULL)
 {
  printf("bitmap文件不存在\n");
  return ;
 }
 int x=x2-spr->x;
 int y=y2-spr->y;
 int32 bit = res->id;
 Act*act = &(spr->act[spr->ind]);
 Pic*pic = &(act->pic[act->ind]);
 drawBitmapEx(bit,
  x,y,spr->w,spr->h,
  pic->px,pic->py,
  pic->pw,pic->ph);
}

void setSprActId(Spr*spr,int id)
{
 if(spr==NULL)
  return ;
 spr->ind = id;
}

void setSprImgId(Spr*spr,int id)
{
 if(spr==NULL)
  return ;
 Act*act = 
 &(spr->act[spr->ind]);
 act->ind=id;
 act->ind = 
 act->ind%act->pic_num;
}

//spr,w,h
void drawSprV9(Spr*spr,int x2,int y2,int iw,int ih,int vw,int vh)
{
 if(spr==NULL)
  return ;
 int x=x2-spr->x;
 int y=y2-spr->y;
 
 int32 bit = 
 getRes(spr->file,tImg)->id;
 Act*act = &(spr->act[spr->ind]);
 Pic*pic = &(act->pic[act->ind]);
 //上一行
 drawBitmapEx(bit,
  x,y,vw,vh,
  pic->px,pic->py,vw,vh);
 drawBitmapEx(bit,
  x+vw,y,
  spr->w-vw*2,vh,
  pic->px+vw,pic->py,
  iw-vw*2,vh);
 drawBitmapEx(bit,
  x+spr->w-vw,y,
  vw,vh,
  pic->px+iw-vw,pic->py,
  vw,vh);
 //绘制中间
 drawBitmapEx(bit,
  x,y+vh,
  vw,spr->h-vh*2,
  pic->px,pic->py+vh,
  vw,ih-vh*2);
 drawBitmapEx(bit,
  x+vw,y+vh,
  spr->w-vw*2,spr->h-vh*2,
  pic->px+vw,pic->py+vh,
  iw-vw*2,ih-vh*2);
 drawBitmapEx(bit,
  x+spr->w-vw,y+vh,
  vw,spr->h-vh*2,
  pic->px+iw-vw,pic->py+vh,
  vw,ih-vh*2);
 //下一行
 drawBitmapEx(bit,
  x,y+spr->h-vh,
  vw,vh,
  pic->px,pic->py+ih-vh,
  vw,vh);
 drawBitmapEx(bit,
  x+vw,y+spr->h-vh,
  spr->w-vw*2,vh,
  pic->px+vw,pic->py+ih-vh,
  iw-vw*2,vh);
 drawBitmapEx(bit,
  x+spr->w-vw,
  y+spr->h-vh,
  vw,vh,
  pic->px+iw-vw,pic->py+ih-vh,
  vw,vh);
}

//设置切片
void setPicJson(Pic*pic,
 cJSON*json,int len)
{
 Pic*pi = pic;
 cJSON*temp[10];
 int i;
 for( i = 0;i<len;i++)
 {
  //获取切片
  temp[0] = 
  cJSON_GetArrayItem(json,i);
  //保存切片
  temp[1] = cJSON_GetObjectItem(
   temp[0],"px");
  pi->px = temp[1]->valueint;
  temp[1] = cJSON_GetObjectItem(
   temp[0],"py");
  pi->py = temp[1]->valueint;
  temp[1] = cJSON_GetObjectItem(
   temp[0],"pw");
  pi->pw = temp[1]->valueint;
  temp[1] = cJSON_GetObjectItem(
   temp[0],"ph");
  pi->ph = temp[1]->valueint;
  pi++;
 }
}


//设置动作
void setActJson(Act*act,
 cJSON*json,int len)
{
 int num;
 //char*name;
 Act*ac = act;
 cJSON*temp[10];
 int i;
 for( i = 0;i<len;i++)
 {
  //获取动作
  temp[0] = 
  cJSON_GetArrayItem(json,i);
  //获取切片
  temp[1] = 
  cJSON_GetObjectItem(temp[0],
   "picture");
  num = 
  cJSON_GetArraySize(temp[1]);
  //载入切片
  setPicJson(&(ac->pic[0]),
   temp[1],num);
  //保存动作
  ac->pic_num = num;
  ac->ind = 0;
  /*
  temp[2] = 
  cJSON_GetObjectItem(temp[0],
   "name");
  name = temp[2]->valuestring;
  ac->name = (char*)
  getRes(name,tStr)->id;*/
  ac++;
 }
}

Spr*loadSprFile(char*path)
{
 int len=0,num=0;
 char*file;
 cJSON*temp[10];
 Spr*spr = malloc(sizeof(Spr));
 //读取精灵文件
 cJSON*sprJson = (cJSON*)
 getRes(path,tJsn)->id;
 //解析精灵文件 
 if(sprJson)
 {
  //读取宽高
  temp[0] = 
  cJSON_GetObjectItem(sprJson,
   "w");
  spr->w = temp[0]->valueint;
  temp[0] = 
  cJSON_GetObjectItem(sprJson,
   "h");
  spr->h = temp[0]->valueint;
  temp[0] = 
  cJSON_GetObjectItem(sprJson,
   "x");
  spr->x = temp[0]->valueint;
  temp[0] = 
  cJSON_GetObjectItem(sprJson,
   "y");
  spr->y = temp[0]->valueint;
  temp[0] = 
  cJSON_GetObjectItem(sprJson,
   "file");
  file = temp[0]->valuestring;
  spr->file = (char*)
  getRes(file,tStr)->path;
  //读取动作
  temp[0] = 
  cJSON_GetObjectItem(sprJson,
   "action");
  num = 
  cJSON_GetArraySize(temp[0]);
  len = cJSON_GetArraySize(temp[0]);
  setActJson(&(spr->act[0]),
   temp[0],len);
 }
 spr->ind = 0;
 spr->xca_file=NULL;
 spr->yca_file=NULL;
 spr->cca_file=NULL;
 spr->act_num = num;
 return spr;
}


//打印spr
char*printSpr(Spr*spr)
{
 //总json
 cJSON*jSpr=
 cJSON_CreateObject();
 //基础属性
 cJSON_AddStringToObject(jSpr,
 "file",spr->file);
 cJSON_AddNumberToObject(jSpr,
 "w",spr->w);
 cJSON_AddNumberToObject(jSpr,
 "h",spr->h);
 cJSON_AddNumberToObject(jSpr,
 "x",spr->x);
 cJSON_AddNumberToObject(jSpr,
 "y",spr->y);
 
 Act *act;
 //act数组
 cJSON*aArr=
 cJSON_CreateArray();
 int i;
 for( i=0;i<spr->act_num;i++)
 {
  act=&(spr->act[i]);
  cJSON*aObj=
  cJSON_CreateObject();
  
  //pic数组
  cJSON*pArr=
  cJSON_CreateArray();
  int j;
  for( j=0;
  j<act->pic_num;j++)
  {
   cJSON*pObj=
   cJSON_CreateObject();
   //循环添加pic
   Pic *pic=&(act->pic[j]);
   cJSON_AddNumberToObject(pObj,
   "pw",pic->pw);
   cJSON_AddNumberToObject(pObj,
   "ph",pic->ph);
   cJSON_AddNumberToObject(pObj,
   "px",pic->px);
   cJSON_AddNumberToObject(pObj,
   "py",pic->py);
   cJSON_AddItemToArray(pArr,
   pObj);
  }
 
  cJSON_AddStringToObject(aObj,
  "name","");
  cJSON_AddItemToObject(aObj,
  "picture",pArr); 
  cJSON_AddItemToArray(aArr,
  aObj);
 }
 cJSON_AddItemToObject(jSpr,
 "action",aArr);
 return cJSON_Print(jSpr);
}

//保存spr
void saveSpr(Spr*spr,char*file)
{
 int32 sFile = open(file,4|8);
 char*data = printSpr(spr);
 write(sFile,data,strlen(data));
 close(sFile);
}


