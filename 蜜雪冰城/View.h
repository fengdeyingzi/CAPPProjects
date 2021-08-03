#ifndef _VIEW_H_
#define _VIEW_H_
#include "base.h"
#include "graphics.h"
#include "ex_math.h"

/*
XGUI
������View�ؼ�
֧��������ɫ ���õ���¼�

Ӱ�Ӿ��ֲ���վ��www.yzjlb.net
�ֻ�C��̳��bbs.yzjlb.net
�ֻ�C����QQȺ��370468001

*/

typedef struct
{
  char *name; //�ؼ�����
int id; //�ؼ�id
int type; //��ť״̬������1���ͷ�0������-1
int isshow; //�Ƿ���ʾ ����ʾʱ������ִ�е���¼�
int isdown; //�Ƿ���
int x; //λ��x
int y; //λ��y
int w; //���
int h; //�߶�
int backgroundColor; //����ɫ
int draw_mode; //ˢ��ģʽ
int32 timer; //��ʱ�����
char *onclick; //����¼��ص�����
} View;


//�����ؼ�
void *view_create(int x,int y,int w,int h)
{
 View *view = malloc(sizeof(View));
 memset(view,0,sizeof(View));
 view->x = x;
 view->y = y;
 view->w = w;
 view->h = h;
 view->isshow=1;
 view->backgroundColor = 0x00000000;
 view->timer = timercreate();
 return view;
}

//����id
void view_setid(View *view,int id)
{
 view->id=id;
}

//��ȡid
int view_getid(View *view)
{
 return view->id;
}

//���ƿؼ�
void view_draw(View *view)
{
 if(view->isshow)
 {
  drawRect(view->x, view->y, view->w, view->h, view->backgroundColor);
 }
}


//���û���ģʽ
void view_setMode(View *view, int mode)
{
 view->draw_mode=mode;
}

//��ʾ
void view_show(View *view)
{
 view->isshow = 1;
 if(view->draw_mode==0)
 {
  view_draw(view);
  ref(view->x,view->y,view->w,view->h);
 }
}

//����
void view_hide(View *view)
{
 view->isshow = 0;
}

//�ж��Ƿ���ʾ
int view_isshow(View *view)
{
 return view->isshow;
}

//���ñ���ɫ argb��ʽ
void view_setBackgroundColor(View *view, int color)
{
 view->backgroundColor = color;
 if(view->draw_mode == 0)
 {
  view_draw(view);
  ref(view->x,view->y,view->w,view->h);
 }
}

//���õ���¼�
void view_setonclick(View *view, char *click)
{
 view->onclick = click;
}

//�ؼ�event�¼�
int view_event(View *view, int type, int p1, int p2)
{
 if(view->isshow)
 {
  if(type == MS_DOWN)
  {
   if(isPointCollRect(p1,p2,view->x,view->y,view->w,view->h))
   {
    view->isdown = 1;
   }
   
  }
  else if(type == MS_UP)
  {
   if(view->isdown)
   {
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
void view_free(View *view)
{
 if(view->timer)
 {
  timerstop(view->timer);
  timerdel(view->timer);
  view->timer = 0;
 }
 
 free(view);
 
}












#endif
