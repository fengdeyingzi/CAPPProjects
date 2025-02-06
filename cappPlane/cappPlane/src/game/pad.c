#include "./pad.h"

#include "../api/base.h"
#include "../api/ex_math.h"
#include "../api/exb.h"
#include "../api/graphics.h"

void runRockPad(int32 id) {
	int x, y, r;
	RockPad* pad = (void*)id;
	if (pad->_i == -1) {
		for (int i = 0; i < 5; i++) {
			if (touch_isdown(i)) {
				x = touch_getx(i);
				y = touch_gety(i);
				if (getLineSize(x, y,
								pad->x2, pad->y2) < pad->r2) {
					pad->_i = i;
					rockPadEvent(pad);
					break;
				}
			}
		}
	} else if (touch_isdown(pad->_i)) {
		x = touch_getx(pad->_i);
		y = touch_gety(pad->_i);
		if (getLineSize(x, y,
						pad->x1, pad->y1) < pad->r1) {
			pad->x2 = x;
			pad->y2 = y;
		} else {
			pad->x2 = pad->x1 + pad->r1;
			pad->y2 = pad->y1;
			r = getRadiam(pad->x1, pad->y1,
						  x, y);
			toSpin(pad->x1, pad->y1,
				   pad->r1, pad->r1, r,
				   &(pad->x2), &(pad->y2));
		}
		rockPadEvent(pad);
	} else if (!touch_isdown(pad->_i)) {
		pad->x2 = pad->x1;
		pad->y2 = pad->y1;
		pad->_i = -1;
		rockPadEvent(pad);
	}
}

void initRockPad(RockPad* pad,
				 int x, int y, int r1, int r2) {
	pad->x1 = x;
	pad->y1 = y;
	pad->r1 = r1;
	pad->x2 = x;
	pad->y2 = y;
	pad->r2 = r2;
	pad->dir = 0;
	pad->_i = -1;
	pad->_t = timercreate();
	timerstart(pad->_t,
			   100, (int32)pad, runRockPad, TRUE);
}

void rockPadEvent(RockPad* pad) {
	pad->dir =
		getRadiam(pad->x1, pad->y1,
				  pad->x2, pad->y2);
	pad->len =
		getLineSize(pad->x1, pad->y1,
					pad->x2, pad->y2);
	//event((int)pad,pad->dir,pad->len);
}

void drawRockPad(RockPad* pad) {
	drawCir(pad->x1, pad->y1,
			pad->r1, 0x80909060);
	drawCir(pad->x2, pad->y2,
			pad->r2, 0xfff0f0f0);
}

void delRockPad(RockPad* pad) {
	timerdel(pad->_t);
}
