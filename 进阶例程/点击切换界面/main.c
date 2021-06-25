/*************************
*����л�����***���ߣ�С�
*************************/

#include <base.h>
#include <android.h>

/************
*����Activity*
*************/
enum
{
  MainActivity,
  NextActivity
}Activity;


/**********
*�����溯��*
**********/
void Main()
{
  cls(0,0,0);
  
  /*�����־*/
  Activity=MainActivity;
  
  /*��տؼ�*/
  clearView();
  
  /*���ض�Ӧ�����ļ�*/
  setContextView("main.xml");
  
  ref(0,0,SCRW,SCRH);
}


/***********
*Next���溯��*
************/
void Next()
{
  cls(0,0,0);
  
  /*�����־*/
  Activity=NextActivity;
  
  /*��տؼ�*/
  clearView();
  
  /*���ض�Ӧ�����ļ�*/
  setContextView("next.xml");
  
  ref(0,0,SCRW,SCRH);
}

void viewDown(int id)
{
  /*�ֽ��洦���¼�*/
  switch(Activity)
  {
    /*������*/
    case MainActivity:
        /*��Id�����¼�*/
        switch(id)
        {
          case 1:
          break;
          
          /*��ת����*/
          case 2:
             Next();
          break;
          
          case 3:
             clearView();
             exit();
          break;
        }
    break;
    
    /*Next����*/
    case NextActivity:
        /*��Id�����¼�*/
        switch(id)
        {
          case 1:
          break;
          
          /*��ת����*/
          case 2:
             Main();
          break;
          
          case 3:
             clearView();
             exit();
          break;
        }
    break;
  }
 
}

int init()
{
  Main();
  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    /*����ť������*/
    if(VIEW_DOWN == type)
    {
      viewDown(p1);
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
 