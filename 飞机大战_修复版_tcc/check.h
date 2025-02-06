
#ifndef CHECK_H
#define CHECK_H
#include <base.h>
int32 checkTimer;

/*飞机plan , 敌人emeN  EmeN个*/
void delCheckTimer();
//飞机和当前敌人
void planAeme(Plan *plan,Plan *emei)
{
  if(plan->x>=emei->x-emei->w/2-plan->w/2)
  if(plan->x<=emei->x+emei->w/2+plan->w/2)
  
  if(plan->y>=emei->y-emei->h/2-plan->h/2)
  if(plan->y<=emei->y+emei->h/2+plan->h/2)
  {
    shake(500);
    initEme(emei);    
  }
}

//飞机和一个敌机的子弹
void planAray(Plan *plan,Plan *emei)
{
 int i;
 for(i=0;i<RayN;i++)
 {
  if(plan->x>=emei->ray[i]->x-emei->ray[i]->w/2-plan->w/2)
  if(plan->x<=emei->ray[i]->x+emei->ray[i]->w/2+plan->w/2)
  
  if(plan->y>=emei->ray[i]->y-emei->ray[i]->h/2-plan->h/2)
  if(plan->y<=emei->ray[i]->y+emei->ray[i]->h/2+plan->h/2)
  {
    shake(50);
    initEmeRay(emei,emei->ray[i]);
  }
 }

}


//敌机和子弹
void emeAray(Plan *plan,Plan *emei)
{
 int i;
 for(i=0;i<RayN;i++)
 {
  if(plan->ray[i]->x>=emei->x-emei->w/2-plan->ray[i]->w/2)
  if(plan->ray[i]->x<=emei->x+emei->w/2+plan->ray[i]->w/2)
  
  if(plan->ray[i]->y>=emei->y-emei->h/2-plan->ray[i]->h/2)
  if(plan->ray[i]->y<=emei->y+emei->h/2+plan->ray[i]->h/2)
  {
      initEme(emei);
  }
  
 }  
   
}


//飞机和全部敌人
void planAemeN()
{
  int i;
  for(i=0;i<EmeN;i++)
  {
     //飞机和敌人
     planAeme(&plan,&emeN[i]);
     
     //飞机和子弹
     planAray(&plan,&emeN[i]);
     
     //敌人和子弹
     emeAray(&plan,&emeN[i]);
  }
 
}



void check(int32 data)
{
  printf("check................\r\n");
  planAemeN();
  printf("check success\r\n");
}

//开始检测定时器
void startCheckRun()
{
 checkTimer=timercreate();
 timerstart(checkTimer,30,0,check,1);
}


void delCheckTimer()
{
 timerdel(checkTimer); 
}



#endif