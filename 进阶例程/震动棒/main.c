#include <base.h>
#include <android.h>

int main,bar;
int pro;

int init()
{
  cls(0,0,0);
  /*����XML*/
  setContextView("main.xml");
  
  /*�ҵ����֣����SeekBar*/
  main=findViewById(1);
  bar=createView("SeekBar");
  
  /*����SeekBar��ID*/
  setView(bar,"android:id=\"2\"");
  addView(main,bar); 

  ref(0,0,SCRW,SCRH);
  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    /*���ȸı�*/
    if(23 == type)
    {
      if(p1 == 2)
      {
         pro=p2;
         printf("%d\n",p2);
      }
    }
    
    /*��ʼ����*/
    if(24 == type)
    {
    }
    
    /*ֹͣ����*/
    if(25 == type)
    {
      if(2 == p1)
         shake(20*pro);
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
 