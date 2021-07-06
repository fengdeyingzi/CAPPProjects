#ifndef __HTTPCLIENT_H__
#define __HTTPCLIENT_H__

#ifdef WIN32
#define _WIN32_WINNT 0x0600
#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock2.h>
#elif 1
#include <netinet/in.h>
#include <sys/socket.h>
#endif
#include "base.h"

typedef void (*HTTP_ONPROGRESS)(int32 pos);
typedef void (*HTTP_ONSUCCESS)(int32 ip, char *data, char *body);
typedef void (*HTTP_ONERROR)(int32 code);
typedef void (*test_test)(int32 data);
//数据缓冲区大小
#define BUFFER_MAX 1024 * 20

enum {
	HTTP_ERROR_NETINIT,
	HTTP_ERROR_HOST,
	HTTP_ERROR_SOCKET,	//socket创建失败
	HTTP_ERROR_CONNECT,
	HTTP_ERROR_SEND,
	HTTP_ERROR_RECV
};

enum {
	HTTP_PROGRESS_CONNECT = -2,
	HTTP_PROGRESS_SEND = -1,
	HTTP_PROGRESS_HEAD = 0
};

void http_init(void);
void http_getData(char *url, HTTP_ONPROGRESS onprogress, HTTP_ONSUCCESS onsuccess, HTTP_ONERROR onerror);
void http_postData(char *url,char *data, HTTP_ONPROGRESS onprogress, HTTP_ONSUCCESS onsuccess, HTTP_ONERROR onerror);
void http_exit(void);

#endif