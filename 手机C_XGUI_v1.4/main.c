//加载系统头文件base.h
#include <base.h>
#include "android.h"
#include "button.h"

 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}

void click_ok(int32 id)
{
 printf("%s：%d\n","点击",id);
 toast("按钮点击",0);
 draw_main();
 //printf("点\n");
// return 0;
}


button *btn_ok,*btn_2;


//绘制画面
void draw_main()
{
    cls(240,240,240);
    //绘制按钮
    btn_draw(btn_ok);
    btn_draw(btn_2);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
 
}



//入口函数，程序启动时开始执行
int init()
{
 int DECVIDE_WIDTH=0;
 int DECVIDE_HEIGHT=0;
 if(SCRW<SCRH)
 {
  DECVIDE_WIDTH=720;
  DECVIDE_HEIGHT = 720*SCRH/SCRW;
 }
 else
 {
  DECVIDE_WIDTH=720;
  DECVIDE_HEIGHT = 720*SCRW/SCRH;
 }
 
 
 
 setscrsize(720,720*DECVIDE_HEIGHT/DECVIDE_WIDTH);
    //创建按钮
    btn_ok = btn_create("测试1",20,20,720-40,120-40);
    btn_2 = btn_create("测试2",20,120+20,720-40,120-40);
    //设置按钮点击事件
    btn_setonclick(btn_ok, "click_ok");
    btn_setonclick(btn_2, "click_ok");
    //设置按钮id
    btn_setid(btn_ok,1);
    btn_setid(btn_2,2);
    //隐藏按钮2
    btn_hide(btn_2);
    draw_main();
    return 0;
}

void exit_free()
{
 btn_free(btn_ok);
 btn_free(btn_2);
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{
 //监听event事件
 btn_event(btn_ok,type,p1,p2);
 btn_event(btn_2,type,p1,p2);
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
        exit_free();
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
 