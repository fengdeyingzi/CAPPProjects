//����ϵͳͷ�ļ�base.h
#include <base.h>
#include "coding.h"
#include "cod.h"

/*
����תũ��

*/
#define _YEAR 2013
#define _MONTH 2
#define _DAY 10

int edit;



 void helloworld()
{
    //��ָ����ɫ�����Ļ
    cls(0,0,0);
    char text[300];
    sprintf(text,"%d��%d��%d��",_YEAR,_MONTH,_DAY);
    //������
    dtext ( text, 0, 0, 255, 255, 255, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
}


//��ں�������������ʱ��ʼִ��
int init()
{
    //���ú���helloworld
    helloworld();
    main();
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
        //�˳�ǰ�ͷű༭��
        editdel(edit);
         exit();
            break;
        case _MENU:
        //edit = editcreate("\x8f\x93Qe\x0","",0,500);
            break;
        }
    }
    //���¼�== MR_DIALOG �����༭���¼�
    else if( MR_DIALOG == type)
    {
     if(p1==DLG_OK)
     {
     cls(0,0,0);
     dtext("�༭�򱻰���ȷ����",0,0,255,255,255,0,1);
     printf("dtext\n");
     dtext(editget(edit), 0, 100, 255,255,255, 1, 2);
     char *text=editget(edit);
     printf("un\n");
     char *temp=unToGb(text);
     printf("get\n");
     char *http=getHttp(temp);
     printf("%s",http);
     if((int)temp);
     free(temp);
     if((int)http)
     free(http);
     
     ref(0,0,SCRW,SCRH);
     }
     if(p1==DLG_CANCEL)
     {
      cls(0,0,0);
      dtext("�༭�򱻰��·��ؼ�",0,0,255,255,255,0,1);
      ref(0,0,SCRW,SCRH);
      }
    }

    return 0;
}

//��ǰ��λ�ַ�ת��char
char hextoc(char *text)
{
 uint8 c=0;
 char temp=*text;
 for(int i=0;i<2;i++)
 {
  temp=text[i];
 //��дתСд
 if(temp>='0' && temp<='9')
  {
   c=(c<<4)+(temp-'0');
  }
 else if(temp>='A' && temp<='F')
 {
  c=(c<<4)+(temp-'A'+10);
 }
 else if(temp>='a' && temp<='f')
 {
  c=(c<<4)+(temp-'a'+10);
 }
 }
 
 
return c;
}


//src=http%3A%2F%2Fpan.baidu.com%2Fshare%2Flink%3Fshareid%3D3195637869%26uk%3D288217650
char *getHttp(char *text)
{
 int len;
 char *ptr;
 char *buf;
 char *temp;
 if(text==NULL)
 {
  printf("%d \n",text);
  }
 if(*text==0)return NULL;
 
 len=strlen(text);
 //������ַsrc
 ptr=strstr(text,"src=");
 if(ptr==NULL)return NULL;
 ptr+=4;
 
 if(ptr==NULL)return NULL;
 buf=malloc(len+2);
 temp=buf;
 *buf=0;
 //��%���ʮ������ת�����ַ�
 while(*ptr!=0)
 {
  if(*ptr=='%')
  {
   ptr++;
   *temp=hextoc(ptr);
   ptr++;
  }
  else
  {
   *temp=*ptr;
   
  }
   ptr++;
   temp++;
   
   
  }
  
  
 
 *temp=0;
 
 return buf;
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
 
