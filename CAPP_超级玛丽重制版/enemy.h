
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "array.h"
#include "readtext.h"
#include "map.h"
#include "hero.h"
#include "ex_game.h"

typedef struct {
    int type; //敌人的类型 0蘑菇 1乌龟
    int x; //敌人出现的位置
    int y; //敌人出现的坐标
    int direction; //运动方向
    int sprite; //精灵
} _ENEMY;


typedef struct {
    int load; //进度
    int size; //敌人数量
    int bitmap_mogu;
    int bitmap_turtle;
    int bitmap_flower;
    _ARRAY *enemys; //所有敌人
} _EN_TASK;

typedef struct _TILED{
    int bitmap;
    int width;
    int height;
    int itemw;
    int itemh;
    int *sprite;
    int *data;
    _EN_TASK *en_task;
    int world;
    int camera;
} _TILED;


//初始化所有敌人
void *en_create(char *filename) {
    _EN_TASK *task = malloc(sizeof(_EN_TASK));
    memset(task, 0, sizeof(_EN_TASK));
    printf("加载bitmap\n");
    task->bitmap_mogu = readBitmapFromAssets("mogu.png");
    task->bitmap_turtle = readBitmapFromAssets("turtle.png");
    task->bitmap_flower = readBitmapFromAssets("flower.png");


    _ENEMY *en = NULL;

    _ARRAY *array = array_create();
    task->enemys = array;
    char *text = text_readFromAssets(filename);
    char c;
    int type = 0;
    printf("循环读取敌人数据\n");
    while (c = *text) {
        switch (type) {
            case 0:
                if (en == NULL)
                    en = malloc(sizeof(_ENEMY));
                if (c >= '0' && c <= '9') {
                    en->type = atoi(text);
                    switch (en->type) {
                        case 0: //蘑菇
                            en->sprite = sp_read("mogu.sprite", task->bitmap_mogu);
                            sp_setDraw(en->sprite, 0);
                            break;
                        case 1: //鸭子
                            en->sprite = sp_read("turtle.sprite", task->bitmap_turtle);
                            sp_setDraw(en->sprite, 0);
                            break;
                        case 2: //食人花
                            en->sprite = sp_read("flower.sprite", task->bitmap_flower);
                            sp_setDraw(en->sprite, 0);
                            break;

                    }
                    type = 1;
                }
                break;
            case 1:
                if (c == ':') {
                    type = 2;
                } else if (c == '\n') {
                    type = 0;
                }
                break;
            case 2:
                if (c >= '0' && c <= '9') {
                    en->x = atoi(text);
                    type = 3;
                } else if (c == '\n') {
                    type = 0;
                }
                break;
            case 3:
                if (c == ' ') {
                    type = 4;
                } else if (c == '\n') {
                    type = 0;
                }
                break;
            case 4:
                if (c >= '0' && c <= '9') {
                    en->y = atoi(text);
                    sp_setxy(en->sprite, en->x * 20, en->y * 20);
                    if (en->type == 2)
                        sp_move(en->sprite, 10, 0);
                    type = 5;
                } else if (c == '\n') {
                    type = 0;
                }
                break;
            case 5:
                if (c == '\n') {
                    array_append(array, (int) en);
                    en = NULL;
                    task->size++;
                    type = 0;
                }
                break;
        }

        text++;
    }
    if (en != NULL) {
        array_append(array, (int) en);
        task->size++;
    }
    printf("创建成功\n");

    return task;
};

//将所有敌人添加到世界中
int en_addWorld(_EN_TASK *task, int world) {
    for (int i = 0; i < task->size; i++) {
        _ENEMY *en = (void *) array_get(task->enemys, i);
        world_addSprite(world, en->sprite);
    }
    return 0;
}


//判断敌人是否可以加载
int en_load(_EN_TASK *task, int x) {
    _ENEMY *en = NULL;
    if (task->load >= task->size)
        return FALSE;
    en = (void *) array_get(task->enemys, task->load);
    if (x > en->x) {
        sp_setDraw(en->sprite, 1);
        task->load++;
        if (task->load >= task->size)
            task->load = task->size;
    }

    return TRUE;
}

//敌人运动事件
int en_run(_EN_TASK *task, _TILED *tiled, _HERO *hero) {
    for (int i = 0; i < task->load; i++) {
        _ENEMY *en = (void *) array_get(task->enemys, i);
        int sx = sp_getx(en->sprite);
        int sy = sp_gety(en->sprite);
        if (sp_isDraw(en->sprite) && sp_getAction(en->sprite) != 1) {
            switch (en->type) {
                case 0:
                case 1:
                    if (en->direction == 0) {
                        sx--;
                        //检测是否撞到东西
                        if (tiled_getDataCoor(tiled, sx, sy))
                            en->direction = 1;
                        //检测是否会掉下去
                        if (!tiled_getDataCoor(tiled, sx, sy + 20)) {
                            en->direction = 1;
                        }
                    } else {
                        sx++;
                        //检测是否撞到东西
                        if (tiled_getDataCoor(tiled, sx + 19, sy))
                            en->direction = 0;
                        //检测是否会掉下去
                        if (!tiled_getDataCoor(tiled, sx + 20, sy + 20)) {
                            en->direction = 0;
                        }
                    }


                    break;
                case 2:
                    if (en->direction == 0) //向上
                    {
                        sy--;
                        if (sy < en->y * 20 - 32) {
                            en->direction = 2;


                        }
                    } else if (en->direction == 1) {
                        sy++;
                        if (sy > en->y * 20) en->direction = 2;
                    } else {
                        //人物距离食人花很近，那么食人花不动
                        int sp_len = hero->x - sx;
                        if (sp_len > 26 || sp_len < -26) {
                            if (sy > en->y * 20) en->direction = 0;
                            else
                                en->direction = 1;
                        }
                    }

            } //switch
            sp_setxy(en->sprite, sx, sy);
            //与主角碰撞

            if (sp_crash(en->sprite, hero->sprite) && sp_getAction(en->sprite) != 1) {
                if (en->type == 2) {

                    hero->hp--;
                } else {
                    if (hero->isjump && hero->hv > 0) {
                        hero->hv = -8;
                        sp_setAction(en->sprite, 1);
                    } else
                        hero->hp--;
                }
            }
        } //if

    } //for

    return 0;
}


//销毁敌人
int en_free(_EN_TASK *task) {
    //销毁bitmap
    bitmapFree(task->bitmap_mogu);
    bitmapFree(task->bitmap_flower);
    bitmapFree(task->bitmap_turtle);
    //销毁精灵
    for (int i = 0; i < task->size; i++) {
        _ENEMY *en = (void *) array_get(task->enemys, i);
        sp_free(en->sprite);
        //销毁敌人
        free(en);
    }


    //销毁数组
    array_free(task->enemys);
    //销毁task
    free(task);
    return 0;
}


#endif







