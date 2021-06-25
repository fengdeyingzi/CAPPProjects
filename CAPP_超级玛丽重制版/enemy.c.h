#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "graphics.h"
#include "ex_game.h"
#include "world_hero.c.h"
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
    int bitmap;
    int sprite; //精灵
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
    int bitmap;
    int sprite; //精灵
    struct _ENEMY *next;
    int bullet_x;
    int bullet_y;
    //导弹子弹的x y坐标
    int bullet_sprite; //导弹子弹的精灵

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
    int bitmap;
    int sprite; //精灵
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
    int bitmap;
    int sprite; //精灵
    struct _ENEMY *next;

    int action; //状态
    int gv; //重力加速度
    int isCheckTile; //是否检测地图图块进行运动 为了模拟真实的蘑菇运动 在小范围时间内让它不检测图块
    int checkTime; //检测图块的时间 这个时间越短 那么蘑菇就越聪明
    int runTime; //记录运动时间
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
    int bitmap;
    int sprite; //精灵
    struct _ENEMY *next;

    int action; //状态
    int gv; //重力加速度
    int isCheckTile; //是否检测地图图块进行运动 为了模拟真实的蘑菇运动 在小范围时间内让它不检测图块
    int checkTime; //检测图块的时间 这个时间越短 那么蘑菇就越聪明
    int runTime; //记录运动时间
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
    int bitmap;
    int sprite; //精灵
    struct _ENEMY *next;

} _GANODERMA; //灵芝 （灵芝什么的弱爆了 一动不动的就可以了）


//创建敌人 参数 敌人类型，(精灵文件，敌人图片根据敌人类型自动设置)
_ENEMY *enemy_create(char *enemy_name) {
    if(strcmp(enemy_name,"_FLOWER")==0){ //花
    _FLOWER *flower = malloc(sizeof(_FLOWER));
    memset(flower,0, sizeof(_FLOWER));
    flower->name = "_FLOWER";
//    flower->isSleep=1;
    flower->isDraw = 1;
    flower->hp = 1;
    flower->direction = _UP;
    flower->bitmap = readBitmapFromAssets("flower.png");
    flower->sprite = sp_read("flower.sprite",flower->bitmap);
    sp_setxy( flower->sprite,flower->x,flower->y);
        return (_ENEMY *) flower;
    }
    if(strcmp(enemy_name,"_GANODERMA")==0){ //灵芝
    _GANODERMA *ganoderma = malloc(sizeof(_GANODERMA));
    memset(ganoderma,0, sizeof(_GANODERMA));
    ganoderma->name = "_GANODERMA";
    ganoderma->isDraw = 1;
    ganoderma->bitmap = readBitmapFromAssets("ganoderma.png");
    ganoderma->sprite = sp_read("ganoderma.sprite",ganoderma->bitmap);
    sp_setxy(ganoderma->sprite,ganoderma->x,ganoderma->y);
        return (_ENEMY *) ganoderma;
    }
    if(strcmp(enemy_name,"_HEDGEHOG")==0){ //刺猬
        _HEDGEHOG *hedgehog = malloc(sizeof(_HEDGEHOG));
        memset(hedgehog,0, sizeof(_HEDGEHOG));
        hedgehog->name = "_HEDGEHOG";
        hedgehog->isDraw = 1;
        hedgehog->bitmap = readBitmapFromAssets("hedgehog.png");
        hedgehog->sprite = sp_read("hedgehog.sprite",hedgehog->bitmap);
        return (_ENEMY *) hedgehog;
    }
    if(strcmp(enemy_name,"_MUSHROOM")==0){ //蘑菇
        _MUSHROOM *mushroom = malloc(sizeof(_MUSHROOM));
        memset(mushroom,0, sizeof(_MUSHROOM));
        mushroom->name = "_MUSHROOM";
        mushroom->isDraw = 1;
        mushroom->bitmap = readBitmapFromAssets("mogu.png");
        mushroom->sprite = sp_read("mogu.sprite", mushroom->bitmap);
        mushroom->checkTime = 10;
        return (_ENEMY *) mushroom;
    }
    if(strcmp(enemy_name,"_MISSILE")==0){ //导弹
        _MISSILE *missile = malloc(sizeof(_MISSILE));
        memset(missile,0, sizeof(_MISSILE));
        missile->name = "_MISSILE";
        missile->isDraw = 1;
        missile->bitmap = readBitmapFromAssets("bullet.png");
        missile->sprite = sp_read("bullet.sprite",missile->bitmap);
        return (_ENEMY *) missile;
    }


    return null;
}

