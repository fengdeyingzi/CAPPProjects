
#ifndef _CAMERA_H_
#define _CAMERA_H_
/*
照相机
做游戏专用

风的影子 编写
*/

#include <base.h>
#include <graphics.h>

typedef struct CAMERA
{
 int x;
 int y;
 int w;
 int h;
 
} CAMERA;

int32 ca_create(int x,int y,int w,int h)
{
 CAMERA *ca=malloc(sizeof(CAMERA));
 ca->x=x;
 ca->y=y;
 ca->w=w;
 ca->h=h;
 
 return (int32)ca;
};
/*
//创建照相机
int ca_create(int x,int y,int w,int h)
{
 CAMERA *ca=malloc(sizeof(CAMERA));
 ca->x=x;
 ca->y=y;
 ca->w=w;
 ca->h=h;
 
 return (int)ca;
}
*/


//设置照相机的位置
int ca_setxy(long int id,int x,int y)
{
 CAMERA *ca=(void*)id;
 ca->x=x;
 ca->y=y;
 return 0;
}

int ca_getx(long int id)
{
 CAMERA *ca=(void*)id;
 return ca->x;
}

int ca_gety(long int id)
{
 CAMERA *ca=(void*)id;
 return ca->y;
 
}

//照相机移动
int ca_move(long int id,int movex,int movey)
{
 CAMERA *ca=(void*)id;
 ca->x+=movex;
 ca->y+=movey;
 
 return 0;
}

//销毁照相机
int ca_free(long int id)
{
 CAMERA *camera=(void*)id;
 free(camera);
 return 0;
}






#endif
