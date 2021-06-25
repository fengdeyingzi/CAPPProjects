
/*
�ֻ�C���� ը������Ϸ
����2.5D��ͼ
��ʹ���ֻ�C���� 2.7�����ϰ汾����

���Ӱ�� ��д
*/


//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <graphics.h>
#include <android.h>
#include <ex_math.h>
#include <ex_game.h>
#include <exb.h>
#include "map.h"
#include "sprite_write.h"
#include "data.h"
#include "enemy.h"

#define C 1


//����
int32 hero;
int32 hero_bitmap;
//ը��
int32 bomb;
int32 bomb_bitmap;
//����ģ��
int32 enemy01;
int32 enemy01_bitmap;

//���е���
int32 enemys[10];

//int bitmap;
int32 camera;
//��ʱ��
int32 timer;
int32 timer_run;

//����
int32 world_map;
//����
int32 world_back;
//��ͼ
int32 map;
//��Ϸ����
_DATA *data;
//��ں�������������ʱ��ʼִ��
int init()
{
 if(_VERSION < 2800)
 {
  cls(0,0,0);
  dtext("�汾���ͣ�������ֻ�C����",0,0,255,255,255,0,1);
  ref(0,0,SCRW,SCRH);
  sleep(4000);
  exit();
  return 0;
 }
 
 int i;
  
  //printf_sprite(510,425,85,85);
  //printf_tmx("c/1.tmx");
    data=data_load(1);
    printf("%s\n","����");
    map=data_getMap(data);
    printf("%s\n","����");
    world_back=data->world_back;
    world_map=data->world;
    camera=data->camera;
   // printf_sprite(760,62,40,40);
   if(SCRW<SCRH)
   setscrsize(320,320*SCRH/SCRW);
   else
   setscrsize(640,640*SCRH/SCRW);
   //��ȡbitmap
    hero_bitmap=readBitmapFromAssets("girl.png");
    printf("%s\n","����");
   //��������
    hero=sp_read("hero.sprite",hero_bitmap);
    printf("%s\n","����");
    //������������
    sp_setxy(hero,40,40);
    //��������ӵ�����
    world_addSprite(world_map, hero);
    printf("%s\n","����5");
    //��ʼ��ը��
    bomb_bitmap=readBitmapFromAssets( "bomb/bomb01.png");
    printf("%s\n","����6");
    bomb=sp_read("bomb/bomb.sprite", bomb_bitmap);
    world_addSprite (world_map,bomb);
    
    //��ʼ������
    printf("%s\n","����7");
    enemy01_bitmap=readBitmapFromAssets("enemy/enemy01.png");
    enemy01=sp_read("enemy/enemy01.sprite", enemy01_bitmap);
    printf("%s\n","����8");
   for(i=0;i<10;i++)
   {
    enemys[i]=sp_copy(enemy01);
    world_addSprite (world_map,enemys[i]);
    //��⵱ǰͼ���Ƿ�Ϊ�գ�����Ϊ�վ��������
    while(1)
    {
     int ix,iy;
     if(map_getData(map,ix=rand()%20,iy=rand()%20)==0)
     {
      sp_setxy(enemys[i],ix*40,iy*40);
     break;
     }
    }
   }

    printf("%s\n","����9");
    sp_setDraw(bomb,FALSE);
    
    ref(0,0,SCRW,SCRH);
    timer=timercreate();
    timerstart(timer,30,1,"logoc",TRUE);
    timer_run=timercreate();
    timerstart(timer_run,200,2,"run",TRUE);
    setpadtype(2);
    return 0;
}

int crash(int32 sp1,int32 sp2)
{
 return isCollRect(sp_getx(sp1),sp_gety(sp1),sp_getWidth(sp1),sp_getHeight(sp1),
 sp_getx(sp2),sp_gety(sp2),sp_getWidth(sp2),sp_getHeight(sp2));
}


//ת�����鶯��
void setAction(int32 sprite,int type)
{
 if(sp_getAction(sprite)!=type&& sp_getAction(sprite)<4)
 {
  sp_setAction(sprite,type);
  map_setXY(sprite,40,40);
 }
}
void run(int data)
{
 //ը����ըʱ��
 static int time=0;
 int i;
 if(sp_isDraw(bomb))
 {
 //sp_run(bomb);
 time++;
 if(time>20)
 {
  time=0; 
  sp_setDraw(bomb,FALSE);
  //��ը �ж��ĸ������Ƿ�������
  int mx=sp_getx(bomb)/40;
  int my=sp_gety(bomb)/40;
  if(map_getData(map,mx,my-1)==2)
  {
   map_setData(map,mx,my-1,0);
  }
  if(map_getData(map,mx,my+1)==2)
  {
   map_setData(map,mx,my+1,0);
  }
  if(map_getData(map,mx-1,my)==2)
  {
   map_setData(map,mx-1,my,0);
  }
  if(map_getData(map,mx+1,my)==2)
  {
   map_setData(map,mx+1,my,0);
  }
  for(i=0;i<10;i++)
   {
   if(en_impact(bomb,enemys[i]))
   {
    //world_removeSprite(world_map,enemys[i]);
    sp_setAction(enemys[i],4);
   }
   }
 }
 }
}



