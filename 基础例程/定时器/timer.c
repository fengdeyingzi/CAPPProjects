#include <base.h>

//��ʱ�����
int32 timer;

//����ͳ�ƶ�ʱ��ִ�д���
int a=0;


void timerCD(int data)
{
    char text[20];
    sand(getuptime());
    cls(255,255,255);
    //��a��ֵת�����ַ���
    sprintf (text, "%d", a);
    //�������ֵ���Ļ��
    dtext (text, 10, 10, 20, 20, 20, 0, 2);
    
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
    //���printf
    printf("timer,data=%d,a=%d\r\n",data,a++);
    
}


int init(void)
{
 
    //������ʱ��
    timer=timercreate();
    //������ʱ�� �����ֱ��ǣ���ʱ���������ʱ��ʱ������ʱ���ص�data����ʱ���ص��������Ƿ�ѭ��
    timerCD(0);
    timerstart (timer, 1000, 1234, "timerCD", TRUE);
    
    return 0;
}

int event(int type, int p1, int p2)
{
    if(KY_DOWN == type)
    {
        switch(p1)
        {
         //�����ؼ��˳�
        case _BACK:
            exitapp();
            break;
        case _1:
            break;
        case _2:
            break;
        }
    }

    return 0;
}

int pause(void)
{
    return 0;
}

int resume(void)
{
    return 0;
}

int exitapp(void)
{
    //�˳�ʱɾ����ʱ��
    timerdel(timer);
    
    exit();
    return 0;
}