#ifndef _WORLD_HERO_H_
#define _WORLD_HERO_H_


#include "base.h"
#include "readSprite.h"
#include "tmx.h"
#include "exb.h"
#include "world_enemy.c.h"

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
    int bitmap; //图片
    int bitmap_big;
    int sprite; //精灵
    int sprite_big; //放大状态的精灵
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
_HERO *hero_create(char *sprite, char *sprite_big, char *bitmapname, char *bitmap_big) {
    _HERO *hero = malloc(sizeof(_HERO));
    memset(hero, 0, sizeof(_HERO));
    hero->bitmap = readBitmapFromAssets(bitmapname);
    hero->bitmap_big = readBitmapFromAssets(bitmap_big);
    hero->sprite = sp_read(sprite, hero->bitmap);
    hero->sprite_big = sp_read(sprite_big, hero->bitmap_big);

    hero->hp = 1;
    return hero;
}

//绘制主角
void hero_draw(_HERO *hero, int camera) {
//    logi("开始绘制hero");
    if (hero->isbig) {
        sp_draw(hero->sprite_big, camera);
    } else {
        sp_draw(hero->sprite, camera);
    }
//    logi("结束绘制");
}

int hero_getX(_HERO *hero) {
    return hero->x;
}

int hero_getY(_HERO *hero) {
    return hero->y;
}

//
int hero_getSprite(_HERO *hero) {
    if (hero->isbig) {
        return hero->sprite_big;
    }
    return hero->sprite;
}

int hero_getW(_HERO *hero) {
    int sprite = hero_getSprite(hero);
    return sp_getWidth(sprite);
}

int hero_getH(_HERO *hero) {
    int sprite = hero_getSprite(hero);
    return sp_getHeight(sprite);
}

//设置主角位置
int hero_setxy(_HERO *hero, int x, int y) {
    hero->x = x;
    hero->y = y;
    sp_setxy(hero->sprite, x, y);
    return 0;
}

//设置主角变大
int hero_setBig(_HERO *hero, int isBig) {
    hero->isbig = isBig;
    return 0;
}

//获取主角重心点y坐标
int hero_getGY(_HERO *hero) {
    if (!hero->isbig) {
        return hero->y + 19;
    } else {
        return hero->y + 39;
    }
}

int hero_getAction(_HERO *hero) {
    return hero->action;
}

void hero_setAction(_HERO *hero, int action) {
    hero->action = action;
}

//获取主角横向速度
int hero_getSpeedW(_HERO *hero) {
    return hero->wv;
}

//获取主角纵向速度
int hero_getSpeedH(_HERO *hero) {
    return hero->hv;
}

