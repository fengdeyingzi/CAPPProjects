//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <graphics.h>
#include "map.h"
#include "sprite_write.h"
#include "enemy.h"
#include "hero.h"

//printf_sprite(96, 32, 32, 32);

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "��ͼ������", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

//����
_HERO  *hero;


int bitmap_background;

//����
int world;
//�����
int camera;
//��ͼ����
_TILED *tiled;

int itemw;///ͼ���С

int timer;
int time_data;


//���е���
_EN_TASK *en_task;


 



void logoc(int32 data)
{
 //��������
 
 
  hero_run(hero);

  
 
 
 
 
 
 int hero_x=hero->x;
 int hero_y=hero->y;
 //���������
 if(hero_x > ca_getx(camera)+SCRW/2)
 ca_move(camera,4,0);
 
 //�����˶��¼�
 en_load(en_task,ca_getx(camera));
 en_run(en_task,tiled,hero);
 
 
 
 cls(0,0,0);
 drawBitmap(bitmap_background,0,SCRH-360);
 if(time_data%4==0)
 world_run(world);
 time_data++;
 world_draw(world);
    ref(0,0,SCRW,SCRH);
 if(hero_y>SCRH)
  {
  timerstop(timer);
  
  //timerstart(timer,20,1,"logo_exit",0);
  }
}



//��ں�������������ʱ��ʼִ��
int init()
{
    //���ú���helloworld
    helloworld();
    time_data=0;
    
    setpadtype(2);
    setscrsize(480,480*SCRH/SCRW);

    //��ȡbitmap
    int bitmap=readBitmapFromAssets("grass.png");
    bitmap_background=readBitmapFromAssets("background_sunset.png");
    //ͨ��txt sprite �� bitmap ����һ�ŵ�ͼ
    tiled = tiled_createData("mali.txt","mali.tmx.sprite",bitmap);
    //��ȡ���磬������ʾ����Ļ��
    world=tiled_getWorld(tiled);
    //��ȡ������������ƶ�����
    camera=tiled_getCamera(tiled);
    en_task = tiled->en_task;
    itemw=tiled_getItemWidth(tiled);
    printf("itemw %d\n",itemw);
    //����
    cls(0,0,0);
    //��ʾ����(���ڵ�ͼ���ص������У�������ʾ����ͻ���ʾ��ͼ)
    world_draw(world);
    
    dtext("�������",0,0,60,168,255,0,1);
    ref(0,0,SCRW,SCRH);
    
    //��������
    
   hero =  hero_create("mario_small.sprite","mario_small.png");
    hero_setxy(hero,0,9*20);
    world_addSprite(world,hero->sprite);
    


    timer=timercreate();
    timerstart(timer,30,1,"logoc",1);
    printf("��Ļ���%d %d\n",SCRW,SCRH);
    
    return 0;
}



static int hx,hy;
//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{

    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK: 
        exitApp();
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(type==MS_DOWN)
    {
     hx=p1;
     hy=p2;
     
    }
    if(type==MS_MOVE)
    {
     //ca_move(camera,hx-p1,hy-p2);
     
     hx=p1;
     hy=p2;
    }
    

    return 0;
}

//Ӧ����ͣ������������̨���Ϊ���ɼ�ʱ����ô˺���
int pause()
{
printf("pause");
    return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
int resume()
{
printf("resume");
    return 0;
}
 
 
 
int exitApp()
{
 timerdel(timer);
 
 bitmapFree(bitmap_background);
 //�˳�ʱ�ͷŵ�ͼ
 tiled_free(tiled);
 //�ͷ�����
 hero_free(hero);
 //���ٵ���
 en_free(en_task);
 
 
 printf("�˳���Ϸ\n");
 return 0;
}