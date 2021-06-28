//加载系统头文件base.h
#include <base.h>
#include "rclist.h"
#include "coding.h"

int32 rc;
char temp[400];


 void rc_draw()
{
    //用指定颜色清除屏幕
    cls(60,60,60);
    //画文字
    //rc编辑器
    dtext ( rc_getText(rc,0), 0, 0, 255, 255, 255, 1, 1);
    printf("%d\n",(int)rc_getText(rc,0));
    
    //风的影子 作品
    rc_getTextGb(rc,1,temp);
    dtext(gbToUn(temp),0,40,255,255,255,1,1);
    char *un= rc_getText(rc,0);
    printf("%d\n",(int)un);
    //刀？？？？
    dtext ( unToGb(un), 0, 80, 255, 255, 255, 0, 1);
    printf("%d\n",(int)un);
    printf("%d %d \n",*un,*(un+1));
    
    //dtext ( unToGb( "\x0\x52\x0\x43\x7f\x16\x8f\x91\x56\x68\x0\x0" ), 0, 80, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
    //读取rc文件
    rc= rc_read("res_lang0.rc",30);
    
    rc_draw();
    return 0;
}




//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK
:
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
 