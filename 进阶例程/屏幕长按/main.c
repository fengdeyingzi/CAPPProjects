//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>
#include "keytime.h"

/*
��ס��Ļ����
����toast

���ߣ����Ӱ��
���������������ܵġ�
*/

int keytime;

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "�����¼�����", 0, 0, 255, 255, 255, 0, 1);
    
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
    //���ú���helloworld
    helloworld();
    toast("��Ļ��������",0);
    toast("���������������ܵġ�",0);
    //�����¼�
    keytime=key_create();
    //���ó���ʱ��
    key_settime(keytime,2000);
    
    return 0;
}
int exitapp()
{
 key_free(keytime);
 exit();
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
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(type==MS_DOWN)
    {
     //��ʼ�����¼�
     key_start(keytime);
    }
    else if(type==MS_UP)
    {
     key_stop(keytime);
    }
    //���ճ����¼�
    if(type==(int)keytime)
    {
     toast("�����¼�����",0);
     dtext("�����¼�����",0,50,240,0,0,0,1);
     ref(0,0,SCRW,SCRH);
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
 
 