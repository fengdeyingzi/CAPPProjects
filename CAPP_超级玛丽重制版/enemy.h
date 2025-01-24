
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "base.h"
#include "map.h"
#include "array.h"
#include "hero.h"

typedef struct _ENEMY{
    int type; //敌人的类型 0蘑菇 1乌龟
    int x; //敌人出现的位置
    int y; //敌人出现的坐标
    int direction; //运动方向
    int32 sprite; //精灵
} _ENEMY;


typedef struct _EN_TASK{
    int load; //进度
    int size; //敌人数量
    int32 bitmap_mogu;
    int32 bitmap_turtle;
    int32 bitmap_flower;
    _ARRAY *enemys; //所有敌人
} _EN_TASK;




//初始化所有敌人
void *en_create(char *filename);

//将所有敌人添加到世界中
int en_addWorld(_EN_TASK *task, int32 world);


//判断敌人是否可以加载
int en_load(_EN_TASK *task, int x);



//敌人运动事件
int en_run(_EN_TASK *task, struct _TILED *tiled, _HERO *hero);

//销毁敌人
int en_free(_EN_TASK *task);


#endif







