
#ifndef _TILED_H_
#define _TILED_H_

#include "base.h"
#include "sprite_write.h"

extern char *readtiledToSprite(char *text);


//读取文本数据
char *readText(char *filename);


//写入文本数据
int writeText(char *filename, void *data, int len);

//将tmx文件转换为精灵文件
int readTiledToSpriteFile(char *tilefilename, char *spritefilename);
//将tmx地图转换为精灵
char *readtiledToSprite(char *text);


//读取tmx地图并转换为数组
void printf_tmx(char *filename);


//获取tmx地图宽度 高度 图块宽度 高度
//返回地图data，需要手动释放内存
int32 *readtiledInfo(char *text, int *width, int *height, int *item_width, int *item_height);


int32 *readTextInfo(char *text, int *width, int *height, int *item_width, int *item_height);


#endif



