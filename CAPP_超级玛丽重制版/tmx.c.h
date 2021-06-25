#ifndef _TMX_C_
#define _TMX_C_

//#include <malloc.h>
//#include <stdlib.h>
#include <stdlib.h>
#include "base.h"
#include "graphics.h"
#include "android.h"
#include "tmx.h"
#include "ex_math.h"
#include "readtext.h"
#include "log.h"

#ifndef null
#define null (void*)0
#endif


//创建地图
TILED_MAP *tiled_create_map() {
    TILED_MAP *tiled_map = malloc(sizeof(TILED_MAP));
    memset(tiled_map,0, sizeof(TILED_MAP));
    return tiled_map;
}

static char *getValue(char *word) {
    int i = 0;
    char c = 0;
    char *buf = NULL;
    while (word[i]) {
        c = word[i];
        if (c == '\"') {
            buf = malloc(i + 1);
            memset(buf, 0, i + 1);
            memcpy(buf, word, i);
            return buf;
        }
        i++;
    }
    return buf;
}


static void layer_addLayer(TILED_LAYER *layer, TILED_LAYER *new_layer) {
    while (layer->next) {
        layer = layer->next;
    }
    layer->next = new_layer;
    new_layer->next = null;
}

//在地图中添加一个图层
static void tiled_addLayer(TILED_MAP *map, TILED_LAYER *layer) {
    map->layer_size++;
    printf("添加一个图层%s", layer->name);
    TILED_LAYER *temp_layer = map->layer;
    if (map->layer == null) {
        map->layer = layer;
        layer->next = null;
    } else {
        layer_addLayer(map->layer, layer);
    }

}

//删除一个图层
void tiled_delLayer(TILED_MAP *map, TILED_LAYER *layer) {
    TILED_LAYER *temp_layer = map->layer;

    if (map->layer == layer) {
        map->layer = null;
        return;
    }
    while (temp_layer->next) {
        if (temp_layer->next == layer) {
            temp_layer->next = temp_layer->next->next;
            return;
        }
        temp_layer = temp_layer->next;
    }

}

