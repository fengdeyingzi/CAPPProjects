//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>

int b=0;


 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
   int a = getuptime();
   printf("%d",a);
   dtext ("���������η��ؼ��˳�", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
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
            
            int a = getuptime();
           int c = a - b;
           
            printf("\nʱ��%d",c);
            if(c < 1500){
            
             printf("���Ϊ%d",c);
             
            exit();
            break;
             }
             else{
             
             b = getuptime();
char* wen="�ٰ�һ�η��ؼ��˳�";
toast(wen, LENGTH_SHORT );
              
              }
            
            break;
        case _MENU:
        
            exit();
           
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
 