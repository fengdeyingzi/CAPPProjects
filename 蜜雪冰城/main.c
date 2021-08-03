//加载系统头文件base.h
#include <base.h>

#include "ImageButton.h"
#include "View.h"
#include "android.h"
#include "xcoding.h"
#include "logo.h"
#include "prompt.h"
#include "game.h"
#include "sound.h"

int win_type = 0; //当前界面 0 logo 1 提示页 2 主页 3 游戏页
int32 timer_logo = 0;
//是否播放声音
int isPlaySound;

void click_ok(long id) {
	printf("%s：%d\n", "点击", id);
	if (id == 1) {
		updateUI(3);
	} else if (id == 10) { //禁止播放
		img_hide(btn_sound);
		img_show(btn_soundoff);
		isPlaySound = 0;
		updateMusic();
	} else if (id == 11) { //播放
		img_hide(btn_soundoff);
		img_show(btn_sound);
		isPlaySound = 1;
		updateMusic();
	}
	//  toastUTF("按钮点击",0);
	draw_main();
	//printf("点\n");
	// return 0;
}

void updateMusic(){
	if(isPlaySound){
		if(win_type == 2){
		soundloadfile(1, "assets://background.mid");
		soundplay(1,0, 1);
		}
	}else{
		soundstop(1);
		soundstop(2);
	}
}

ImageButton *btn_start;
ImageButton *btn_sound;
ImageButton *btn_soundoff;
//背景
ImageButton *img_background;

//更新界面
void updateUI(int type){
    win_type = type;
    view_hide((void*)btn_start);
    view_hide((void*)btn_sound);
    view_hide((void*)btn_soundoff);
    view_hide((void*)img_background);
	soundstop(1);
	soundstop(2);

    switch (win_type)
    {
    case 0:
	    
        logo_draw();
        break;
    case 1:
	    
        break;
    case 2:
	    soundloadfile(1, "assets://background.mid");
		soundplay(1,0, 1);
		view_show((void*)btn_start);
		if(isPlaySound){
			view_show((void*)btn_sound);
		}else{
			view_show((void*)btn_soundoff);
		}
		
		view_show((void*)img_background);
		
        break;
    case 3: //游戏开始
	    img_hide(btn_start);
		img_hide(btn_sound);
		img_hide(btn_soundoff);
		img_hide(img_background);
	    game_start();
        break;
    default:
        break;
    }
	draw_main();
}

//绘制画面
void draw_main() {
	cls(121, 189, 204);
    switch (win_type)
    {
    case 0:
        logo_draw();
        break;
    case 1:
    draw_prompt();
    break;
    case 2:
    //绘制按钮
	img_draw(img_background);
	img_draw(btn_start);
	img_draw(btn_sound);
	img_draw(btn_soundoff);
    break;
    case 3:

    break;
    default:
        break;
    }
    
	
	//刷新屏幕
	ref(0, 0, SCRW, SCRH);
}

void logoc_logo(int data){
	updateUI(1);
	
}

//入口函数，程序启动时开始执行
int init() {
	int DECVIDE_WIDTH = 0;
	int DECVIDE_HEIGHT = 0;
	isPlaySound = 1;
	soundinit(1);
	soundinit(2);
	if (SCRW < SCRH) {
		DECVIDE_WIDTH = 720;
		DECVIDE_HEIGHT = 720 * SCRH / SCRW;
	} else {
		DECVIDE_WIDTH = 720;
		DECVIDE_HEIGHT = 720 * SCRW / SCRH;
	}

	setscrsize(DECVIDE_WIDTH, DECVIDE_HEIGHT);
    timer_logo = timercreate();
    timerstart(timer_logo, 2500, 1, "logoc_logo", 0);
    
    logo_init();
	//创建按钮
	btn_start = img_create("assets://btn_start.png", (SCRW - 240) / 2, SCRH / 2 + 350, 240, 120);
	btn_sound = img_create("assets://sound_open.png", SCRW - 120 - 80, 120, 120, 120);
	btn_soundoff = img_create("assets://sound_off.png", SCRW - 120 - 80, 120, 120, 120);
	img_background = img_create("assets://background.png", 0, 0, SCRW, SCRH);
	// img_setmode(btn_start,1);
	img_setmode(btn_sound, 1);
	img_setmode(btn_soundoff, 1);
	img_setmode(img_background, 1);
	//设置按钮点击事件
	img_setonclick(btn_start, "click_ok");
	img_setonclick(btn_sound, "click_ok");
	img_setonclick(btn_soundoff, "click_ok");
	//设置按钮id
	img_setid(btn_start, 1);
	img_setid(btn_sound, 10);
	img_setid(btn_soundoff, 11);
	//隐藏按钮2
	img_hide(btn_soundoff);
	updateUI(0);
	draw_main();
	return 0;
}

void exit_free() {
    logo_free();
	img_free(btn_start);
	img_free(btn_sound);
	img_free(img_background);
	img_free(btn_soundoff);
	game_end();
	soundstop(1);
	soundstop(2);
	soundclose(1);
	soundclose(2);
    timerdel(timer_logo);
}

//event函数，接收消息事件
int event(int type, int p1, int p2) {
	//监听event事件
	img_event(btn_start, type, p1, p2);
	img_event(btn_sound, type, p1, p2);
	img_event(btn_soundoff, type, p1, p2);
    switch (win_type)
    {
    case 0:
        
        break;
    case 1:
    if(type == MS_UP){
        updateUI(2);
    }
    break;
	case 3: //游戏开始
game_event(type,p1,p2);
    default:
        break;
    }
	if (KY_UP == type) {
		switch (p1) {
		case _BACK:
			exit_free();
			exit();
			break;
		case _MENU:
			break;
		}
	}

	return 0;
}

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause() {
	return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume() {
	return 0;
}

int exitApp() {
	return 0;
}
