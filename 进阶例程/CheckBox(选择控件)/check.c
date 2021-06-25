//加载系统头文件base.h
#include <base.h>
#include <android.h>


int check;

 void draw()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    //dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
    draw();
    setContextView("check.xml");
    check=findViewById(100);
    //设置CheckBox被选中
    setChecked(check,TRUE);
    
    //获取CheckBox选中状态
    printf(" CheckBox状态：%d ",isChecked(check));
    
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
 