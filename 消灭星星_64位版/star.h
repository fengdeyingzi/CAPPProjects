
#ifndef _STAR_H_
#define _STAR_H_
#include <base.h>
#include <graphics.h>
#include "bitmap.h"
#include "li.h"
#include "coding.h"

typedef struct
{
 int x;     // x坐标
 int y;     //
 int type; //类型
 int isDraw; //是否显示
 int isBeset; //是否被圈住
 } STAR;

typedef struct
{
 int32 bitmap[6];
 _LI *li;
 int32 par_bitmap[6];
 STAR *star;
 int x;
 int y;
 int itemw;
 int itemh;
 int width;
 int height;
 int fen;
 int32 view_fen;
 } _STARS;
 
 void star_upset(_STARS *stars);
 

//创建星星数组
//参数：x坐标 y坐标 宽度 高度
_STARS *star_create(int x,int y,int width,int height)
{
 char text[50];
 _STARS *stars=malloc(sizeof(_STARS));
 memset(stars,0,sizeof(_STARS));
 stars->star=malloc(sizeof(STAR)*width*height);
 stars->x= x;
 stars->y= y;
 stars->width=width;
 stars->height=height;
 stars->itemw=64;
 stars->itemh=64;
 int i;
 for(i=0;i<=5;i++)
 {
  sprintf(text,"block_%d.png",i);
  printf("%s\n","测试1");
  stars->bitmap[i]=readBitmapFromAssets(text);
 }
 
 int temp_bitmap=readBitmapFromAssets("particle.png");
   //小星星粒子
   int color[6]={0xffffff, 0xff90aa, 0x30f000, 0x8dc0f0, 0xf060f0, 0xffff00};
   printf("%s\n","测试2");
   for(i=0;i<=5;i++)
   {
   stars->par_bitmap[i] =bitmap_drawColor(temp_bitmap,color[i]);
   
   }
 bitmapFree(temp_bitmap);
 printf("%s\n","测试3");
 stars->li= li_create(SCRW/2,SCRH/2);
 li_setColor(stars->li,0xff6420);
   li_setSpeed(stars->li,5);
   li_setHp(stars->li,50);
   li_setSize(stars->li,80);
   li_setV(stars->li,70);
   
   li_setFirst(stars->li);
   printf("%s\n","测试4");
   li_setBitmap(stars->li,stars->par_bitmap[0]);
 
 //循环生成星星
 
 int j;
 int irand=1;
 for(i=0;i<height;i++)
 {
  for(j=0;j<width;j++)
  {
   stars->star[i*width+j].type=irand;
   stars->star[i*width+j].isDraw=TRUE;
   stars->star[i*width+j].x=j*stars->itemw;
   stars->star[i*width+j].y=i*stars->itemh;
   stars->star[i*width+j].isBeset=0;
  }
  irand++;
  if(irand>5)irand=1;
 }
 printf("%s\n","测试5");
 star_upset(stars);
 return stars;
};

//设置分数控件
void star_setview(_STARS *stars,int view)
{
 stars->view_fen=view;
 
}


//打乱星星
void star_upset(_STARS *stars)
{
 int i;
 int j;
 int len=stars->width*stars->height;
 for(i=0;i<len;i++)
 {
  STAR temp=stars->star[i];
  int ri=i+rand()%(len-i);
  stars->star[i]= stars->star[ri];
  stars->star[ri]=temp;
 }
 
}

int star_getType(_STARS *stars,int x,int y)
{
 return stars->star[y*stars->width + x].type;
}

//消灭指定坐标内的星星

//判断指定位置是否有星星
int star_isDraw(_STARS *stars,int x,int y)
{
 if(x>=0 && x<stars->width && y>=0 && y<stars->height && stars->star[y*stars->width + x].isDraw)
 return TRUE;
 return FALSE;
}

int star_isBeset(_STARS *stars,int x,int y)
{
 if(x>=0 && x<stars->width && y>=0 && y<stars->height && (!stars->star[y*stars->width + x].isBeset))
 return FALSE;
 return TRUE;
}

//获取指定位置的星星
STAR *star_get(_STARS *stars,int x,int y)
{
 if(x>=0 && x<stars->width && y>=0 && y<stars->height)
 return &(stars->star[y*stars->width + x]);
 return NULL;
}

//获取星星粒子播放时间
int star_getTime(_STARS *stars)
{
 return stars->li->time;
}

