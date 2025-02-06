
#include "def.h"

//主角碰撞
void heroColl(void* sel, void* othe) {
	Obj* self = sel;
	Obj* other = othe;
	if (other->group != self->group) {
		if (other->group == 1) {
			delOneObj(other);

			self->data[3]++;
			if (self->data[3] > self->data[2]) {
				self->data[3] = self->data[2];
				self->spr = Game.spr[1];
			}
		}
	}
}

//主角步事件
void heroStep(void* ob) {
	Obj* bult;
	Obj* obj = (Obj*)ob;
	collAllObj(obj);

	//死亡动画
	if (obj->spr == Game.spr[1]) {
		int num = obj->spr->act[obj->act].pic_num;
		if (obj->img >= num - 1) {
			Game.sta = OVER;
			Game.resume->view = TRUE;
		}
		return;
	}

	//玩家移动
	int x = obj->x + obj->sp * 100;
	int y = obj->y;
	toSpin(obj->x, obj->y, obj->sp * 100, obj->sp * 100, obj->dir, &x, &y);
	obj->x += (x - obj->x) / 100;
	obj->y += (y - obj->y) / 100;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x > SW)
		x = SW;
	if (y > SH)
		y = SH;
	obj->x = x;
	obj->y = y;

	//发出子弹
	if (obj->spr == Game.spr[0])
		obj->data[0]++;
	if (obj->data[0] > obj->data[1]) {
		obj->data[0] = 0;

		for (int i = 0; i < obj->data[4]; i++) {
			bult =
				newObj(Game.hero->x +
						   i * 15 + 15 / 2 - obj->data[4] * 15 / 2,
					   Game.hero->y, Game.spr[2]);
			bult->group = -1;
			bult->sp = 30;
			bult->dir = -90;
		}
	}
}
