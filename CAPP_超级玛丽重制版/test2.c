

#include "base.h"

extern int exitApp();

int32 picoc_init() {
    printf("picoc_init");
    cls(255, 255, 255);
    ref(0, 0, SCRW, SCRH);
    init();
    return 0;
}

int32 picoc_event(int32 type, int32 p1, int32 p2) {
    event(type, p1, p2);
    return 0;
}

int32 picoc_pause() {
    pause();
    return 0;
}

int32 picoc_resume() {
    resume();
    return 0;
}

int32 picoc_exitApp() {
    printf("exitapp");
    exitApp();
    return 0;
}

int32 so_init() {
    printf("so init");
    cls(255, 255, 0);
    ref(0, 0, SCRW, SCRH);
    return 0;
}

int32 so_event(int32 type, int32 p1, int32 p2) {

    return 0;
}

int32 so_pause() {
    return 0;
}

int32 so_resume() {
    return 0;
}

int32 so_exitApp() {
    return 0;
}


//int init(){
//
//    return 0;
//}
//
//int event(int type,int p1,int p2){
//
//    return 0;
//}
//
//
//int pause(){
//    return 0;
//}
//
//
//
//int resume(){
//
//    return 0;
//}
//
//int exitApp(){
//
//    return 0;
//}


