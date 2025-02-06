//加载系统头文件base.h
#include "base.h"
#include "graphics.h"
#include "map.h"
#include "sprite_write.h"
#include "ex_game.h"
#include "enemy.h"
#include "hero.h"
#include "tmx.h"

//printf_sprite(96, 32, 32, 32);

void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "地图加载中", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}

//人物
_HERO  *hero;


int32 bitmap_background;

//世界
int32 world;
//照相机
int32 camera;
//地图数据
_TILED *tiled;

int itemw;///图块大小

int32 timer;
int32 time_data;


//所有敌人
_EN_TASK *en_task;






void logoc(int32 data)
{
    //人物下落


    hero_run(hero);


printf("测试读取tmx");
//   TILED_MAP *map = tiled_readFileCreateTiled("mali.tmx");
//
//   tiled_free(map);



    int hero_x=hero->x;
    int hero_y=hero->y;
    //照相机跟随
    if(hero_x > ca_getx(camera)+SCRW/2)
        ca_move(camera,4,0);

    //敌人运动事件
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



//入口函数，程序启动时开始执行
int init()
{
    //调用函数helloworld
    printf("start run\r\n");
    helloworld();
    time_data=0;

    setpadtype(2);
    setscrsize(480,480*SCRH/SCRW);

    //读取bitmap
    int bitmap=readBitmapFromAssets("grass.png");
    bitmap_background=readBitmapFromAssets("background_sunset.png");
    //通过txt sprite 和 bitmap 创建一张地图
    tiled = tiled_createData("mali.txt","mali.tmx.sprite",bitmap);
    //获取世界，用来显示到屏幕上
    world=tiled_getWorld(tiled);
    //获取摄像机，用来移动画面
    camera=tiled_getCamera(tiled);
    en_task = tiled->en_task;
    itemw=tiled_getItemWidth(tiled);
    printf("itemw %d\n",itemw);
    //清屏
    cls(0,0,0);
    //显示世界(由于地图加载到世界中，所以显示世界就会显示地图)
    world_draw(world);

    dtext("加载完成",0,0,60,168,255,0,1);
    ref(0,0,SCRW,SCRH);

    //加载玛利

    hero =  hero_create("mario_small.sprite","mario_small.png");
    hero_setxy(hero,0,9*20);
    world_addSprite(world,hero->sprite);



    timer=timercreate();
    timerstart(timer,30,1,logoc,1);
    printf("屏幕宽高%d %d\n",SCRW,SCRH);

    return 0;
}



static int hx,hy;
//event函数，接收消息事件
int event(int type, int p1, int p2)
{

    if(KY_UP == type)
    {
        switch(p1)
        {
            case _BACK:
                // exitApp();
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

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause()
{
    printf("pause");
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
    printf("resume");
    return 0;
}



int exitApp()
{
    if(timer){
        timerdel(timer);
        timer = 0;
    }
    
    if(bitmap_background){
        bitmapFree(bitmap_background);
        bitmap_background = 0;
    }
    
    //退出时释放地图
    if(tiled != NULL){
        tiled_freemap(tiled);
        tiled = NULL;
    }
    
    //释放主角
    if(hero!=NULL){
       hero_free(hero); 
       hero = NULL;
    }
    
    //销毁敌人
    if(en_task!=NULL){
        en_free(en_task);
        en_task = NULL;
    }
    


    printf("退出游戏\n");
    return 0;
}