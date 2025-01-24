#ifndef _WORLD_HERO_H_
#define _WORLD_HERO_H_


#include "base.h"
#include "readSprite.h"
#include "tmx.h"
#include "exb.h"
#include "world_enemy.h"

typedef struct {
    int type; //精灵状态
    int isbig; //是否处于放大状态
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
    int32 bitmap; //图片
    int32 bitmap_big;
    int32 sprite; //精灵
    int32 sprite_big; //放大状态的精灵
} _HERO;

enum {
    HERO_STAND, //静止
    HERO_RUN, //运动
    HERO_JUMP, //跳
    HERO_DOWN, //下蹲
    HERO_RIGHT, //右移
    HERO_END, //过关
    HERO_DIE = 7 //死亡
};


extern int camera;
extern TILED_TILE_LAYER *layer_tiled;

void hero_run(_HERO *hero, TILED_OBJECT_LAYER *layer_tiled);

//创建主角
_HERO *hero_create2(char *sprite, char *sprite_big, char *bitmapname, char *bitmap_big);

//绘制主角
void hero_draw(_HERO *hero, int camera);

int hero_getX(_HERO *hero);

int hero_getY(_HERO *hero);

//
int hero_getSprite(_HERO *hero);

int hero_getW(_HERO *hero);

int hero_getH(_HERO *hero);

//设置主角位置
int hero_setxy2(_HERO *hero, int x, int y);

//设置主角变大
int hero_setBig(_HERO *hero, int isBig);
//获取主角重心点y坐标
int hero_getGY(_HERO *hero);

int hero_getAction(_HERO *hero);

void hero_setAction(_HERO *hero, int action);

//获取主角横向速度
int hero_getSpeedW(_HERO *hero);

//获取主角纵向速度
int hero_getSpeedH(_HERO *hero);

//判断主角是否碰到碰撞层
int hero_isCollObjectLayer(_HERO *hero, TILED_OBJECT_LAYER *layer);

//void hero_keyrun(_HERO *hero, int type, int p1, int p2) {
//    int sprite = hero_getSprite(hero);
//    int hero_action = hero->action;
//    int isjump = hero->isjump;
//    int iskey = hero->iskey;
//
//    if (hero_action == HERO_DIE) {
//        hero->y += 4;
//    } else {
////        logi("判断按键");
//        //判断按键
//        if (type == KY_DOWN) {
//            if (p1 == _LEFT) {
//                if (hero_action == HERO_STAND && !isjump) {
//                    hero_action = HERO_RUN;
//                }
//                hero->wv = -4;
//                hero->x -= 4;
//                if (hero_isCollObjectLayer(hero, (TILED_OBJECT_LAYER *) layer_tiled)) hero->x += 4;
//                if (hero->x < 0)hero->x = 0;
//                if (hero->x < ca_getx(camera))
//                    hero->x += 4;
//            } else if (p1 == _RIGHT) {
//                if (hero_action == HERO_STAND && !isjump) {
//                    hero_action = HERO_RUN;
//                }
//                hero->wv = 4;
//                hero->x += 4;
//                if (hero_isCollObjectLayer(hero, layer_tiled))
//                    hero->x -= 4;
//            } else {
//                hero->wv = 0;
//                if (hero_action == HERO_RUN) {
//                    hero_action = HERO_STAND;
//                }
//            }
//            if (p1 == _POUND) {
//                if (hero_action != HERO_JUMP && !iskey && !isjump) {
//                    hero->iskey = 1;
//                    hero_action = HERO_JUMP;
//                    isjump = 1;
//                }
//                if (hero->iskey) {
//                    if (hero->iskey == 1)
//                        hero->hv -= 8;
//                    if (hero->iskey == 3)
//                        hero->hv -= 8;
//                    hero->iskey++;
//                }
//            } else {
//                hero->iskey = 0;
//            }
//
//
////        logi("检测跳跃");
//
//
//        }
//    }
//}

//新的主角运动事件 检测采用碰撞层
void hero_run(_HERO *hero, TILED_OBJECT_LAYER *layer_tiled);

//输出调试信息
void hero_debug(_HERO *hero);


//主角运动事件
void hero_run_old(_HERO *hero, TILED_TILE_LAYER *layer_tiled);

//设置主角状态
void hero_setType2(_HERO *hero, int type);

//设置主角隐身
//参数：是否隐身，隐身时间ms
void hero_setColak2(_HERO *hero, int isColak, int time);
//销毁主角
int hero_free2(_HERO *hero);


#endif