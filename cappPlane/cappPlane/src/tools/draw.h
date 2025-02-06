#ifndef _DRAW_H_
#define _DRAW_H_

#include "../api/base.h"
#include "../api/ex_math.h"
#include "../api/graphics.h"
//圆环结构体
extern void drawCirCir(int x, int y, int r1, int r2, int32 color, int ii, int radi);

/**************
*用圆绘制粗斜线
*起点坐标：x,y
*倾斜角度：radi
*线的长度：size
*圆的大小：r
*线的颜色：color
***************/
/**
 * 用圆绘制粗斜线
 * @param x 起点x
 * @param y 起点y
 * @param radi 角度
 * @param size 长度
 * @param r 圆的半径
 * @param color 颜色
 * @returns 0
 */
extern int drawCirLine(int x, int y, int radi, int size, int r, int32 color);

/**************
*用圆绘制粗斜线
*起点坐标：x1,y1
*终点坐标：x2,y2
*圆的大小：r
*线的颜色：color
***************/
extern int drawCirLine2(int x1, int y1, int x2, int y2, int r, int32 color);

#endif
