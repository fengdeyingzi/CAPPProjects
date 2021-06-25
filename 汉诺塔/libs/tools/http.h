#ifndef HTTP_H
#define HTTP_H
#include "./dex.h"
//HTTP工具
//小蟀制作第三方版
#define HTTP_DEX "assets://dexs/HttpTool.dex"
#define HTTP_CLS "top.huisai.http.CappHttp"

//载入HTTP dex
//返回_DEX* 需要释放内存
void*httpInitTool()
{
 return dex_create(HTTP_DEX,HTTP_CLS);
}

//注册HTTP event事件
//http事件会自动触发event(type, p1, p2)函数
//type http事件，可自定义，默认100
//p1 0success 1error 2failure 3complete
//p2 http response code
void httpRegisterEvent(_DEX*http,int type)
{
 char cmd[100];
 sprintf(cmd,"register %d",type);
 char*tmp = dex_put(http,cmd);
 if(tmp!=NULL)
 	free(tmp);
}

//设置HTTP请求地址和类型
//地址 例如 http://www.huisai.top
//类型 GET POST PUT DELETE等
void httpSetRequest(_DEX*http,char*url,char*mod)
{
 char*cmd = malloc(sizeof(char)*(100+strlen(url)+strlen(mod)));
 sprintf(cmd,"request %s %s",url,mod);
 char*tmp = dex_put(http,cmd);
 if(tmp!=NULL)
 	free(tmp);
 free(cmd);
}

//设置HTTP请求头
void httpAddHeader(_DEX*http,char*key,char*value)
{
 char*cmd = malloc(sizeof(char)*(100+strlen(key)+strlen(value)));
 sprintf(cmd,"header %s %s",key,value);
 char*tmp = dex_put(http,cmd);
 if(tmp!=NULL)
 	free(tmp);
 free(cmd);
}

//设置HTTP请求数据
//暂未测试
void httpSetData(_DEX*http,char*data)
{
 char*cmd = malloc(sizeof(char)*(100+strlen(data)));
 sprintf(cmd,"setdata %s",data);
 char*tmp = dex_put(http,cmd);
 if(tmp!=NULL)
 	free(tmp);
 free(cmd);
}

//发送HTTP请求
void httpSend(_DEX*http)
{
 char*tmp = dex_put(http,"send");
 if(tmp!=NULL)
 	free(tmp);
}

//获取HTTP数据
//在event得到响应之后可以获取数据
//返回char*需手动判断释放
char*httpGetData(_DEX*http)
{
 return dex_put(http,"getdata");
}

//释放结构内存
void httpDexFree(_DEX*http)
{
 if(http!=NULL)
 	dex_free(http);
}

#endif
