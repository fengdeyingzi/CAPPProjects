//����ϵͳͷ�ļ�base.h
#include <base.h>
#include "android.h"
#include "ProgressBar.h"

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

void onstart(int id)
{
 printf("%s id=%d ����:%d\n","������ʼ",id,pos_getProgress(seekBar));
 
 //draw_main();
 //printf("��\n");
// return 0;
 }
 

void onpos(int id)
{
 printf("%s id=%d ����=%d\n","����",id,pos_getProgress(seekBar));
 
 //draw_main();
 //printf("��\n");
// return 0;
 }
 
 
void onstop(int id)
{
 printf("%s id=%d ����=%d\n","��������",id,pos_getProgress(seekBar));
 
 //draw_main();
 //printf("��\n");
// return 0;
 }

typedef struct
{
 char *name;
} CH;

ProgressBar *seekBar;


//���ƻ���
void draw_main()
{
    cls(240,240,240);
    //���ư�ť
    pos_draw(seekBar);
    
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
    cls(240,240,240);
    ref(0,0,SCRW,SCRH);
    //����SekBar
    seekBar = pos_create(50,50,720-100,100);
    
    //����SeekBar����
    pos_setProgress(seekBar, 30);
    pos_setMax(seekBar,100);
    /*
    for(int i=0;i<=10;i++)
    {
     pos_setProgress(seekBar, 10*i);
     sleep(100);
    }
    */
    
    
    CH *ch = (void*)seekBar;
    printf("%s\n", ch->name);
    //����id
    pos_setid(seekBar,1);
    
    
    draw_main();
    return 0;
}

void exit_free()
{
 pos_free(seekBar);
 
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
 //����event�¼�
 pos_event(seekBar,type,p1,p2);
 
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
 printf("pause\n");
    return 0;
}

//Ӧ�ûָ��������Ϊ�ɼ�ʱ���ô˺���
int resume()
{
 printf("resume\n");
    return 0;
}