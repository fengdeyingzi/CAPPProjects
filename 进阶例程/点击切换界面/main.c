/*************************
*点击切换界面***作者：小蟀
*************************/

#include <base.h>
#include <android.h>

/************
*定义Activity*
*************/
enum
{
  MainActivity,
  NextActivity
}Activity;


/**********
*主界面函数*
**********/
void Main()
{
  cls(0,0,0);
  
  /*界面标志*/
  Activity=MainActivity;
  
  /*清空控件*/
  clearView();
  
  /*加载对应布局文件*/
  setContextView("main.xml");
  
  ref(0,0,SCRW,SCRH);
}


/***********
*Next界面函数*
************/
void Next()
{
  cls(0,0,0);
  
  /*界面标志*/
  Activity=NextActivity;
  
  /*清空控件*/
  clearView();
  
  /*加载对应布局文件*/
  setContextView("next.xml");
  
  ref(0,0,SCRW,SCRH);
}

void viewDown(int id)
{
  /*分界面处理事件*/
  switch(Activity)
  {
    /*主界面*/
    case MainActivity:
        /*分Id处理事件*/
        switch(id)
        {
          case 1:
          break;
          
          /*跳转界面*/
          case 2:
             Next();
          break;
          
          case 3:
             clearView();
             exit();
          break;
        }
    break;
    
    /*Next界面*/
    case NextActivity:
        /*分Id处理事件*/
        switch(id)
        {
          case 1:
          break;
          
          /*跳转界面*/
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



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    /*处理按钮被按下*/
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

//应用暂停，当程序进入后台或变为不可见时会调用此函数
int pause()
{
    return 0;
}

//应用恢复，程序变为可见时调用此函数
int resume()
{
    return 0;
}
 