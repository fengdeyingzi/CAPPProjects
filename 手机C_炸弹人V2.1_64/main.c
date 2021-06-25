
/*
手机C语言 炸弹人游戏
采用2.5D地图
请使用手机C语言 2.7及以上版本运行

风的影子 编写
*/


//加载系统头文件base.h
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


//人物
int32 hero;
int32 hero_bitmap;
//炸弹
int32 bomb;
int32 bomb_bitmap;
//敌人模板
int32 enemy01;
int32 enemy01_bitmap;

//所有敌人
int32 enemys[10];

//int bitmap;
int32 camera;
//定时器
int32 timer;
int32 timer_run;

//世界
int32 world_map;
//背景
int32 world_back;
//地图
int32 map;
//游戏数据
_DATA *data;
//入口函数，程序启动时开始执行
int init()
{
 if(_VERSION < 2800)
 {
  cls(0,0,0);
  dtext("版本过低，请更新手机C语言",0,0,255,255,255,0,1);
  ref(0,0,SCRW,SCRH);
  sleep(4000);
  exit();
  return 0;
 }
 
 int i;
  
  //printf_sprite(510,425,85,85);
  //printf_tmx("c/1.tmx");
    data=data_load(1);
    printf("%s\n","测试");
    map=data_getMap(data);
    printf("%s\n","测试");
    world_back=data->world_back;
    world_map=data->world;
    camera=data->camera;
   // printf_sprite(760,62,40,40);
   if(SCRW<SCRH)
   setscrsize(320,320*SCRH/SCRW);
   else
   setscrsize(640,640*SCRH/SCRW);
   //读取bitmap
    hero_bitmap=readBitmapFromAssets("girl.png");
    printf("%s\n","测试");
   //创建人物
    hero=sp_read("hero.sprite",hero_bitmap);
    printf("%s\n","测试");
    //设置人物坐标
    sp_setxy(hero,40,40);
    //将主角添加到世界
    world_addSprite(world_map, hero);
    printf("%s\n","测试5");
    //初始化炸弹
    bomb_bitmap=readBitmapFromAssets( "bomb/bomb01.png");
    printf("%s\n","测试6");
    bomb=sp_read("bomb/bomb.sprite", bomb_bitmap);
    world_addSprite (world_map,bomb);
    
    //初始化敌人
    printf("%s\n","测试7");
    enemy01_bitmap=readBitmapFromAssets("enemy/enemy01.png");
    enemy01=sp_read("enemy/enemy01.sprite", enemy01_bitmap);
    printf("%s\n","测试8");
   for(i=0;i<10;i++)
   {
    enemys[i]=sp_copy(enemy01);
    world_addSprite (world_map,enemys[i]);
    //检测当前图块是否为空，若不为空就重新添加
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

    printf("%s\n","测试9");
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


//转换精灵动作
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
 //炸弹爆炸时间
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
  //爆炸 判断四个方向是否有箱子
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
 printf("检测键盘事件 world_run %d\n", world_map == (int)world_map);
 if(time%5==0)
 world_run(world_map);
 printf("%s\n","测试0");
 //随机改变敌人方向
 if(time%6==0)
 {
  int ftype=rand()%4;
  
  int fi=rand()%10;
  setAction(enemys[fi],ftype);
  map_setXY(enemys[fi],40,40);
 }
 printf("%s\n","测试1");
 for(i=0;i<10;i++)
 en_run(enemys[i]);
 //检测键盘事件
 time++;
 if(getkeypressed(_UP)==0)
 {
  setAction(hero,3);
  sp_move(hero,0,-4);
    //判断是否超过边界
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
   //判断是否超过边界
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
    //判断是否超过边界
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
    //判断是否超过边界
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

 //判断人物是否撞到敌人
 for(i=0;i<10;i++)
 {
  if(sp_getAction(enemys[i])<4 && sp_isDraw(hero))
  {
   if(crash(enemys[i],hero))
   {
    sp_setDraw(hero,FALSE);
    toast("游戏失败",1);
   }
  }
 }
 printf("%s\n","测试2");
 
 cls(0,0,0);
 printf("世界排序\n");
 world_rank(world_map,4);
 //sp_run(bomb);
 printf("绘制背景\n");
 world_draw(world_back);
 world_draw(world_map);
// sp_draw(hero,camera);
char text[30];
sprintf(text,"%d %d",sp_getx(hero),sp_gety(hero));
dtext(text,0,0,0xf0,0xf0,0xf0,0,1);
//drect(sp_getx(hero),sp_gety(hero),40,40,20,20,20);

 ref(0,0,SCRW,SCRH);
 
 
}

//event函数，接收消息事件
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

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause()
{
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
    return 0;
}
 
 
int exitApp()
{
 //退出时释放资源
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