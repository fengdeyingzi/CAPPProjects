#include <android.h>
#include <base.h>
#include <pthread.h>
/*
本项目仅支持手机C 4.8及以上版本
风的影子
*/
pthread_t thread_draw;
int isRun;

int client_entry() {
	while (isRun) {
		sleep(1000);
		int color = rand() % 255;
		cls(color, color, color);
		ref(0, 0, SCRW, SCRH);
	}

	return 0;
}

void drawUI(char *text) {
	cls(240, 240, 240);
	dtext(text, 10, 10, 20, 20, 20, 0, 1);
	ref(0, 0, SCRW, SCRH);
}

int init() {
	thread_draw = 1;
	isRun = 1;
	pthread_create(&thread_draw, NULL, (void *)client_entry, (void *)NULL);
	cls(200, 200, 200);
	dtext("start", 10, 10, 20, 20, 20, 0, 1);
	ref(0, 0, SCRW, SCRH);
	return 0;
}

int event(int type, int p1, int p2) {
	if (type == KY_UP) {
		if (p1 == _BACK) {
			drawUI("exit");
			isRun = 0;
			pthread_join(thread_draw, NULL);
			exit();
		}
	}
	if (type == MS_DOWN) {
		drawUI("down");
	}
	return 0;
}

int pause() {
	return 0;
}

int resume() {
	return 0;
}

int exitApp() {
	return 0;
}