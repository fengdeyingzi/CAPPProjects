//����ϵͳͷ�ļ�base.h
#include <base.h>
#include "android.h"
#include "button.h"

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

void click_ok(int32 id)
{
 printf("%s��%d\n","���",id);
 toast("��ť���",0);
 draw_main();
 //printf("��\n");
// return 0;
}


button *btn_ok,*btn_2;


//���ƻ���
void draw_main()
{
    cls(240,240,240);
    //���ư�ť
    btn_draw(btn_ok);
    btn_draw(btn_2);
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
    //������ť
    btn_ok = btn_create("����1",20,20,720-40,120-40);
    btn_2 = btn_create("����2",20,120+20,720-40,120-40);
    //���ð�ť����¼�
    btn_setonclick(btn_ok, "click_ok");
    btn_setonclick(btn_2, "click_ok");
    //���ð�ťid
    btn_setid(btn_ok,1);
    btn_setid(btn_2,2);
    //���ذ�ť2
    btn_hide(btn_2);
    draw_main();
    return 0;
}

void exit_free()
{
 btn_free(btn_ok);
 btn_free(btn_2);
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
 //����event�¼�
 btn_event(btn_ok,type,p1,p2);
 btn_event(btn_2,type,p1,p2);
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
 