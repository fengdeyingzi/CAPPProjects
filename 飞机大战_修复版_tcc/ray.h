#ifndef RAY_H
#define RAY_H

typedef struct Ray
{
 //����
 int x;
 int y;
 
 //�˶�
 int dx;
 int dy;
 
 //���
 int w;
 int h;
 
 //��ת
 int r;
 
 //ͼƬ
 int32 img;
}Ray;

//�ӵ���ʱ�����ɻ����ƣ�
int32 rayTimer;

//ȫ���ӵ�
Ray ray[10];

//��ʼ���ӵ�ͼƬ
Ray *createRay(Ray *ray)
{
 ray->img=readBitmapFromAssets("p2.png");
 return ray; 
};

//�ӵ���ʱ��
void startRay()
{
 rayTimer=timercreate();
 timerstart(rayTimer,10,0,rayRunTimer,1); 
}

//��ʼ���ӵ�
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

//�����ӵ�
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

//�ͷ��ӵ�ͼƬ����
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

//��ʱ������
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

















