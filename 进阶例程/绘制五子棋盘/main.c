/**********************
**������������**����С�**
***********************/
#include <base.h>

/*�������̿��*/
#define nX 12
#define nY 17
#define W  SCRW/nX
#define H  SCRH/nY

typedef struct
{
  int x;
  int y;
  int w;
  int h;
}Line;

Line mapX[nX];
Line mapY[nY];

void initMap()
{
  int i;
  /*������*/
  for(i=0;i<nY;i++)
  {
    mapY[i].x=W/2;
    mapY[i].y=i*H+H/2;
    mapY[i].w=SCRW-W;
    mapY[i].h=2;
  }
  
  for(i=0;i<nX;i++)
  {
    mapX[i].x=i*W+W/2;
    mapX[i].y=H/2;
    mapX[i].w=2;
    mapX[i].h=SCRH-H;
  }
  
}

void drawMap()
{
  cls(255,255,255);
  int r=0,g=0,b=0,i;
  
  for(i=0;i<nY;i++)
  {
    /*���ƺ���*/
    drect(mapY[i].x,mapY[i].y,mapY[i].w,mapY[i].h,r,g,b);
  }
  
  for(i=0;i<nX;i++)
  {
    /*��������*/
    drect(mapX[i].x,mapX[i].y,mapX[i].w,mapX[i].h,r,g,b);
  }
  
  ref(0,0,SCRW,SCRH);
}

int init()
{
  /*������Ļ�ֱ���*/
  setscrsize(600,600*SCRH/SCRW);
  
  initMap();
  drawMap();
  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exit();
            break;
        case _MENU:
            break;
        }
    }

    return 0;
}

//Ӧ����ͣ������������̨���Ϊ���ɼ�ʱ����ô˺���
int pause()
{
    return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
int resume()
{
    return 0;
}
 