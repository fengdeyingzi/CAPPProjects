//����ϵͳͷ�ļ�base.h
#include <base.h>
//�����Զ���ͷ�ļ�
#include "helloworld.h"


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
        //���·��ؼ������˳�
        case _SRIGHT:
            exit();
            break;
        case _1:
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
 