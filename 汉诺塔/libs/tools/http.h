#ifndef HTTP_H
#define HTTP_H
#include "./dex.h"
//HTTP����
//С�������������
#define HTTP_DEX "assets://dexs/HttpTool.dex"
#define HTTP_CLS "top.huisai.http.CappHttp"

//����HTTP dex
//����_DEX* ��Ҫ�ͷ��ڴ�
void*httpInitTool()
{
 return dex_create(HTTP_DEX,HTTP_CLS);
}

//ע��HTTP event�¼�
//http�¼����Զ�����event(type, p1, p2)����
//type http�¼������Զ��壬Ĭ��100
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

//����HTTP�����ַ������
//��ַ ���� http://www.huisai.top
//���� GET POST PUT DELETE��
void httpSetRequest(_DEX*http,char*url,char*mod)
{
 char*cmd = malloc(sizeof(char)*(100+strlen(url)+strlen(mod)));
 sprintf(cmd,"request %s %s",url,mod);
 char*tmp = dex_put(http,cmd);
 if(tmp!=NULL)
 	free(tmp);
 free(cmd);
}

//����HTTP����ͷ
void httpAddHeader(_DEX*http,char*key,char*value)
{
 char*cmd = malloc(sizeof(char)*(100+strlen(key)+strlen(value)));
 sprintf(cmd,"header %s %s",key,value);
 char*tmp = dex_put(http,cmd);
 if(tmp!=NULL)
 	free(tmp);
 free(cmd);
}

//����HTTP��������
//��δ����
void httpSetData(_DEX*http,char*data)
{
 char*cmd = malloc(sizeof(char)*(100+strlen(data)));
 sprintf(cmd,"setdata %s",data);
 char*tmp = dex_put(http,cmd);
 if(tmp!=NULL)
 	free(tmp);
 free(cmd);
}

//����HTTP����
void httpSend(_DEX*http)
{
 char*tmp = dex_put(http,"send");
 if(tmp!=NULL)
 	free(tmp);
}

//��ȡHTTP����
//��event�õ���Ӧ֮����Ի�ȡ����
//����char*���ֶ��ж��ͷ�
char*httpGetData(_DEX*http)
{
 return dex_put(http,"getdata");
}

//�ͷŽṹ�ڴ�
void httpDexFree(_DEX*http)
{
 if(http!=NULL)
 	dex_free(http);
}

#endif