//判断主角是否碰到碰撞层
int hero_isCollObjectLayer(_HERO *hero, TILED_OBJECT_LAYER *layer) {
//    logi("检测");
    TILED_OBJECT *object = layer->object;
    while (object) {
//        logi("%d",object);
        if (isCollisionRect(hero->x, hero->y, sp_getWidth(hero_getSprite(hero)),
                            sp_getHeight(hero_getSprite(hero)), object->x, object->y, object->width,
                            object->height)) {
            return 1;
        }
        object = object->next;
    }
    return 0;
}

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
void hero_run(_HERO *hero, TILED_OBJECT_LAYER *layer_tiled) {
//    logi("hero run");
    int sprite = hero_getSprite(hero);
//    int hero_action = hero->action;
//        int isjump = hero->isjump;
//        int iskey = hero->iskey;
//    logi("sprite=%d action=%d isjump=%d iskey=%d layer=%d ",sprite,hero_action,isjump,iskey,layer_tiled->item_width);
    //重力下落
//        logi("重力下落");

    //printf("判断主角是否死亡\n");

    hero->y += hero->hv;
    //判断脚的碰撞
    if (hero->hv>0 && (tiled_isCollObjectLayer(layer_tiled, hero_getX(hero),
                                               hero_getY(hero) + hero_getH(hero) - 1) ||
                       tiled_isCollObjectLayer(layer_tiled, hero_getX(hero) + hero_getW(hero) - 1,
                                               hero_getY(hero) + hero_getH(hero) - 1))) {
        hero->y -= hero->hv;
        if (hero->hv > 0)
            hero->hv = 0;
        if (hero->action == HERO_JUMP) {
            hero->action = HERO_STAND;
            hero->isjump = 0;
            logi("撞到地面");
            sp_setAction(hero_getSprite(hero), hero->action);
        }
        logi("碰撞1");
//        toast("碰撞",0);
//        hero->action = HERO_STAND;
    }
    hero->hv++;
    if (hero->hv >= 6)hero->hv = 6;

    if (hero->hp <= 0) {
        hero->action = HERO_DIE;
    }
    if (hero->action == HERO_RIGHT) {
        hero->x += 4;
        sp_setxy(sprite, hero->x, hero->y);
        sp_run(hero->sprite);
        return;
    }
    //printf("加载主角\n");
    if (hero->action == HERO_DIE) {
        hero->y += 4;
    } else {
//        logi("判断按键");
        //判断按键

        if (getkeypressed(_LEFT) == 0) {
            if (hero->action == HERO_STAND && !hero->isjump) {
                hero->action = HERO_RUN;
                sp_setAction(hero_getSprite(hero), hero->action);
            }
            hero->wv = -4;
            hero->x -= 4;
            if (tiled_isCollObjectLayer( layer_tiled, hero_getX(hero),hero_getY(hero)) ||
            tiled_isCollObjectLayer(layer_tiled,hero_getX(hero),hero_getY(hero)+hero_getH(hero)-1)
            ) hero->x += 4;
            if (hero->x < 0)hero->x = 0;
            if (hero->x < ca_getx(camera))
                hero->x += 4;

        } else if (getkeypressed(_RIGHT) == 0) {
            if (hero->action == HERO_STAND && !hero->isjump) {
                hero->action = HERO_RUN;
                sp_setAction(hero_getSprite(hero), hero->action);
            }
            hero->wv = 4;
            hero->x += 4;
            if (tiled_isCollObjectLayer( layer_tiled, hero_getX(hero)+hero_getW(hero)-1, hero_getY(hero)) ||
            tiled_isCollObjectLayer(layer_tiled,hero_getX(hero)+hero_getW(hero)-1,hero_getY(hero)+hero_getH(hero)-1)
            )
                hero->x -= 4;
        } else {
//            logi("检测结束");
            if (hero->action == HERO_RUN) {
                hero->action = HERO_STAND;
                sp_setAction(hero_getSprite(hero), hero->action);
                hero->wv = 0;
            }
        }
//            if(hero_action==HERO_RUN || hero_action==HERO_JUMP){
//                hero->x += hero->wv;
//            }

//        logi("检测跳跃");

        if (getkeypressed(_POUND) == 0) {

            if ((hero->action != HERO_JUMP) && (!hero->iskey) && (!hero->isjump)) {
                logi("000 %d %d %d ", hero->action, hero->iskey, hero->isjump);
                hero->iskey = 1;/////
                hero->action = HERO_JUMP;
                hero->action = HERO_JUMP;
                sp_setAction(hero_getSprite(hero), hero->action);

                hero->isjump = 1;
            } else {
//                    hero->iskey = 0;
                logi("111  %d %d %d ", hero->action, hero->iskey, hero->isjump);
            }

            if (hero->iskey) {

                if (hero->iskey == 1) {

                    hero->hv -= 9;
                    hero->y += hero->hv;
                    logi("开始起跳%d",hero->hv);
                }
//                else if(hero->iskey<15){
//                    hero->hv-=1;
//                }

                if (hero->iskey == 5){
                    hero->hv -= 5;

                    logi("起跳第二段%d",hero->hv);
                }

                hero->iskey++;
//                   hero->iskey++;
            }

            //判断是否落到地上

        } else {
            hero->iskey = 0;
//                logi("iskey == 0");
//                hero->action = HERO_STAND;
//                hero_action = HERO_STAND;
            hero->isjump = 0;
        }


        //判断脚碰撞
//        if (tiled_isCollObjectLayer(layer_tiled, hero_getX(hero),
//                                    hero_getY(hero) + hero_getH(hero) - 1) ||
//            tiled_isCollObjectLayer(layer_tiled, hero_getX(hero) + hero_getW(hero) - 1,
//                                    hero_getY(hero) + hero_getH(hero) - 1)) {
////            if (hero_isCollObjectLayer(hero, layer_tiled)) {
//            logi("撞到地面");
////                hero->y -= hero->hv;
//            hero->hv = 0;
//            hero->y = hero->y - hero->y % 20;
//            hero->action = HERO_STAND;
//            if (hero->action == HERO_JUMP) {
//                hero->action = HERO_STAND;
//                hero->isjump = 0;
//                sp_setAction(hero_getSprite(hero), hero->action);
//            }
//
//            if (hero->hv > 0)
//                hero->hv = 0;
//        } else {
//            //判断头部是否撞到墙
//            if (hero_isCollObjectLayer(hero, layer_tiled))
//                if (hero->hv < 0)
//                    hero->hv = -hero->hv;
//        }


    }
//    logi("设置坐标");
//    if (hero->action != sp_getAction(sprite)) sp_setAction(sprite, hero->action);
    sp_setxy(sprite, hero->x, hero->y);


//        sp_setAction(hero_getSprite(hero),hero->action);
    sp_run(hero_getSprite(hero));

//    logi("主角run success\n");
}