//判断星星是否可以点击
int star_isImpact(_STARS *stars,int x,int y)
{
 int ix=x;
 int iy=y;
 int type;
 int isimpact=0;
 //判断当前是否有星星
 if(star_isDraw(stars,ix,iy))
 {
  type=star_getType(stars,ix,iy);
  
  
  //判断四个方向
  if(star_isDraw(stars,ix,iy-1) && star_getType(stars,ix,iy-1)==type)
  {
  
  return TRUE;
  
  }
  if(star_isDraw(stars,ix,iy+1) && star_getType(stars,ix,iy+1)==type)
  {
  
  return TRUE;
  
  }
  if(star_isDraw(stars,ix-1,iy)&& star_getType(stars,ix-1,iy)==type )
  {
  
  return TRUE;
  
  }
  if(star_isDraw(stars,ix+1,iy) && star_getType(stars,ix+1,iy)==type)
  {
  
  return TRUE;
  
  }
  
  
  
 }
 return FALSE;
 
}

//设置待点击的星星(圈住星星)
int star_beset(_STARS *stars,int x,int y)
{
 int ix=x;
 int iy=y;
 int type;
 int isimpact=0;
 //判断当前是否有星星
 if(star_isDraw(stars,ix,iy))
 {
  type=star_getType(stars,ix,iy);
  stars->star[iy * stars->width +ix].isBeset=TRUE;
  
  //判断四个方向
  if(!star_isBeset(stars,ix,iy-1) && star_getType(stars,ix,iy-1)==type)
  {
  
  star_beset(stars,ix,iy-1);
  isimpact=1;
  
  }
  if(!star_isBeset(stars,ix,iy+1) && star_getType(stars,ix,iy+1)==type)
  {
  
  star_beset(stars,ix,iy+1);
  isimpact=1;
  
  }
  if(!star_isBeset(stars,ix-1,iy)&& star_getType(stars,ix-1,iy)==type )
  {
  
  star_beset(stars,ix-1,iy);
  isimpact=1;
  
  }
  if(!star_isBeset(stars,ix+1,iy) && star_getType(stars,ix+1,iy)==type)
  {
  
  star_beset(stars,ix+1,iy);
  isimpact=1;
  
  }
  
  
  
 }
 return 0;
}

//将圈住的星星销毁
int star_burst(_STARS *stars)
{
  int ix,iy;
  int i=0;
 for(iy=0;iy<stars->height;iy++)
 {
  for(ix=0;ix<stars->width;ix++)
  {
   STAR *star=&(stars->star[iy*stars->width+ix]);
   if(star->isBeset)
   {
    star->isDraw=FALSE;
    star->isBeset=FALSE;
    li_setBitmap(stars->li,stars->par_bitmap[star->type]);
    i++;
   }
  }
 }
 //分数增加
 stars->fen+=i*i*10;
 //更新分数
 if(stars->view_fen)
 {
 char text[300];
 sprintf(text,"分数：%d",stars->fen);
 char *un=gbToUn(text);
 view_setText(stars->view_fen, un);
 free(un);
 }
 if(i>0)
 li_start(stars->li);
 
 return 0;
}

//点击一颗星星
int star_impact(_STARS *stars,int x,int y)
{
 int ix=x;
 int iy=y;
 int type;
 int isimpact=0;
 //判断当前是否有星星
 if(star_isDraw(stars,ix,iy))
 {
  type=star_getType(stars,ix,iy);
  stars->star[iy * stars->width +ix].isDraw=0;
  
  //判断四个方向
  if(star_isDraw(stars,ix,iy-1) && star_getType(stars,ix,iy-1)==type)
  {
  
  star_impact(stars,ix,iy-1);
  isimpact=1;
  
  }
  if(star_isDraw(stars,ix,iy+1) && star_getType(stars,ix,iy+1)==type)
  {
  
  star_impact(stars,ix,iy+1);
  isimpact=1;
  
  }
  if(star_isDraw(stars,ix-1,iy)&& star_getType(stars,ix-1,iy)==type )
  {
  
  star_impact(stars,ix-1,iy);
  isimpact=1;
  
  }
  if(star_isDraw(stars,ix+1,iy) && star_getType(stars,ix+1,iy)==type)
  {
  
  star_impact(stars,ix+1,iy);
  isimpact=1;
  
  }
  
  
  
 }
 return 0;
}


