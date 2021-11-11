#ifndef __GAME_H__
#define __GAME_H__
#include "ImageButton.h"
#include "View.h"
#include "base.h"
#include "graphics.h"
#include "xcoding.h"
#define SHOW_WIDTH 120
enum {
	ACTION_HELLO = 1,
	ACTION_HOLD,
	ACTION_LEFT,
	ACTION_RIGHT,
	ACTION_YES
};
int32 timer_game = 0;
int32 time_start;  //开始时间
int32 time_size;   //限制时长
int action_cur;	   //当前要做的动作
int action_mine;   //我的动作
int action_size;   //动作次数
int hp;			   //生命
int game_type;	   //游戏状态
ImageButton *btn_hello, *btn_holo, *btn_left, *btn_right, *btn_yes;
ImageButton *img_ex, *img_mine;
ImageButton *btn_restart, *btn_home;

void game_click(long id) {
	// toastUTF("点击");
	printf("%s：%d\n", "点击", id);
	if (id == 1) {
		img_mine = btn_hello;
		action_mine = ACTION_HELLO;
	} else if (id == 2) {
		img_mine = btn_holo;
		action_mine = ACTION_HOLD;
	} else if (id == 3) {
		img_mine = btn_left;
		action_mine = ACTION_LEFT;
	} else if (id == 4) {
		img_mine = btn_right;
		action_mine = ACTION_RIGHT;
	} else if (id == 5) {
		img_mine = btn_yes;
		action_mine = ACTION_YES;
	} else if (id == 20) {
		time_start = getuptime();
		time_size = 5 * 1000;
		action_cur = ACTION_HELLO;
		action_mine = 0;
		action_size = 0;
		hp = 100;
		game_type = 1;
        soundloadfile(1, "assets://game_music.mp3");
		if(isPlaySound)
	    soundplay(1,0, 1);
	} else if (id == 21) {
		game_end();
		updateUI(2);
	}
}

//重新生成一个动作
void game_action_re() {
	sand(getuptime());
	action_cur = rand() % 5 + 1;
	switch (action_cur) {
	case 1:
		img_ex = btn_hello;
		break;
	case 2:
		img_ex = btn_holo;
		break;
	case 3:
		img_ex = btn_left;
		break;
	case 4:
		img_ex = btn_right;
		break;
	case 5:
		img_ex = btn_yes;
	}
	img_mine = NULL;
	action_mine = 0;
}

