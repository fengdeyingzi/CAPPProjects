#ifndef _PAD_H_
#define _PAD_H_

#include "../api/base.h"

extern int event(int type, int p1, int p2);

typedef struct Rock {
	int x1;
	int y1;	 //中心坐标
	int r1;	 //大圆
	int x2;
	int y2;
	int r2;	 //小圆
	int dir;
	int len;
	int _i;		//手指
	int _t;		//定时器
	int _type;	//event事件
} RockPad;

extern void runRockPad(int32 id);
extern void initRockPad(RockPad* pad,
				 int x, int y, int r1, int r2);
extern void rockPadEvent(RockPad* pad);
extern void drawRockPad(RockPad* pad);
extern void delRockPad(RockPad* pad);

#endif
