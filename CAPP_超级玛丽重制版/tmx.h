#ifndef _TMX_H_
#define _TMX_H_

#include "base.h"
#include "graphics.h"
#include "android.h"


//地图超类 模拟继承效果
typedef struct TILED_LAYER {
    char *name; //公共变量 用于识别结构体名字（类）
    char *layer_name; //图层名
    struct TILED_LAYER *next;
} TILED_LAYER;

//地图背景层
typedef struct TILED_BACKGROUND_LAYER {
    char *name;
    char *layer_name;
    struct TILED_LAYER *next;
    int bitmap_background;
} TILED_BACKGROUND_LAYER;

//地图图块层
typedef struct TILED_TILE_LAYER {
    char *name; //用于判断地图类型
    char *layer_name; //图层名字
    struct TILED_LAYER *next; //下一个图层数据
    int *data; //地图数据
    int width;//    地图宽度
    int height;//    地图高度
    int item_width;//    地图图块宽度
    int item_height;//    地图图块高度

} TILED_TILE_LAYER;


//
typedef struct TILED_OBJECT{
    int id;
    int x;
    int y;
    int width;
    int height;
    struct TILED_OBJECT *next;
} TILED_OBJECT;

//地图碰撞层
typedef struct TILED_OBJECT_LAYER {
    char *name;
    char *layer_name; //图层名字
    struct TILED_LAYER *next;
    struct TILED_OBJECT *object;
} TILED_OBJECT_LAYER;

typedef struct TILED_IMAGE{
    int bitmap;
    int width;
    int height;
    struct TILED_IMAGE *next;
} TILED_IMAGE;

//地图数据
typedef struct TILED_MAP {
    TILED_LAYER *layer; //图层数据
    struct TILED_IMAGE *image; //地图图片
    int layer_size; //图层数
    int tilewidth;
    int tileheight;
    int width;
    int height;
} TILED_MAP;

//在对象层中添加一个对象
void tiled_addObject(TILED_OBJECT_LAYER *layer, TILED_OBJECT *object);
//通过读取文件来创建地图 assets目录
TILED_MAP *tiled_readFileCreateTiled(char *filename);
//创建一个对象层
TILED_OBJECT_LAYER *tiled_createObjectLayer();

//创建一个图块层
TILED_TILE_LAYER *tiled_createTiledLayer();
//创建一个背景层
TILED_BACKGROUND_LAYER *tiled_crreteBackgroundLayer();

//获取当前图层的名字
char *tiled_getMapName(TILED_LAYER *layer);


//设置图块上x y点的数据
void tiled_setTileDataXY(TILED_TILE_LAYER *layer, int x, int y, int data);

//获取图层指定位置的数据
int tiled_getTileDataXY(TILED_TILE_LAYER *layer, int x, int y);


//获取图层指定世界坐标的点的数据
int tiled_getWorldData(TILED_TILE_LAYER *layer, int x, int y);

//寻找图层上指定点的位置
int tiled_findData(TILED_TILE_LAYER *layer, int data);

//寻找指定名称的图层
TILED_LAYER *tiled_findLayerFromName(TILED_MAP *map, char *name);

//获取当前图层的类型
char *tiled_getMapType(TILED_LAYER *layer);

//读取指定图层的数据
TILED_LAYER *tiled_getLayer(TILED_MAP *map, int i);

void tiled_delLayer(TILED_MAP *map, TILED_LAYER *layer);

//获取指定层数据
int *tiled_getData(TILED_TILE_LAYER *layer);

//释放内存
int tiled_free(TILED_MAP *map);













#endif


