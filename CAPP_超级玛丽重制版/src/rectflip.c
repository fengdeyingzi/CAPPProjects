#include "rectflip.h"
#include "base.h"

RECTFLIP *new_rect()
{
 RECTFLIP *rect=mrc_malloc(sizeof(RECTFLIP));
 
 return rect;
};

//创建一个矩形裁剪块
RECTFLIP *rect_create(int x,int y,int px,int py,int pw,int ph)
{
 RECTFLIP *rect=malloc(sizeof(RECTFLIP));
 rect->x=x;
 rect->y=y;
 rect->px=px;
 rect->py=py;
 rect->pw=pw;
 rect->ph=ph;
 
 return rect;
};

RECTFLIP *rect_copy(RECTFLIP *rect)
{
 RECTFLIP *new_rect=malloc(sizeof(RECTFLIP));
 memcpy(new_rect,rect,sizeof(RECTFLIP));
 return new_rect;
};


//销毁矩形裁剪块
int rect_free(RECTFLIP *rect)
{
 if(rect==NULL)return -1;
 free(rect);
 return 0;
}

