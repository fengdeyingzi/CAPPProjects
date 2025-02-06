
#include "def.h"

//敌机类型
typedef enum eneType {
	eOne = 3,
	eTwo,
	eThree
} EneType;

/*
data[0]计数
data[1]攻击延时
data[2]血量
data[3]血量计数
*/

//绘制敌机血条
void enemyDraw(void* ob) {
	printf("enemyDraw");
	Obj* obj = ob;
	_drawObj(obj);

	int xue = 360 -
			  360 * obj->data[3] / obj->data[2];

	if (xue != 0) {
		drawCirCir(obj->x, obj->y,
				   10, 15, 0xffff0000, 180, 360);
		drawCirCir(obj->x, obj->y,
				   10, 15, 0xff00ff00, 180, xue);
	}
	printf("enemydraw success...");
}

//敌人碰撞
void enemyColl(void* sel, void* othe) {
	Obj* self = sel;
	Obj* other = othe;

	//清除子弹
	if (other->group == -1) {
		delOneObj(other);

		self->data[3]++;
		//血量一半，敌机受损
		if (self->data[3] > self->data[2] / 2) {
			self->act = 1;
		}
		//血量清零，敌机死亡
		if (self->data[3] >= self->data[2]) {
			self->data[3] =
				self->data[2];
			self->act = 2;
		}
	}
}

//敌人步事件
void enemyStep(void* ob) {
	Obj* bult;
	Obj* obj = (Obj*)ob;

	//死亡动画
	if (obj->act == 2) {
		int num = obj->spr->act[obj->act].pic_num;
		if (obj->img >= num - 1) {
			Game.kill++;
			Game.score += 10;
			delOneObj(obj);
		}
		return;
	}

	//检测碰撞
	collAllObj(obj);

	//敌机移动
	if (obj->group != eOne)
		_defStep(obj);
	else
		_follObj(obj, Game.hero->x, Game.hero->y, 5);

	//发出子弹
	obj->data[0]++;
	if (obj->data[0] > obj->data[1]) {
		obj->data[0] = 0;
		switch (obj->group) {
		//敌机1，普通攻击
		case eOne:
			bult =
				newObj(obj->x, obj->y, Game.spr[2]);
			bult->group = 1;
			bult->sp = 15;
			bult->act = 1;
			bult->dir = 90;
			break;

		//敌机2，180度弹幕
		case eTwo:
			for (int i = 0; i < 9; i++) {
				bult =
					newObj(obj->x,
						   obj->y, Game.spr[2]);
				bult->group = 1;
				bult->sp = 15;
				bult->act = 1;
				bult->dir = i * 20;
			}
			break;

		//敌机3，360度弹幕
		case eThree:
			for (int i = 0; i < 36; i++) {
				bult =
					newObj(obj->x,
						   obj->y, Game.spr[2]);
				bult->group = 1;
				bult->sp = 15;
				bult->act = 1;
				bult->dir = i * 10;
			}
			break;

		default:

			break;
		}
	}
}

//创建敌人
void createEnemy(int x, int y, EneType type, int dir) {
	Obj* ene =
		newObj(x, y, Game.spr[type]);
	switch (type) {
	//敌机1，攻速10/s，血量1
	case eOne:
		ene->data[1] = Game.fps / 10 * 5;
		ene->data[2] = 1000;
		ene->sp = 30;
		break;

	//敌机2，攻速1/s，血量10
	case eTwo:
		ene->data[1] = Game.fps / 10 * 10;
		ene->data[2] = 10;
		ene->sp = 5;
		break;

	//敌机3，攻速1/2s，血量20
	case eThree:
		ene->data[1] = Game.fps / 10 * 20;
		ene->data[2] = 20;
		ene->sp = 2;
		break;
	default:

		break;
	}

	ene->step = enemyStep;
	ene->coll = enemyColl;
	ene->draw = enemyDraw;
	ene->group = type;
	ene->dir = dir;
}

//敌机小队
void newEnemyList(int type) {
	switch (type) {
	//侦查小队
	case 0:
		for (int i = 0; i < 8; i++) {
			createEnemy(i * SCRW / 8 +
							SCRW / 8 / 2,
						100, 3, 90);
		}
		break;

	//巡逻战队
	case 1:
		for (int i = 0; i < 5; i++) {
			createEnemy(i * SCRW / 5 + SCRW / 20 - SCRW / 2,
						i * 100 - 200, 4, 60);
		}
		break;

	//boos战争
	case 2:
		newEnemyList(0);
		for (int i = 0; i < 3; i++) {
			createEnemy(i * SCRW / 3 +
							SCRW / 3 / 2,
						0, 5, 90);
		}
		break;
	}
}
