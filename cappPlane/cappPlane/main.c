
#include "./def.h"

//主角碰撞
extern void heroColl(void* self, void* other);
//主角步事件
extern void heroStep(void* ob);
//创建敌人
extern void newEnemyList(int type);

//绘制logo
void drawLogo() {
	
	fnt_drawline(Game.logo, "飞机大战", 150, 200);
	fnt_drawline(Game.logo, "飞机大战", 160, 210);
	fnt_drawline(Game.menu, "      powered by capp ", 280, SH - 100);
	
}

void drawBkg(void* ob) {
	Obj* obj = ob;
	drawSpr(obj->spr, obj->x, obj->y - 1400);
	drawSpr(obj->spr, obj->x, obj->y);
	drawSpr(obj->spr, obj->x, obj->y + 1400);
}

void drawGameUi() {
	char text[20];
	int xue = SCRW / 4 - SCRW / 4 *
							 Game.hero->data[3] /
							 Game.hero->data[2];

	drawRect(0, 0, SCRW, 200, 0x80ff8000);
	drawRect(5, 5, SCRW - 10, 190, 0x80805060);

	//玩家
	sprintf(text, "%d", Game.score);
	fnt_drawline(Game.menu, "SCORE", 160, 50);
	fnt_drawline(Game.menu, text, 360, 50);

	sprintf(text, "%d", Game.kill);
	fnt_drawline(Game.menu, "Kill", 590, 50);
	fnt_drawline(Game.menu, text, 690, 50);

	fnt_drawline(Game.menu, "LIFE", 590, 120);

	fnt_drawline(Game.menu, "HP", 160, 120);

	drawSpr(Game.hero->spr, 80, 100);
	drawRect(300, 130, SCRW / 4, 20, 0x80ff0000);
	drawRect(300, 130, xue, 20, 0x8000ff00);
}

//运行游戏
void runGame(int32 data) {
	
	cls(0xff, 0xff, 0xff);

	//背景运动
	Game.bkg->y += 10;
	if (Game.bkg->y > 1400)
		Game.bkg->y = 0;

	//obj逻辑
	Game.time++;
	if (Game.time > 700)
		Game.time = 0;
	if (Game.sta == RUN) {
		if (Game.time == 100)
			newEnemyList(0);

		if (Game.time == 300)
			newEnemyList(1);

		if (Game.time == 500)
			newEnemyList(2);

		runObj();
	}

	//绘制所有
	drawObj();

	//主页面
	if (Game.sta == MAIN)
		drawLogo();

	//游戏暂停
	if (Game.sta == STOP)
		drawGameUi();

	//游戏结束
	if (Game.sta == OVER)
		drawLogo();

	//游戏运行
	if (Game.sta == RUN)
		drawGameUi();

	Game.hero->data[4] =
		Game.score / 100 + 1;
	if (Game.hero->data[4] > 5)
		Game.hero->data[4] = 5;
	ref(0, 0, SW, SH);

}


//初始化
void initGameRes() {
	//载入精灵
	Game.spr[0] = (Spr*)
					  getRes("spr/hero.spr", tSpr)
						  ->id;
	Game.spr[1] = (Spr*)
					  getRes("spr/hero_death.spr", tSpr)
						  ->id;
	Game.spr[2] = (Spr*)
					  getRes("spr/bullet.spr", tSpr)
						  ->id;
	Game.spr[3] = (Spr*)
					  getRes("spr/enemy1.spr", tSpr)
						  ->id;
	Game.spr[4] = (Spr*)
					  getRes("spr/enemy2.spr", tSpr)
						  ->id;
	Game.spr[5] = (Spr*)
					  getRes("spr/enemy3.spr", tSpr)
						  ->id;
	Game.spr[6] = (Spr*)
					  getRes("spr/bkg.spr", tSpr)
						  ->id;
	Game.spr[7] = (Spr*)
					  getRes("spr/bomb.spr", tSpr)
						  ->id;

	Game.spr[8] = (Spr*)
					  getRes("spr/life.spr", tSpr)
						  ->id;
	Game.spr[9] = (Spr*)
					  getRes("spr/logo.spr", tSpr)
						  ->id;
	Game.spr[10] = (Spr*)
					   getRes("spr/pause.spr", tSpr)
						   ->id;
	Game.spr[11] = (Spr*)
					   getRes("spr/resume.spr", tSpr)
						   ->id;
	Game.spr[12] = (Spr*)
					   getRes("spr/supply.spr", tSpr)
						   ->id;

	//载入字体
	Game.logo = (_FNT*)
					getRes("font/logo.fnt", tFnt)
						->id;
	Game.menu = (_FNT*)
					getRes("font/menu.fnt", tFnt)
						->id;

	//定时器
	Game.timer =
		getRes("Game.timer", tTim)->id;
}

void initGame() {
	//背景
	Game.bkg = newObj(0, 0, Game.spr[6]);
	Game.bkg->draw = drawBkg;

	//开始按钮
	Game.resume = newObj(SW / 2, SH / 2 + 300, Game.spr[11]);

	//主角数据
	Game.hero_sp = 15;
	Game.hero = newObj(SW / 2, SH / 2 - 200, Game.spr[0]);
	Game.hero->step = heroStep;
	Game.hero->coll = heroColl;

	//游戏数据
	Game.fps = 45;
	Game.sta = MAIN;

	//定时器
	timerstart(Game.timer,
			   1000 / Game.fps, 0, runGame, TRUE);
	Game.time = getuptime();
}

void startGame() {
	Game.sta = RUN;
	Game.score = 0;
	Game.kill = 0;

	Game.hero->data[0] = 0;
	Game.hero->data[1] = 2;
	Game.hero->data[2] = 50;
	Game.hero->data[3] = 0;
	Game.hero->data[4] = 1;
	Game.hero->spr = Game.spr[0];
}

int init() {
	printf("init game\r\n");
	cls(0x00, 0xff, 0xff);
	printf("cls");
	setscrsize(960, 960 * SH / SW);
	printf("setscrsize");
	clearView();
	printf("clear view..\r\n");
	initGameRes();
	printf("load res success..\r\n");
	initGame();
	printf("ref ....");
	ref(0, 0, SW, SH);
	printf("ref success ...");
	return 0;
}

int event(int type, int p1, int p2) {
	//开始游戏
	//if(Game.sta==MAIN)
	{
		if (type == MS_DOWN) {
			if (_posCollObj(p1, p2, Game.resume)) {
				Game.resume->act = 1;
			}
		}

		if (type == MS_UP) {
			if (_posCollObj(p1, p2, Game.resume)) {
				Game.resume->act = 0;
				Game.resume->view = FALSE;
				startGame();
			}
		}
	}

	//主角移动
	if (Game.sta == RUN) {
		if (type == MS_DOWN) {
			Game.data[0] = p1;
			Game.data[1] = p2;
		}
		if (type == MS_MOVE) {
			Game.hero->x +=
				p1 - Game.data[0];
			Game.hero->y +=
				p2 - Game.data[1];
			Game.data[0] = p1;
			Game.data[1] = p2;
		}
	}

	if (KY_UP == type) {
		switch (p1) {
		case _BACK:
			exit();
			break;
		case _MENU:
			break;
		}
	}

	return 0;
}

int exitApp() {
	delObj();
	freeRes();
	return 0;
}

int pause() {
	Game.sta = STOP;
	Game.resume->view = TRUE;
	return 0;
}

int resume() {
	initGameRes();
	return 0;
}

