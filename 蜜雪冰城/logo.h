#ifndef __LOGO_H__
#define __LOGO_H__

#include <base.h>
#include <android.h>
#include "View.h"
#include "ImageButton.h"

ImageButton *img_logo;

//初始化logo
void logo_init(){
    img_logo = img_create("assets://logo.png", (SCRW-320)/2, (SCRH-320)/2, 320,320);
    img_setmode(img_logo,0);
}

void logo_draw(){
    cls(255,255,255);
    img_draw(img_logo);
}

//释放logo
void logo_free(){
    if(img_logo!=NULL){
        img_free(img_logo);
        img_logo = NULL;
    }
}

#endif
