#ifndef TOOL_H
#define TOOL_H
//�ֻ�CAPP���ع��ܲ��ּ���
#include "../api/android.h"

//��ȡimei
char*get_imei()
{
 return dex_putString(0,"imei ");
}

//��ȡimsi
char*get_imsi()
{
 return dex_putString(0,"imsi ");
}

//��ȡCPU����
char*get_cpuAbi()
{
 return dex_putString(0,"CPU_ABI ");
}

//��ȡ��׿�汾
char*get_sdkInt()
{
 return dex_putString(0,"SDK_INT ");
}

//����״̬����ɫ
void set_statusBarColor(int color)
{
 char tmp[100];
 sprintf(tmp,"setStatusBarColor #%x",color);
 dex_putString(0,tmp);
}

//�����ļ�
void share_file(char*title,char*file)
{
// if(filestate(file)==1)
 {
  char*tmp = malloc(sizeof(20+strlen(title)+strlen(file)));
  sprintf(tmp,"shareFile %s %s",title,file);
  dex_putString(0,tmp);
  free(tmp);
 }
}

//����ͼƬ
void share_image(char*title,char*image)
{
// if(filestate(image)==1)
 {
  char*tmp = malloc(sizeof(20+strlen(title)+strlen(image)));
  sprintf(tmp,"shareImage %s %s",title,image);
  dex_putString(0,tmp);
  free(tmp);
 }
}

//��������
void share_text(char*title,char*text)
{
 char*tmp = malloc(sizeof(20+strlen(title)+strlen(text)));
 sprintf(tmp,"shareText %s %s",title,text);
 dex_putString(0,tmp);
 free(tmp);
}

//��Ӧ���̵�
void goMarket(char *app)
{
 char tmp[200];
 sprintf(tmp, "market://details?id=%s", app);
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
}

//����QQ
void goQQ(char *qq)
{
char tmp[200];
 sprintf(tmp, "mqqwpa://im/chat?chat_type=wpa&uin=%s&version=1", qq);
 
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
}

//�鿴QQ����
void joinQQ(char *qq)
{
 char tmp[200];
 sprintf(tmp, "mqqapi://card/show_pslcard?src_type=internal&version=1&uin=%s&card_type=person&source=qrcode", qq);
 
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
            
}

//����QQȺ
void goQun(char *qun)
{
 char tmp[200];
 sprintf(tmp, "mqqwpa://im/chat?chat_type=group&uin=%s&version=1", qun);
 
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
}

//�鿴QQȺ����
void joinQun(char *qun)
{
 char tmp[200];
 sprintf(tmp, "mqqapi://card/show_pslcard?src_type=internal&version=1&uin=%s&card_type=group&source=qrcode", qun);
 
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
}



#endif