//从assets目录读取地图
TILED_MAP *tiled_readFileCreateTiled(char *filename) {
//    printf(filename);
    char *text = text_readFromAssets(filename);
    char text_temp[266];
    strncpy(text_temp, text,200);
    printf("读取文件：%s ",text_temp);
    printf("开始循环");

    int i = 0;
    char c = 0;
    int type = 0;
    int img_width, img_height;
    char *buf = null;
    char *head = null;
    char *item = null;
    char *word = null;
//    int *data = NULL;
    int offset = 0;
    int temp_num = 0;
    TILED_TILE_LAYER *tile_layer_temp = null;
    TILED_BACKGROUND_LAYER *background_layer_temp = null;
    TILED_OBJECT_LAYER *object_layer_temp = null;
    TILED_OBJECT *object = null;
    TILED_MAP *tiled_map = malloc(sizeof(TILED_MAP));
    memset(tiled_map,0, sizeof(TILED_MAP));
    TILED_IMAGE *tiled_image = malloc(sizeof(TILED_IMAGE));
    memset(tiled_image,0, sizeof(TILED_IMAGE));
    tiled_map->image = tiled_image;
    int index_num = 0;

    while (text[i]) {
        c = text[i];
//        printf("%c",  c);
        switch (type) {
            case 0:
                if (c == '<')
                    type = 1;
                break;
            case 1: //解析头信息
                head = text + i;
                type = 2;

                break;
            case 2: //跳过空格
                if (c == ' ')
                    type = 3;
                else if (c == '>')
                    type = 0;
                break;
            case 3: //解析参数
                item = text + i;
                type = 4;
                if (c == '>')
                    type = 0;

                if (c == '>')
                    type = 0;
                if (c == '/')
                    type = 9;

                break;
            case 4: //等于
                if (c == '=')
                    type = 5;
                break;
            case 5: //解析引号
                if (c == '"') {
                    type = 6;
                    word = text + i + 1;

                    if (strncmp(head, "map", 3) == 0) {
                        printf("map\n");
                        if (strncmp(item, "tilewidth", 5 + 4) == 0) {
                            tiled_map->tilewidth = atoi(word);

                        } else if (strncmp(item, "tileheight", 6 + 4) == 0) {
                            tiled_map->tileheight = atoi(word);
                        }
                        else if(strncmp(item,"width",5)==0){
                            tiled_map->width = atoi(word);
                        }
                        else if(strncmp(item,"height",6)==0){
                            tiled_map->height = atoi(word);
                        }
                    }////////////////
                    else if (strncmp(head, "image", 5) == 0) {
                        printf("image %s = %s\n",getValue(item),getValue(word));
                        if (strncmp(item, "width", 5) == 0) {
                            img_width = atoi(word);
tiled_image->width = atoi(word);
                        } else if (strncmp(item, "height", 6) == 0) {
                            img_height = atoi(word);
tiled_image->height = atoi(word);

                        }
                        else if(strncmp(item,"source",6)==0){
                            int len = 0;
                            printf("加载图片%s",getValue(word));
                            tiled_image->bitmap = readBitmapFromAssets(getValue(word));
                        }
                    }//////////
                    else if (strncmp(head, "layer", 5) == 0) {
                        if (strncmp(item, "width", 5) == 0) {
                            tile_layer_temp->width = atoi(word);
                            printf("width=%d\n", tile_layer_temp->width);
                        } else if (strncmp(item, "height", 6) == 0) {
                            tile_layer_temp->height = atoi(word);
                            printf("height=%d\n", tile_layer_temp->height);
                        } else if (strncmp(item, "name", 4) == 0) {
                            //创建一个图层
                            tile_layer_temp = malloc(sizeof(TILED_TILE_LAYER));
                            memset(tile_layer_temp, 0, sizeof(TILED_TILE_LAYER));
                            tile_layer_temp->name = "TILED_TILE_LAYER";
                            tile_layer_temp->item_height=tiled_map->tileheight;
                            tile_layer_temp->item_width=tiled_map->tilewidth;
                            tile_layer_temp->layer_name = getValue(word);
                            tiled_addLayer(tiled_map, (TILED_LAYER *) tile_layer_temp);
                        }
                        if (tile_layer_temp->width != 0 && tile_layer_temp->height != 0) {
                            tile_layer_temp->data = malloc(
                                    tile_layer_temp->width * (tile_layer_temp->height) *
                                    sizeof(int));
                            printf("malloc width%d height%d\n", tile_layer_temp->width,
                                   tile_layer_temp->height);
                        }
                    }//////////
                    else if (strncmp(head, "data", 4) == 0) {
                        if (strncmp(item, "encoding", 8) == 0) {
                            if (strncmp(word, "csv", 3) == 0) {
//读取data数据
                                type = 10;
                            } else {
                                printf("不支持的地图加载编码:%s", word);
                            }
                        }
                    } else if (strncmp(head, "tile ", 5) == 0) {
                        if (strncmp(item, "gid", 3) == 0)
                            tile_layer_temp->data[offset++] = atoi(word);
                    } else if (strncmp(head, "objectgroup", 11) == 0) {
                        if (strncmp(item, "name", 4) == 0) {
                            //创建对象层
                            object_layer_temp = malloc(sizeof(TILED_OBJECT_LAYER));
                            memset(object_layer_temp, 0, sizeof(TILED_OBJECT_LAYER));
                            object_layer_temp->name = "TILED_OBJECT_LAYER";
                            object_layer_temp->layer_name = getValue(word);
                            tiled_addLayer(tiled_map, (TILED_LAYER *) object_layer_temp);
                        }
                    } else if (strncmp(head, "object ", 7) == 0) {
                        if (strncmp(item, "id", 2) == 0) {
                            object = malloc(sizeof(TILED_OBJECT));
                            memset(object, 0, sizeof(TILED_OBJECT));
                            object->id = atoi(word);
                            tiled_addObject(object_layer_temp, object);

                        } else if (strncmp(item, "x", 1) == 0) {
                            object->x = atoi(word);
                        } else if (strncmp(item, "y", 1) == 0) {
                            object->y = atoi(word);
                        } else if (strncmp(item, "width", 5) == 0) {
                            object->width = atoi(word);
                        } else if (strncmp(item, "height", 6) == 0) {
                            object->height = atoi(word);
                        }
                    } else if (strncmp(head, "backgrounf", 10) == 0) {  //读取背景层 暂未实现

                    }
                }
                break;
            case 6: //解析反引号
                if (c == '"') {
                    type = 2;
                }
                break;
            case 7:
                if (c == '>') {
                    type = 0;
                } else if (c == '/') {
                    type = 9;
                }
                break;
            case 9:
                if (c == '>')
                    type = 0;
                break;
            case 10:
                if (c >= '0' && c <= '9') {
                    temp_num = temp_num * 10 + (c - '0');

                } else if (c == ',') {
                    tile_layer_temp->data[index_num] = temp_num;
                    index_num++;
                    temp_num = 0;
                } else if (c == '<') {
                    tile_layer_temp->data[index_num] = temp_num;
                    temp_num = 0;
                    type = 1;
                    index_num = 0;
                }
                break;
            case 11:
            default:
                break;
        }
        i++;
    }
    free(text);

    //printf("width=%d height=%d itemw=%d itemh=%d\n", *width, *height, *item_width, *item_height);

    return tiled_map;
}

TILED_TILE_LAYER *tiled_createTiledLayer() {
    TILED_TILE_LAYER *layer = malloc(sizeof(TILED_TILE_LAYER));
    memset(layer, 0, sizeof(TILED_TILE_LAYER));
    return layer;
}

TILED_OBJECT_LAYER *tiled_createObjectLayer() {
    TILED_OBJECT_LAYER *layer = malloc(sizeof(TILED_OBJECT_LAYER));
    memset(layer, 0, sizeof(TILED_OBJECT_LAYER));
    return layer;
}

TILED_BACKGROUND_LAYER *tiled_crreteBackgroundLayer() {
    TILED_BACKGROUND_LAYER *layer = malloc(sizeof(TILED_BACKGROUND_LAYER));
    memset(layer, 0, sizeof(TILED_BACKGROUND_LAYER));
    return layer;
}

