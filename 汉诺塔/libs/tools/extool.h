#ifndef TOOL_H
#define TOOL_H
//手机CAPP隐藏功能部分集合
#include "../api/android.h"

//获取imei
char*get_imei()
{
 return dex_putString(0,"imei ");
}

//获取imsi
char*get_imsi()
{
 return dex_putString(0,"imsi ");
}

//获取CPU类型
char*get_cpuAbi()
{
 return dex_putString(0,"CPU_ABI ");
}

//获取安卓版本
char*get_sdkInt()
{
 return dex_putString(0,"SDK_INT ");
}

//设置状态栏颜色
void set_statusBarColor(int color)
{
 char tmp[100];
 sprintf(tmp,"setStatusBarColor #%x",color);
 dex_putString(0,tmp);
}

//分享文件
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

//分享图片
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

//分享文字
void share_text(char*title,char*text)
{
 char*tmp = malloc(sizeof(20+strlen(title)+strlen(text)));
 sprintf(tmp,"shareText %s %s",title,text);
 dex_putString(0,tmp);
 free(tmp);
}

//打开应用商店
void goMarket(char *app)
{
 char tmp[200];
 sprintf(tmp, "market://details?id=%s", app);
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
}

//拉起QQ
void goQQ(char *qq)
{
char tmp[200];
 sprintf(tmp, "mqqwpa://im/chat?chat_type=wpa&uin=%s&version=1", qq);
 
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
}

//查看QQ资料
void joinQQ(char *qq)
{
 char tmp[200];
 sprintf(tmp, "mqqapi://card/show_pslcard?src_type=internal&version=1&uin=%s&card_type=person&source=qrcode", qq);
 
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
            
}

//拉起QQ群
void goQun(char *qun)
{
 char tmp[200];
 sprintf(tmp, "mqqwpa://im/chat?chat_type=group&uin=%s&version=1", qun);
 
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
}

//查看QQ群资料
void joinQun(char *qun)
{
 char tmp[200];
 sprintf(tmp, "mqqapi://card/show_pslcard?src_type=internal&version=1&uin=%s&card_type=group&source=qrcode", qun);
 
 int in=in_createIntent();
 in_setData(in, tmp);
 startActivity(in);
}



#endif


