
#ifndef PLAN_H
#define PLAN_H

#define RayN 3



typedef struct Plan
{
 //坐标
 int x; int y;
 //宽高
 int w; int h;
 //运动
 int dx; int dy;
 //旋转
 int r;
 //图片
 int32 img;
 
 struct Plan *ray[RayN];
}Plan;

//全局飞机
Plan plan;
Plan *initRay(Plan *plan,Plan *ray);
int createPlanImg(Plan *plan);
Plan *createRayImg(Plan *ray);
//初始化飞机，返回Plan指针
Plan *initPlan(Plan *plan)
{
  plan->x=400;
  plan->y=700;
    
  plan->w=140;
  plan->h=80;
  
  plan->dx=10;
  plan->dy=8;
  
  plan->r=0;
  
  //初始化
  createPlanImg(plan);
  
  int i;
  for(i=0;i<RayN;i++)
  {
    //给子弹分配内存
    plan->ray[i]=malloc(sizeof(Plan));
    
    createRayImg(plan->ray[i]);
    initRay(plan,plan->ray[i]);
  }
  
  return plan;
};

//初始化子弹
Plan *initRay(Plan *plan,Plan *ray)
{
  //坐标和旋转度数和飞机相同
  ray->r=plan->r; 
  ray->x=plan->x;
  ray->y=plan->y;
  
  ray->w=41;
  ray->h=111;
  
  ray->dy=-rand()%20-20;
  ray->dx=0;
  
  return ray;
};

//初始化飞机图片
int createPlanImg(Plan *plan)
{
 
 plan->img=readBitmapFromAssets("plan_1.png");  
 
 return plan->img;
}

//初始化子弹图片
Plan *createRayImg(Plan *ray)
{
 ray->img=readBitmapFromAssets("p2.png");
 return ray; 
};


//绘制子弹
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

//绘制飞机
void drawPlan(Plan *plan)
{
  drawBitmapRotate(plan->img,plan->x,plan->y,plan->w/2,plan->h/2,plan->r,255);
  
  //循环绘制子弹数组
  int i;
  for(i=0;i<RayN;i++)
  {
    drawRay(plan->ray[i]);
  }
  
};

//运动的子弹
void rayRun(Plan *plan,Plan *ray)
{     
  if(ray->y<=0)
    initRay(plan,ray); 
       
  ray->x+=ray->dx;
  ray->y+=ray->dy;
}

//运动的飞机
void planRun(Plan *plan,int p1,int p2)
{
  //右
  if(p1>plan->x)
  { 
    plan->x+=plan->dx;
    plan->r=45;
  }
  
  //左   
  if(p1<plan->x)
  {
    plan->x-=plan->dx;
    plan->r=-45;
  }
  
  //下
  if(p2>plan->y+plan->h)
  { 
    plan->y+=plan->dy;
  }
   
  //上     
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


//释放飞机内存
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









