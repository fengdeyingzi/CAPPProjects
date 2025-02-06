
#ifndef TIMER_H
#define TIMER_H

//绘制定时器
int32 drawPlanTimer;
int32 planRayRun;
extern void delCheckTimer();
//飞机子弹运动函数
void rayRunTimer(int32 data)
{
  int i;
  for(i=0;i<RayN;i++)
  { 
    rayRun(&plan,plan.ray[i]);
  }
  
  //敌机移动
  for(i=0;i<EmeN;i++)
  {  
    emeRun(&emeN[i]);
  }
 
}
 
//开始运动定时器
void startRayRun()
{
 planRayRun=timercreate();
 timerstart(planRayRun,30,0,rayRunTimer,1);
}

void endRayTimer()
{
 timerdel(planRayRun); 
}

//绘制飞机函数
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
 
//开始飞机定时器
void startDrawPlan()
{
 drawPlanTimer=timercreate();
 timerstart(drawPlanTimer,30,0,dPlanTimer,1);
}

//结束飞机定时器
void endPlanDraw()
{
 timerdel(drawPlanTimer);
}

//结束全部定时器
void endAllTimer()
{
 endPlanDraw();
 endRayTimer(); 
 delCheckTimer();
}

#endif