void game_logoc(long data) {
	cls(255, 255, 255);
	int32 font_w, font_h;
	//显示剩余时间
	char temp[300];
	int32 timesize = time_size - (getuptime() - time_start);
	//如果剩余时间为负 就刷新判断
	if (timesize <= 0) {
		time_start = getuptime();
		time_size -= 50;
		if (time_size < 1000) {
			time_size = 1000;
		}
		if (action_cur == action_mine) {  //成功
			action_size++;
			if(action_size == 2){
				time_size-= 1000;
			}else if(action_size == 3){
				time_size-= 1000;
			}else if(action_size == 10){
				time_size-= 500;
			}else if(action_size == 20){
				time_size-= 500;
			}
		} else {  //失败
			hp -= 30;
			// 播放失败音效
			if (hp <= 0) {
				game_type = -1;	 //失败
                soundstop(1);
			}
		}
		game_action_re();
	}
	if (game_type == 1) {
		//显示当前图片
		if (img_ex != NULL) {
			drawBitmapEx(img_ex->bitmap, SCRW / 2 - 200 - SHOW_WIDTH, SCRH / 2 - 150, SHOW_WIDTH, SHOW_WIDTH, 0, 0, 279, 279);
		}
		//显示我的图片 如果没有不显示
		if (img_mine != NULL) {
			drawBitmapEx(img_mine->bitmap, SCRW / 2 + 200, SCRH / 2 - 150, SHOW_WIDTH, SHOW_WIDTH, 0, 0, 279, 279);
		}

		//显示按钮
		img_draw(btn_hello);
		img_draw(btn_holo);
		img_draw(btn_left);
		img_draw(btn_right);
		img_draw(btn_yes);
		drawRect(0, SCRH / 2 + 50, SCRW * timesize / time_size, 30, 0xfff05098);
		sprintf(temp, "剩余%d毫秒", timesize);
		dtextUTF(temp, 30, SCRH / 2 + 120, 20, 20, 20, 0, 1);
		sprintf(temp, "生命：%02d 分数：%d", hp, action_size*10);
		dtextUTF(temp, 20, 60, 20, 20, 20, 0, 1);
	} else if (game_type == -1) {
		textwhUTF("影", 1, &font_w, &font_h);
		sprintf(temp, "分数：%d", action_size*10);
		dtextUTF(temp, SCRW/2 - font_w*6, SCRH/2+100, 240, 45, 0x9a);
		dtextUTF("游戏失败", SCRW / 2 - font_w * 2, SCRH / 2, 20, 20, 20, 0, 1);
		img_show(btn_restart);
		img_show(btn_home);
	}
	img_draw(btn_restart);
	img_draw(btn_home);

	ref(0, 0, SCRW, SCRH);
}
//游戏启动
void game_start() {
	btn_hello = img_create("assets://action_hello.png", 20, SCRH / 2 + 200, SHOW_WIDTH, SHOW_WIDTH);
	btn_holo = img_create("assets://action_hold.png", 20 + (20 + SHOW_WIDTH) * 1, SCRH / 2 + 200, SHOW_WIDTH, SHOW_WIDTH);
	btn_left = img_create("assets://action_left.png", 20 + (20 + SHOW_WIDTH) * 2, SCRH / 2 + 200, SHOW_WIDTH, SHOW_WIDTH);
	btn_right = img_create("assets://action_right.png", 20 + (20 + SHOW_WIDTH) * 3, SCRH / 2 + 200, SHOW_WIDTH, SHOW_WIDTH);
	btn_yes = img_create("assets://action_yes.png", 20 + (20 + SHOW_WIDTH) * 4, SCRH / 2 + 200, SHOW_WIDTH, SHOW_WIDTH);
	btn_restart = img_create("assets://btn_restart.png", SCRW / 2 - 100 - 240, SCRH / 2 + 360, 240, 180);
	btn_home = img_create("assets://btn_home.png", SCRW / 2 + 100, SCRH / 2 + 360, 240, 180);
	img_setmode(btn_restart, 1);
	img_setmode(btn_home, 1);

	img_setid(btn_hello, 1);
	img_setid(btn_holo, 2);
	img_setid(btn_left, 3);
	img_setid(btn_right, 4);
	img_setid(btn_yes, 5);
	img_setid(btn_restart, 20);
	img_setid(btn_home, 21);
	img_setmode(btn_hello, 2);
	img_setmode(btn_holo, 2);
	img_setmode(btn_left, 2);
	img_setmode(btn_right, 2);
	img_setmode(btn_yes, 2);
	img_setonclick(btn_hello, "game_click");
	img_setonclick(btn_holo, "game_click");
	img_setonclick(btn_left, "game_click");
	img_setonclick(btn_right, "game_click");
	img_setonclick(btn_yes, "game_click");
	img_setonclick(btn_restart, "game_click");
	img_setonclick(btn_home, "game_click");
	img_hide(btn_restart);
	img_hide(btn_home);
	timer_game = timercreate();
	timerstart(timer_game, 33, 1, "game_logoc", 1);
	time_start = getuptime();
	time_size = 5 * 1000;
	action_cur = ACTION_HELLO;
	action_mine = 0;
	action_size = 0;
	hp = 100;
	game_type = 1;
    soundloadfile(1, "assets://game_music.mp3");
	if(isPlaySound)
	soundplay(1,0, 1);
	game_action_re();
}
//游戏event事件
int game_event(int type, int p1, int p2) {
	img_event(btn_restart, type, p1, p2);
	img_event(btn_home, type, p1, p2);
	img_event(btn_hello, type, p1, p2);
	img_event(btn_holo, type, p1, p2);
	img_event(btn_left, type, p1, p2);
	img_event(btn_right, type, p1, p2);
	img_event(btn_yes, type, p1, p2);
	return 0;
}

//游戏停止
void game_end() {
    soundstop(1);
	if (timer_game) {
		timerdel(timer_game);
		timer_game = 0;
		img_free(btn_hello);
		img_free(btn_holo);
		img_free(btn_left);
		img_free(btn_right);
		img_free(btn_yes);

		img_free(btn_restart);
		img_free(btn_home);
	}
}

#endif
