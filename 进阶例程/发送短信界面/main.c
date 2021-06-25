/***********************
**发送短信界面**作者：小蟀
************************/

#include <base.h>
#include <android.h>

/*****************
*unicode编码转gb
*需手动释放返回内存
*引自 风的影子
******************/
char *unToGb(char *text)
{
 char *input= text;
int input_len= wstrlen(input);
 char *output= malloc(input_len+2);
 int output_len;
 u2c( input, input_len, &output, &output_len);
 return output;
}


/***********************
*生成一个按钮，返回按钮句柄
************************/
int addBtn(char* name)
{
  /*生成一个按钮*参数Button*/
  int btn=createView("Button");
  char* text=malloc(100);
  
  sprintf(text,"
  android:id=\"0\"
  ");
  
  /*设置控件属性*/
  setView(btn,text);
  
  /*设置控件文字*/
  view_setText(btn,name); 
  
  free(text);
  return btn;
}

/***************
*用户点击发送按钮
***************/
void go(int id)
{
  if(id == 3)
  {
    char* temp=malloc(100);
    char* gbNum=malloc(100);
    char* Text=malloc(100);
    
    //获取号码
    int num=findViewById(1);
    temp=view_getText(num);
    gbNum=unToGb(temp);

    //获取内容
    int text=findViewById(2);
    Text=view_getText(text);
    
    /*发送短信（un编码内容）*/
    sms(gbNum,Text,1);
    
    /*生成一个按钮到可滑动布局*/
    int see=findViewById(4);
    int btn=addBtn(Text);
    addView(see,btn);
    
    free(temp);
    free(gbNum);
    free(Text);
  }
}



//入口函数，程序启动时开始执行
int init()
{
  cls(0,0,0);
  setContextView("sms.xml");
  ref(0,0,SCRW,SCRH);
  return 0;
}


//event函数，接收消息事件
int event(int type, int p1, int p2)
{
  if(VIEW_DOWN == type)
  {
    go(p1);
  }
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            clearView();
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
 