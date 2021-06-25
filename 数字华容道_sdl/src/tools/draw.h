#ifndef _DRAW_H_
#define _DRAW_H_
#include "../api/base.h"
#include "../api/ex_math.h"
#include "../api/graphics.h"

int bitmap_getWidth(int32 bit);
int bitmap_getHeight(int32 bit);
int bitmap_getPix(BITMAPINFO *info, int x,int y);
int bitmap_setPix(BITMAPINFO *info, int x,int y,int color);
int32 bitmap_turn(int bitmap,int up, int left);

//圆环结构体
void drawCirCir(int x,int y,int r1,int r2,int color,int ii,int radi);

/**************
*用圆绘制粗斜线
*起点坐标：x,y
*倾斜角度：radi
*线的长度：size
*圆的大小：r
*线的颜色：color
***************/
int drawCirLine(int x,int y,int radi,int size,int r,int color);


/**************
*用圆绘制粗斜线
*起点坐标：x1,y1
*终点坐标：x2,y2
*圆的大小：r
*线的颜色：color
***************/
int drawCirLine2(int x1,int y1,int x2,int y2,int r,int color);

#endif