int time=0;
void logoc(int data)
{
 int i;
 printf("�������¼� world_run %d\n", world_map == (int)world_map);
 if(time%5==0)
 world_run(world_map);
 printf("%s\n","����0");
 //����ı���˷���
 if(time%6==0)
 {
  int ftype=rand()%4;
  
  int fi=rand()%10;
  setAction(enemys[fi],ftype);
  map_setXY(enemys[fi],40,40);
 }
 printf("%s\n","����1");
 for(i=0;i<10;i++)
 en_run(enemys[i]);
 //�������¼�
 time++;
 if(getkeypressed(_UP)==0)
 {
  setAction(hero,3);
  sp_move(hero,0,-4);
    //�ж��Ƿ񳬹��߽�
   if(sp_gety(hero)-ca_gety(camera)<SCRH/2)
   ca_move(camera,0,-4);
  if((map_getData(map,sp_getx(hero)/40,sp_gety(hero)/40)!=0)|| (map_getData(map,(sp_getx(hero)+39)/40,sp_gety(hero)/40)!=0))
  {
   sp_move(hero,0,4);
  }
  //sp_run(hero);
 }
 else if(getkeypressed(_DOWN)==0)
 {
  setAction(hero,0);
  sp_move(hero,0,4);
   //�ж��Ƿ񳬹��߽�
   if(sp_gety(hero)-ca_gety(camera)>SCRH/2)
   ca_move(camera,0,4);
  if((map_getData(map,sp_getx(hero)/40,(sp_gety(hero)+39)/40)!=0)||(map_getData(map,(sp_getx(hero)+39)/40,(sp_gety(hero)+39)/40)!=0))
  {
   sp_move(hero,0,-4);
   
  }
  //sp_run(hero);
 }
 else if(getkeypressed(_LEFT)==0)
 {
  setAction(hero,1);
  sp_move(hero,-4,0);
    //�ж��Ƿ񳬹��߽�
   if(sp_getx(hero)-ca_getx(camera)<SCRW/3)
   ca_move(camera,-4,0);
  if((map_getData(map,sp_getx(hero)/40,sp_gety(hero)/40)!=0)|| (map_getData(map,sp_getx(hero)/40,(sp_gety(hero)+39)/40)!=0))
  {
   sp_move(hero,4,0);
  }
  //sp_run(hero);
 }
 else if(getkeypressed(_RIGHT)==0)
 {
  setAction(hero,2);
  sp_move(hero,4,0);
    //�ж��Ƿ񳬹��߽�
   if(sp_getx(hero)-ca_getx(camera)>SCRW*2/3)
   ca_move(camera,4,0);
  if( (map_getData(map,(sp_getx(hero)+39)/40,sp_gety(hero)/40)!=0) || (map_getData(map,(sp_getx(hero)+39)/40,(sp_gety(hero)+39)/40)!=0) )
  {
   sp_move(hero,-4,0);
  }
  //sp_run(hero);
 }
 else
 {
  sp_setAction(hero,sp_getAction(hero));
 }
 if(getkeypressed(_STAR)==0)
 {
  if(!sp_isDraw(bomb) && sp_isDraw(hero))
  {
  sp_setDraw(bomb,TRUE);
  sp_setxy(bomb,sp_getx(hero),sp_gety(hero));
 map_setXY(bomb,40,40);
 
  }
 }

 //�ж������Ƿ�ײ������
 for(i=0;i<10;i++)
 {
  if(sp_getAction(enemys[i])<4 && sp_isDraw(hero))
  {
   if(crash(enemys[i],hero))
   {
    sp_setDraw(hero,FALSE);
    toast("��Ϸʧ��",1);
   }
  }
 }
 printf("%s\n","����2");
 
 cls(0,0,0);
 printf("��������\n");
 world_rank(world_map,4);
 //sp_run(bomb);
 printf("���Ʊ���\n");
 world_draw(world_back);
 world_draw(world_map);
// sp_draw(hero,camera);
char text[30];
sprintf(text,"%d %d",sp_getx(hero),sp_gety(hero));
dtext(text,0,0,0xf0,0xf0,0xf0,0,1);
//drect(sp_getx(hero),sp_gety(hero),40,40,20,20,20);

 ref(0,0,SCRW,SCRH);
 
 
}

//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK
:
          #ifndef JNI
          exitApp();
          #endif
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
 
 
int exitApp()
{
 //�˳�ʱ�ͷ���Դ
 int i;
 bitmapFree(hero_bitmap);
 bitmapFree(bomb_bitmap);
 bitmapFree(enemy01_bitmap);
 sp_free(hero);
 sp_free(bomb);
 sp_free(enemy01);
 for(i=0;i<10;i++)
 sp_free(enemys[i]);
 data_free(data);
 timerdel(timer);
 timerdel(timer_run);
 //world_free(world_map);
// world_free(world_back);
 //bitmapFree(hero_bitmap);
// ca_free(camera);
 return 0;
}