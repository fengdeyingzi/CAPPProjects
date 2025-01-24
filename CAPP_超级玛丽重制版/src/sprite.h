
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "base.h"
#include "graphics.h"
//#include "graphics.h"
//#include "ex_math.h"
#include "camera.h"
#include "action.h"

/*
精灵
做游戏专用
风的影子 编写
*/


typedef struct {
    int x;
    int y;
    int w;
    int h;
} _RECT;


//精灵 包含多个动作
typedef struct {
    int x; //屏幕坐标
    int y;
    int w; //精灵宽度
    int h;
    int32 bitmap;//图片资源
    ACTION *action[60];//动作数组
    int cx;  //显示中心点
    int cy;
    int id; //精灵id
    int offset;//当前所处的动作
    int size; //动作的数量
    int gravity; //显示方式
    int isdraw; //显示/隐藏

} SPRITE;
enum GRAVITY {
    _center,
    _left,
    _right,
    _top,
    _bottom
};

extern int32 sp_new();

/*
//加载精灵文件，参数：Sprite文件，bitmap
SPRITE *sp_read(char *filename, int bitmap)
{
 SPRITE *sp=sp_new();
 
 
 return sp;
};

*/




//给精灵添加动作
int sp_add(long int id, ACTION *action);
//通过图片创建精灵
SPRITE *sp_bitmapcreate(long int bitmap, int width, int height);

//新建一个精灵
int32 sp_new();
//创建精灵
SPRITE *sp_create(ACTION *action, int size);

//通过加载一张图片完成精灵创建
//参数：精灵id，精灵宽度 高度
/*
int sp_createsprite(char *filename,int width,int height)
{
 int bitmap=readBitmapFromAssets(filename);
 int temp;
 int x,y;
 
 
 SPRITE *sprite=sp_new();
 sprite->bitmap=bitmap;
 ACTION *action = malloc(sizeof(ACTION));
 sprite->action[0]=action;
// action->rotate=0;
// action->alpha=255;
// action->type=0;
// action->w=width;
// action->h=height;
 sprite->offset=0;
 sprite->size=1;
 
 BITMAPINFO picinfo;
bitmapGetInfo(bitmap,&picinfo);
int size=0;
//如果裁剪图片和当前图片尺寸相等，就返回原图片

if(width==picinfo.width && height==picinfo.height)
{
 action->size=1;
 action->bitmap[size]=bitmap;
 return (int)sprite;
}
 for(y=0;y<picinfo.height;y+=height)
 for( x=0;x<picinfo.width;x+=width)
 {
  temp=clipBitmap(bitmap, x,y,width,height);
 // printf(" 裁剪图片 %d %d %d %d \n",x,y,width,height);
  action->bitmap[size]=temp;
  size++;
 }
 
// action->size=1;
// action->bitmap[size]=bitmap;
 bitmapFree(bitmap);
 return (int)sprite;
}
*/

//输出rectflip(纵向计算rectflip坐标)
/*
void printf_rectf(int x,int y,int width,int height,int movex,int movey)
{
 int i;
 int ix=0,iy=0;
 while(ix<width)
 {
 while(iy<height)
 {
 printf("
   <picture
   >
      <rectflip
      x=\"%d\"
      y=\"%d\"
      width=\"%d\"
      height=\"%d\"
      px=\"%d\"
      py=\"%d\"
      />
   </picture>\n
      ",0,0,movex,movey,x+ix,y+iy);
 iy+=movey;
 }
 ix+=movex;
 }
}
*/

//设置精灵的图片
void sp_setBitmap(long int id, int32 bitmap);

//设置精灵显示/隐藏
int sp_setDraw(long int id, int isdraw);

int sp_isDraw(long int id);


//获取精灵id
int sp_getId(long int id);


int sp_setId(long int sprite, int id);

int sp_getFrame(long int id);

//复制一个精灵
long sp_copy(long int id) ;

//添加精灵的动作
//参数：精灵句柄，动作句柄
int sp_addAction(long int sprite_ptr, long int action_ptr);

//设置精灵的动作
//参数：精灵句柄，动作id
int sp_setAction(long int id, int ac_id);

//获取精灵的动作
int sp_getAction(long int id);

//精灵移动
int sp_move(long int id, int x, int y);


int sp_setxy(long int id, int x, int y);

int sp_getx(long int id);

int sp_gety(long int id);

int sp_getWidth(long int id);

int sp_getHeight(long int id);

//精灵是否被x y点中
int sp_impact(long int id, int x, int y);


int isCollisionRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

//精灵碰撞事件
//参数：精灵1 精灵2
//返回值：TRUE碰撞 FALSE不碰撞
int sp_crash(long int id1,long int id2);

//显示精灵
int sp_draw(long int id,long int ca);

void sp_run(long int id);


//销毁精灵
int sp_free(long int id);


#endif