//设置敌人坐标
void enemy_setxy(_ENEMY *enemy, int x, int y){
    enemy->x = x;
    enemy->y = y;
//    logi("setxy");
    sp_setxy(enemy->sprite, enemy->x, enemy->y);
//    logi("set success");
    //只有导弹需要特殊处理
    if(strcmp(enemy->name,"_MISSILE") == 0){
        _MISSILE *missile = (_MISSILE *) enemy;
        missile->bullet_y = missile->y;
        missile->bullet_x = missile->x;
    }
}

//添加一个敌人
void enemy_add(_ENEMY *enemys,_ENEMY *temp){
    while (enemys->next){
        enemys=enemys->next;
    }
    enemys->next = temp;
}


//花的运动事件 因为花不需要依赖地图 所以不需要传地图参数
void enemy_flower_run(_FLOWER *enemy) {
    //move_y取值 0到-20
    if (enemy->isSleep)return;
    if(enemy->isDel)
        return;;
    enemy->move_y += enemy->move_v;
    if (enemy->move_y <= -30) {
        enemy->move_v = 1;
    }
    if (enemy->move_y >= 0) {
        enemy->move_v = -1;
    }
    sp_setxy(enemy->sprite, enemy->x, enemy->y + enemy->move_y);
    sp_run(enemy->sprite);
}

//绘制花
void enemy_flower_draw(_FLOWER *enemy, int camera) {
    if (enemy->isSleep) return;
    if (!enemy->isDraw) return;
    //计算出屏幕坐标
    int ix = enemy->x - ca_getx(camera);
    int iy = enemy->y - ca_gety(camera);
    sp_draw(enemy->sprite, camera);
}

//花与主角碰撞
int enemy_flower_coll(_FLOWER *enemy, _HERO *hero) {
    if (enemy->isSleep) return 0;
    if(enemy->isDel) return 0;
    int sprite_hero = hero_getSprite(hero);
    return sp_crash(sprite_hero, enemy->sprite);
}

//蘑菇运动事件
void enemy_mushroom_run(_MUSHROOM *mushroom, TILED_OBJECT_LAYER *layer) {
    if (mushroom->isSleep) return;
    if(mushroom->isDel) return;
//    logi("蘑菇运动");
    int width = sp_getWidth(mushroom->sprite);
    int height = sp_getHeight(mushroom->sprite);
    int action = sp_getAction(mushroom->sprite);
    //下落
    mushroom->y += mushroom->gv;
    //判断是否碰撞 如果是，则不下落
    if (tiled_isCollObjectLayer(layer, mushroom->x + width / 2, mushroom->y + height - 1)) {
        mushroom->y -= mushroom->gv;
    }
        //如果否，则加速
    else {
        mushroom->gv++;
        if (mushroom->gv > 5) {
            mushroom->gv = 5;
        }
    }
    if(action==0) {


        if (mushroom->direction == _LEFT) {
            mushroom->x -= 2;
            mushroom->runTime++;
            if (!tiled_isCollObjectLayer(layer, mushroom->x,
                                         mushroom->y + height)) {
                if (mushroom->runTime >= mushroom->checkTime) {
                    mushroom->direction = _RIGHT;
                    mushroom->runTime = 0;
                }
            }
            //判断是否撞到墙
            if(tiled_isCollObjectLayer(layer, mushroom->x, mushroom->y+height/2)){
                mushroom->direction = _RIGHT;
                mushroom->runTime = 0;
            }
        } else if (mushroom->direction == _RIGHT) {
            mushroom->x += 2;
            mushroom->runTime++;
            if (!tiled_isCollObjectLayer(layer, mushroom->x + width - 1, mushroom->y + height)) {
                if (mushroom->runTime >= mushroom->checkTime) {
                    mushroom->direction = _LEFT;
                    mushroom->runTime = 0;
                }
            }
            //判断是否撞到墙
            if(tiled_isCollObjectLayer(layer, mushroom->x+width-1, mushroom->y+height/2)){
                mushroom->direction = _LEFT;
                mushroom->runTime = 0;
            }
        } else {
            mushroom->direction = _LEFT;
        }
    }
    sp_setxy(mushroom->sprite, mushroom->x, mushroom->y);
    sp_run(mushroom->sprite);


}

