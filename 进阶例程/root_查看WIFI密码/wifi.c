//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <exb.h>
#include <android.h>
#include "coding.h"


 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

char *text;
char *edit_text;
int edit;
//��ں�������������ʱ��ʼִ��
int init()
{
    setContextView("wifi.xml");
    edit=findViewById(100);
    
    rootcmd("chmod 777 data/misc/wifi/wpa_supplicant \ncp data/misc/wifi/wpa_supplicant.conf /sdcard/mythroad/wifi.txt");
    
    int len=getlen("wifi.txt");
    text=malloc(len+1);
    edit_text=malloc(len+100);
    
    memset(text,0,len+1);
    int f=open("wifi.txt",1);
    
    read(f,text,len);
    close(f);
    printf(text);
    edit_text=gbToUn(text);
    view_setText(edit,edit_text);
    free(text);
    free(edit_text);
    remove("wifi.txt");
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
 