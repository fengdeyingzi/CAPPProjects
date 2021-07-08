
#ifdef WIN32
#define _WIN32_WINNT 0x0600
#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock2.h>
#elif 1
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
#endif
// #include <errno.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/types.h>
// #include <unistd.h>

#include "buffer.h"
#include "httpclient.h"

#define PORT 80
#define SERVER_IP "111.123.50.143"
#define _BACKLOG_ 10

int32 net_init_type;
char *send_buf = NULL;
int32 send_len = 0;
char *local_ip = "127.0.0.1";
int32 socket_state;	 // socket状态 0 gethost 1 connect 2 send 3 recv 4 ok -1

STRING_BUFFER *buffer_http;
HTTP_ONPROGRESS lis_progress;
HTTP_ONSUCCESS lis_onsuccess;
HTTP_ONERROR lis_onerror;
int32 timer_http;
int http_result;	   //与线程通信
int http_result_data;  //result内容

extern char *getHostByName(const char *host);
extern char *getUrlRoad(char *url);
extern char *getUrlHost(char *url);
void timer_onHttpData(int32 data);

#ifdef WIN32
int init_socket() {
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) {
		return -1;
	}
	return 0;
}
int writesocket(int s, const char *buf, int len, int flags) {
	return send(s, buf, len, flags);
}
int readsocket(int s, char *buf, int len, int flags) {
	return recv(s, buf, len, flags);
}
void close_socket(int s) {
	closesocket(s);
	WSACleanup();
}
#elif 1
int init_socket() {
	return 0;
}
int writesocket(int s, const char *buf, int len, int flags) {
	// return write(s, buf, len);
	return send(s, buf, len, flags);
}
int readsocket(int s, char *buf, int len, int flags) {
	// return read(s, buf, len);
	return recv(s, buf, len, flags);
}
void close_socket(int s) {
	close(s);
}
#endif
int32 ip_htonl(int32 ip) {
	return ((ip >> 24) & 0xff) | ((ip >> 8) & 0xff00) | ((ip << 8) & 0xff0000) | ((ip << 24) & 0xff000000);
}
int32 str2ip(char *strip) {
	char temp[32];
	strcpy(temp, strip);
	int type = 0;
	int i = 0;
	int start = 0;
	int len = strlen(strip);
	int32 temp_ip;
	for (i = 0; i < len; i++) {
		switch (type) {
		case 0:
			if (temp[i] == '.' || i == len - 1) {
				temp[i] = 0;
				temp_ip |= atoi(temp + start);
				start = i + 1;
				if (i != len - 1)
					temp_ip = temp_ip << 8;
			}
			break;

		default:
			break;
		}
	}
	printf("str2ip %s %x", strip, temp_ip);
	return temp_ip;
}

int client_entry(char *url) {
	printf("client_entry %s", url);
	char *ip = NULL;

	int tl = 0;

	int i = 0;
	
	int32 temp_int = 0;
	char *temp_str;
	int32 content_len = 0;
	int32 temp_re = 0;
	char *host = getUrlHost(url);
	char *road = getUrlRoad(url);

	ip = getHostByName((const char *)host);
	free(road);
	free(host);

	// printf("host=%s road=%s ip=%s\n", host, road,ip);

	if (ip == NULL) {
		//   drawInfo("getHostByName失败");
		// lis_onerror(HTTP_ERROR_HOST);
		http_result = 3;
		http_result_data = HTTP_ERROR_HOST;
		// timerstart(timer_http, 1, HTTP_ERROR_HOST, timer_onError, 0);
		return -1;
	} else {  //直接获取ip
		printf("getHost 3");
	}

	init_socket();
	struct sockaddr_in server_sock;
	int32 sock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server_sock, 0, sizeof(server_sock));
	server_sock.sin_family = AF_INET;
#ifdef WIN32
	inet_pton(AF_INET, ip, &server_sock.sin_addr);
#else
	server_sock.sin_addr.s_addr = ip_htonl(str2ip(ip));
