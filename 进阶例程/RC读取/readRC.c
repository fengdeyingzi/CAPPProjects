//����ϵͳͷ�ļ�base.h
#include <base.h>
#include "rclist.h"
#include "coding.h"

int32 rc;
char temp[400];


 void rc_draw()
{
    //��ָ����ɫ�����Ļ
    cls(60,60,60);
    //������
    //rc�༭��
    dtext ( rc_getText(rc,0), 0, 0, 255, 255, 255, 1, 1);
    printf("%d\n",(int)rc_getText(rc,0));
    
    //���Ӱ�� ��Ʒ
    rc_getTextGb(rc,1,temp);
    dtext(gbToUn(temp),0,40,255,255,255,1,1);
    char *un= rc_getText(rc,0);
    printf("%d\n",(int)un);
    //����������
    dtext ( unToGb(un), 0, 80, 255, 255, 255, 0, 1);
    printf("%d\n",(int)un);
    printf("%d %d \n",*un,*(un+1));
    
    //dtext ( unToGb( "\x0\x52\x0\x43\x7f\x16\x8f\x91\x56\x68\x0\x0" ), 0, 80, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
    //��ȡrc�ļ�
    rc= rc_read("res_lang0.rc",30);
    
    rc_draw();
    return 0;
}




//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK
:
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
 