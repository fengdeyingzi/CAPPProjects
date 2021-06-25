//加载系统头文件base.h
#include <base.h>

//对话框句柄
int dialog;

 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
    //创建一个对话框 参数：对话框标题 对话框内容
    //注意，创建的对话框是unicode编码，请使用hex编码转换(转换为un)转码之后，将文本放入对话框中
    dialog=dlgcreate("\x5b\xf9\x8b\xdd\x68\x46\x68\x7\x98\x98\x0\x0" ,"\x5b\xf9\x8b\xdd\x68\x46\x51\x85\x5b\xb9\x0\x0",1);
    
    return 0;
}



//event函数，接收消息事件
int event(int type, int p1, int p2)
{
  if(type==MR_DIALOG)
  {
     if(p1==DLG_OK)
    {
        dtext("对话框的确定键被点击", 0, 50, 255, 255, 255, 0, 1);
        ref(0, 0, SCRW, SCRH);
        return 0;
     }
    
       
     if(p1==DLG_CANCEL)
    {
        dtext("对话框的返回键被点击", 0, 50, 255, 255, 255, 0, 1);
        ref(0, 0, SCRW, SCRH);
        return 0;
    }
   }

    if(KY_UP == type)
    {
        switch(p1)
        {
        //返回键被按下
        case _BACK:
        //释放对话框
            dlgdel(dialog);
            exit();
            break;
        case _MENU:
            break;
        
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
 