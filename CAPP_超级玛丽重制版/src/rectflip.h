
#ifndef _RECTFLIP_H_
#define _RECTFLIP_H_


typedef struct
{
 int x;//显示在画面上的相对位置
 int y;
 int px;//bitmap裁剪区域
 int py;
 int pw;
 int ph;
 
 
} RECTFLIP;

RECTFLIP *new_rect();

//创建一个矩形裁剪块
RECTFLIP *rect_create(int x,int y,int px,int py,int pw,int ph);

RECTFLIP *rect_copy(RECTFLIP *rect);


//销毁矩形裁剪块
int rect_free(RECTFLIP *rect);






#endif
