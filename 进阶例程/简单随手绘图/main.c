#include <base.h>

/*����С�����*/
void draw(int x,int y)
{
  drect(x,y,5,5,100,100,100);
  ref(0,0,SCRW,SCRH);
}

int init()
{
    
  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(MS_DOWN == type)
    {
      cls(0,0,0);
    }
    
    if(MS_MOVE == type)
    {
      draw(p1,p2);
    }
    
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
 