#ifndef _VIEW_H_
#define _VIEW_H_
#include "base.h"
#include "ex_math.h"
#include "graphics.h"

/*
XGUI
基础的View控件
支持设置颜色 设置点击事件

影子俱乐部网站：www.yzjlb.net
手机C论坛：bbs.yzjlb.net
手机C交流QQ群：370468001
最后修改于：2019-11-10
*/

typedef struct
{
	char *name;			  //控件名字
	int32 id;			  //控件id
	int isshow;			  //是否显示 不显示时将不会执行点击事件
	int isdown;			  //是否按下
	int x;				  //位置x
	int y;				  //位置y
	int w;				  //宽度
	int h;				  //高度
	int backgroundColor;  //背景色
	int draw_mode;		  //绘制模式 0自动绘制 1手动绘制
	int timer;			  //定时器句柄
	void *onclick;		  //点击事件回调函数
	void *tag;			  //标签
} View;

//创建控件
void *view_create(int x, int y, int w, int h) {
	View *view = (View*)malloc(sizeof(View));
	memset(view, 0, sizeof(View));
	view->x = x;
	view->y = y;
	view->w = w;
	view->h = h;
	view->isshow = 1;
	view->backgroundColor = 0x00000000;
	view->timer = timercreate();
	return view;
}

//设置id
void view_setid(View *view, int32 id) {
	view->id = id;
}

//获取id
int view_getid(View *view) {
	return view->id;
}

//绘制控件
void view_draw(View *view) {
	if (view->isshow) {
		drawRect(view->x, view->y, view->w, view->h, view->backgroundColor);
	}
}

//设置绘制模式
void view_setMode(View *view, int mode) {
	view->draw_mode = mode;
}

//显示
void view_show(View *view) {
	view->isshow = 1;
	if (view->draw_mode == 0) {
		view_draw(view);
		ref(view->x, view->y, view->w, view->h);
	}
}

//隐藏
void view_hide(View *view) {
	view->isshow = 0;
}

//判断是否显示
int view_isshow(View *view) {
	return view->isshow;
}

//设置背景色 argb格式
void view_setBackgroundColor(View *view, int color) {
	view->backgroundColor = color;
	if (view->draw_mode == 0) {
		view_draw(view);
		ref(view->x, view->y, view->w, view->h);
	}
}

//设置点击事件
void view_setonclick(View *view, void *click) {
	view->onclick = click;
}

//控件event事件
int view_event(View *view, int type, int p1, int p2) {
	if (view->isshow) {
		if (type == MS_DOWN) {
			if (isPointCollRect(p1, p2, view->x, view->y, view->w, view->h)) {
				view->isdown = 1;
			}

		} else if (type == MS_UP) {
			if (view->isdown) {
				view->isdown = 0;
				if (view->onclick != NULL) {
					timerstart(view->timer, 10, view->id, (timerCB)(view->onclick), 0);
				}
			}
		}
	}

	return 0;
}

//释放内存
void view_free(View *view) {
	if (view->timer) {
		timerstop(view->timer);
		timerdel(view->timer);
		view->timer = 0;
	}
	free(view);
}

#endif