//刺猬运动事件 刺猬比蘑菇运动慢
void enemy_hedgehog_run(_HEDGEHOG *mushroom, TILED_TILE_LAYER *layer) {
    if (mushroom->isSleep) return;
    if(mushroom->isDel) return;
    int width = sp_getWidth(mushroom->sprite);
    int height = sp_getHeight(mushroom->sprite);
    //下落
    mushroom->y += mushroom->gv;
    //判断是否碰撞 如果是，则不下落
    if (tiled_getWorldData(layer, mushroom->x + width / 2, mushroom->y + height - 1)) {
        mushroom->y -= mushroom->gv;
    }
        //如果否，则加速
    else {
        mushroom->gv++;
        if (mushroom->gv > 5) {
            mushroom->gv = 5;
        }
    }
    if (mushroom->direction == _LEFT) {
        mushroom->x -= 1;
        if (!tiled_getWorldData((TILED_TILE_LAYER *) layer, mushroom->x,
                                mushroom->y + height - 1)) {
            if (mushroom->runTime >= mushroom->checkTime) {
                mushroom->direction = _RIGHT;
            }
        }
    } else if (mushroom->direction == _RIGHT) {
        mushroom->x += 1;
        if (!tiled_getWorldData((TILED_TILE_LAYER *) layer, mushroom->x + width - 1, mushroom->y)) {
            if (mushroom->runTime >= mushroom->checkTime) {
                mushroom->direction = _RIGHT;
            }
        }
    }
    sp_setxy(mushroom->sprite, mushroom->x, mushroom->y);
    sp_run(mushroom->sprite);


}


//鸭子运动事件


//导弹运动事件 导弹不需要判断地图碰撞
void enemy_missile_run(_MISSILE *missile) {
    if(missile->isSleep) return;
    if(missile->isDel) return;
    //子弹运动
    if (missile->direction == _LEFT) {
        missile->bullet_x -= 3;
        if (missile->x - missile->bullet_x > 1000) {
            missile->bullet_x = missile->x; //初始化导弹
        }
    } else if (missile->direction == _RIGHT) {
        missile->bullet_x += 3;
        if (missile->bullet_x - missile->x > 1000) {
            missile->bullet_x = missile->x;
        }

    }
    sp_setxy(missile->bullet_sprite, missile->bullet_x, missile->bullet_y);
    sp_run(missile->bullet_sprite);
    sp_run(missile->sprite);
}


//敌人运动 参数 敌人 图层 主角坐标
void enemys_run(_ENEMY *enemy, TILED_OBJECT_LAYER *layer, int hero_x,int hero_y){

    while (enemy){
        if(!enemy->isDel || !enemy->isSleep) {


            if (strcmp(enemy->name, "_HEDGEHOG") == 0) { //刺猬
                enemy_hedgehog_run((_HEDGEHOG *) enemy, layer);
            }
            if (strcmp(enemy->name, "_FLOWER") == 0) { //花
                enemy_flower_run((_FLOWER *) enemy);
            }
            if (strcmp(enemy->name, "_MISSILE") == 0) { //导弹
                enemy_missile_run((_MISSILE *) enemy);
            }
            if (strcmp(enemy->name, "_MUSHROOM") == 0) { //蘑菇
                enemy_mushroom_run((_MUSHROOM *) enemy, layer);
            }
        }
        else{
            logi("对象运动失败 %s",enemy->name);
        }
        enemy = enemy->next;
    }
}