#endif
	server_sock.sin_port = htons(PORT);

	int ret = connect(sock, (struct sockaddr *)&server_sock, sizeof(server_sock));
	printf("connect %d %d\n", sock, ret);
	if (ret < 0) {
		// printf("connect failed...,errno is %d,errstring is %s\n", errno, strerror(errno));
		// lis_onerror(HTTP_ERROR_CONNECT);
		http_result = 3;
		http_result_data = HTTP_ERROR_CONNECT;
		// timerstart(timer_http, 1, HTTP_ERROR_CONNECT, timer_onError, 0);
		return -1;
	}
	struct timeval timeout = {10, 0};  //10s
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval));
	//设置接收超时
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
	//设置接收超时时间
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(struct timeval));
	printf("connect sercer success !\n");
	int write_len = writesocket(sock, send_buf, strlen(send_buf), 0);
	if (write_len != strlen(send_buf)) {
		printf("write 未完成 %d\n", write_len);
	}

	

	
	while (1) {
		char buf[4096] = {0};
		
		temp_int = readsocket(sock, buf, sizeof(buf), 0);
		if (temp_int > 0) {
			
			buffer_appendx(buffer_http, buf, temp_int);
			printf("read %d %d\n",temp_int,buffer_http->len);
			//判断header是否完成
			if (strstr(buffer_http->data, "\r\n\r\n")) {
				buffer_http->body = strstr(buffer_http->data, "\r\n\r\n") + 4;
				//读取头完成
				temp_str = strstr(buffer_http->header, "Content-Length");
				printf("header read ok");
				if (temp_str != NULL && (strstr(temp_str, "\r\n") != NULL)) {
					printf("getline_value begin\n");
					temp_str = getline_value(temp_str);
					printf("getline_value %s\n", temp_str);
					content_len = atoi(temp_str);
					buffer_http->body_len = content_len;
					printf("atoi %d\n", content_len);
					free(temp_str);

					temp_int = isContentSuccess(buffer_http->data, content_len);
					if (temp_int) {
						sock = -1;
						buffer_http->body = strstr(buffer_http->data, "\r\n\r\n");
						buffer_http->body += 4;
						printf("http success %s \n", buffer_http->body);
						// drawInfo("http获取成功");
						// lis_onsuccess(local_ip, buffer_http->data, buffer_http->body);
						http_result = 2;
						http_result_data = 0;
						// timerstart(timer_http, 1, local_ip, timer_onSuccess, 0);
						// drawBody(buffer_http->body);
						socket_state = -1;
						break;
					} else {
						// lis_progress(100 * ((buffer_http->len - (buffer_http->body - buffer_http->data))) / buffer_http->body_len);
						http_result = 1;
						http_result_data = 100 * ((buffer_http->len - (buffer_http->body - buffer_http->data))) / buffer_http->body_len;
						// timerstart(timer_http, 1, 100 * ((buffer_http->len - (buffer_http->body - buffer_http->data))) / buffer_http->body_len, timer_onProgress, 0);
						printf("headlen %d bodylen %d content_len %d\n", (buffer_http->body - buffer_http->data), (buffer_http->len - (buffer_http->body - buffer_http->data)), buffer_http->body_len);
					}
				}
			} else {
				// lis_progress(HTTP_PROGRESS_HEAD);
				http_result = 1;
				http_result_data = HTTP_PROGRESS_HEAD;
				// timerstart(timer_http, 1, HTTP_PROGRESS_HEAD, timer_onProgress, 0);
			}
		} else if(temp_int<0) {
			break;
		}
	}
	printf("recv done\n");

	close_socket(sock);
	return 0;
}

void print_ip(int32 ip) {
	unsigned char *data = (unsigned char *)&ip;
	printf("ip:%d.%d.%d.%d\n", data[3], data[2], data[1], data[0]);
}

//通过url获取host 需free
char *getUrlHost(char *url) {
	int len = strlen(url);
	char *host = malloc(len);
	int i = 0;
	int type = 0;
	int start = 0;
	int end = len;
	memset(host, '\0', len);
	while (url[i]) {
		switch (type) {
		case 0:
			if (url[i] == ':') {
				type = 1;
			}
			break;
		case 1:
			if (url[i] == '/') {
				type = 2;
			} else {
				goto out_host;
			}
			break;
		case 2:
			if (url[i] == '/') {
				start = i + 1;
				type = 3;
			} else {
				goto out_host;
			}
			break;
		case 3:
			if (url[i] == '/') {
				end = i;
			}
			break;
		default:
			break;
		}

		i++;
	}
out_host:
	if (start > 0 && end > 0) {
		memcpy(host, url + start, end - start);
		return host;
	}
	free(host);
	return NULL;
}

