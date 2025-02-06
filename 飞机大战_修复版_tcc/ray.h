#ifndef RAY_H
#define RAY_H

typedef struct Ray
{
 //坐标
 int x;
 int y;
 
 //运动
 int dx;
 int dy;
 
 //宽高
 int w;
 int h;
 
 //旋转
 int r;
 
 //图片
 int32 img;
}Ray;

//子弹定时器（飞机绘制）
int32 rayTimer;

//全局子弹
Ray ray[10];

//初始化子弹图片
Ray *createRay(Ray *ray)
{
 ray->img=readBitmapFromAssets("p2.png");
 return ray; 
};

//子弹定时器
void startRay()
{
 rayTimer=timercreate();
 timerstart(rayTimer,10,0,rayRunTimer,1); 
}

//初始化子弹
Ray *initRay(Ray *ray)
{
  ray->r=plan.r; 
  
  ray->x=plan.x;
  ray->y=plan.y;
  
  ray->w=41;
  ray->h=111;
  
  ray->dy=-rand()%10-10;
  ray->dx=0;
  
  return ray;
};

//绘制子弹
void drawRay(Ray *ray)
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
 
// drawBitmapRotate(ray->img,ray->x-5,ray->y-ray->h+10,ray->w/2,ray->h/2,ray->r,255);
};

//释放子弹图片缓存
void delRay()
{
 timerdel(rayTimer);
 
 int i;
 for(i=0;i<sizeof(ray)/sizeof(Ray);i++)
   bitmapFree(ray[i].img);
};

void rayRun(Ray *ray)
{
  ray->x+=ray->dx;
  ray->y+=ray->dy;
     
  if(ray->y<=0)
    initRay(ray);    
}

//定时器函数
void rayRunTimer(int32 data)
{
  printf("rayRunTimer\r\n");
 int i;
 
 for(i=0;i<sizeof(ray)/sizeof(Ray);i++)
 {
   rayRun(&ray[i]); 
 }

}

#endif

