//星星event事件
int star_event(_STARS *stars,int type,int p1,int p2)
{
 //判断点中了哪个星星
 if(type==MS_DOWN)
 {
  int ix=( p1 - stars->x)/stars->itemw;
 int iy= (p2 - stars->y)/stars->itemh;
  if(ix>=0 && ix<stars->width && iy>=0 && iy<stars->height)
 {
  //将星星隐藏
  if(star_isImpact(stars,ix,iy))
  star_beset(stars,ix,iy);
  li_setxy(stars->li,p1,p2);
 }
 }
 if(type==MS_UP)
 {
 star_burst(stars);
 
 }
 
 return 0;
}

//判断星星是否可以点击，(如果找不到可以点击的星星就进入下一关)
int star_isNoImpact(_STARS *stars)
{
 int ix,iy;
 for(iy=0;iy<stars->height;iy++)
 {
  for(ix=0;ix<stars->width;ix++)
  {
   if(star_isImpact(stars,ix,iy))
     return FALSE;
  }
 }
 return TRUE;
}

//星星整体右移
int star_moveRight(_STARS *stars)
{
 int ix,iy=0;
 int type=0;
 iy= stars->height-1;
   for(ix=stars->width-1; ix>0;ix--)
   {
   
    //检测一纵列都木有星星
    
    for(iy=0;iy<stars->height;iy++)
    {
          STAR *temp=star_get(stars,ix,iy);
    
     
     if(temp->isDraw)
     type=1;
    }
    if(type==1)
    {
     type=0;
     continue;
    }
    STAR *star=star_get(stars,ix,stars->height-1);
    STAR *starleft=star_get(stars,ix-1,stars->height-1);
    
    //右移
    if( !star->isDraw && starleft->isDraw)
    {
     for(int i=0;i<stars->height;i++)
     {
     star = star_get(stars, ix,i);
     starleft = star_get (stars,ix-1,i);
     STAR *temp= star;
     
     star->y= starleft->y;
     star->x= starleft->x;
     star->type=starleft->type;
     star->isDraw= starleft->isDraw;
     starleft->isDraw=FALSE;
     
     }
    }
    
   }
 
 return 0;
}

//星星运动事件
//星星下落
int star_run(_STARS *stars)
{
 int len=stars->width*stars->height;
 int ix,iy;
 //屏幕坐标
 int px,py;
 
 
 
 
 for(iy=stars->height-1;iy>=0;iy--)
 {
  for(ix=0;ix<stars->width;ix++)
  {
   STAR *star= star_get(stars,ix,iy);
   STAR *starup= star_get(stars,ix,iy-1);
  
    //下落
    //判断下方是否为空
    
    if(starup!=NULL)
    if(!star->isDraw && starup->isDraw)
    {
     //交换位置
     
     STAR *temp= star;
     
     star->y= starup->y;
     star->x= starup->x;
     star->type=starup->type;
     star->isDraw= starup->isDraw;
     starup->isDraw=FALSE;
     
     //*star=*starup;
     //*starup=*temp;
    }
    
    star=star_get(stars,ix,iy);
    px=stars->itemw * ix;
    py=stars->itemh * iy;
    int tx=star->x;
    int ty=star->y;
    if(tx<px)tx+=8;
    else if(tx>px)tx-=8;
    if(ty<py)ty+=8;
    else if(ty>py)ty-=8;
    star->x=tx;
    star->y=ty;
   
   
  }
 }
 star_moveRight(stars);
 li_run(stars->li);
 
 
 return 0;
}



//显示星星
int star_draw(_STARS *stars)
{
 int ix,iy;
 for(iy=0;iy<stars->height;iy++)
 {
  for(ix=0;ix<stars->width;ix++)
  {
   STAR star=stars->star[iy*stars->width + ix];
   if(star.isBeset)
   drawBitmap(stars->bitmap[0],stars->x+star.x,stars->y+star.y);
   if(star.isDraw)
   drawBitmap(stars->bitmap[star.type],stars->x+star.x,stars->y+star.y);
   
  }
 }
 li_draw(stars->li);
 return 0;
}

//销毁星星
int star_free(_STARS *stars)
{
 //释放bitmap
 for(int i=0;i<=5;i++)
 {
  bitmapFree(stars->bitmap[i]);
  bitmapFree(stars->par_bitmap[i]);
 }
 //释放star
 free(stars->star);
 li_free(stars->li);
 //释放全部
 free(stars);
 
 return 0;
}























#endif

