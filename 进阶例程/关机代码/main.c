
#include <base.h>
#include "android.h"

/*
�ֻ�c�ػ�����
��ҪrootȨ��

���Ӱ�� ��д

*/


 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "�ֻ�c�ػ�����", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
    toast("�����ػ�",0);
    rootcmd("reboot");
    
}


//��ں�������������ʱ��ʼִ��
int init()
{
    //���ú���helloworld
    helloworld();
    
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
 