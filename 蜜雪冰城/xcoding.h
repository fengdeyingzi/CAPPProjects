#ifndef __XCODING_H__
#define __XCODING_H__

#include <base.h>
#include <exb.h>
#include <android.h>

//显示toast
void toastUTF(char *text){
    char *temp = ex_coding(text, strlen(text), "UTF-8", "GBK");
    toast(temp,0);
    free(temp);
}

//获取文字宽高
void textwhUTF(char *text, int font, int32* w,int32 *h){
    char *temp = ex_coding(text,strlen(text), "UTF-8", "GBK");
    textwh(temp, 0, font,w,h);
    free(temp);
}

//绘制单行文字
void dtextUTF(char *text, int x,int y,int r,int g,int b, int is_unicode, int font){
    char *temp = NULL;
    if(is_unicode){
        dtext(text,x,y,r,g,b,is_unicode,font);
    }else{
        temp = ex_coding(text, strlen(text), "UTF-8", "GBK");
        dtext(temp, x,y,r,g,b,is_unicode,font);
        free(temp);
    }
}

#endif
