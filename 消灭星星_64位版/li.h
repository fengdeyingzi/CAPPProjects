
#ifndef _LI_H_
#define _LI_H_
#include <base.h>
#include <graphics.h>
#include <android.h>
#include <ex_math.h>



typedef struct
{
 float x; //����
 float y; //����
 int r;
 float speed_x;  //�����˶�ֵ
 float speed_y;   //�����˶�ֵ
 int hp; //����
 int color;
 int alpha; //͸����
} _POINT;


typedef struct
{
 _POINT *point;
 int32 bitmap; //����ͼƬ
 int x;
 int y; //���ӷ����� ����
 int r; //���
 int v; //�ٶ�
 int min_v; //��С�ٶ�
 int size; //��������
 int birth; //������
 int speed; //���ӵݼ���
 int hp; //����
 int color; //��ɫ rgbֵ
 int coreColor; //������ɫ
 int isRandColor; //�Ƿ���������ɫ
 int isDirection; //�Ƿ��з���
 int direction;//����
 int isFirst; //�Ƿ�ֻ����һ��
 int time; //��������ʱ��
} _LI;



//��������
_LI *li_create(int x,int y)
{
 _LI *li = malloc(sizeof(_LI));
 li->x=x;
 li->y=y;
 li->r=5;
 li->v=2;
 li->min_v=4;
 li->bitmap=0;
 li->isRandColor=FALSE;
 li->speed=20;
 li->isDirection=FALSE;
 li->direction=270;
 li->hp= 20;
 li->birth=6;
 li->size=400;
 li->time=0;
 li->point = malloc(sizeof(_POINT)*li->size);
 memset(li->point,0,sizeof(_POINT)*li->size);
 li->color=0xffffff;
 li->coreColor=0xffffff;
 
 return li;
};

int li_start(_LI *li)
{
 memset(li->point,0,sizeof(_POINT)*li->size);
 
 return 0;
}

//�����˶�
int li_run(_LI *li)
{
 //��������
 int i;
 int size=0;
 
 for(i=0;i<li->size;i++)
 {
 if(li->point[i].hp<=0)
  {
   _POINT *point=&(li->point[i]);
   //�ж��Ƿ�Ϊ��һ������
   if((point->x!=0) && (point->y!=0) && li->isFirst) break;

  point->hp=li->hp;
  point->x=li->x;
  point->y=li->y;
  point->alpha=255;
  int alpha=point->alpha;
  point->color=li->color;
  if(li->isRandColor)
  point->color|=rand()%0xffffff;
  point->r=li->r;
  point->speed_x=-3+rand()%6;
  point->speed_y=-3+rand()%6;
  int x,y;
  int v=( (rand()%(li->v - li->min_v+1)) +li->min_v)*100+10;
 // printf("%d\n",v);
  toSpin(0,0, v, v, rand()%360, &x,&y);
  point->speed_x=((float)x)/100;
  point->speed_y=((float)y)/100;
  size++;
  if(size>=li->birth) break;
  }
 }
 
 
 //�˶�
 for(i=0;i<li->size;i++)
 {
  _POINT *point=&(li->point[i]);
  point->x+=point->speed_x;
  point->y+=point->speed_y;
  int x,y;
  int v=200;
  if(li->isDirection)
  {
   toSpin(0,0, v, v, li->direction, &x,&y);
   point->speed_x+=((float)x)/100;
  point->speed_y+=((float)y)/100;
  }
  point->hp--;
  point->alpha-=li->speed;
  if(point->alpha<0)
  point->alpha=0;
 }
 
 li->time++;
 
 return 0;
}
//���������ٶ�
int li_setV(_LI *li,int v)
{
 
 li->v=v;
 return 0;
}

//��������ֻ����һ��
int li_setFirst(_LI *li)
{
 li->isFirst=TRUE;
 return 0;
}

//��������ͼƬ
int li_setBitmap(_LI *li, int bitmap)
{
 li->bitmap= bitmap;
 return 0;
}

//��������ֻ����һ��

//��ȡ���Ӳ���ʱ��
int li_getTime(_LI *li)
{
 
 return li->time;
}



//��������͸���ȵݼ�����
int li_setSpeed(_LI *li, int speed)
{
 li->speed=speed;
 
 return 0;
}

//�����������ɽǶ�
int li_setDirection(_LI *li, int direction)
{
  li->isDirection=TRUE;
  li->direction=direction;
return 0;
}


//������������
int li_setHp(_LI *li, int hp)
{
 li->hp=hp;
 
 return 0;
}

//������������
int li_setSize(_LI *li, int size)
{
 li->size=size;
 if(li->point) free(li->point);
 li->point = malloc(sizeof(_POINT)*li->size);
 memset(li->point,0,sizeof(_POINT)*li->size);
 return 0;
}

//������������
int li_setxy(_LI *li,int x,int y)
{
 li->x=x;
 li->y=y;
 return 0;
}

//����������ɫ
int li_setColor(_LI *li, int color)
{
 li->color=color;
 return 0;
}

//��ʾ����
int li_draw(_LI *li)
{
 int i;
 int r,g,b;
 
 //�����ͼƬ
 if(li->bitmap)
 {
  for(i=0;i<li->size;i++)
  {
   _POINT *point= &(li->point[i]);
   if( point->hp>0 )
   drawBitmapRotate(li->bitmap, point->x,point->y,0,0, 0, point->alpha);
  }
  
 }
 else
 {
 for(i=0;i<li->size;i++)
 {
  _POINT *point= &(li->point[i]);
   if(point->hp>0 && point->x>=0 &&point->x<SCRW && point->y>=0 && point->y<SCRH)
   {
   r= (point->color>>16) & 0xff;
   g= (point->color>>8) & 0xff;
   b= (point->color)&0xff;
   r= r+(255-r)*point->alpha/255;
   g= g+(255-g)*point->alpha/255;
   b= b+(255-b)*point->alpha/255;
  drawCir(point->x,point->y,point->r, (point->alpha<<24) | (r<<16) | (g<<8) | b); 
//  drawCir(point->x,point->y,point->r/2,  (point->alpha<<24) | point->color);
  //dpoint(point->x,point->y,point->color);
  }
 }
 }
 
 return 0;
}



//ɾ������
int li_free(_LI *li)
{
 free(li->point);
 free(li);
 return 0;
}












#endif






























