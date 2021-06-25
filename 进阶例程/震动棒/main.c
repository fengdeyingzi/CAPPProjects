#include <base.h>
#include <android.h>

int main,bar;
int pro;

int init()
{
  cls(0,0,0);
  /*加载XML*/
  setContextView("main.xml");
  
  /*找到布局，添加SeekBar*/
  main=findViewById(1);
  bar=createView("SeekBar");
  
  /*设置SeekBar的ID*/
  setView(bar,"android:id=\"2\"");
  addView(main,bar); 

  ref(0,0,SCRW,SCRH);
  return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    /*进度改变*/
    if(23 == type)
    {
      if(p1 == 2)
      {
         pro=p2;
         printf("%d\n",p2);
      }
    }
    
    /*开始滑动*/
    if(24 == type)
    {
    }
    
    /*停止滑动*/
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
 