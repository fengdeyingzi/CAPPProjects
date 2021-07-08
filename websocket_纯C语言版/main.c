  //加载系统头文件base.h
#include "base.h"
#include "httpclient.h"
#include <pthread.h>
#include "exb.h"

void drawInfo(char *text){
    printf("%s\n",text);
    char *temp = NULL;
    rectst re;
    colorst co;
    re.x = 10;
    re.y = 10;
    re.w = SCRW;
    re.h = SCRH;
    co.r = 10;
    co.g = 10;
    co.b = 10;
    cls(240,240,240);
    temp = ex_coding(text,strlen(text),"UTF-8", "UTF-16BE");
    dtextex(temp, 10, 10, &re,&co, 1|2, 1);
    ref(0,0,SCRW,SCRH);
    free(temp);
}
int32 temp_pos = 0;
void http_onProgress(int32 pos) {
	char temp[100];
    // if(temp_pos != pos){
        sprintf(temp, "获取中 %d", pos);
	drawInfo(temp);
    temp_pos = pos;
    // }
	
}
void http_onSuccess(int32 ip, char *data, char *body) {
	drawInfo(body);
}

void http_onError(int32 err) {
	printf("获取出错 %d",err);
    drawInfo("获取出错");
}

void http_get(char *url){
    printf("http_get %s\n",url);
http_getData(url, http_onProgress, http_onSuccess, http_onError);
}

void http_post(char *url){
    printf("http_post %s\n",url);
http_postData(url,"id=1", http_onProgress, http_onSuccess, http_onError);
}

void logoc(int32 data){
    ref(0,0,SCRW,SCRH);
}



pthread_t thread_http;
int32 timer;
//入口函数，程序启动时开始执行
int init()
{
    thread_http = 1;
    printf("http_init\n");
    http_init();
    printf("pthread\n");
    drawInfo("获取中");
    timer = timercreate();
    pthread_create(&thread_http, NULL, (void *)http_post, (void *)"http://app.yzjlb.net/");

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

//应用退出函数，在应用退出时可做一些内存释放操作
int exitApp()
{
    http_exit();
    return 0;
}

