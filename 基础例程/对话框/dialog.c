//����ϵͳͷ�ļ�base.h
#include <base.h>

//�Ի�����
int dialog;

 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
    //����һ���Ի��� �������Ի������ �Ի�������
    //ע�⣬�����ĶԻ�����unicode���룬��ʹ��hex����ת��(ת��Ϊun)ת��֮�󣬽��ı�����Ի�����
    dialog=dlgcreate("\x5b\xf9\x8b\xdd\x68\x46\x68\x7\x98\x98\x0\x0" ,"\x5b\xf9\x8b\xdd\x68\x46\x51\x85\x5b\xb9\x0\x0",1);
    
    return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
  if(type==MR_DIALOG)
  {
     if(p1==DLG_OK)
    {
        dtext("�Ի����ȷ���������", 0, 50, 255, 255, 255, 0, 1);
        ref(0, 0, SCRW, SCRH);
        return 0;
     }
    
       
     if(p1==DLG_CANCEL)
    {
        dtext("�Ի���ķ��ؼ������", 0, 50, 255, 255, 255, 0, 1);
        ref(0, 0, SCRW, SCRH);
        return 0;
    }
   }

    if(KY_UP == type)
    {
        switch(p1)
        {
        //���ؼ�������
        case _BACK:
        //�ͷŶԻ���
            dlgdel(dialog);
            exit();
            break;
        case _MENU:
            break;
        
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
 