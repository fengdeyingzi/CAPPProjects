
#ifndef TIMER_H
#define TIMER_H

//���ƶ�ʱ��
int32 drawPlanTimer;
int32 planRayRun;
extern void delCheckTimer();
//�ɻ��ӵ��˶�����
void rayRunTimer(int32 data)
{
  int i;
  for(i=0;i<RayN;i++)
  { 
    rayRun(&plan,plan.ray[i]);
  }
  
  //�л��ƶ�
  for(i=0;i<EmeN;i++)
  {  
    emeRun(&emeN[i]);
  }
 
}
 
//��ʼ�˶���ʱ��
void startRayRun()
{
 planRayRun=timercreate();
 timerstart(planRayRun,30,0,rayRunTimer,1);
}

void endRayTimer()
{
 timerdel(planRayRun); 
}

//���Ʒɻ�����
void dPlanTimer(int32 data)
{
  printf("dplan..\r\n");
 cls(0,0,0);
 
 drawPlan(&plan);
 
 int i;
 for(i=0;i<EmeN;i++)
 { 
   drawEme(&emeN[i]);
 }
 
 ref(0,0,SCRW,SCRH);
}
 
//��ʼ�ɻ���ʱ��
void startDrawPlan()
{
 drawPlanTimer=timercreate();
 timerstart(drawPlanTimer,30,0,dPlanTimer,1);
}

//�����ɻ���ʱ��
void endPlanDraw()
{
 timerdel(drawPlanTimer);
}

//����ȫ����ʱ��
void endAllTimer()
{
 endPlanDraw();
 endRayTimer(); 
 delCheckTimer();
}

#endif