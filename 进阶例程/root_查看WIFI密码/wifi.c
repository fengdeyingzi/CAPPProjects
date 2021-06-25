//加载系统头文件base.h
#include <base.h>
#include <exb.h>
#include <android.h>
#include "coding.h"


 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}

char *text;
char *edit_text;
int edit;
//入口函数，程序启动时开始执行
int init()
{
    setContextView("wifi.xml");
    edit=findViewById(100);
    
    rootcmd("chmod 777 data/misc/wifi/wpa_supplicant \ncp data/misc/wifi/wpa_supplicant.conf /sdcard/mythroad/wifi.txt");
    
    int len=getlen("wifi.txt");
    text=malloc(len+1);
    edit_text=malloc(len+100);
    
    memset(text,0,len+1);
    int f=open("wifi.txt",1);
    
    read(f,text,len);
    close(f);
    printf(text);
    edit_text=gbToUn(text);
    view_setText(edit,edit_text);
    free(text);
    free(edit_text);
    remove("wifi.txt");
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
 