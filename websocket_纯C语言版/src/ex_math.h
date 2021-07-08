
#ifndef _EX_MATH_H_
#define _EX_MATH_H_
#include <math.h>

/*
“shell（希尔）法”
shell法是一个叫 shell 的美国人与1969年发明的。它首先把相距k(k>=1)的那几个元素排好序，再缩小k值（一般取其一半），再排序，直到k=1时完成排序。下面让我们来分析其代码：
*/
void shell(int *a,int n);


//判断点(x,y)是否在矩形区域(rectx,recty,rectw,recth)内
int isPointCollRect(int x,int y,int rectx,int recty,int rectw,int recth);


// 矩形和圆形碰撞检测
int isCirCollRect(float circleXPos, float circleYPos, float radius, float rectX, float rectY, float rectW, float rectH);

// 线段和线段碰撞检测
/*
int IsLineCollisionLine(int p1, int p2, int p3, int p4)
{
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) 
        return FALSE;

    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;

    // Check if the x and y coordinates are within both lines
    if ( x < MIN(x1, x2) || x > MAX(x1, x2) ||
        x < MIN(x3, x4) || x > MAX(x3, x4) )
        return FALSE;

    if ( y < MIN(y1, y2) || y > MAX(y1, y2) ||
        y < MIN(y3, y4) || y > MAX(y3, y4) ) 
        return FALSE;

    return TURE;
}
*/


int isCollRect(int x1, int y1, int w1, int h1, int x2, int  y2, int w2, int h2);
	
	

	
	
		//点(x,y)旋转指定弧度r，得到旋转后的坐标
	//旋转一条水平线，得到旋转后的坐标
//参数：旋转中心点(px,py)，旋转横向半径rx，旋转纵向半径ry， 旋转后坐标指针(*x,*y)
	void toSpin(int px,int py,int rx,int ry,int r,int* x,int* y);
	
	//求两点之间距离 可用于计算圆与圆的碰撞(当两个圆的圆心距离大于它们的半径只和，那么碰撞成功)
	float getLineSize(int x,int y,int x2,int y2);
	
	
	
	//求点与点之间弧度
	float getRadiam(float x,float y,float rx,float ry);

	#endif