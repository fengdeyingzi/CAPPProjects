
#include "plan.h"

#ifndef EME_H
#define EME_H

#define EmeN 5

//ȫ�ֵл�
Plan emeN[EmeN];

//��ʼ���ӵ�
Plan *initEmeRay(Plan *plan,Plan *ray)
{
  //�������ת�����ͷɻ���ͬ
  ray->r=plan->r; 
  ray->x=plan->x;
  ray->y=plan->y+plan->h/2;
  
  ray->w=15;
  ray->h=15;
  
  ray->dy=rand()%10+5+plan->dy;
  ray->dx=rand()%10-5;
  
  return ray;
};

//��ʼ���ɻ�ͼƬ
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
  
  //��ʼ��
  createEmeImg(emei);
  
  int i;
  for(i=0;i<RayN;i++)
  {
    //���ӵ������ڴ�
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


//�˶����ӵ�
void emeRayRun(Plan *plan,Plan *ray)
{    
  if(ray->y>=SCRH)
    initEmeRay(plan,ray); 
  
  
  ray->x+=ray->dx;
  ray->y+=ray->dy;
}

//�л��˶�
void emeRun(Plan *eme)
{
 
 eme->y+=eme->dy;
 eme->x+=eme->dx;
 
 //�ӵ��˶�
 int i;
 for(i=0;i<RayN;i++)
 {
   emeRayRun(eme,eme->ray[i]); 
 }
 
 //�ﵽ�ײ�
 if(eme->y>=SCRH)
   initEme(eme);
 
}


void delEme()
{
 //�ӵ��˶�
 int i;
 for(i=0;i<EmeN;i++)
 {
   delPlan(&emeN[i]);
 }

}

#endif

