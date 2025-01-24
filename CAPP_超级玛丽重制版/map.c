

#include "base.h"
#include "exb.h"
#include "android.h"
#include "graphics.h"
#include "ex_game.h"
#include "readSprite.h"

#include "tiled.h"
#include "enemy.h"
#include "world.h"
#include "map.h"

void *tiled_createData(char *txtfile, char *spritefile, int bitmap) {
    _TILED *tiled = malloc(sizeof(_TILED));
    int len;
    memset(tiled, 0, sizeof(_TILED));
    tiled->camera = ca_create(0, 0, SCRW, SCRH);
    tiled->world = world_create();
    world_setCamera(tiled->world, tiled->camera);
    //创建敌人
    tiled->en_task = en_create("enemy1.txt");
    en_addWorld(tiled->en_task, tiled->world);
    char *buf = readFileFromAssets(txtfile, &len);
    char *text = malloc(len + 1);
    memcpy(text, buf, len);
    text[len] = 0;

    tiled->data = readTextInfo(text, &(tiled->width), &(tiled->height), &(tiled->itemw),
                               &(tiled->itemh));
    tiled->bitmap = bitmap;
    free(text);
    printf("申请精灵\n");
    tiled->sprite = malloc(tiled->width * tiled->height * 4);
    //读取精灵
    printf("读取精灵\n");
    int sprite = sp_read(spritefile, bitmap);

    //将图块循环添加到世界中
    printf("添加图块\n");
    int ix, iy;
    int sp_temp;
    for (iy = 0; iy < tiled->height; iy++)
        for (ix = 0; ix < tiled->width; ix++) {

            sp_temp = sp_copy(sprite);
            sp_setxy(sp_temp, ix * tiled->itemw, iy * tiled->itemh);
            sp_setAction(sp_temp, tiled->data[iy * tiled->width + ix]);
            tiled->sprite[iy * tiled->width + ix] = sp_temp;

            world_addSprite(tiled->world, sp_temp);
            //printf("action=%d\n", tiled-> data[iy*tiled->width+ix]);
        }

    sp_free(sprite);
    return tiled;

}


//创建tiled
//参数：地图文件路径 精灵文件路径
void *tiled_create(char *tmxfile, char *spritefile, int bitmap) {
    _TILED *tiled = malloc(sizeof(_TILED));
    int len;
    memset(tiled, 0, sizeof(_TILED));
    char *buf = readFileFromAssets(tmxfile, &len);
    char *text = malloc(len + 1);
    memcpy(text, buf, len);
    text[len] = 0;

    tiled->data = readtiledInfo(text, &(tiled->width), &(tiled->height), &(tiled->itemw),
                                &(tiled->itemh));
    tiled->bitmap = bitmap;
    free(text);
    printf("申请精灵\n");
    tiled->sprite = malloc(tiled->width * tiled->height * 4);
    //读取精灵
    printf("读取精灵\n");
    int sprite = sp_read(spritefile, bitmap);
    tiled->camera = ca_create(0, 0, SCRW, SCRH);
    tiled->world = world_create();
    world_setCamera(tiled->world, tiled->camera);
    //将图块循环添加到世界中
    printf("添加图块\n");
    int ix, iy;
    int32 sp_temp;
    for (iy = 0; iy < tiled->height; iy++)
        for (ix = 0; ix < tiled->width; ix++) {

            sp_temp = sp_copy(sprite);
            sp_setxy(sp_temp, ix * tiled->itemw, iy * tiled->itemh);
            sp_setAction(sp_temp, tiled->data[iy * tiled->width + ix]);
            tiled->sprite[iy * tiled->width + ix] = sp_temp;

            world_addSprite(tiled->world, sp_temp);
            //printf("action=%d\n", tiled-> data[iy*tiled->width+ix]);
        }

    sp_free(sprite);
    return tiled;
}


//获取世界
int tiled_getWorld(_TILED *tiled) {
    return tiled->world;
}

//获取图块宽度
int tiled_getItemWidth(_TILED *tiled) {
    return tiled->itemw;
}

//获取摄像机
int tiled_getCamera(_TILED *tiled) {
    return tiled->camera;
}

//获取指定位置的图块精灵
int tiled_getSprite(_TILED *tiled, int x, int y) {
    return tiled->sprite[y * tiled->width + x];
}

//获取指定位置的地图数据
int tiled_getDataXY(_TILED *tiled, int x, int y) {
    return tiled->data[y * tiled->width + x];
}

//通过世界坐标获取地图数据
int tiled_getDataCoor(_TILED *tiled, int x, int y) {
    return tiled->data[y / tiled->itemw * tiled->width + x / tiled->itemh];
}


//销毁地图
int tiled_free(_TILED *tiled) {
    if(tiled == NULL){
        return 0;
    }
    //bitmap
    if(tiled->bitmap){
        bitmapFree(tiled->bitmap);
        tiled->bitmap = 0;
    }
    
    //sprite
    for (int i = 0; i < tiled->width * tiled->height; i++){
        if(tiled->sprite[i]){
            sp_free(tiled->sprite[i]);
            tiled->sprite[i] = 0;
        }
        
    }
    if(tiled->sprite){
        free(tiled->sprite);
        tiled->sprite = 0;
    }
    
    //camera
    if(tiled->camera){
        ca_free(tiled->camera);
        tiled->camera = 0;
    }
    
    //world
    if(tiled->world){
        world_free(tiled->world);
        tiled->world = 0;
    }
    
    //data
    if(tiled->data != NULL){
        free(tiled->data);
        tiled->data = NULL;
    }
    

    //tiled
    free(tiled);
    return 0;
}




