#ifndef _HERO_H_
#define _HERO_H_

#include "base.h"
#include "ex_game.h"
#include "map.h"
#include "enemy.h"

typedef struct
{
    int type; //状态
    int action; //人物动作
    int x; // x坐标
    int y; // y坐标
    int hp; //生命
    int isjump; //是否悬空
    int isColak; //是否隐身
    int colak_time; //隐身时间
    int iskey; //是否按下跳跃键
    int wv; //横向速度
    int hv; //纵向速度
    int32 bitmap;
    int32 sprite; //精灵
} _HERO;

enum
{
    HERO_STAND, //静止
    HERO_RUN, //运动
    HERO_JUMP, //跳
    HERO_DOWN, //下蹲
    HERO_DIE =7 //死亡
};

extern int itemw;///图块大小
extern int32 camera;
// extern struct TILED_LA *tiled; //xldebug
extern struct _TILED *tiled;

//创建主角
void *hero_create(char *filename,char *bitmapname);

//设置主角位置
int hero_setxy(_HERO *hero,int x, int y);

//主角运动事件
void hero_run(_HERO *hero);

//设置主角状态
void hero_setType(_HERO *hero,int type);
//设置主角隐身
//参数：是否隐身，隐身时间ms
void hero_setColak(_HERO *hero,int isColak,int time);

//销毁主角
int hero_free(_HERO *hero);





#endif







