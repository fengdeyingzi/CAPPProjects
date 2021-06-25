//加载系统头文件base.h
#include <base.h>
#include <graphics.h>
#include <android.h>
#include <exb.h>

#include "coding.h"

 void helloworld()
{
    //用指定颜色清除屏幕
    
    cls(240,240,240);
    //画文字
    dtext ( "helloworld", 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


int btn_select,btn_con;
int edit;

//转换bmp
void con_bmp(char *path){
 char *bmp_file = malloc(strlen(path)+10);
 
 sprintf(bmp_file,"%s.bmp",path);
int bitmap = readBitmap(path);
 saveBitmap(bitmap, bmp_file, _BMP16,0);
 bitmapFree(bitmap);
 free(bmp_file);
 toast("转换成功",0);
 printf("转换成功%s\n",bmp_file);
}


//入口函数，程序启动时开始执行
int init()
{
    //调用函数helloworld
    helloworld();
    //加载布局
    setContextView("main.xml");
    btn_select = findViewById(2);
    btn_con = findViewById(100);
    edit = findViewById(1);
    
    
    return 0;
}




//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            exit();
            break;
        case _MENU:
            break;
        }
    }
    
    if(VIEW_UP == type){
     if(p1==2){
      fv_init(0);
      fv_settype(".png|.PNG|.gif|.GIF|.jpg|.JPG|.bmp|.BMP",TRUE);
      fv_begin("");
      
     }
     if(p1==100){
      char *path_un = view_getText(edit);
      char *path = unToGb(path_un);
      printf("path = %s\n",path);
      
      con_bmp(path);
      free(path_un);
      free(path);
     }
    }
    
    //event(int type=10,p1=DLG_OK,0);//文件浏览器确定键被点击
    if(type==10){
     if(p1==DLG_OK){
      char *path = fv_getpath();
      char *path_un = gbToUn(path);
      view_setText(edit,path_un);
      free(path_un);
      //free(path);
      fv_end();
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
