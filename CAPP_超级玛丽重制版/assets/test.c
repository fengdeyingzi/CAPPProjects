

#include "base.h"
#include "tmx.h"
#include "android.h"
#include "graphics.h"
#include "ex_game.h"
#include "exb.h"
#include "tmx_world.h"
#include "world_hero.h"
#include "enemy.h"

//#include "graphics.h"
//#include "android.h"
//#include "tmx.h"
TILED_MAP *map;
TILED_TILE_LAYER *layer_tiled;
TILED_OBJECT_LAYER *layer_coll; //图块碰撞
TILED_OBJECT_LAYER *layer_banner; //旗帜
TILED_OBJECT_LAYER *layer_occ; //遮挡
TILED_OBJECT_LAYER *layer_end; //终点
_ENEMY *enemys;
int32 camera;
int upx, upy;
_HERO *hero;

//
void refreshMap();

void logoc(int32 data);

void objectToEnemy(_ENEMY *enemys, TILED_OBJECT_LAYER *layer_enemy, char *enemy_name);
_ENEMY *enemy_remove(_ENEMY *enemys, _ENEMY *temp);

int32 timer;

int init() {
    setscrsize(300 * SCRW / SCRH, 300);
    setpadtype(2);
    logi("测试读取tmx");
    map = tiled_readFileCreateTiled("mali.tmx");
    layer_tiled = (TILED_TILE_LAYER *) tiled_getLayer(map, 0);
    layer_coll = (TILED_OBJECT_LAYER *) tiled_findLayerFromName(map, "碰撞");
    if (layer_coll == null)logi("layer coll is null");
    layer_banner = (TILED_OBJECT_LAYER *) tiled_findLayerFromName(map, "旗帜");
    layer_occ = (TILED_OBJECT_LAYER *) tiled_findLayerFromName(map, "遮挡层");
    layer_end = (TILED_OBJECT_LAYER *) tiled_findLayerFromName(map, "城堡");

    TILED_OBJECT_LAYER *layer_gano = (TILED_OBJECT_LAYER *) tiled_findLayerFromName(map, "灵芝");
    TILED_OBJECT_LAYER *layer_mushroom = (TILED_OBJECT_LAYER *) tiled_findLayerFromName(map, "毒蘑菇");
    TILED_OBJECT_LAYER *layer_flower = (TILED_OBJECT_LAYER* ) tiled_findLayerFromName(map,"食人花");

    logi("111:)");

    TILED_OBJECT *object_mushroom = layer_mushroom->object;
    logi("222");
    enemys = enemy_create("_GANODERMA");
    logi("333");
    enemy_setxy(enemys, 0, 60);
    logi("444");

    objectToEnemy(enemys, layer_gano, "_GANODERMA");
    objectToEnemy(enemys, layer_mushroom, "_MUSHROOM");
    objectToEnemy(enemys,layer_flower,"_FLOWER");

    tiled_toString(map);
    logi("读取完成");

    logi("创建照相机");
    camera = ca_create(0, 0, SCRW, SCRH);
    logi("绘制图层");
    hero = hero_create("mario_small.sprite", "mario_small.sprite", "mario_small.png",
                       "mario_small.png");

    logi("测试完成");
//    tiled_toString(map);
    refreshMap();
    timer = timercreate();
    timerstart(timer, 50, 1, logoc, 1);
    hero_setxy(hero,20,9*20);
    return 0;
}

//将对象层生成对象
void objectToEnemy(_ENEMY *enemys, TILED_OBJECT_LAYER *layer_enemy, char *enemy_name) {
    TILED_OBJECT *object_gano = layer_enemy->object;
    while (object_gano) {
        logi("while");
        _ENEMY *enemy = enemy_create(enemy_name);
        enemy_setxy(enemy, object_gano->x, object_gano->y);
        logi("setxy %d %d", object_gano->x, object_gano->y);
        enemy_add(enemys, enemy);

        object_gano = object_gano->next;
    }
}

