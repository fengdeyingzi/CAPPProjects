//����ϵͳͷ�ļ�base.h
#include <base.h>
#include "android.h"
#include "SeekBar.h"
#include "View.h"

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

void onColor(int id)
{
 int a = seek_getProgress(seek_a);
 int r = seek_getProgress(seek_r);
 int g = seek_getProgress(seek_g);
 int b = seek_getProgress(seek_b);
 
int color = (a<<24) | (r<<16) | (g<<8) | b;

 view_setBackgroundColor(view_color,color);
 draw_main();
}
 
void onRed(int id)
{
 
 
}

void onGreen(int id)
{
 
}

void onBlue(int id)
{
 
}


View *view_color;
SeekBar *seek_a, *seek_r, *seek_g, *seek_b;


//���ƻ���
void draw_main()
{
    cls(240,240,240);
    
    //����
    view_draw(view_color);
    seek_draw(seek_a);
    seek_draw(seek_r);
    seek_draw(seek_g);
    seek_draw(seek_b);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
 
}



//��ں�������������ʱ��ʼִ��
int init()
{
 int DECVIDE_WIDTH=0;
 int DECVIDE_HEIGHT=0;
 if(SCRW<SCRH)
 {
  DECVIDE_WIDTH=720;
  DECVIDE_HEIGHT = 720*SCRH/SCRW;
 }
 else
 {
  DECVIDE_WIDTH=720;
  DECVIDE_HEIGHT = 720*SCRW/SCRH;
 }
 
 
 
 setscrsize(720,720*DECVIDE_HEIGHT/DECVIDE_WIDTH);
    //����
    view_color = view_create(30,150,SCRW-60,90);
    seek_a = seek_create(10,300,SCRW-20,80);
    seek_r = seek_create(10,400,SCRW-20,80);
    seek_g = seek_create(10,500,SCRW-20,80);
    seek_b = seek_create(10,600,SCRW-20,80);
    view_setMode(view_color,2);
    
    
    seek_setMax(seek_a,255);
    seek_setMax(seek_r,255);
    seek_setMax(seek_g,255);
    seek_setMax(seek_b,255);
    seek_setProgress(seek_a,255);
    seek_setColor(seek_a,0xff909090);
    seek_setColor(seek_r,0xfff05d6e);
    seek_setColor(seek_g,0xff70de7d);
    seek_setColor(seek_b,0xff60a0f0);
    
    seek_onProgressChanged(seek_a,"onColor");
    seek_onProgressChanged(seek_r,"onColor");
    seek_onProgressChanged(seek_g,"onColor");
    seek_onProgressChanged(seek_b,"onColor");
    
    
    onColor(0);
    return 0;
}

void exit_free()
{
 view_free(view_color);
 seek_free(seek_a);
 seek_free(seek_r);
 seek_free(seek_g);
 seek_free(seek_b);
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
 //����event�¼�
 seek_event(seek_a,type,p1,p2);
 seek_event(seek_r,type,p1,p2);
 seek_event(seek_g,type,p1,p2);
 seek_event(seek_b,type,p1,p2);
 view_event(view_color,type,p1,p2);
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
        exit_free();
            exit();
            break;
        case _MENU:
            break;
        }
    }

    return 0;
}

//Ӧ����ͣ������������̨���Ϊ���ɼ�ʱ����ô˺���
int pause()
{
    return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
int resume()
{
    return 0;
}
 