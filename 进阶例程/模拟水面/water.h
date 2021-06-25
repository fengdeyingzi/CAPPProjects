

#ifndef _WATER_H_
#define _WATER_H_

typedef struct WATER
{
 int x;
 int y;
 int size;
 int r; //角度
} WATER;

typedef struct
{
 WATER *waters[300];
 int size;
} WATERS;

//创建海面
WATERS *wa_create()
{
 
 WATERS *wa=malloc(sizeof(WATERS));
 memset(wa,0,sizeof(WATERS));
 return wa;
};

//添加一个水滴
void wa_add(WATERS *was,int x,int y,int size,int r)
{
 WATER *wa=malloc(sizeof(WATER));
 wa->x=x;
 wa->y=y;
 wa->size=size;
 wa->r=r;
 was->waters[was->size++]=wa;
 
}

//显示水滴
void wa_draw(WATERS *was)
{
 int i;
 int x,y;
  for(i=0;i<was->size;i++)
 {
  WATER *wa=was->waters[i];
  toSpin(wa->x,wa->y,4,8,wa->r,&x,&y);
  drawRect(x,y,8,SCRH-100,0xff90a0f0);

  drawCir(x,y, was->waters[i]->size,0x8090a0f0);
  
 }
 
}

void wa_run(WATERS *was)
{
 int i;
 
 for(i=0;i<was->size;i++)
 {
  
    was->waters[i]->r+=12;
 }
 
}

//释放

void wa_free(WATERS *was)
{
 int i;
 for(i=0;i<was->size;i++)
 {
  free(was->waters[i]);
 }
 free(was);
 
}


#endif