//通过url获取路由 需free
char *getUrlRoad(char *url) {
	int len = strlen(url);
	char *host = malloc(len);
	int i = 0;
	int type = 0;
	int start = 0;
	int end = len;
	memset(host, '\0', len);
	while (url[i]) {
		switch (type) {
		case 0:
			if (url[i] == ':') {
				type = 1;
			}
			break;
		case 1:
			if (url[i] == '/') {
				type = 2;
			} else {
				goto out_road;
			}
			break;
		case 2:
			if (url[i] == '/') {
				type = 3;
			} else {
				goto out_road;
			}
			break;
		case 3:
			if (url[i] == '/') {
				start = i;
				type = 4;
				goto out_road;
			}
			break;
		case 4:

			break;
		default:
			break;
		}
		if (i == len - 1) {
			start = -1;
			goto out_road;
		}
		i++;
	}
out_road:
	if (start > 0 && end > 0) {
		memcpy(host, url + start, len);
		return host;
	} else {
		memcpy(host, "/", 1);
		return host;
	}
	free(host);
	return NULL;
}

/*
int32 getHostByName(const char *host) {
	char **pptr;
	struct hostent *hptr;
	char ipstr[64];
	int32 temp_ip=0;
	int err;
	int32 ret;
#if defined(WIN32)
	struct sockaddr_in in;
#endif
	

	printf("getHostByName(%s)\n", host);

	//查询DNS
	if ((hptr = gethostbyname(host)) == NULL) {
		printf(" error host!\n");
		return NULL;
	}

	//主机规范名
	printf(" official hostname:%s\n", hptr->h_name);

	//获取主机别名列表char *[]
	for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
		printf("  alias:%s\n", *pptr);

	//IP类型
	switch (hptr->h_addrtype) {
	case AF_INET:
	case AF_INET6: {
#if defined(WIN32)
		memcpy(&in.sin_addr, hptr->h_addr, sizeof(hptr->h_addr));
		printf(" first address: %s\n", inet_ntoa(in.sin_addr));
#else
// if (hptr->h_addr_list[0] != NULL) {
//                 struct in_addr addr;
//                 addr.s_addr = *(u_long *)hptr->h_addr_list[0];
//                 // printf("%d\n", addr.S_un.S_addr);
//                 printf("getHost %s\n", inet_ntoa(addr));
//                 ret = ntohl(addr.S_un.S_addr);
//                 emu_requestCallback(CALLBACK_GETHOSTBYNAME, ret);
//             }


		// printf(" first address: %s\n",
		// 	   inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str)));
#endif
		printf("for\n");
		pptr = hptr->h_addr_list;  //IP地址列表 char*[]
		for (; *pptr != NULL; pptr++) {
#if defined(WIN32)
			host = inet_ntoa(in.sin_addr);
			strcpy(ipstr, inet_ntoa(in.sin_addr));
			printf("  address:%s\n", inet_ntoa(in.sin_addr));
#else
			sprintf(ipstr,"%d.%d.%d.%d\n", *(*pptr),*((*pptr)+1),*((*pptr)+2),*((*pptr)+3));
			temp_ip = ((*(*pptr))<<24) | ((*((*pptr)+1))<<16) | ((*((*pptr)+2))<<8) | (*((*pptr)+3));
			printf("address:%s\n",ipstr);
			break;
            // printf("address : %s\n", inet_ntoa(addr));
			// host = inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
			// printf("  address:%s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
#endif
		}

		memcpy(&ret, hptr->h_addr, 4);

		break;
	}

	default:
		printf(" unknown address type\n");
		break;
	}
	return temp_ip;
}
*/

char *getHostByName(const char *host) {
	char **pptr;
	struct hostent *hptr;
	char *ipstr = malloc(64);
	int err;
	int32 ret;
#if defined(WIN32)
	struct sockaddr_in in;
#endif

	printf("getHostByName(%s)\n", host);

	//查询DNS
	if ((hptr = gethostbyname(host)) == NULL) {
		printf(" error host!\n");
		return NULL;
	}

	//主机规范名
	printf(" official hostname:%s\n", hptr->h_name);

	//获取主机别名列表char *[]
	for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
		printf("  alias:%s\n", *pptr);

	//IP类型
	switch (hptr->h_addrtype) {
	case AF_INET:
	case AF_INET6: {
#if defined(WIN32)
		memcpy(&in.sin_addr, hptr->h_addr, sizeof(hptr->h_addr));
		printf(" first address: %s\n", inet_ntoa(in.sin_addr));
#else
		// if (hptr->h_addr_list[0] != NULL) {
		//                 struct in_addr addr;
		//                 addr.s_addr = *(u_long *)hptr->h_addr_list[0];
		//                 // printf("%d\n", addr.S_un.S_addr);
		//                 printf("getHost %s\n", inet_ntoa(addr));
		//                 ret = ntohl(addr.S_un.S_addr);
		//                 emu_requestCallback(CALLBACK_GETHOSTBYNAME, ret);
		//             }

		// printf(" first address: %s\n",
		// 	   inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str)));
#endif
		printf("for\n");
		pptr = hptr->h_addr_list;  //IP地址列表 char*[]
		for (; *pptr != NULL; pptr++) {
#if defined(WIN32)
			host = inet_ntoa(in.sin_addr);
			strcpy(ipstr, inet_ntoa(in.sin_addr));
			printf("  address:%s\n", inet_ntoa(in.sin_addr));
#else
			sprintf(ipstr, "%d.%d.%d.%d\n", *(*pptr), *((*pptr) + 1), *((*pptr) + 2), *((*pptr) + 3));
			host = ipstr;
			printf("address:%s\n", ipstr);
			break;
			// printf("address : %s\n", inet_ntoa(addr));
			// host = inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str));
			// printf("  address:%s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
#endif
		}

		memcpy(&ret, hptr->h_addr, 4);

		break;
	}

	default:
		printf(" unknown address type\n");
		break;
	}
	return ipstr;
}

