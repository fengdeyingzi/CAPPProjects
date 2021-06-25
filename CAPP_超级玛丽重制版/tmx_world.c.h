#ifndef _TMX_WORLD_H_
#define _TMX_WORLD_H_

#include "base.h"
#include "tmx.c.h"
#include "ex_game.h"

//绘制一个线框
static void drawLineRect(int x, int y, int w, int h) {
    int r = 255;
    int g = 0;
    int b = 0;
    dline(x, y, x, y + h, r, g, b);
    dline(x + w, y, x + w, y + h, r, g, b);
    dline(x, y, x + w, y, r, g, b);
    dline(x, y + h, x + w, y + h, r, g, b);
}

//绘制地图 参数 相机 图片 地图
void drawLayer(int camera, TILED_IMAGE *tiled_image, TILED_LAYER *layer) {
    int dx =  ca_getx(camera);
    int dy =  ca_gety(camera);
//    printf("屏幕宽高%d %d dx=%d dy=%d",SCRW,SCRH,dx,dy);
    int i = 0;
    //获取bitmap宽度

    if (strcmp(layer->name, "TILED_TILE_LAYER") == 0) {
        TILED_TILE_LAYER *tile_layer = (TILED_TILE_LAYER *) layer;
        for (i = 0; i < tile_layer->width * tile_layer->height; i++) {
            int ix = i % tile_layer->width * tile_layer->item_width;
            int iy = i / tile_layer->width * tile_layer->item_height;
//            printf("ix=%d iy=%d",ix,iy);
            //计算图块的x y
            int bx = 0;
            int by = 0;
            for (int ii = 0; ii < tile_layer->data[i]-1; ii++) {
                bx += tile_layer->item_width;
                if (bx + tile_layer->item_width > tiled_image->width) {
                    bx = 0;
                    by += tile_layer->item_height;
                }


            }
            if (tile_layer->data[i]!=0  && ix>dx-tile_layer->item_width && iy>dy-tile_layer->item_height &&
                (ix < dx + SCRW) && (iy < dy + SCRH)) {
//                printf("绘制%d %d %d %d %d %d", dx+ix,
//                       dy+ iy , bx, by, tile_layer->item_width,
//                       tile_layer->item_height);

                drawBitmapFlip(tiled_image->bitmap, ix-dx,
                               iy-dy,  tile_layer->item_width,
                               tile_layer->item_height,bx, by);

            }

        }
    } else if (strcmp(layer->name, "TILED_OBJECT_LAYER") == 0) {
        TILED_OBJECT *object = (TILED_OBJECT *) ((TILED_OBJECT_LAYER *) layer)->object;
        while (object) {
            drawLineRect(dx + object->x, dy+ object->y,
                         object->width, object->height);
            object =  object->next;
        }
    }

}





//


#endif