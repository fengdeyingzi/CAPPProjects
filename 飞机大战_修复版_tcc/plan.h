
#ifndef PLAN_H
#define PLAN_H

#define RayN 3



typedef struct Plan
{
 //����
 int x; int y;
 //���
 int w; int h;
 //�˶�
 int dx; int dy;
 //��ת
 int r;
 //ͼƬ
 int32 img;
 
 struct Plan *ray[RayN];
}Plan;

//ȫ�ַɻ�
Plan plan;
Plan *initRay(Plan *plan,Plan *ray);
int createPlanImg(Plan *plan);
Plan *createRayImg(Plan *ray);
//��ʼ���ɻ�������Planָ��
Plan *initPlan(Plan *plan)
{
  plan->x=400;
  plan->y=700;
    
  plan->w=140;
  plan->h=80;
  
  plan->dx=10;
  plan->dy=8;
  
  plan->r=0;
  
  //��ʼ��
  createPlanImg(plan);
  
  int i;
  for(i=0;i<RayN;i++)
  {
    //���ӵ������ڴ�
    plan->ray[i]=malloc(sizeof(Plan));
    
    createRayImg(plan->ray[i]);
    initRay(plan,plan->ray[i]);
  }
  
  return plan;
};

//��ʼ���ӵ�
Plan *initRay(Plan *plan,Plan *ray)
{
  //�������ת�����ͷɻ���ͬ
  ray->r=plan->r; 
  ray->x=plan->x;
  ray->y=plan->y;
  
  ray->w=41;
  ray->h=111;
  
  ray->dy=-rand()%20-20;
  ray->dx=0;
  
  return ray;
};

//��ʼ���ɻ�ͼƬ
int createPlanImg(Plan *plan)
{
 
 plan->img=readBitmapFromAssets("plan_1.png");  
 
 return plan->img;
}

//��ʼ���ӵ�ͼƬ
Plan *createRayImg(Plan *ray)
{
 ray->img=readBitmapFromAssets("p2.png");
 return ray; 
};


//�����ӵ�
Plan *drawRay(Plan *ray)
{
  if(ray->r==0)
  drawBitmapRotate(ray->img,ray->x-5,ray->y-ray->h+10,ray->w/2,ray->h/2,ray->r,255);
  
  if(ray->r==45)
  {
    ray->dx=-ray->dy;
    drawBitmapRotate(ray->img,ray->x+ray->w,ray->y-ray->h/2+10,ray->w/2,ray->h/2,ray->r,255);
  }
  
  if(ray->r==-45)
  {
    ray->dx=ray->dy;
    drawBitmapRotate(ray->img,ray->x-ray->w-10,ray->y-ray->h/2+10,ray->w/2,ray->h/2,ray->r,255);
  }
  
  if(ray->r==180)
  {
    drawBitmapRotate(ray->img,ray->x-5,ray->y-ray->h+10,ray->w/2,ray->h/2,ray->r,255);
  }
  
  return ray;
};

//���Ʒɻ�
void drawPlan(Plan *plan)
{
  drawBitmapRotate(plan->img,plan->x,plan->y,plan->w/2,plan->h/2,plan->r,255);
  
  //ѭ�������ӵ�����
  int i;
  for(i=0;i<RayN;i++)
  {
    drawRay(plan->ray[i]);
  }
  
};

//�˶����ӵ�
void rayRun(Plan *plan,Plan *ray)
{     
  if(ray->y<=0)
    initRay(plan,ray); 
       
  ray->x+=ray->dx;
  ray->y+=ray->dy;
}

//�˶��ķɻ�
void planRun(Plan *plan,int p1,int p2)
{
  //��
  if(p1>plan->x)
  { 
    plan->x+=plan->dx;
    plan->r=45;
  }
  
  //��   
  if(p1<plan->x)
  {
    plan->x-=plan->dx;
    plan->r=-45;
  }
  
  //��
  if(p2>plan->y+plan->h)
  { 
    plan->y+=plan->dy;
  }
   
  //��     
  if(p2<plan->y)
  {
    plan->y-=plan->dy;
  }
  
  //
  if(p1>=plan->x-plan->w/2)
  if(p1<=plan->x+plan->w/2)
  {
    plan->r=0;
  }
  
  if(p2>=plan->y-plan->h/2)
  if(p2<=plan->y+plan->h/2)
  {
    plan->r=0;
  }
  
}


//�ͷŷɻ��ڴ�
void delPlan(Plan *plan)
{
  bitmapFree(plan->img);
 
  int i;
  for(i=0;i<RayN;i++)
  { 
    bitmapFree(plan->ray[i]->img);
    free(plan->ray[i]);
  }
  
};


#endif









