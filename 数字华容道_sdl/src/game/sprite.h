#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../tools/res.h"
#include "../tools/draw.h"
#include "../tools/cJSON.h"

//裁剪结构体
typedef struct
{
 //裁剪
 int px;
 int py;
 int pw;
 int ph;
}Pic;

//动作结构体
typedef struct
{
 char*name;
 Pic pic[30];
 int pic_num;//数量
 int ind;//当前pic
}Act;


//精灵结构体
typedef struct
{
 char*file;//图片路径
 char*xca_file;
 char*yca_file;
 char*cca_file;
 Act act[30];//动作
 int act_num;
 int ind;//当前动作
 int w;//精灵宽度
 int h;
 int x;//相对坐标
 int y;
}Spr;

extern Spr*copySpr(Spr*spr);
extern char*getScaSprPath(Spr*spr,int xsca,int ysca);
//获取翻转的spr
Spr*getScaSpr(Spr*spr,int xsca,int ysca);
extern int32 getScaImg(Spr*spr,int xsca,int ysca);

/***精灵碰撞事件***
参数：精灵1 精灵2
返回值：TRUE碰撞 FALSE不碰撞
*****************/
//运行精灵
extern void runSpr(Spr*spr);
//绘制精灵
extern void drawSpr(Spr*spr,int x,int y);
void drawSprAngle(Spr*spr,int x2,int y2,int roat);

extern void setSprActId(Spr*spr,int id);
extern void setSprImgId(Spr*spr,int id);
//spr,w,h
extern void drawSprV9(Spr*spr,int x,int y,int iw,int ih,int vw,int vh);
//设置切片
extern void setPicJson(Pic*pic,
 cJSON*json,int len);
//设置动作
extern void setActJson(Act*act,
 cJSON*json,int len);
extern Spr*loadSprFile(char*path);

extern char*printSpr(Spr*spr);
//保存spr
extern void saveSpr(Spr*spr,char*file);

#endif

