

#ifndef DRAW_H
#define DRAW_H

//»æÖÆ¶¨Ê±Æ÷
int32 drawTimer;

void draw(int32 data)
{
  printf("draw...\r\n");
 cls(0,0,0);
 
 int i;
 for(i=0;i<sizeof(ray)/sizeof(Ray);i++)
   drawRay(&ray[i]);
 
 drawPlan(&plan);
 
 for(i=0;i<sizeof(b)/sizeof(Ball);i++)
   drawBall(&b[i]); 
   
 ref(0,0,SCRW,SCRH);
}
 
 
void startDraw()
{
 drawTimer=timercreate();
 timerstart(drawTimer,30,0,draw,1);
}


void endDraw()
{
 timerdel(drawTimer);
} 

#endif