void logoc(int32 data) {

    hero_run(hero, layer_coll);
    enemys_run(enemys,layer_coll,hero_getX(hero)+hero_getW(hero)/2,hero_getY(hero)+hero_getH(hero)/2);
    if (hero_getAction(hero) != HERO_RIGHT && hero_isCollObjectLayer(hero, layer_banner)) {
        hero_setAction(hero, HERO_RIGHT);
        logi("撞到旗帜");
        toast("撞到旗帜", 0);
    }
    if (hero_isCollObjectLayer(hero, layer_end)) {
        logi("过关");
        hero_setAction(hero, HERO_RUN);
    }
    //设置相机跟随
    if (hero_getSpeedW(hero) > 0) { //前进
        if (hero_getX(hero) + SCRW / 2 > ca_getx(camera) + ca_getw(camera)) {
            ca_move(camera, 4, 0);
            if (ca_getx(camera) < 0) {
                ca_setxy(camera, 0, ca_gety(camera));
            }
        }

    } else if (hero_getSpeedW(hero) < 0) { //后退
        if (ca_getx(camera) > hero_getX(hero) - SCRW / 2) {
            ca_move(camera, -4, 0);
            if (ca_getx(camera) < 0) {
                ca_setxy(camera, 0, ca_gety(camera));
            }
        }
    }

    refreshMap();
}

//循环与主角检测碰撞
void hero_colls(_HERO *hero, _ENEMY *enemys){
    _ENEMY *temp = enemys;
    while (temp){
        if(strcmp(temp->name,"_MUSHROOM")==0){ //蘑菇
            if(enemy_isCollHero(temp,hero)){
                sp_setAction(temp->sprite,1);
            }
        }
        if(strcmp(temp->name,"_GANODERMA")==0){ //灵芝
            if(enemy_isCollHero(temp,hero)){
                //将灵芝从这里移除
                temp->isDel = 0;
//                enemys = enemy_remove(enemys,temp);
//                enemy_free(temp);
            }
        }
        temp = temp->next;
    }
}

//移除一个精灵 但不释放这个精灵的内存
_ENEMY *enemy_remove(_ENEMY *enemys, _ENEMY *temp){
    if(enemys == temp){
        return enemys->next;
    }
    _ENEMY *reenemys = enemys;
    while (reenemys){
        if(reenemys->next == temp){
            reenemys->next = reenemys->next->next;
        }
        reenemys = reenemys->next;
    }
    return reenemys;
}



void refreshMap() {
    cls(255, 255, 255);
    int32 time = getuptime();
    enemys_draw(enemys, camera);
    drawLayer(camera, map->image, (TILED_LAYER *) layer_tiled);
//    logi("绘制图层%d",getuptime()-time);
    hero_draw(hero, camera);
//    logi("绘制角色%d",getuptime()-time);
    //绘制旗帜
    drawLayer(camera, map->image, (TILED_LAYER *) layer_banner);
    //绘制遮罩
    drawLayer(camera, map->image, (TILED_LAYER *) layer_occ);
//    logi("绘制遮罩%d",getuptime()-time);
//绘制敌人

    hero_debug(hero);
    ref(0, 0, SCRW, SCRH);
}


int event(int type, int p1, int p2) {
//    if (type == MS_DOWN) {
//        upx = p1;
//        upy = p2;
//    }
//    if (type == MS_MOVE) {
//        ca_move(camera, p1 - upx, 0);
//        refreshMap();
//        upx = p1;
//        upy = p2;
//    }
//    hero_keyrun(hero, type, p1, p2);
    if (type == _LEFT) {

    }

    if (type == KY_DOWN) {
        if (p1 == _BACK) {
            exit();
        }
    }

    return 0;
}


int pause() {
    return 0;
}

int resume() {
    return 0;
}


int exitApp() {
    printf("应用退出");
    tiled_freemap(map);
    hero_free(hero);
    enemys_free(enemys);
    timerstop(timer);
    timerdel(timer);
    return 0;
}










