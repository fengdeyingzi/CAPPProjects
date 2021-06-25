#ifndef XGUI_SEEKBAR_H
#define XGUI_SEEKBAR_H

#include "../api/base.h"
#include "../api/graphics.h"
#include "../api/ex_math.h"

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
int32 timer_onstart; //��ʱ��
int32 timer_onpos;
int32 timer_onstop;
int draw_mode; //ˢ��ģʽ
void *onstart; //�����ص�
void *onpos;
void *onstop;
} SeekBar;

//���ƿؼ�
void seek_draw(SeekBar *seekbar);

//�����϶���
void* seek_create(int x,int y,int w,int h)
{
 SeekBar *seekbar = malloc(sizeof(SeekBar));
 memset(seekbar, 0, sizeof(SeekBar));
 seekbar->name = "SeekBar";
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
void seek_setid(SeekBar *seekbar,int id)
{
 seekbar->id=id;
}

//��ʾ�ؼ�
void seek_show(SeekBar *seekbar)
{
 seekbar->isshow = 1;
 if(seekbar->draw_mode==0)
 {
 seek_draw(seekbar);
 ref(seekbar->x, seekbar->y, seekbar->w, seekbar->h);
 }
}
//���ؿؼ�
void seek_hide(SeekBar *seekbar)
{
 seekbar->isshow = 0;
}

//���ƿؼ�
void seek_draw(SeekBar *seekbar)
{
 if(seekbar->isshow)
 {
 //������
 if(seekbar->draw_mode==0)
 drawRect(seekbar->x, seekbar->y, seekbar->w, seekbar->h, seekbar->backgroundColor);
 //������
 drawRect(seekbar->x+seekbar->r, seekbar->y+(seekbar->h-seekbar->h_load)/2, seekbar->w-seekbar->r*2, seekbar->h_load, 0xa0a0a0a0);
 drawRect(seekbar->x+seekbar->r, seekbar->y+(seekbar->h-seekbar->h_load)/2, (seekbar->w-seekbar->r*2)*seekbar->load/seekbar->max, seekbar->h_load, 0xa060aef0);
 //��Բ�ΰ�ť
 int cir_x,cir_y;
 cir_x = seekbar->x+seekbar->r+ (seekbar->w-seekbar->r*2) * seekbar->load / seekbar->max;
 cir_y = seekbar->y + seekbar->h/2;
 if(seekbar->isdown)
 {
 
 drawCir(cir_x,cir_y,seekbar->r, 0x40a0bef0);
 drawCir(cir_x,cir_y,seekbar->r*7/12, 0xff80befa);
 }
 else
 drawCir(cir_x,cir_y,seekbar->r*13/24, 0xff60aef0);
 }
}

//���ö�ʱ��ģʽ
void seek_setref(SeekBar *seekbar, int mode)
{
 seekbar->draw_mode = mode;
}

//���ñ���ɫ Ĭ�ϰ�ɫ
void seek_setBackgroundColor(SeekBar *seekbar, int color)
{
 seekbar->backgroundColor = color;
}

//�жϿؼ��Ƿ���ʾ
int seek_isshow(SeekBar *seekbar)
{
 return seekbar->isshow;
}

//���ý���
void seek_setProgress(SeekBar *seekbar, int pos)
{
 seekbar->load = pos;
 if(seekbar->draw_mode==0)
 {
  seek_draw(seekbar);
  ref(seekbar->x,seekbar->y, seekbar->w,seekbar->h);
  
 }
}

//��ȡ����
int seek_getProgress(SeekBar *seekbar)
{
 return seekbar->load;
}

//�������ֵ
void seek_setMax(SeekBar *seekbar, int max)
{
 seekbar->max = max;
}


//����������ʼ�¼� ��ʱ���ص�����
void seek_onStartTrackingTouch(SeekBar *seekbar, void *onstart)
{
 seekbar->onstart = onstart;
}

//���������¼� ��ʱ���ص�����
void seek_onProgressChanged(SeekBar *seekbar, void *onpos)
{
 seekbar->onpos = onpos;
}
//�������������¼� ��ʱ���ص�����
void seek_onStopTrackingTouch(SeekBar *seekbar, void *onstop)
{
 seekbar->onstop = onstop;
}

//event�¼�
int seek_event(SeekBar *seekbar, int type, int p1, int p2)
{
 //��������
 int px,py;
 if(seekbar->isshow)
 {
  if(type==MS_DOWN)
  {
   //���ݽ������Բ�ΰ�ť����
   px = seekbar->x+seekbar->r+ (seekbar->w-seekbar->r*2)* seekbar->load/seekbar->max;
   py = seekbar->y+ seekbar->h/2;
   printf("���룺%d\n", getLineSize(p1,p2,px,py));
   if(getLineSize(p1,p2, px,py)<=seekbar->r)
   {
    seekbar->isdown = 1;
    if(seekbar->onstart!=NULL)
    timerstart(seekbar->timer_onstart, 10, seekbar->id, seekbar->onstart,0);
    if(seekbar->draw_mode == 0)
    {
     seek_draw(seekbar);
     ref(seekbar->x, seekbar->y, seekbar->w, seekbar->h);
    }
   }
   
  }
  
  if(type == MS_MOVE)
  {
   if(seekbar->isdown)
   {
    //������Ļ�������seekbar����
    int load = seekbar->max * (p1 - (seekbar->x+seekbar->r)) / (seekbar->w-seekbar->r*2);
    //���ý���
    if(load>seekbar->max)load = seekbar->max;
    if(load<0)load=0;
    seek_setProgress(seekbar, load);
    if(seekbar->onpos!=NULL)
    timerstart(seekbar->timer_onpos, 10, seekbar->id, seekbar->onpos,0);
    if(seekbar->draw_mode == 0)
    {
     seek_draw(seekbar);
     ref(seekbar->x, seekbar->y, seekbar->w, seekbar->h);
    }
   }
   
  }
  if(type == MS_UP)
  {
   if(seekbar->isdown)
   {
    seekbar->isdown = 0;
    //������Ļ�������seekbar����
    int load = seekbar->max * (p1 - (seekbar->x+seekbar->r)) /(seekbar->w-seekbar->r*2);
    if(load>seekbar->max)load = seekbar->max;
    if(load<0)load=0;
    //���ý���
    seek_setProgress(seekbar, load);
    if(seekbar->onstop!=NULL)
    timerstart(seekbar->timer_onstop, 10, seekbar->id, seekbar->onstop,0);
    if(seekbar->draw_mode == 0)
    {
     seek_draw(seekbar);
     ref(seekbar->x, seekbar->y, seekbar->w, seekbar->h);
    }
   }
  }
 }
 
 return 0;
}

//�ͷſؼ�
void seek_free(SeekBar *seekbar)
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