//����ϵͳͷ�ļ�base.h
#include <base.h>
#include "android.h"
#include "ImageButton.h"

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

void click_ok(int id)
{
 printf("%s��%d\n","���",id);
 toast("��ť���",0);
 draw_main();
 //printf("��\n");
// return 0;
 }


ImageButton *btn_ok,*btn_2;


//���ƻ���
void draw_main()
{
    cls(240,240,240);
    //���ư�ť
    img_draw(btn_ok);
    
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
    btn_ok = img_create("assets://icon.png",20,20,720-40,220);
    
    //���ð�ť����¼�
    img_setonclick(btn_ok, "click_ok");
    //������ʾģʽ
    img_setmode(btn_ok,2);
    //���ð�ťid
    img_setid(btn_ok,1);
    
    
    draw_main();
    return 0;
}

void exit_free()
{
 img_free(btn_ok);
 
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
 //����event�¼�
 img_event(btn_ok,type,p1,p2);
 
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
 