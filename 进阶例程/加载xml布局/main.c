//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>

/*
xml���ֿ��Է���Ĺ��������棬��߿����ٶ�
�ֻ�cҲ֧��xml����
��xml�ļ��ŵ����̵�assetsĿ¼�£�Ȼ��ͨ��setContextView�������ز��֡�
���๦����μ�API�ĵ���android.h

�ֻ�C�Դ�һ�������xml�༭������UI��ʹ�÷�����μ��˵�>������֧�֡�
*/







//��ں�������������ʱ��ʼִ��
int init()
{
    //����setContextView�������ز���
    setContextView("main.xml");
    
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
    
    if(type==VIEW_UP)
    {
     if(p1==1)
     {
      toast("�����˰�ť1",0);
     }
     if(p1==2)
     {
      toast("�����˰�ť2",0);
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
 