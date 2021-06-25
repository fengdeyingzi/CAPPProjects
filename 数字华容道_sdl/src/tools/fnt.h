#ifndef _FNT_H_
#define _FNT_H_

#include "../api/base.h"
#include "../api/graphics.h"
#include "../api/android.h"
#include "../api/exb.h"

typedef struct
{
 int id;//un编号
 int x;//字体在图片上的x坐标
 int y;//字体在图片上的y坐标
 int width;//字宽
 int height;//字高
 int xoffset;
 int yoffset;
}_FONT;

typedef struct
{
 int bitmap;//图片
 int lineHeight;//行高
 int base;//字体大小
 int scaleW;//图片宽度
 int scaleH;//图片高度
 _FONT**font;
 int size;
 
}_FNT;


//创建结构体，加载字体文件
//参数：图片名 fnt文件名
extern void*fnt_create(char*imgname,char*fntname);


//显示单行文字
extern void fnt_drawline(_FNT*fnt,char*text,int x,int y);

//显示多行文字
extern void fnt_drawrect(_FNT*fnt,char*text,int x,int y,int w,int h);

//显示单个文字 参数：文字编号
extern void fnt_draw(_FNT*fnt,int id,int x,int y);

//获取指定文字的宽度
extern int fnt_getW(_FNT*fnt,int id);

extern int  fnt_getLineW(_FNT*fnt,char*text);

//检测文字是否在字体中存在 
//返回值：TRUE/FALSE
extern int fnt_check(_FNT*fnt,int id);

//释放字体
extern int fnt_free(_FNT*fnt);

#endif
