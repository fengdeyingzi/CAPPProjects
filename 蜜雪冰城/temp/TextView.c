//����ϵͳͷ�ļ�base.h
#include <base.h>
#include "android.h"
#include "TextView.h"

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
 toast("���",0);
 draw_main();
 //printf("��\n");
// return 0;
 }


TextView *view;


//���ƻ���
void draw_main()
{
    cls(240,240,240);
    //���ư�ť
    textview_draw(view);
    
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
    view = textview_create(20,20,720-40,220);
    
    //���õ���¼�
    textview_setonclick(view, "click_ok");
 
    //���ÿؼ�id
    textview_setid(view,10);
    
    //��������
    textview_setText(view,"�ֻ�C QQ����Ⱥ��370468001\nӰ����̳��bbs.yzjlb.net\nӰ�Ӿ��ֲ���www.yzjlb.net\n");
    
    //���ñ߾�
    textview_setpadding(view,16);
    
    //���ñ���ɫ ��ɫ
    textview_setBackgroundColor (view, 0xffe0e0e0);
    
    draw_main();
    return 0;
}

void exit_free()
{
 textview_free(view);
 
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
 //����event�¼�
 textview_event(view,type,p1,p2);
 
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
 