/***************************
*滑动切换界面***作者:小蟀
*重点看event函数的处理部分
****************************/

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
*主界面函数
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


/*************
*Next界面函数
**************/
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


/*定义变量用于判断滑动*/
int goActivity , tempX;


int init()
{
  Main();
  return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    /*按下屏幕初始化变量*/
    if(MS_DOWN == type)
    {
      goActivity=0;
      tempX=p1;
    }
    
    /*滑动增加变量属性*/
    if(MS_MOVE == type)
    {
      goActivity+=p1-tempX;
      tempX=p1;
    }
    
    /*抬起切换界面*/
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
 