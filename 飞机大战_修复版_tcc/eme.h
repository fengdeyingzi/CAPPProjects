
#include "plan.h"

#ifndef EME_H
#define EME_H

#define EmeN 5

//全局敌机
Plan emeN[EmeN];

//初始化子弹
Plan *initEmeRay(Plan *plan,Plan *ray)
{
  //坐标和旋转度数和飞机相同
  ray->r=plan->r; 
  ray->x=plan->x;
  ray->y=plan->y+plan->h/2;
  
  ray->w=15;
  ray->h=15;
  
  ray->dy=rand()%10+5+plan->dy;
  ray->dx=rand()%10-5;
  
  return ray;
};

//初始化飞机图片
int32 createEmeImg(Plan *plan)
{
 plan->img=readBitmapFromAssets("plan_blue.png");  
 
 
 return plan->img;
};


Plan *initEme(Plan *emei)
{
  printf("initEme..\r\n");
  sand(getuptime());
  printf("rand..\r\n");
 
  emei->x=rand()%SCRW;
  emei->y=0;
    
  emei->w=120;
  emei->h=100;
  
  emei->dx=0;
  emei->dy=rand()%5+2;
  
  emei->r=180;
  
  //初始化
  createEmeImg(emei);
  
  int i;
  for(i=0;i<RayN;i++)
  {
    //给子弹分配内存
    emei->ray[i]=malloc(sizeof(Plan));
    
    createRayImg(emei->ray[i]);
    initEmeRay(emei,emei->ray[i]);
    
    emei->ray[i]->img=readBitmapFromAssets("blue.png");    
       
  }
  
  return emei; 
};

void drawEme(Plan *emei)
{
  drawPlan(emei);
}


//运动的子弹
void emeRayRun(Plan *plan,Plan *ray)
{    
  if(ray->y>=SCRH)
    initEmeRay(plan,ray); 
  
  
  ray->x+=ray->dx;
  ray->y+=ray->dy;
}

//敌机运动
void emeRun(Plan *eme)
{
 
 eme->y+=eme->dy;
 eme->x+=eme->dx;
 
 //子弹运动
 int i;
 for(i=0;i<RayN;i++)
 {
   emeRayRun(eme,eme->ray[i]); 
 }
 
 //达到底部
 if(eme->y>=SCRH)
   initEme(eme);
 
}


void delEme()
{
 //子弹运动
 int i;
 for(i=0;i<EmeN;i++)
 {
   delPlan(&emeN[i]);
 }

}

#endif

