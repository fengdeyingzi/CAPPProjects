#ifndef _PROGRESSBAR_H_
#define _PROGRESSBAR_H_

#include "base.h"
#include "graphics.h"
#include "ex_math.h"

/*
�϶����ؼ� ProgressBar

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
int x; //��ťλ��x
int y; //��ťλ��y
int w; //��ť���
int h; //��ť�߶�
int load; //����
int h_load; //��������ʾ�ĸ߶�
int max; //seekbar���ֵ
int r; //�϶���ť�뾶
int backgroundColor; //����ɫ
int timer_onstart; //��ʱ��
int timer_onpos;
int timer_onstop;
int draw_mode; //ˢ��ģʽ
char *onstart; //�����ص�
char *onpos;
char *onstop;
} ProgressBar;

//�����϶���
void* pos_create(int x,int y,int w,int h)
{
 ProgressBar *seekbar = malloc(sizeof(ProgressBar));
 memset(seekbar, 0, sizeof(ProgressBar));
 seekbar->name = "ProgressBar";
 seekbar->x=x;
 seekbar->y=y;
 seekbar->w=w;
 seekbar->h=h;
 seekbar->isshow = 1;
 seekbar->max = 100;
 seekbar->backgroundColor = 0xffffffff;
 seekbar->timer_onstart = timercreate();
 seekbar->timer_onpos = timercreate();
 seekbar->timer_onstop = timercreate();
 int dev_w = 0;
 if(SCRW<SCRH)
 dev_w = SCRW;
 else
 dev_w = SCRH;
 seekbar->r = dev_w /20;
 seekbar->h_load = dev_w /100;
 if(seekbar->r>h) seekbar->r=h;
 
 return seekbar;
}

//���ÿؼ�id
void pos_setid(ProgressBar *seekbar,int id)
{
 seekbar->id=id;
}

//��ʾ�ؼ�
void pos_show(ProgressBar *seekbar)
{
 seekbar->isshow = 1;
 if(seekbar->draw_mode==0)
 {
 pos_draw(seekbar);
 ref(seekbar->x, seekbar->y, seekbar->w, seekbar->h);
 }
}
//���ؿؼ�
void pos_hide(ProgressBar *seekbar)
{
 seekbar->isshow = 0;
}

//���ƿؼ�
void pos_draw(ProgressBar *seekbar)
{
 if(seekbar->isshow)
 {
 //������
 if(seekbar->draw_mode==0)
 drawRect(seekbar->x, seekbar->y, seekbar->w, seekbar->h, seekbar->backgroundColor);
 //������
 drawRect(seekbar->x, seekbar->y+(seekbar->h-seekbar->h_load)/2, seekbar->w, seekbar->h_load, 0xb0808080);
 //����
 drawRect(seekbar->x, seekbar->y+(seekbar->h-seekbar->h_load)/2, seekbar->w*seekbar->load/seekbar->max, seekbar->h_load, 0xff7ec0f0);
 }
}

//���ö�ʱ��ģʽ
void pos_setref(ProgressBar *seekbar, int mode)
{
 seekbar->draw_mode = mode;
}

//���ñ���ɫ Ĭ�ϰ�ɫ
void pos_setBackgroundColor(ProgressBar *seekbar, int color)
{
 seekbar->backgroundColor = color;
}

//�жϿؼ��Ƿ���ʾ
int pos_isshow(ProgressBar *seekbar)
{
 return seekbar->isshow;
}

//���ý���
void pos_setProgress(ProgressBar *seekbar, int pos)
{
 seekbar->load = pos;
 if(seekbar->draw_mode==0)
 {
  pos_draw(seekbar);
  ref(seekbar->x,seekbar->y, seekbar->w,seekbar->h);
  
 }
}

//��ȡ����
int pos_getProgress(ProgressBar *seekbar)
{
 return seekbar->load;
}

//�������ֵ
void pos_setMax(ProgressBar *seekbar, int max)
{
 seekbar->max = max;
}


//����������ʼ�¼� ��ʱ���ص�����
void pos_onStartTrackingTouch(ProgressBar *seekbar, char *onstart)
{
 seekbar->onstart = onstart;
}

//���������¼� ��ʱ���ص�����
void pos_onProgressChanged(ProgressBar *seekbar, char *onpos)
{
 seekbar->onpos = onpos;
}
//�������������¼� ��ʱ���ص�����
void pos_onStopTrackingTouch(ProgressBar *seekbar, char *onstop)
{
 seekbar->onstop = onstop;
}

//event�¼�
int pos_event(ProgressBar *seekbar, int type, int p1, int p2)
{
 //��������
 int px,py;
 if(seekbar->isshow)
 {
  
 }
 
 return 0;
}

//�ͷſؼ�
void pos_free(ProgressBar *seekbar)
{
 if(seekbar->timer_onstart)
 {
 timerstop(seekbar->timer_onstart);
 timerdel(seekbar->timer_onstart);
 seekbar->timer_onstart=0;
 }
 
 if(seekbar->timer_onpos)
 {
 timerstop(seekbar->timer_onpos);
 timerdel(seekbar->timer_onpos);
 seekbar->timer_onpos=0;
 }
 if(seekbar->timer_onstop)
 {
 timerstop(seekbar->timer_onstop);
 timerdel(seekbar->timer_onstop);
 seekbar->timer_onstop=0;
 }
 
 free(seekbar);
}










#endif