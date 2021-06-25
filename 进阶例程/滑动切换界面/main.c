/***************************
*�����л�����***����:С�
*�ص㿴event�����Ĵ�����
****************************/

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
*�����溯��
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


/*************
*Next���溯��
**************/
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


/*������������жϻ���*/
int goActivity , tempX;


int init()
{
  Main();
  return 0;
}



//event������������Ϣ�¼�
int event(int type, int p1, int p2)
{
    /*������Ļ��ʼ������*/
    if(MS_DOWN == type)
    {
      goActivity=0;
      tempX=p1;
    }
    
    /*�������ӱ�������*/
    if(MS_MOVE == type)
    {
      goActivity+=p1-tempX;
      tempX=p1;
    }
    
    /*̧���л�����*/
    if(MS_UP == type)
    {
      if(Activity==MainActivity)
      {
        if(goActivity<=-SCRW/4)
          Next(); 
      }
      
      if(Activity==NextActivity)
      {
        if(goActivity>=SCRW/4)
          Main();
      }
     
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
 