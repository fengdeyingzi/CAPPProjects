#include "./object.h"

#include "../api/base.h"
#include "../api/ex_math.h"

ObjSen* _objSen = NULL;

//创建obj
Obj* newObj(int x, int y, Spr* spr) {
	Obj* obj = malloc(sizeof(Obj));
	obj->x = x;
	obj->y = y;
	obj->spr = spr;
	obj->act = 0;

	obj->img = 0;
	obj->img_sp = 100;
	obj->_img_tim = getuptime();

	obj->sp = 0;
	obj->dir = 0;
	obj->view = TRUE;
	obj->group = 0;
	for (int i = 0; i < 5; i++) {
		obj->data[i] = 0;
	}
	obj->step = _defStep;
	obj->coll = NULL;
	obj->draw = _defDraw;
	_addObj(obj);
	return obj;
}

//设置id
void setObjGroup(Obj* obj, int group) {
	obj->group = group;
}

//添加obj
void _addObj(Obj* obj) {
	int n = 0;
	ObjSen* last = NULL;
	ObjSen* temp = _objSen;
	while (TRUE) {
		n++;
		if (temp == NULL) {
			if (last == NULL) {
				_objSen = malloc(sizeof(ObjSen));
				temp = _objSen;
				break;
			} else {
				last->next = malloc(sizeof(ObjSen));
				temp = last->next;
				break;
			}
		}
		last = temp;
		temp = temp->next;
	}
	//printf("添加第%d个obj\n",n);
	temp->obj = obj;
	temp->next = NULL;
}

//默认step
void _defStep(void* ob) {
	Obj* obj = (Obj*)ob;
	int x = obj->x + obj->sp * 100;
	int y = obj->y;
	toSpin(obj->x, obj->y,
		   obj->sp * 100, obj->sp * 100,
		   obj->dir, &x, &y);
	obj->x += (x - obj->x) / 100;
	obj->y += (y - obj->y) / 100;
	//矩形与obj碰撞
	if (!_rectCollObj(0, 0,
					  SCRW, SCRH, obj)) {
		delOneObj(obj);
	}
}

//追踪x,y，用于制作追踪导弹
//xy坐标，r每帧旋转角度
void _follObj(Obj* obj, int x, int y, int r) {
	//获取目标角度
	int radi = getRadiam(obj->x, obj->y, x, y);
	//计算差值
	int rr = obj->dir - radi;
	if (rr != 0)
		obj->dir -= rr / abs(rr) * r;
	_defStep(obj);
}

//运行obj
void _runObj(Obj* obj) {
	if (getuptime() - obj->_img_tim > obj->img_sp) {
		setSprActId(obj->spr, obj->act);
		setSprImgId(obj->spr, obj->img);
		runSpr(obj->spr);
		obj->img = obj->spr->act[obj->spr->ind].ind;
		obj->_img_tim = getuptime();
	}

	if (obj->step != NULL) {
		(*obj->step)(obj);
	}
	//obj->act=obj->spr->ind;
}

void runObj() {
	ObjSen* temp = _objSen;
	while (TRUE) {
		if (temp == NULL)
			return;
		_runObj(temp->obj);
		temp = temp->next;
	}
}

//绘制obj
void _drawObj(Obj* obj) {
	setSprActId(obj->spr, obj->act);
	setSprImgId(obj->spr, obj->img);
	drawSpr(obj->spr, obj->x, obj->y);
}

void _defDraw(void* ob) {
	
	Obj* obj = ob;
	if (obj->view)
		_drawObj(obj);
}

void drawObj() {
	ObjSen* temp = _objSen;
	while (TRUE) {
		if (temp == NULL)
			return;
		(*temp->obj->draw)(temp->obj);
		temp = temp->next;
	}
}

//检测一个obj碰撞
void collAllObj(Obj* obj) {
	ObjSen* temp = _objSen;
	while (TRUE) {
		if (temp == NULL)
			return;
		if (obj != temp->obj)
			if (obj->group !=
				temp->obj->group)
				if (_objCollObj(obj, temp->obj)) {
					(*obj->coll)(obj, temp->obj);
				}
		temp = temp->next;
	}
}

//碰撞检测,不检测碰撞组
int _objCollObj(Obj* obj1, Obj* obj2) {
	Spr* spr1 = obj1->spr;
	Spr* spr2 = obj2->spr;

	int x1 = obj1->x - spr1->x;
	int y1 = obj1->y - spr1->y;
	int x2 = obj2->x - spr2->x;
	int y2 = obj2->y - spr2->y;

	return isCollRect(x1, y1, spr1->w, spr1->h,
					  x2, y2, spr2->w, spr2->h);
}
//点与obj碰撞
int _posCollObj(int x, int y, Obj* obj) {
	Spr* spr = obj->spr;
	int x1 = obj->x - spr->x;
	int y1 = obj->y - spr->y;

	return isPointCollRect(x, y,
						   x1, y1, spr->w, spr->h);
}
//矩形与obj碰撞
int _rectCollObj(int x, int y, int w, int h, Obj* obj) {
	Spr* spr = obj->spr;
	int x1 = obj->x - spr->x;
	int y1 = obj->y - spr->y;

	return isCollRect(x, y, w, h,
					  x1, y1, spr->w, spr->h);
}
//删除一个obj
void delOneObj(Obj* obj) {
	ObjSen* last = NULL;
	ObjSen* temp = _objSen;
	while (TRUE) {
		if (temp == NULL)
			return;
		//释放
		if (temp->obj == obj) {
			_freeObj(temp->obj);
			if (last != NULL)
				last->next = temp->next;
			free(temp);
			return;
		}
		last = temp;
		temp = temp->next;
	}
}
//删除obj
void delObj() {
	ObjSen* fSen = _objSen;
	ObjSen* temp = _objSen;
	while (TRUE) {
		if (temp == NULL)
			return;
		_freeObj(temp->obj);
		fSen = temp->next;
		free(temp);
		temp = fSen;
	}
}
//释放obj
void _freeObj(Obj* obj) {
	free(obj);
}
