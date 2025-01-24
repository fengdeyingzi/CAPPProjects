#ifndef _READSPRITE_H_
#define _READSPRITE_H_
#include <base.h>
// #include <android.h>
#include "sprite.h"



//读取底层嵌套(只做解析，无意义)
char *readflip(char *text);

//跳过头信息
static char *breakHead(char *text);

//读取rectflip层，返回读取后指针
char *readRectFlip(PICTURE *pic,char *text);

//读取picture层
char *readPicture(ACTION *ac,char *text);

//读取action层
char *readAction(int32 sp,char *text);


//读取Sprite层
int32 readSprite(char *filename,int32 bitmap);


int32 sp_read(char *filename,int32 bitmap);




#endif