//判断是否与主角碰撞 导弹只有子弹才有碰撞
int enemy_isCollHero(_ENEMY *enemy, _HERO *hero) {
    int hero_sprite = hero_getSprite(hero);
    if(enemy->isDel) return 0;
    if(enemy->isSleep) return 0;
    //花
    if (strcmp(enemy->name, "_FLOWER") == 0) {
        _FLOWER *flower = (_FLOWER *) enemy;
        return (sp_crash(flower->sprite, hero_sprite));


    }
//        刺猬
    else if (strcmp(enemy->name, "_HEDGEHOG") == 0) {
        _HEDGEHOG *hedgehog = (_HEDGEHOG *) enemy;
        return sp_crash(hedgehog->sprite, hero_sprite);
    }
//        蘑菇
    else if (strcmp(enemy->name, "_MUSHROOM") == 0) {
        _MUSHROOM *mushroom = (_MUSHROOM *) enemy;
        return sp_crash(mushroom->sprite, hero_sprite);
    }
//        导弹
    else if (strcmp(enemy->name, "_MISSILE") == 0) {
        _MISSILE *missile = (_MISSILE *) enemy;
        return sp_crash(missile->bullet_sprite, hero_sprite);
    }
//        灵芝
    else if (strcmp(enemy->name, "_GANODERMA") == 0) {
        _GANODERMA *ganoderma = (_GANODERMA *) enemy;
        return sp_crash(ganoderma->sprite, hero_sprite);
    }
//        花
    return 0;
}

//绘制敌人 判断敌人类型进行绘制
void enemys_draw(_ENEMY *enemy,int camera){

    while (enemy){
        if(enemy->isDraw) {


            if (strcmp(enemy->name, "_GANODERMA") == 0) {
                _GANODERMA *ganoderma = (_GANODERMA *) enemy;
                sp_setDraw(ganoderma->sprite, 1);
                sp_draw(ganoderma->sprite, camera);

//            drawBitmap(ganoderma->bitmap,0,0);
//                logi("画蘑菇 %d %d %d", ganoderma->sprite, ganoderma->x, ganoderma->y);
            }
            if (strcmp(enemy->name, "_FLOWER") == 0) {
                _FLOWER *flower = (_FLOWER *) enemy;
                enemy_flower_draw(flower, camera);
            }
            if (strcmp(enemy->name, "_HEDGEHOG") == 0) {
                _HEDGEHOG *hedgehog = (_HEDGEHOG *) enemy;
                sp_draw(hedgehog->sprite, camera);
            }
            if (strcmp(enemy->name, "_MISSILE") == 0) {
                _MISSILE *missile = (_MISSILE *) enemy;
                sp_draw(missile->sprite, camera);
                sp_draw(missile->bullet_sprite, camera);
            }
            if (strcmp(enemy->name, "_MUSHROOM") == 0) {
                _MUSHROOM *mushroom = (_MUSHROOM *) enemy;
                sp_draw(mushroom->sprite, camera);
            }
        }
        enemy = enemy->next;
    }
}

//释放敌人 将精灵 图片 一并释放
void enemy_free(_ENEMY *enemy){
    //花
    if (strcmp(enemy->name, "_FLOWER") == 0) {
        _FLOWER *flower = (_FLOWER *) enemy;
        sp_free(flower->sprite);
    }
//        刺猬
    else if (strcmp(enemy->name, "_HEDGEHOG") == 0) {
        _HEDGEHOG *hedgehog = (_HEDGEHOG *) enemy;
        sp_free(hedgehog->sprite);
    }
//        蘑菇
    else if (strcmp(enemy->name, "_MUSHROOM") == 0) {
        _MUSHROOM *mushroom = (_MUSHROOM *) enemy;
        sp_free(mushroom->sprite);
    }
//        导弹
    else if (strcmp(enemy->name, "_MISSILE") == 0) {
        _MISSILE *missile = (_MISSILE *) enemy;
        sp_free(missile->sprite);
        sp_free(missile->bullet_sprite);
    }
//        灵芝
    else if (strcmp(enemy->name, "_GANODERMA") == 0) {
        _GANODERMA *ganoderma = (_GANODERMA *) enemy;
        sp_free(ganoderma->sprite);
    }

    bitmapFree(enemy->bitmap);
    free(enemy);

}

void enemys_free(_ENEMY *enemys){

    while (enemys){
        _ENEMY *temp = enemys->next;
        enemy_free(enemys);
        enemys = temp;
    }
}






#endif

