/*************************
*����Logo����ҳ��***���ߣ�С�
*************************/

#include <base.h>
#include <android.h>

/************
*����Activity*
*************/
enum
{
  MainActivity,
  LogoActivity
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
*Logo���溯��*
************/
void Logo()
{
  cls(0,0,0);
  
  /*�����־*/
  Activity=LogoActivity;
  
  /*��տؼ�*/
  clearView();
  
  /*���ض�Ӧ�����ļ�*/
  setContextView("logo.xml");
  
  Main();
  ref(0,0,SCRW,SCRH);
}

             
int init()
{
  Logo();
  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
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
 