//加载系统头文件base.h
#include <base.h>
#include "coding.h"
#include "cod.h"

/*
公历转农历

*/
#define _YEAR 2013
#define _MONTH 2
#define _DAY 10

int edit;



 void helloworld()
{
    //用指定颜色清除屏幕
    cls(0,0,0);
    char text[300];
    sprintf(text,"%d年%d月%d日",_YEAR,_MONTH,_DAY);
    //画文字
    dtext ( text, 0, 0, 255, 255, 255, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
}


//入口函数，程序启动时开始执行
int init()
{
    //调用函数helloworld
    helloworld();
    main();
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
        //退出前释放编辑框
        editdel(edit);
         exit();
            break;
        case _MENU:
        //edit = editcreate("\x8f\x93Qe\x0","",0,500);
            break;
        }
    }
    //当事件== MR_DIALOG 触发编辑框事件
    else if( MR_DIALOG == type)
    {
     if(p1==DLG_OK)
     {
     cls(0,0,0);
     dtext("编辑框被按下确定键",0,0,255,255,255,0,1);
     printf("dtext\n");
     dtext(editget(edit), 0, 100, 255,255,255, 1, 2);
     char *text=editget(edit);
     printf("un\n");
     char *temp=unToGb(text);
     printf("get\n");
     char *http=getHttp(temp);
     printf("%s",http);
     if((int)temp);
     free(temp);
     if((int)http)
     free(http);
     
     ref(0,0,SCRW,SCRH);
     }
     if(p1==DLG_CANCEL)
     {
      cls(0,0,0);
      dtext("编辑框被按下返回键",0,0,255,255,255,0,1);
      ref(0,0,SCRW,SCRH);
      }
    }

    return 0;
}

//将前两位字符转成char
char hextoc(char *text)
{
 uint8 c=0;
 char temp=*text;
 for(int i=0;i<2;i++)
 {
  temp=text[i];
 //大写转小写
 if(temp>='0' && temp<='9')
  {
   c=(c<<4)+(temp-'0');
  }
 else if(temp>='A' && temp<='F')
 {
  c=(c<<4)+(temp-'A'+10);
 }
 else if(temp>='a' && temp<='f')
 {
  c=(c<<4)+(temp-'a'+10);
 }
 }
 
 
return c;
}


//src=http%3A%2F%2Fpan.baidu.com%2Fshare%2Flink%3Fshareid%3D3195637869%26uk%3D288217650
char *getHttp(char *text)
{
 int len;
 char *ptr;
 char *buf;
 char *temp;
 if(text==NULL)
 {
  printf("%d \n",text);
  }
 if(*text==0)return NULL;
 
 len=strlen(text);
 //查找网址src
 ptr=strstr(text,"src=");
 if(ptr==NULL)return NULL;
 ptr+=4;
 
 if(ptr==NULL)return NULL;
 buf=malloc(len+2);
 temp=buf;
 *buf=0;
 //将%后的十六进制转换成字符
 while(*ptr!=0)
 {
  if(*ptr=='%')
  {
   ptr++;
   *temp=hextoc(ptr);
   ptr++;
  }
  else
  {
   *temp=*ptr;
   
  }
   ptr++;
   temp++;
   
   
  }
  
  
 
 *temp=0;
 
 return buf;
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
 
