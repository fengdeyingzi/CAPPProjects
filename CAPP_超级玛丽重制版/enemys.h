#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "graphics.h"
#include "ex_game.h"
#include "world_hero.h"
#include "log.h"

enum {
    E_RUN,  //运行
    E_STOP,  //停止
    E_OVER, //死亡
    E_SLEEP //休眠
};

enum {
    ENEMY_MUSHROOM, //蘑菇
    ENEMY_MISSILE, //导弹
    ENEMY_TORTOISE, //乌龟
    ENEMY_TORTOISE_HERO, //投弹人
    BOSS_TORTOISE, //BOSS乌龟
    BOSS_PRINCESS, //公主
    BOSS_ASSASSIN, //刺客
    ENEMY_HEDGEHOG, //刺猬
    ENEMY_FLOWER, //花
    ENEMY_DUCK  //鸭子
};

//敌人的超类
typedef struct _ENEMY {
    char *name; //类名字
    char *enemy_name; //敌人名字
    int type; //敌人的类型 0蘑菇 1乌龟
    int x; //敌人出现的位置
    int y; //敌人出现的坐标、
    int hp; //生命值
    int isDraw;  //是否显示
    int isDel; //是否死亡
    int isSleep; //是否休眠 默认是
    int direction; //运动方向 上_UP  下_DOWN 左_LEFT 右_RIGHT
    int32 bitmap;
    int32 sprite; //精灵
    struct _ENEMY *next;

} _ENEMY;

typedef struct _MISSILE {
    char *name; //类名字
    char *enemy_name; //敌人名字
    int type; //敌人的类型 0蘑菇 1乌龟(失效）
    int x; //敌人出现的位置
    int y; //敌人出现的坐标、
    int hp; //生命值
    int isDraw;  //是否显示
    int isDel; //是否死亡
    int isSleep; //是否休眠 默认是
    int direction; //运动方向 上 下 左 右
    int32 bitmap;
    int32 sprite; //精灵
    struct _ENEMY *next;
    int bullet_x;
    int bullet_y;
    //导弹子弹的x y坐标
    int32 bullet_sprite; //导弹子弹的精灵

} _MISSILE; //导弹

typedef struct _FLOWER {
    char *name; //类名字
    char *enemy_name; //敌人名字
    int type; //敌人的类型 已失效
    int x; //敌人出现的位置
    int y; //敌人出现的坐标、
    int hp; //生命值
    int isDraw;  //是否显示
    int isDel; //是否死亡
    int isSleep; //是否休眠 默认是
    int direction; //运动方向 上 下 左 右
    int32 bitmap;
    int32 sprite; //精灵
    struct _ENEMY *next;
    int move_y; //花盆的y坐标 用来让花进行相对移动
    int move_v; //移动速度
} _FLOWER; //花

typedef struct _MUSHROOM {
    char *name; //类名字
    char *enemy_name; //敌人名字
    int type; //敌人的类型 已失效
    int x; //敌人出现的位置
    int y; //敌人出现的坐标、
    int hp; //生命值
    int isDraw;  //是否显示
    int isDel; //是否死亡
    int isSleep; //是否休眠 默认是
    int direction; //运动方向 上 下 左 右
    int32 bitmap;
    int32 sprite; //精灵
    struct _ENEMY *next;

    int action; //状态
    int gv; //重力加速度
    int isCheckTile; //是否检测地图图块进行运动 为了模拟真实的蘑菇运动 在小范围时间内让它不检测图块
    int checkTime; //检测图块的时间 这个时间越短 那么蘑菇就越聪明
    int32 runTime; //记录运动时间
} _MUSHROOM; //蘑菇

typedef struct _HEDGEHOG {
    char *name; //类名字
    char *enemy_name; //敌人名字
    int type; //敌人的类型 已失效
    int x; //敌人出现的位置
    int y; //敌人出现的坐标、
    int hp; //生命值
    int isDraw;  //是否显示
    int isDel; //是否死亡
    int isSleep; //是否休眠 默认是
    int direction; //运动方向 上 下 左 右
    int32 bitmap;
    int32 sprite; //精灵
    struct _ENEMY *next;

    int action; //状态
    int gv; //重力加速度
    int isCheckTile; //是否检测地图图块进行运动 为了模拟真实的蘑菇运动 在小范围时间内让它不检测图块
    int checkTime; //检测图块的时间 这个时间越短 那么蘑菇就越聪明
    int32 runTime; //记录运动时间
} _HEDGEHOG; //刺猬

typedef struct _GANODERMA {
    char *name; //类名字
    char *enemy_name; //敌人名字
    int type; //敌人的类型 已失效
    int x; //敌人出现的位置
    int y; //敌人出现的坐标、
    int hp; //生命值
    int isDraw;  //是否显示
    int isDel; //是否死亡
    int isSleep; //是否休眠 默认是
    int direction; //运动方向 上_UP  下_DOWN 左_LEFT 右_RIGHT
    int32 bitmap;
    int32 sprite; //精灵
    struct _ENEMY *next;

} _GANODERMA; //灵芝 （灵芝什么的弱爆了 一动不动的就可以了）


//创建敌人 参数 敌人类型，(精灵文件，敌人图片根据敌人类型自动设置)
_ENEMY *enemy_create(char *enemy_name);

//设置敌人坐标
void enemy_setxy(_ENEMY *enemy, int x, int y);

//添加一个敌人
void enemy_add(_ENEMY *enemys,_ENEMY *temp);


//花的运动事件 因为花不需要依赖地图 所以不需要传地图参数
void enemy_flower_run(_FLOWER *enemy);

//绘制花
void enemy_flower_draw(_FLOWER *enemy, int camera);

//花与主角碰撞
int enemy_flower_coll(_FLOWER *enemy, _HERO *hero);

//蘑菇运动事件
void enemy_mushroom_run(_MUSHROOM *mushroom, TILED_OBJECT_LAYER *layer);

//刺猬运动事件 刺猬比蘑菇运动慢
void enemy_hedgehog_run(_HEDGEHOG *mushroom, TILED_TILE_LAYER *layer);


//鸭子运动事件


//导弹运动事件 导弹不需要判断地图碰撞
void enemy_missile_run(_MISSILE *missile);


//敌人运动 参数 敌人 图层 主角坐标
void enemys_run(_ENEMY *enemy, TILED_OBJECT_LAYER *layer, int hero_x,int hero_y);

//判断是否与主角碰撞 导弹只有子弹才有碰撞
int enemy_isCollHero(_ENEMY *enemy, _HERO *hero);

//绘制敌人 判断敌人类型进行绘制
void enemys_draw(_ENEMY *enemy,int camera); 

//释放敌人 将精灵 图片 一并释放
void enemy_free(_ENEMY *enemy);

void enemys_free(_ENEMY *enemys);





#endif

