
#include <base.h>


int init()
{
    cls(0,0,0);
    
    dtext("�����Ļ��", 30,30,0,255,0,0,1);
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
    
    //����Ļ����ʱ��ִ����
    if(MS_DOWN==type)
    {
    printf("��ִ�� %d\n",getuptime());
    shake(50);
    
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
  