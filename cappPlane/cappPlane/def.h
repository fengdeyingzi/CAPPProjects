#ifndef DEF_H
#define DEF_H

#include "src/api/android.h"
#include "src/api/base.h"
#include "src/api/ex_math.h"
#include "src/game/object.h"
#include "src/game/sprite.h"
#include "src/tools/draw.h"
#include "src/tools/fnt.h"
#include "src/tools/res.h"

//特殊点
#define SW SCRW
#define SH SCRH
#define SX SW / 2
#define SY SH / 2

#define DEBUG 1

//页面声明
typedef enum STA {
	MAIN = 0,
	RUN,
	OVER,
	STOP
} GSTA;

struct
{
	//字体，精灵资源
	Spr* spr[20];
	_FNT* logo;
	_FNT* menu;

	//帧率，分数，页面
	int fps;
	int kill;
	int score;
	GSTA sta;

	//定时器
	int32 time;
	int32 timer;

	//背景
	Obj* bkg;
	Obj* resume;

	//音乐
	int snd_on;
	Obj* snd;

	//主角
	int hero_sp;
	Obj* hero;

	//数据
	int data[5];
} Game;

#endif
