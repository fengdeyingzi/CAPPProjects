
#ifndef CHECK_H
#define CHECK_H
#include <base.h>
int32 checkTimer;

/*�ɻ�plan , ����emeN  EmeN��*/
void delCheckTimer();
//�ɻ��͵�ǰ����
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

//�ɻ���һ���л����ӵ�
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


//�л����ӵ�
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


//�ɻ���ȫ������
void planAemeN()
{
  int i;
  for(i=0;i<EmeN;i++)
  {
     //�ɻ��͵���
     planAeme(&plan,&emeN[i]);
     
     //�ɻ����ӵ�
     planAray(&plan,&emeN[i]);
     
     //���˺��ӵ�
     emeAray(&plan,&emeN[i]);
  }
 
}



void check(int32 data)
{
  printf("check................\r\n");
  planAemeN();
  printf("check success\r\n");
}

//��ʼ��ⶨʱ��
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