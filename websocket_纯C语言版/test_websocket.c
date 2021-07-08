  //加载系统头文件base.h
#include "base.h"
#include "httpclient.h"
#include "exb.h"
int32 websocket;
int32 timer_active;
int isSend;
void drawInfo(char *text){
    // printf("%s\n",text);
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


void ws_onOpen(int32 ws) {
	printf("ws_onOpen\n");
}

void ws_onMessage(int32 ws,char *msg){
    // printf("onMessage %s\n",msg);
    drawInfo(msg);
    if(!isSend){
        http_ws_send(ws, "{\"action\":\"setname\", \"data\":\"test\"}");
        isSend = TRUE;
    }
    
}

void ws_onClose(int32 ws){
    printf("ws_onClose\n");
    drawInfo("ws_onClose");
    websocket = 0;
}

void ws_onError(int32 ws,int error){
    printf("ws_onError %d\n",error);
    websocket = 0;
}


void logoc_active(int32 data){
    http_ws_send(websocket, "#");
}


void logoc(int32 data){
    ref(0,0,SCRW,SCRH);
}




int32 timer;
//入口函数，程序启动时开始执行
int init()
{
    
    isSend = FALSE;
    printf("http_init\n");
    cls(240,240,240);
    ref(0,0,SCRW,SCRH);
    http_init();
    
    drawInfo("获取中");
    
    websocket = http_ws("ws://websocket.yzjlb.net:2022/socket", ws_onOpen, ws_onMessage, ws_onClose, ws_onError);
    timer_active = timercreate();
    timerstart(timer_active, 5000, websocket, logoc_active, 1);
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
        drawInfo("退出中");
        http_ws_exit(websocket);
        websocket = 0;
        drawInfo("socket退出");
        http_exit();
        drawInfo("http退出");
        
            exit();
            break;
        case _MENU:
            break;
        }
    }
    if(MS_UP == type){
        printf("退出\n");
        http_ws_exit(websocket);
        websocket = 0;
        http_exit();
        
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
    timerdel(timer_active);
    return 0;
}

