/*************************************
*�Ի水ť�İ�����̧��Ч��**����:С�*******
*������ֻ����ʾ��������о��뿴SGL,tWin**
*************************************/

#include <base.h>
#include <button.h>
#include <ex_math.h>

/*��ť������*/
void down(int x,int y)
{
  if(isPointCollRect(x,y,b->x,b->y,b->w,b->h)==TRUE)
  {
    b->isDown=1;
  }
  else
  {
    b->isDown=0;
  }
  drawBtn(b);
}

void up()
{
  b->isDown=0;
  drawBtn(b);
}

Btn* b;

int init()
{
  cls(0,0,0);
   
  b=newBtn(100,200,100,50);
  drawBtn(b);
  
  ref(0,0,SCRW,SCRH);
  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    if(MS_DOWN == type)
    {
      down(p1,p2);
    }
    
    if(MS_UP == type)
    {
      up();
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
 