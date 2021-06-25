#ifndef __ORGAN_C_H__
#define __ORGAN_C_H__

#include "base/base.h"
#include "world_hero.c.h"

enum {
    R_UP, //向上运动
    R_DOWM, //向下运动
    R_STOP //停止运动
} EMUM_ORGAN;


typedef struct ORGAN_RECT {
    char *name;
    char *organ_name;
    int x;
    int y;
    int width;
    int height;
    int type;
    int isShow;
    int isSleep;
    int hv;
    int wv;
    int min_y;
    int max_y;
} ORGAN_RECT;

//创建机关
ORGAN_RECT *organ_creare() {
    ORGAN_RECT *organ = malloc(sizeof(ORGAN_RECT));
    memset(organ, 0, sizeof(ORGAN_RECT));
    organ->name = "ORGAN_RECT";
    organ->organ_name = "rect";
    organ->isSleep = 1;
    return organ;
}



//机关运动
void organ_run(ORGAN_RECT *organ_rect){
    if(!organ_rect->isSleep){
        organ_rect->y += organ_rect->hv;
        organ_rect->x += organ_rect->wv;
    }
}

//检测主角是否碰撞到机关
int organ_isCollHero(ORGAN_RECT *organ_rect, _HERO *hero){
    if(isCollisionRect(hero_getX(hero),hero_getY(hero),hero_getW(hero),hero_getH(hero), organ_rect->x,organ_rect->y,organ_rect->width,organ_rect->height)){
        return 1;
    }
    return 0;
}

//获取机关y坐标
int origan_getX(ORGAN_RECT *organ_rect){
    return organ_rect->x;
}

//获取机关x坐标
int origan_getY(ORGAN_RECT *organ_rect){
    return organ_rect->y;
}


//释放内存
void origan_free(ORGAN_RECT *organ_rect){
    free(organ_rect);
}


#endif