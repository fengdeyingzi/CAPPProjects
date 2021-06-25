//加载系统头文件base.h
#include <base.h>
#include <android.h>

int b=0;


 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
   int a = getuptime();
   printf("%d",a);
   dtext ("连续按两次返回键退出", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
    //调用函数helloworld
    helloworld();
    
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
            
            int a = getuptime();
           int c = a - b;
           
            printf("\n时间%d",c);
            if(c < 1500){
            
             printf("间隔为%d",c);
             
            exit();
            break;
             }
             else{
             
             b = getuptime();
char* wen="再按一次返回键退出";
toast(wen, LENGTH_SHORT );
              
              }
            
            break;
        case _MENU:
        
            exit();
           
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
 