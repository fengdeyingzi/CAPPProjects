#include "base.h"

int32 timer;

void logoc(int data){
    drawTest("logoc assets");
}
int init(){
    printf("capp_picoc init\n");
    printf("test");
    cls(24,255,0);
    dtext("测试 from assets",0,0,255,255,255,0,1);
    ref(0,0,SCRW,SCRH);
    timer = timercreate();
    drawTest("定时器创建");
    timerstart(timer, 1000, 1, "logoc", 1);

    return 0;
}

void drawTest(char *text){
    cls(24,24,24);
    dtext(text,0,0,255,255,255,0,1);
    ref(0,0,SCRW,SCRH);
}

int event(int type,int p1,int p2){
    if(type == MS_DOWN){
        drawTest("屏幕按下");
    }
    else if(type == MS_UP){
        drawTest("屏幕释放");
    }
    return 0;
}

int pause(void){
    return 0;
}

int resume(void){
    return 0;
}

int exitApp(void){
    timerdel(timer);
    return 0;
}