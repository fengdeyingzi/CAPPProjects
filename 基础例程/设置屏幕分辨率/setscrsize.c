#include <base.h>

/*
������Ļ�ֱ���

���ú���setscrsize���÷ֱ���
�ú��������³�ʼ����Ļ
SCRW SCRH ��ֵҲ����֮�ı�

������init��������ô˺���

*/
char text[300];

int init()
{
    //������Ļ�ֱ���Ϊ480*800
    setscrsize(480,800);
    cls(0,0,0);
    
    sprintf(text,"��Ļ��ȣ�%d",SCRW);
    printf("��Ļ��������� %d %d",SCRW,SCRH);
    
    
    dtext(text, 30,30,255,255,255,0,1);
    ref(0,0,SCRW,SCRH);
    
    return 0;
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
        case _1:
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
 