//输出调试信息
void hero_debug(_HERO *hero) {
    char text[300];
    sprintf(text, "action=%d isjump=%d iskey=%d", hero->action, hero->isjump, hero->iskey);
    dtext(text, 10, 10, 20, 20, 20, 2, 1);
}


//主角运动事件
void hero_run_old(_HERO *hero, TILED_TILE_LAYER *layer_tiled) {
//    logi("hero run");
    int sprite = hero_getSprite(hero);
    int hero_action = hero->action;
    int isjump = hero->isjump;
    int iskey = hero->iskey;
//    logi("sprite=%d action=%d isjump=%d iskey=%d layer=%d ",sprite,hero_action,isjump,iskey,layer_tiled->item_width);
    //printf("判断主角是否死亡\n");
    if (hero->hp <= 0) {
        hero_action = HERO_DIE;
    }
    //printf("加载主角\n");
    if (hero_action == HERO_DIE) {
        hero->y += 4;
    } else {
//        logi("判断按键");
        //判断按键

        if (getkeypressed(_LEFT) == 0) {
            if (hero_action == HERO_STAND && !isjump) {
                hero_action = HERO_RUN;
            }

            hero->x -= 4;
            if (tiled_getWorldData(layer_tiled, hero->x, hero->y)) hero->x += 4;
            if (hero->x < 0)hero->x = 0;
            if (hero->x < ca_getx(camera))
                hero->x += 4;

        } else if (getkeypressed(_RIGHT) == 0) {
            if (hero_action == HERO_STAND && !isjump) {
                hero_action = HERO_RUN;
            }
            hero->x += 4;
            if (tiled_getWorldData(layer_tiled, (hero->x + layer_tiled->item_width - 1),
                                   hero->y))
                hero->x -= 4;
        } else {
//            logi("检测结束");
            if (hero_action == HERO_RUN) {
                hero_action = HERO_STAND;
            }
        }

        //printf("检测跳跃\n");
//logi("检测跳跃");

        if (getkeypressed(_POUND) == 0) {

            if (hero_action != HERO_JUMP && !iskey && !isjump) {
                hero->iskey = 1;
                hero_action = HERO_JUMP;
                hero->action = HERO_JUMP;
                isjump = 1;
            }
            if (hero->iskey) {
                if (hero->iskey == 1)
                    hero->hv -= 8;
                if (hero->iskey == 3)
                    hero->hv -= 8;
                hero->iskey++;
            }
            //判断是否落到地上

        } else {
            hero->iskey = 0;
        }

        //printf("下落\n");
        //重力下落
//        logi("重力下落");
        hero->hv++;
        if (hero->hv >= 6)hero->hv = 6;
        hero->y += hero->hv;
        //判断脚碰撞
        if (tiled_getWorldData(layer_tiled, (hero->x + 1), hero_getGY(hero)) ||
            tiled_getWorldData(layer_tiled, (hero->x + 19), (hero_getGY(hero)))) {
            logi("撞到地面");
            hero->y -= hero->y % layer_tiled->item_width;
            if (hero_action == HERO_JUMP) {
                hero_action = HERO_STAND;
            }
            isjump = 0;
            if (hero->hv > 0)
                hero->hv = 0;
        } else {
            isjump = 1;
            //判断头部是否撞到墙
            if (tiled_getWorldData(layer_tiled, (hero->x + 1), (hero->y)) ||
                tiled_getWorldData(layer_tiled, (hero->x + 19), (hero->y)))
                if (hero->hv < 0)
                    hero->hv = -hero->hv;
        }
    }
//    logi("设置坐标");
    if (hero_action != sp_getAction(sprite)) sp_setAction(sprite, hero_action);
    sp_setxy(sprite, hero->x, hero->y);
    hero->action = hero_action;
    hero->isjump = isjump;
//    logi("主角run success\n");
}

//设置主角状态
void hero_setType(_HERO *hero, int type) {
    hero->type = type;
    sp_setAction(hero->sprite, type);
}

//设置主角隐身
//参数：是否隐身，隐身时间ms
void hero_setColak(_HERO *hero, int isColak, int time) {
    hero->isColak = isColak;
    hero->colak_time = time;
}

//销毁主角
int hero_free(_HERO *hero) {
    //销毁精灵
    sp_free(hero->sprite);
    sp_free(hero->sprite_big);
    //销毁bitmap
    bitmapFree(hero->bitmap);
    bitmapFree(hero->bitmap_big);
    //销毁hero
    free(hero);
    return 0;
}


#endif