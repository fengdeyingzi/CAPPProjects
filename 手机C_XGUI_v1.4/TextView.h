#ifndef _TEXTVIEW_H_
#define _TEXTVIEW_H_
#include "base.h"
#include "graphics.h"
#include "ex_math.h"
#include "coding.h"

/*
XGUI
�ı���ؼ�

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
int padding; //�߾���
int tx;
int ty;//����xy����
int textColor; //������ɫ
int backgroundColor; //����ɫ
char *text;
int draw_mode; //ˢ��ģʽ
int32 timer; //��ʱ�����
int font; // �����С ȡֵ��0 1 2
char *onclick; //����¼��ص�����
} TextView;


//�����ؼ�
void *textview_create(int x,int y,int w,int h)
{
 TextView *view = malloc(sizeof(TextView));
 memset(view,0,sizeof(TextView));
 view->x = x;
 view->y = y;
 view->w = w;
 view->h = h;
 view->tx=x;
 view->ty=y;
 view->isshow=1;
 view->backgroundColor = 0x00000000;
 view->font = 1;
 view->timer = timercreate();
 return view;
}

//�������� gb2312����
void textview_setText(TextView *view, char *text)
{
 if(view->text!=NULL)
 {
 free(view->text);
 view->text = NULL;
 }
 
 view->text = gbToUn(text);
 
}

//�����ı���ɫ argb��ʽ
void textview_setTextColor(TextView *view, int color)
{
 view->textColor = color;
}

//���ñ߾�
void textview_setpadding(TextView *view, int padding)
{
 view->padding = padding;
 view->tx = view->x+padding;
 view->ty = view->y+padding;
}

//����id
void textview_setid(TextView *view,int id)
{
 view->id=id;
}

//��ȡid
int textview_getid(TextView *view)
{
 return view->id;
}

//���ƿؼ�
void textview_draw(TextView *view)
{
 rectst rect;
colorst color;
rect.x= view->x+view->padding;
rect.y= view->y+view->padding;
rect.w= view->w-view->padding*2;
rect.h= view->h-view->padding*2;
color.r=(view->textColor>>16)&0xff;
color.g=(view->textColor>>8)&0xff;
color.b=(view->textColor)&0xff;

 if(view->isshow)
 {
  drawRect(view->x, view->y, view->w, view->h, view->backgroundColor);
  if(view->text!=NULL)
  dtextex(view->text,view->tx,view->ty,&rect,&color,1|2,view->font);
 }
}

//��ʾ
void textview_show(TextView *view)
{
 view->isshow = 1;
 if(view->draw_mode==0)
 {
  view_draw(view);
  ref(view->x,view->y,view->w,view->h);
 }
}

//����
void textview_hide(TextView *view)
{
 view->isshow = 0;
}

//�ж��Ƿ���ʾ
int textview_isshow(TextView *view)
{
 return view->isshow;
}

//���ñ���ɫ argb��ʽ
void textview_setBackgroundColor(TextView *view, int color)
{
 view->backgroundColor = color;
}

//���õ���¼�
void textview_setonclick(TextView *view, char *click)
{
 view->onclick = click;
}

//�ؼ�event�¼�
int textview_event(TextView *view, int type, int p1, int p2)
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
void textview_free(TextView *view)
{
 if(view->timer)
 {
  timerstop(view->timer);
  timerdel(view->timer);
  view->timer = 0;
 }
 if(view->text!=NULL)
 free(view->text);
 free(view);
 
}












#endif

