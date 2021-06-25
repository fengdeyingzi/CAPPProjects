#ifndef XGUI_TOOLBAR_H
#define XGUI_TOOLBAR_H
//小蟀制作仅供参考
#include "./View.h"
#include "./TextView.h"
#include "./ImageButton.h"

typedef struct
{
 char*name;//控件名字
 int id;//控件id
 int isshow;//是否显示
 
 //默认仅支持修改高度
 int x;//位置x
 int y;//位置y
 int w;//宽度
 int h;//高度
 
 TextView *title;//标题
 ImageButton *nav;//导航按钮
 
 int bkgColor;//背景色
 int draw_mode;//刷新模式
 int32 timer;//定时器句柄
 void*onclick;//点击事件回调函数
}ToolBar;

//创建控件
void *toolbar_create(char*title)
{
 ToolBar *tb = malloc(sizeof(ToolBar));
 memset(tb,0,sizeof(ToolBar));
 tb->x = 0;
 tb->y = 0;
 tb->w = SW;
 tb->h = 100;
 tb->isshow=1;
 tb->bkgColor = 0xffffffff;
 tb->timer = timercreate();
 
 //创建标题
 tb->title=textview_create(0, 0, tb->w, tb->h);
 textview_setText(tb->title, title);
 //创建图标
 tb->nav=NULL;
 return tb;
}


//释放内存
void toolbar_free(ToolBar *tb)
{
 if(tb->timer)
 {
  timerstop(tb->timer);
  timerdel(tb->timer);
  tb->timer = 0;
 }
 if(tb->title)
 textview_free(tb->title);
 if(tb->nav)
 img_free(tb->nav);
 free(tb);
}


#endif