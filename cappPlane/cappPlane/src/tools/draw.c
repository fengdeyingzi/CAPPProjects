
#include "./draw.h"

//绘制圆环
void drawCirCir(int x, int y, int r1, int r2, int32 color, int ii, int radi) {
	int dx, dy;
	//计算圆半径
	int r = (r2 - r1) / 2;
	//循环绘制
	for (int i = 0; i < ii; i++) {
		dx = x + r;
		dy = y;
		toSpin(x, y, r1 + r, r1 + r, i * radi / ii, &dx, &dy);
		drawCir(dx, dy, r, color);
	}
}

/**************
*用圆绘制粗斜线
*起点坐标：x,y
*倾斜角度：radi
*线的长度：size
*圆的大小：r
*线的颜色：color
***************/
int drawCirLine(int x, int y, int radi, int size, int r, int32 color) {
	int cx, cy;
	//循环取值
	for (int i = 0; i < size; i++) {
		cx = x;
		cy = y - i;
		//旋转
		toSpin(x, y, i, i, radi, &cx, &cy);
		//绘制
		drawCir(cx, cy, r, color);
	}
	return 0;
}

/**************
*用圆绘制粗斜线
*起点坐标：x1,y1
*终点坐标：x2,y2
*圆的大小：r
*线的颜色：color
***************/
int drawCirLine2(int x1, int y1, int x2, int y2, int r, int32 color) {
	//取长度值
	int size = getLineSize(x1, y1, x2, y2);
	//取弧度值
	int radi = getRadiam(x1, y1, x2, y2);
	//循环取值
	drawCirLine(x1, y1, radi, size, r, color);
	return 0;
}
