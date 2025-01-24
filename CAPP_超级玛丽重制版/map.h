#ifndef _MAP_H_
#define _MAP_H_

#include "base.h"
#include "exb.h"
#include "graphics.h"
#include "ex_game.h"
#include "readSprite.h"
#include "tiled.h"
#include "enemy.h"
#include "world.h"
#include "tmx.h"

typedef struct _TILED{
    int32 bitmap;
    int width;
    int height;
    int itemw;
    int itemh;
    int32 *sprite;
    int32 *data;
    struct _EN_TASK *en_task;
    int32 world;
    int32 camera;
} _TILED;

// 函数声明

// 创建地图数据
void *tiled_createData(char *txtfile, char *spritefile, int bitmap);

// 创建地图
void *tiled_create(char *tmxfile, char *spritefile, int bitmap);

// 获取世界
int tiled_getWorld(_TILED *tiled);

// 获取图块宽度
int tiled_getItemWidth(_TILED *tiled);

// 获取摄像机
int tiled_getCamera(_TILED *tiled);

// 获取指定位置的图块精灵
int tiled_getSprite(_TILED *tiled, int x, int y);

// 获取指定位置的地图数据
int tiled_getDataXY(_TILED *tiled, int x, int y);

// 通过世界坐标获取地图数据
int tiled_getDataCoor(_TILED *tiled, int x, int y);

// 销毁地图
int tiled_freemap(TILED_MAP *tiled);

#endif // _MAP_H_