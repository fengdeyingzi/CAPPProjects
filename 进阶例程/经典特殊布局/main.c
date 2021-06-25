/**************************
*经典特殊布局**作者：风的影子
***************************/

#include <base.h>
#include <android.h>

/*控件属性结构体*/
typedef struct
{
 int id;
 int x;
 int y;
 int w;
 int h;
} VIEW;


int init()
{
    cls(0,0,0);
    int barh=(SCRH-SCRW)/2;
    setContextView("a.xml");
    
    /*********************
    *定义结构体指针并赋值
    **********************/
    VIEW *view=malloc(sizeof(VIEW));
    view->id=0;
    view->x=0;
    view->y=0;
    view->w=SCRW;
    view->h=barh;
    setViewLayout(view);
    
    view->id=1;
    view->x=0;
    view->y=barh;
    view->w=SCRW*2/3;
    view->h=SCRW/3;
    setViewLayout(view);
    
    view->id=2;
    view->x=SCRW*2/3;
    view->y=barh;
    view->w=SCRW/3;
    view->h=SCRW*2/3;
    setViewLayout(view);
    
    view->id=3;
    view->x=0;
    view->y=barh+SCRW/3;
    view->w=SCRW/3;
    view->h=SCRW*2/3;
    setViewLayout(view);
    
    view->id=4;
    view->x=SCRW/3;
    view->y=barh+SCRW/3;
    view->w=SCRW/3;
    view->h=SCRW/3;
    setViewLayout(view);
    
    view->id=5;
    view->x=SCRW/3;
    view->y=barh+SCRW*2/3;
    view->w=SCRW*2/3;
    view->h=SCRW/3;
    setViewLayout(view);
    
    view->id=6;
    view->x=0;
    view->y=SCRH-barh;
    view->w=SCRW;
    view->h=barh;
    setViewLayout(view);
    free(view);
    
    ref(0,0,SCRW,SCRH);
    return 0;
}




//设置view的位置
void setViewLayout(VIEW *view)
{
 char text[300];
 sprintf(text,"
 android:layout_x=\"%d\"
 android:layout_y=\"%d\"
 android:layout_width=\"%d\"
 android:layout_height=\"%d\"
 ", view->x,view->y,view->w,view->h);
 int button=findViewById(view->id);

 if(button!=0)
 {
   /*根据字符串设置控件属性*/
   setView(button,text);
 }
 
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{ 
    printf("%d\n",p1);
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
 