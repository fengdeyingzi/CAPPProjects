/***************************
*小小侧滑栏***作者:小蟀
*这里的侧滑栏并不随手指动
*有兴趣的的可以继续完善此程序
****************************/

#include <base.h>
#include <android.h>

/************
*定义Activity*
*************/
enum
{
  MainActivity,
  MenuActivity
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


/***************
*加载Menu界面函数
****************/
void Menu()
{
  cls(0,0,0);
  Activity=MenuActivity;
  int menu=findViewById(1);
  char* text=malloc(100);
  int menuW;
  for(menuW=0;menuW<=SCRW/2;menuW++)
  {
    sprintf(text,"
    android:layout_width=\"%d\"
    android:layout_height=\"match_parent\"
    ",menuW);
   
    setView(menu,text);
  }

  ref(0,0,SCRW,SCRH);
}


/***************
*隐藏Menu界面函数
****************/
void endMenu()
{
  cls(0,0,0);
  Activity=MainActivity;
  int menu=findViewById(1);
  char* text=malloc(100);
  int menuW;
  for(menuW=SCRW/2;menuW>=0;menuW--)
  {
    sprintf(text,"
    android:layout_width=\"%d\"
    android:layout_height=\"match_parent\"
    ",menuW);
   
    setView(menu,text);
  }

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
        if(goActivity>=SCRW/4)
          Menu(); 
      }
      
      if(Activity==MenuActivity)
      {
        if(goActivity<=-SCRW/4)
          endMenu();
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
 