/*************************
*渐变Logo启动页面***作者：小蟀
*************************/

#include <base.h>
#include <android.h>

/************
*定义Activity*
*************/
enum
{
  MainActivity,
  LogoActivity
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
*Logo界面函数*
************/
void Logo()
{
  cls(0,0,0);
  
  /*界面标志*/
  Activity=LogoActivity;
  
  /*清空控件*/
  clearView();
  
  /*加载对应布局文件*/
  setContextView("logo.xml");
  
  Main();
  ref(0,0,SCRW,SCRH);
}

             
int init()
{
  Logo();
  return 0;
}



//event函数，接收消息事件
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
 