//获取地图第i层数据
TILED_LAYER *tiled_getLayer(TILED_MAP *map, int i) {
    int index = 0;
    TILED_LAYER *layer = map->layer;
    do {
        if (index == i) {
            return layer;
        }
        index++;
        layer = layer->next;
    } while (layer);
    return null;

}

char *tiled_getMapType(TILED_LAYER *layer) {
    return layer->name;
}


void tiled_setTileDataXY(TILED_TILE_LAYER *layer, int x, int y, int data) {
    //判断是否越界
    int width = layer->width;
    int height = layer->height;
    if (x < width && y < height) {
        layer->data[width * y + x] = data;
    }
}

//获取图层xy图块位置的data数据
int tiled_getTileDataXY(TILED_TILE_LAYER *layer, int x, int y) {
    int width = layer->width;
    int height = layer->height;
    if (x < width && y < height) {
        return layer->data[width * y + x];
    }
    return 0;
}

//在对象层中添加一个对象
void tiled_addObject(TILED_OBJECT_LAYER *layer, TILED_OBJECT *object) {
    TILED_OBJECT *temp = layer->object;
    if (temp == null) {
        layer->object = object;
        object->next = null;
    } else {
        object->next = temp;
        layer->object = object;
    }
}

//获取图层在世界中xy坐标的data数据
int tiled_getWorldData(TILED_TILE_LAYER *layer, int x, int y) {
    int scr_w = layer->item_width * layer->width;
    int scr_h = layer->item_height * layer->height;
    int ix = x / layer->item_width;
    int iy = y / layer->item_height;
    if (ix>=0 && iy>=0 && ix < layer->width && iy < layer->height) {
        return layer->data[iy * layer->width + ix];
    }
    return 0;
}

int tiled_isCollObjectLayer( TILED_OBJECT_LAYER *layer,int x,int y) {
//    logi("检测");
if(strcmp(layer->name,"TILED_OBJECT_LAYER")){
    logi("碰撞检测错误 当前图层不是对象层");
}
    TILED_OBJECT *object = layer->object;
    while (object) {
//        logi("%d",object);
        if (isPointCollRect(x, y,  object->x, object->y, object->width,
                            object->height)) {
            return 1;
        }
        object = object->next;
    }
    return 0;
}


//寻找指定名字的图层
TILED_LAYER *tiled_findLayerFromName(TILED_MAP *map, char *name) {
    TILED_LAYER *layer = map->layer;
    do {
        if (strcmp(layer->layer_name, name) == 0) {
            return layer;
        }
        layer = layer->next;
    } while (layer);
    return null;
}


int tiled_findData(TILED_TILE_LAYER *layer, int data) {
    int length = layer->width * layer->height;
    for (int i = 0; i < length; i++) {
        if (layer->data[i] == data) {

            return i;
        }
    }
    return 0;
}

int *tiled_getData(TILED_TILE_LAYER *layer) {
    return layer->data;
}

//获取图层的名称
char *tiled_getMapName(TILED_LAYER *layer) {
    return layer->layer_name;
}

//读取tmx地图



//保存tmx地图







//打印图层信息
void tiled_toString(TILED_MAP *map){
    logi("地图宽度：%d 地图高度：%d 图块宽度：%d 图块高度：%d 图层数：%d", map->width,map->height,map->tilewidth, map->tileheight,map->layer_size);
    //输出图层数据
    TILED_LAYER *layer = map->layer;
    int i=0;
    while (layer){
        logi("第%d层：%s %s",i,layer->name,layer->layer_name);
        layer=layer->next;
        i++;
    }
}



int tiled_free(TILED_MAP *map) {
    TILED_LAYER *layer = map->layer;
    TILED_LAYER *uplayer = null;
    do {

        uplayer = layer;
        layer = layer->next;
        if (uplayer != null) {
            if (strcmp(uplayer->name, "TILED_BACKGROUND_LAYER") == 0) {
                TILED_BACKGROUND_LAYER *background_layer = (TILED_BACKGROUND_LAYER *) uplayer;
                if (background_layer->bitmap_background) {
                    bitmapFree(background_layer->bitmap_background);
                }
                free(layer->layer_name);

            }
            if (strcmp(uplayer->name, "TILED_TILE_LAYER") == 0) {
                TILED_TILE_LAYER *tile_layer = (TILED_TILE_LAYER *) uplayer;
                if (tile_layer->data) {
                    free(tile_layer->data);
                }
                free(tile_layer->layer_name);
            }
            if (strcmp(uplayer->name, "TILED_OBJECT_LAYER") == 0) {
                TILED_OBJECT_LAYER *object_layer = (TILED_OBJECT_LAYER *) uplayer;
                TILED_OBJECT *object = object_layer->object;
                TILED_OBJECT *upobject = null;
                do {
                    upobject = object;
                    object = object->next;
                    if (upobject) {
                        free(upobject);
                    }
                } while (object);
                free(uplayer->layer_name);
            }
            free(uplayer);
        }
    } while (layer);
    free(map);
    return 0;
}

#endif