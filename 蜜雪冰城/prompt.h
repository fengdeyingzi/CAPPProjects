#ifndef __PROMPT_H__
#define __PROMPT_H__
#include <base.h>
#include "xcoding.h"
//绘制提示
void draw_prompt(){
    cls(255,255,255);
    char *text_title = "提示";
    char *text_info = "本游戏运行将播放声音";
    char *text_subtitle = "点击屏幕以继续";
    int32 text_w,text_h;
    textwhUTF(text_title, 1, &text_w,&text_h);
    dtextUTF(text_title, (SCRW-text_w)/2, SCRH/2, 240,20,20, 0, 1);
    textwhUTF(text_info, 1, &text_w, &text_h);
    dtextUTF(text_info, (SCRW-text_w)/2, SCRH/2+50, 240,20,20, 0, 1);

    textwhUTF(text_subtitle, 1, &text_w, &text_h);
    dtextUTF(text_subtitle, (SCRW-text_w)/2, SCRH/2+140, 20,20,20, 0, 1);
    ref(0,0,SCRW,SCRH);
}

#endif
