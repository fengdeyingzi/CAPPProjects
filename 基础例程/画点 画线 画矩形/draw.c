#include <base.h>



int init()
{
    //����
    cls(0,0,0);
    //����
    dpointex(100,100,255,20,0);
    //����
    dline(0,50,SCRW,SCRH,255,255,255);
    //������
    drect(0,0,30,30,45,240,50);
    //ˢ����Ļ
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
 