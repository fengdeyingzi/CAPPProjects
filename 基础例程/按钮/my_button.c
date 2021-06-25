//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>
#include "button.h"

//������ť
button *btn_exit,*btn_start;

//��¼���ֿ��
int fontw,fonth;
#define FONT 1

 void draw()
{
    cls(255,255,255);
    dtext("��ť����¼�",0,0,50,50,50,0,FONT);
    dtext("by�����Ӱ��",0,fonth+4,50,50,50,0,FONT);
    //����ť���Ƶ���Ļ��
    button_draw(btn_exit);
    button_draw(btn_start);
    ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
 //������ִ�С
 textwh("��",0,FONT,&fontw,&fonth);
 
 //��ʼ����ť���½�������ť
 //new_button�����ֱ��� ��ť���� ��ťx���� y���� ��� �߶� 
 btn_start=new_button("��ʼ",0,SCRH-(fonth+10), fontw*4+10 ,fonth+10 );
 btn_exit=new_button("�˳�",SCRW-(fontw*4+10),SCRH-(fonth+10), fontw*4+10, fonth+10);
 //��ʾ
 draw();
 
    return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exitapp();
            break;
        case _MENU:
            break;
        }
    }
    //�жϴ����¼�
    if(type == MS_UP)
    {
     if(button_impact(btn_start, p1, p2))
     {
      toast("������˿�ʼ��ť",0);
     }
     if(button_impact(btn_exit,p1,p2))
     {
      toast("��л����^o^",0);
      exitapp();
     }
     
    }

    return 0;
}

void exitapp()
{
 button_free(btn_start);
 button_free(btn_exit);
 exit();
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
 