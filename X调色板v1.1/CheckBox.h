#ifndef _VIEW_H_
#define _VIEW_H_
#include "base.h"
#include "graphics.h"
#include "bitmap.h"
#include "ex_math.h"
/*
CheckBox�ؼ�

���Ӱ��
Ӱ�Ӿ��ֲ���վ��www.yzjlb.net
�ֻ�C��̳��bbs.yzjlb.net
�ֻ�C����QQȺ��370468001

*/

typedef struct
{
  char *name; //�ؼ�����
int id; //�ؼ�id
int isshow; //�Ƿ���ʾ ����ʾʱ������ִ�е���¼�
int isdown; //�Ƿ���
int x; //λ��x
int y; //λ��y
int w; //���
int h; //�߶�
int tx; //ͼƬ����
int ty;
int isCheck;
int bitmap_unCheck; //δѡ�е�ͼƬ
int bitmap_isCheck; //ѡ�е�ͼƬ
int backgroundColor; //����ɫ
int draw_mode; //ˢ��ģʽ
int timer; //��ʱ�����
char *onclick; //����¼��ص�����
} CheckBox;


//�����ؼ�
void *check_create(int x,int y,int w,int h)
{
 CheckBox *view = malloc(sizeof(CheckBox));
 memset(view,0,sizeof(CheckBox));
 view->x = x;
 view->y = y;
 view->w = w;
 view->h = h;
 view->isshow=1;
 view->backgroundColor = 0x00000000;
 view->bitmap_unCheck= readBitmapFromAssets("check/Box-0.png");
 view->bitmap_isCheck= readBitmapFromAssets("check/Box-1.png");
 view->tx = view->x + (view->w-bitmap_getw(view->bitmap_unCheck))/2;
 view->ty = view->y + (view->h-bitmap_geth(view->bitmap_unCheck))/2;
 view->timer = timercreate();
 return view;
}

//����id
void check_setid(CheckBox *view,int id)
{
 view->id=id;
}

//��ȡid
int check_getid(CheckBox *view)
{
 return view->id;
}

//���ƿؼ�
void check_draw(CheckBox *view)
{
 int tw,th;
 tw = bitmap_getw(view->bitmap_unCheck);
 th = bitmap_geth(view->bitmap_isCheck);
 if(view->isshow)
 {
  drawRect(view->x, view->y, view->w, view->h, view->backgroundColor);
  if(view->isdown)
  {
   drawRect(view->tx, view->ty, tw, th, 0x40cecece);
  }
  drawBitmap(view->bitmap_unCheck, view->tx, view->ty);
  if(view->isCheck)
  {
   drawBitmap(view->bitmap_isCheck, view->tx, view->ty);
  }
  else
  {
   
  }
  
  
 }
}

//��ʾ
void check_show(CheckBox *view)
{
 view->isshow = 1;
 if(view->draw_mode==0)
 {
  view_draw(view);
  ref(view->x,view->y,view->w,view->h);
 }
}

//����
void check_hide(CheckBox *view)
{
 view->isshow = 0;
}

//�ж��Ƿ���ʾ
int check_isshow(CheckBox *view)
{
 return view->isshow;
}

//���ñ���ɫ argb��ʽ
void check_setBackgroundColor(CheckBox *view, int color)
{
 view->backgroundColor = color;
}

//�л�
void check_switch(CheckBox *check)
{
 if(check->isCheck)
   check->isCheck = 0;
 else
   check->isCheck = 1;
 if(check->draw_mode==0)
 {
  check_draw(check);
  ref(check->x,check->y,check->w,check->h);
 }
}

//���õ���¼�
void check_setonclick(CheckBox *view, char *click)
{
 view->onclick = click;
}

//�ؼ�event�¼�
int check_event(CheckBox *view, int type, int p1, int p2)
{
 if(view->isshow)
 {
  if(type == MS_DOWN)
  {
   if(isPointCollRect(p1,p2,view->x,view->y,view->w,view->h))
   {
    view->isdown = 1;
    if(view->draw_mode==0)
    {
     
     check_draw(view);
     ref(view->x,view->y,view->w,view->h);
    }
   }
   
  }
  else if(type == MS_UP)
  {
   if(view->isdown)
   {
    check_switch(view);
    view->isdown = 0;
    if(view->onclick != NULL)
    {
     timerstart(view->timer, 10, view->id, view->onclick, 0);
    }
   }
  }
  
 }
 
 return 0;
}




//�ͷ��ڴ�
void check_free(CheckBox *view)
{
 if(view->timer)
 {
  timerstop(view->timer);
  timerdel(view->timer);
  view->timer = 0;
 }
 
 if(view->bitmap_unCheck)
 {
  bitmapFree(view->bitmap_unCheck);
  view->bitmap_unCheck = 0;
 }
 if(view->bitmap_isCheck)
 {
  bitmapFree(view->bitmap_isCheck);
  view->bitmap_isCheck = 0;
 }
 
 
 free(view);
 
}












#endif
