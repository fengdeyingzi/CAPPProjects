#include <base.h>

/*
文件操作的根目录默认为mythroad而非手机根目录
open 打开文件
read 读取文件
write 写入文件
close 关闭文件

*/

int init()
{
    
    
    cls(240,240,240);
    //写入文本
    writetext();
    dtext("写入文本成功", 0, 0, 30, 30, 30, 0, 1);
    dtext("按菜单键读取文本",0, 100, 255, 30, 30, 0, 1);
    //刷新屏幕
    ref(0,0,SCRW,SCRH);
    
    return 0;
}

//写入文本
void writetext()
{
 char *text="这是写入的内容";
 int f=open("c/a.txt",2|8);
 write(f,text,strlen(text));
 close(f);
 printf("写入文本\n");
}

//读取文本
void readtext()
{
 char *text;
 int len=getlen("c/a.txt");
 //申请内存来保存文本
 text=malloc(len+1);
 //由于字符串要以\0结尾，所以将text内存区域都初始化为0
 memset(text,0,len+1);
 //打开文件
 int f=open("c/a.txt",1|8);
 //读取内容到text
 read(f,text,len);
 //关闭文件
 close(f);
 cls(240,240,240);
 //将文字显示到屏幕
 dtext(text,0, 0, 30, 30, 30, 0, 1);
 //刷新屏幕
 ref(0,0,SCRW,SCRH);
 //释放内存
 free(text);
 printf("读取文本内容\n");
}

int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        
        case _SRIGHT:
            exit();
            break;
        case _SLEFT:
            readtext();
            break;
        }
    }

    return 0;
}


int pause()
{
    return 0;
}


int resume()
{
    return 0;
}
 