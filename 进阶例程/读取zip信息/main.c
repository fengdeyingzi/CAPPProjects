//����ϵͳͷ�ļ�base.h
#include <base.h>
#include <android.h>
#include "zip.h"
#include "String.h"

#define ZIPFILE "C/��ȡzip��Ϣ/ħ����˾.zip"


 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    //������
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}

ZIPHEAD *ziphead;

//��ں�������������ʱ��ʼִ��
int init()
{
int dx=0,dy=0;
    //���ú���helloworld
    helloworld();
    
    setscrsize(320,480);
    cls(45,185,230);
    printf("%d",sizeof(ZIPHEAD));
    //ziphead=malloc(100);
    char text[300];
    char text2[300];
    //��ȡzipͷ��Ϣ
    ziphead=readziphead(ZIPFILE);
    if(ziphead==NULL)
    {
     toast("��ȡʧ��",0);
    }
    //��ʾ
    sprintf(text,"�ļ�ͷ��%x",ziphead->head);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    sprintf(text,"��ѹ������汾��%d", ziphead->version);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    sprintf(text,"ͨ�ñ��ر�־λ��%d", ziphead->bit_flag);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    sprintf(text,"ѹ����ʽ��%d",ziphead->method);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    
    
    
    sprintf(text,"%s",ziphead->filename);
    UTF8ToUni(text, text2, 300);
    dtext(text2, dx,dy,240,240,240,1,1);
    dy+=30;
    sprintf(text,"�ļ�������%d",ziphead->filename_len);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    
    sprintf(text,"��չ�γ���%d",ziphead->field_len);
    dtext(text,dx,dy,240,240,240,0,1);
    dy+=30;
    ref(0,0,SCRW,SCRH);
    return 0;
}

void u2(char *text)
{
 char temp;
 int i=0;
 temp=text[i];
 text[i]=text[i+1];
 text[i+1]=temp;
}


//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exitapp();
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
 
int exitapp()
{
 if(ziphead!=NULL)
 free(ziphead);
 exit();
}