#ifndef _ACTION_H_
#define _ACTION_H_

#include "picture.h"

//动作 包含多帧画面
typedef struct
{
 PICTURE *picture[30]; //画面
 char *name; //动作名称
 int offset; //当前所处的帧
 int size;//帧数
 int id;//id
 int global; //引用数 除当前动作以为其余的引用数量，释放动作时，若引用数归0，那么释放本身
 int mode; //动画播放模式 0普通模式 1循环模式
// int w; //宽度
// int h; //高度(无太大意义)
// int rotate; //旋转
// int alpha; //透明度
} ACTION;

//创建一张空白动作
ACTION *ac_new();

/*
//创建一个动作 参数：id 所有帧 帧数 
ACTION *ac_create(int id, PICTURE *pic, int size)
{
 ACTION *ac=malloc(sizeof(ACTION));
 memset(ac,0,sizeof(ACTION));
 ac->picture=pic;
 ac->size=size;
 
 return ac;
};
*/



//给动作添加一帧画面
int ac_add(ACTION *action, PICTURE *picture);

//设置动作id
int ac_setId(ACTION *ac,int id);
//设置动作名称
int ac_setName(ACTION *ac,char *name);
//设置播放模式
int ac_setPlayMode(ACTION *ac,int mode);
//绘制动作(自动跳转到下一帧)
void ac_draw(long int bitmap,ACTION *ac,int x,int y);

void ac_run(ACTION *ac);


ACTION *ac_copy(ACTION *ac);

//销毁动作
int ac_free(ACTION *ac);



#endif



