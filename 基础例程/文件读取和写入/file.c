#include <base.h>

/*
�ļ������ĸ�Ŀ¼Ĭ��Ϊmythroad�����ֻ���Ŀ¼
open ���ļ�
read ��ȡ�ļ�
write д���ļ�
close �ر��ļ�

*/

int init()
{
    
    
    cls(240,240,240);
    //д���ı�
    writetext();
    dtext("д���ı��ɹ�", 0, 0, 30, 30, 30, 0, 1);
    dtext("���˵�����ȡ�ı�",0, 100, 255, 30, 30, 0, 1);
    //ˢ����Ļ
    ref(0,0,SCRW,SCRH);
    
    return 0;
}

//д���ı�
void writetext()
{
 char *text="����д�������";
 int f=open("c/a.txt",2|8);
 write(f,text,strlen(text));
 close(f);
 printf("д���ı�\n");
}

//��ȡ�ı�
void readtext()
{
 char *text;
 int len=getlen("c/a.txt");
 //�����ڴ��������ı�
 text=malloc(len+1);
 //�����ַ���Ҫ��\0��β�����Խ�text�ڴ����򶼳�ʼ��Ϊ0
 memset(text,0,len+1);
 //���ļ�
 int f=open("c/a.txt",1|8);
 //��ȡ���ݵ�text
 read(f,text,len);
 //�ر��ļ�
 close(f);
 cls(240,240,240);
 //��������ʾ����Ļ
 dtext(text,0, 0, 30, 30, 30, 0, 1);
 //ˢ����Ļ
 ref(0,0,SCRW,SCRH);
 //�ͷ��ڴ�
 free(text);
 printf("��ȡ�ı�����\n");
}

int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        
        case _SRIGHT:
            exit();
            break;
        case _SLEFT:
            readtext();
            break;
        }
    }

    return 0;
}


int pause()
{
    return 0;
}


int resume()
{
    return 0;
}
 