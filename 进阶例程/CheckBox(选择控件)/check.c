//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>


int check;

 void draw()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    //dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
    draw();
    setContextView("check.xml");
    check=findViewById(100);
    //����CheckBox��ѡ��
    setChecked(check,TRUE);
    
    //��ȡCheckBoxѡ��״̬
    printf(" CheckBox״̬��%d ",isChecked(check));
    
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
 