//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>

  void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}
int seekbar;

//��ں�������������ʱ��ʼִ��
int init()
{
    setContextView("seekbar.xml");
    seekbar=findViewById(10);
    if(seekbar!=0)
    {
    //����SeekBar�����ֵ
    seekBar_setMax(seekbar,100);
    //����SeekBar�Ľ���
    seekBar_setProgress(seekbar,50);
    }
    int i=seekBar_getProgress(seekbar);
    
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
          int i=seekBar_getOffset(seekbar);
    printf(" %d ",i);
            break;
        }
    }
    
    //SeekBar�Ļ����¼�
    if(type==23)
    {
     printf("seekBar����");
     int id= p1;
     printf(" id:%d pos:%d\n",p1,p2);
    }
    else if(type==24)
    {
     printf("seekBar��ʼ����\n");
     
    }
    
    else if(type==25)
    {
     printf("seekBar��������\n");
     
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
 