int32 netWorkCb(int32 result) {
	net_init_type = result;
	printf("init network cb %d", result);
	return 0;
}

void timer_onHttpData(int32 data) {
	if (http_result) {
		if (http_result == 1) {
			lis_progress(http_result_data);
		} else if (http_result == 2) {
			lis_onsuccess(local_ip, buffer_http->data, buffer_http->body);
		} else if (http_result == 3) {
			lis_onerror(http_result_data);
		}
		http_result = 0;
	}
}

//初始化
void http_init(void) {
	net_init_type = init_socket();
	timer_http = timercreate();
	send_buf = (char *)malloc(255);
	buffer_http = buffer_create();
	timerstart(timer_http, 100, 1, timer_onHttpData, 1);
}

//获取http数据 参数：url 获取进度 加载成功 加载失败
//进度 -2 connect -1 send 0 接收head成功 0+ 接收body
void http_getData(char *url, HTTP_ONPROGRESS onprogress, HTTP_ONSUCCESS onsuccess, HTTP_ONERROR onerror) {
	lis_progress = onprogress;
	lis_onsuccess = onsuccess;
	lis_onerror = onerror;
	send_len = 0;
	buffer_clear(buffer_http);
	char *host = getUrlHost(url);
	char *road = getUrlRoad(url);
	memset(send_buf, '\0', 255);
	sprintf(send_buf, "GET %s HTTP/1.1\r\nHost:%s\r\n\r\n", road, host);
	free(road);
	free(host);
	printf("send %s\n", send_buf);

	if (net_init_type != 0) {
		// drawInfo("net未初始化成功");
		// lis_onerror(HTTP_ERROR_NETINIT);
		http_result = 2;
		http_result_data = HTTP_ERROR_NETINIT;
		// timerstart(timer_http, 1, HTTP_ERROR_NETINIT, timer_onError,0);
	} else {
		client_entry(url);
	}
}

//获取http数据 参数：url 获取进度 加载成功 加载失败
//进度 -2 connect -1 send 0 接收head成功 0+ 接收body
void http_postData(char *url, char *data, HTTP_ONPROGRESS onprogress, HTTP_ONSUCCESS onsuccess, HTTP_ONERROR onerror) {
	lis_progress = onprogress;
	lis_onsuccess = onsuccess;
	lis_onerror = onerror;
	send_len = 0;
	buffer_clear(buffer_http);
	char *host = getUrlHost(url);
	char *road = getUrlRoad(url);
	memset(send_buf, '\0', 255);
	sprintf(send_buf, "POST %s HTTP/1.1\r\nHost:%s\r\nContent-Length:%d\r\n\r\n%s", road, host, strlen(data), data);
	printf("send %s", send_buf);
	free(road);
	free(host);

	if (net_init_type != 0) {
		// drawInfo("net未初始化成功");
		// lis_onerror(HTTP_ERROR_NETINIT);
		http_result = 2;
		http_result_data = HTTP_ERROR_NETINIT;
		// timerstart(timer_http, 1, HTTP_ERROR_NETINIT, timer_onError,0);
	} else {
		client_entry(url);
	}
}

//释放定时器 释放内存
void http_exit(void) {
	if (buffer_http) {
		buffer_free(buffer_http);
		buffer_http = NULL;
	}
	if (send_buf) {
		free(send_buf);
		send_buf = NULL;
	}
	if (timer_http) {
		timerstop(timer_http);
		timerdel(timer_http);
		timer_http = 0;
	}
	// closeNetwork();
}