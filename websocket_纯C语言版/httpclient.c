
#ifdef WIN32
#define _WIN32_WINNT 0x0600
#include <WS2tcpip.h>
#include <Windows.h>
#include <winsock2.h>
#elif 1
#include <fcntl.h>
#include <linux/tcp.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif
#include <pthread.h>
// #include <errno.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/types.h>
// #include <unistd.h>

#include "array_state.h"
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
pthread_t thread_http;
pthread_t thread_ws;
int http_result;	   //与线程通信
int http_result_data;  //result内容
ARR_STATE *arr_websocket;

extern char *getHostByName(const char *host);
extern char *getUrlRoad(char *url);
extern char *getUrlHost(char *url);
int getUrlPort(char *url);
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
int readsocket(int s, char *buf, size_t len, int flags) {
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
	// printf("str2ip %s %x\n", strip, temp_ip);
	return temp_ip;
}

int client_entry(char *url) {
	// printf("client_entry %s\n", url);
	char *ip = NULL;

	int tl = 0;

	int i = 0;

	int32 temp_int = 0;
	char *temp_str;
	int32 content_len = 0;
	int32 temp_re = 0;
	char *host = getUrlHost(url);
	char *road = getUrlRoad(url);
	int32 port = getUrlPort(url);

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
			  // printf("getHost 3\n");
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
	server_sock.sin_port = htons(port);

	int ret = connect(sock, (struct sockaddr *)&server_sock, sizeof(server_sock));
	socket_state = 1;
	printf("connect %d %d\n", sock, ret);
	if (ret < 0) {
		// printf("connect failed...,errno is %d,errstring is %s\n", errno, strerror(errno));
		// lis_onerror(HTTP_ERROR_CONNECT);
		http_result = 3;
		http_result_data = HTTP_ERROR_CONNECT;
		// timerstart(timer_http, 1, HTTP_ERROR_CONNECT, timer_onError, 0);
		return -1;
	}
	printf("connect sercer success !\n");
	socket_state = 2;
	struct timeval timeout = {10, 0};  //10s
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval));
	//设置接收超时
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
	//设置接收超时时间
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(struct timeval));
	int write_len = writesocket(sock, send_buf, strlen(send_buf), 0);
	if (write_len != strlen(send_buf)) {
		printf("write 未完成 %d\n", write_len);
	}
	
	socket_state = 3;

	while (socket_state != -1) {
		char buf[4096] = {0};

		temp_int = readsocket(sock, buf, sizeof(buf), 0);
		if (temp_int > 0) {
			printf("buffer_append %d %s\n",temp_int, buffer_http->data);
			buffer_appendx(buffer_http, buf, temp_int);
			//判断header是否完成
			if (strstr(buffer_http->data, "\r\n\r\n")) {
				buffer_http->body = strstr(buffer_http->data, "\r\n\r\n") + 4;
				//读取头完成
				temp_str = strstr(buffer_http->header, "Content-Length");
				printf("!=null");
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

						// drawBody(buffer_http->body);
						socket_state = -1;
						break;
					} else {
						// lis_progress(100 * ((buffer_http->len - (buffer_http->body - buffer_http->data))) / buffer_http->body_len);
						http_result = 1;
						http_result_data = 100 * ((buffer_http->len - (buffer_http->body - buffer_http->data))) / buffer_http->body_len;

						// printf("headlen %d bodylen %d content_len %d\n", (buffer_http->body - buffer_http->data), (buffer_http->len - (buffer_http->body - buffer_http->data)), buffer_http->body_len);
					}
				}
			} else {
				// lis_progress(HTTP_PROGRESS_HEAD);
				http_result = 1;
				http_result_data = HTTP_PROGRESS_HEAD;
			}
		} else if(temp_int<0){
			printf("read err\n");
			break;
		}
	}
	printf("recv done\n");
	free(ip);
	ip = NULL;
	close_socket(sock);
	

	printf("http_exit\n");
	return 0;
}

void send_result(int result_type, int32 ws, char *msg, int error) {
	RESULT_DATA *result_data = (RESULT_DATA *)malloc(sizeof(RESULT_DATA));
	HTTP_WEBSOCKET *websocket = (HTTP_WEBSOCKET *)ws;
	memset(result_data, 0, sizeof(RESULT_DATA));
	result_data->result_type = result_type;
	result_data->ws = ws;
	if (msg != NULL) {
		result_data->msg = malloc(strlen(msg) + 2);
		strcpy(result_data->msg, msg);
	}
	result_data->error = error;
	// pthread_mutex_lock(&(websocket->lock));
	arr_add(arr_websocket, (int32)result_data);
	// pthread_mutex_unlock(&(websocket->lock));
}

//读取2字节
static int readShort(char *data, int index) {
	return ((data[index] & 0xff) << 8) | (data[index + 1] & 0xff);
}
static int readInt(char *data, int index) {
	return ((data[index + 0] & 0xff) << 24) | ((data[index + 1] & 0xff) << 16) | ((data[index + 2] & 0xff) << 8) | (data[index + 3] & 0xff);
}
static long readLongLong(char *data, int index) {
	return ((data[index + 4] & 0xff) << 24) | ((data[index + 5] & 0xff) << 16) | ((data[index + 6] & 0xff) << 8) | (data[index + 7] & 0xff);
}

//读取指定长度byte 并在byte后添加\0 需要释放内存
char *readBytes(char *data, int index, int len) {
	char *readData = malloc(len + 2);
	readData[len] = 0;
	readData[len + 1] = 0;
	memcpy(readData, data + index, len);
	return readData;
}

//读取帧 需要释放内存
char *readFrame(HTTP_WEBSOCKET *websocket) {
	//1字节
	int total_len = 0;	//帧的总长度
	int ptr = 0;
	int FIN = 0;			   //1 bit
	int RSV1, RSV2, RSV3 = 0;  //共3bit
	int opcode = 0;			   //4 bit
	//2字节
	int mask = 0;		   //1 bit
	long payload_len = 0;  //7 bit | 7+16 bit | 7+64 bit
	int MaskingKey = 0;	   //0 | 4 bytes 掩码密钥，所有从客户端发送到服务端的帧都包含一个 32bits 的掩码（如果mask被设置成1），否则为0。一旦掩码被设置，所有接收到的 payload data 都必须与该值以一种算法做异或运算来获取真实值。
	char *payload_data;
	char *extension_data;
	int extension_len = 0;
	char *data = websocket->buffer->data;
	if (websocket->buffer->len <= 2)
		return NULL;
	FIN = (data[0] & 0x80) >> 7;
	RSV1 = (data[0] & 0x40) >> 6;
	RSV2 = (data[0] & 0x20) >> 5;
	RSV3 = (data[0] & 0x10) >> 4;
	opcode = (data[0] & 0x8);
	mask = (data[1] & 0x80) >> 7;
	payload_len = (data[1] & 0x7f);
	ptr = 2;
	if (payload_len == 0x7e) {
		if (websocket->buffer->len <= ptr + 2)
			return NULL;
		//接下来的2字节
		payload_len = readShort(data, 2);
		ptr += 2;
	} else if (payload_len == 0x7f) {
		if (websocket->buffer->len <= ptr + 8)
			return NULL;
		//接下来的8字节
		payload_len = readLongLong(data, 2);
		ptr += 8;
	}
	if (mask == 1) {  //存在掩码
		total_len = (int)(ptr + 4 + payload_len + extension_len);
		if (websocket->buffer->len < total_len)
			return NULL;
		MaskingKey = readInt(data, ptr);
		ptr += 4;
	} else {
		total_len = (int)(ptr + payload_len + extension_len);
		if (websocket->buffer->len < total_len)
			return NULL;
	}
	//读取数据
	payload_data = readBytes(data, ptr, (int)payload_len);
	buffer_clear(websocket->buffer);  //读取一帧成功 丢弃帧

	return payload_data;
}

int socket_set_keepalive(int fd) {
	int ret, flag, alive, idle, cnt, intv;

	/* Set: use keepalive on fd */
	alive = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &alive, sizeof alive) != 0) {
		printf("Set keepalive error: .\n");
		return -1;
	}

	/* 10秒钟无数据，触发保活机制，发送保活包 */
	idle = 10;
	if (setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &idle, sizeof idle) != 0) {
		printf("Set keepalive idle error: .\n");
		return -1;
	}

	/* 如果没有收到回应，则5秒钟后重发保活包 */
	intv = 5;
	if (setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &intv, sizeof intv) != 0) {
		printf("Set keepalive intv error: .\n");
		return -1;
	}

	/* 连续3次没收到保活包，视为连接失效 */
	cnt = 3;
	if (setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &cnt, sizeof cnt) != 0) {
		printf("Set keepalive cnt error: .\n");
		return -1;
	}

	return 0;
}

int client_ws(HTTP_WEBSOCKET *websocket) {
	printf("websocket_client %s\n", websocket->url);

	// int timeout = 1000;
	int i = 0;

	int32 temp_int = 0;
	char *temp_str;
	int32 content_len = 0;
	int32 temp_re = 0;
	int isOpen = FALSE;
	char *host = getUrlHost(websocket->url);
	char *road = getUrlRoad(websocket->url);
	int32 port = getUrlPort(websocket->url);

	char *ipstr = getHostByName((const char *)host);
	free(road);
	free(host);

	// printf("host=%s road=%s ip=%s\n", host, road,ip);

	if (ipstr == NULL) {
		//   drawInfo("getHostByName失败");
		// lis_onerror(HTTP_ERROR_HOST);
		send_result(RESULT_WS_ONERROR, (int32)websocket, NULL, HTTP_ERROR_HOST);
		// timerstart(timer_http, 1, HTTP_ERROR_HOST, timer_onError, 0);
		return -1;
	} else {  //直接获取ip
			  // printf("getHost 3");
	}

	init_socket();
	struct sockaddr_in server_sock;
	int32 sock = socket(AF_INET, SOCK_STREAM, 0);
	websocket->socket = sock;
	memset(&server_sock, 0, sizeof(server_sock));
	server_sock.sin_family = AF_INET;
#ifdef WIN32
	inet_pton(AF_INET, ipstr, &server_sock.sin_addr);
#else
	server_sock.sin_addr.s_addr = ip_htonl(str2ip(ipstr));
#endif
	server_sock.sin_port = htons(port);
	// printf("connect 1\n");
	int ret = connect(sock, (struct sockaddr *)&server_sock, sizeof(server_sock));
	// printf("connect %d %d\n", sock, ret);
	if (ret < 0) {
		// printf("connect failed...,errno is %d,errstring is %s\n", errno, strerror(errno));
		send_result(RESULT_WS_ONERROR, (int32)websocket, NULL, HTTP_ERROR_CONNECT);
		// timerstart(timer_http, 1, HTTP_ERROR_CONNECT, timer_onError, 0);
		return -1;
	}
	// printf("connect sercer success !\n");
	int write_len = writesocket(sock, websocket->send_buf, strlen(websocket->send_buf), 0);
	if (write_len != strlen(websocket->send_buf)) {
		printf("write 未完成 %d\n", write_len);
	}

	//设置接收超时时间
	// setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
	//设置发送超时
	struct timeval timeout = {5, 0};  //5s
	setsockopt(websocket->socket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(struct timeval));
	//设置接收超时
	setsockopt(websocket->socket, SOL_SOCKET, SO_RCVLOWAT, (char *)&timeout, sizeof(struct timeval));
	setsockopt(websocket->socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));
	setsockopt(websocket->socket, SOL_SOCKET, SO_TIMESTAMP, (char *)&timeout, sizeof(struct timeval));
	//设置异步模式

	// if((ret = fcntl(websocket->socket, F_GETFL, 0)) < 0){
	// 	printf("  socket unblock err1.");
	// }
	// if (fcntl(websocket->socket, F_SETFL, ret|O_NONBLOCK) < 0){
	// 	printf("  socket unblock err2.");
	// }
	socket_set_keepalive(websocket->socket);
	// printf("get file size:%d\n", filesize);
	while (websocket->socket_state) {
		char buf[4096] = {0};
		// printf("--while \r\n");
		if (websocket->socket >= 0)
			temp_int = readsocket(websocket->socket, buf, sizeof(buf), 0);	//MSG_DONTWAIT MSG_WAITALL
		// printf("--read %d\r\n", temp_int);
		if (temp_int >= 0) {
			for (int ii = 0; ii < temp_int; ii++) {
				buffer_append(websocket->buffer, buf[ii]);
				//判断header是否完成
				if (!isOpen) {
					if (strstr(websocket->buffer->data, "\r\n\r\n")) {
						buffer_clear(websocket->buffer);
						isOpen = TRUE;
						send_result(RESULT_WS_ONOPEN, (int32)websocket, NULL, 0);
					}
				} else {
					char *msgData = readFrame(websocket);
					if (msgData != NULL) {
						// printf("--------- 读取帧成功 %s\n ", msgData);
						send_result(RESULT_WS_ONMESSAGE, (int32)websocket, msgData, 0);
						free(msgData);
					}
				}
			}

		} else {
			// printf("recv err\n");
			send_result(RESULT_WS_ONERROR, (int32)websocket, NULL, 0);
			break;
		}
	}
	// printf("websocket recv done\n");
	free(ipstr);
	ipstr = NULL;
	send_result(RESULT_WS_ONCLOSE, (int32)websocket, NULL, 0);

	printf("websocket exit\n");
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
			if (url[i] == '/' || url[i] == ':') {
				end = i;
				goto out_host;
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

//通过url获取port 需free
int getUrlPort(char *url) {
	int len = strlen(url);

	int i = 0;
	int type = 0;
	int start = 0;
	int end = len;
	int port = 80;

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
			if (url[i] == ':') {
				start = i + 1;
				type = 4;
				// printf("atoi \n");
				port = atoi(url + start);
				goto out_road;
			} else if (url[i] == '/') {
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

	return port;
}

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
	printf("gethostbyname 2\n");
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
	HTTP_WEBSOCKET *ws = NULL;
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
	while (arr_getlen(arr_websocket) > 0) {
		RESULT_DATA *result_data = NULL;
		// pthread_mutex_init(&(ws->lock), NULL);
		// pthread_mutex_lock(&(ws->lock));
		result_data = (RESULT_DATA *)arr_get(arr_websocket);
		// pthread_mutex_unlock(&(ws->lock));
		if (result_data->result_type == RESULT_WS_ONOPEN) {
			ws = (HTTP_WEBSOCKET *)result_data->ws;
			if (ws->onOpen)
				ws->onOpen((int32)ws);
		} else if (result_data->result_type == RESULT_WS_ONMESSAGE) {
			ws = (HTTP_WEBSOCKET *)result_data->ws;
			if (ws->onMessage)
				ws->onMessage((int32)ws, result_data->msg);
			free(result_data->msg);
		} else if (result_data->result_type == RESULT_WS_ONCLOSE) {
			ws = (HTTP_WEBSOCKET *)result_data->ws;
			if (ws->onClose)
				ws->onClose((int32)ws);
		} else if (result_data->result_type == RESULT_WS_ONERROR) {
			ws = (HTTP_WEBSOCKET *)result_data->ws;
			if (ws->onError)
				ws->onError((int32)ws, result_data->error);
		}

		free(result_data);
	}
}

//初始化
void http_init(void) {
	net_init_type = init_socket();
	timer_http = timercreate();
	send_buf = (char *)malloc(255);
	buffer_http = buffer_create();
	timerstart(timer_http, 100, 1, timer_onHttpData, 1);
	thread_http = 0;

	arr_websocket = arr_create();
}

//获取http数据 参数：url 获取进度 加载成功 加载失败
//进度 -2 connect -1 send 0 接收head成功 0+ 接收body
void http_getData(char *url, HTTP_ONPROGRESS onprogress, HTTP_ONSUCCESS onsuccess, HTTP_ONERROR onerror) {
	lis_progress = onprogress;
	lis_onsuccess = onsuccess;
	lis_onerror = onerror;
	thread_http = 1;
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
		pthread_create(&thread_http, NULL, (void *)client_entry, (void *)url);
		// client_entry(url);
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
	thread_http = 1;
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
		pthread_create(&thread_http, NULL, (void *)client_entry, (void *)url);
		// client_entry(url);
	}
}

int32 http_ws(char *url, WS_ONOPEN onOpen, WS_ONMESSAGE onMessage, WS_ONCLOSE onClose, WS_ONERROR onError) {
	HTTP_WEBSOCKET *ws = (HTTP_WEBSOCKET *)malloc(sizeof(HTTP_WEBSOCKET));
	char *key = "puVOuWb7rel6z2AVZBKnfw==";

	memset(ws, 0, sizeof(HTTP_WEBSOCKET));
	int len = strlen(url);
	printf("http_ws %d\n", 1);
	ws->url = malloc(len + 2);
	strcpy(ws->url, url);
	printf("http_ws %d\n", 2);
	ws->buffer = buffer_create();
	printf("http_ws %d\n", 3);
	ws->port = getUrlPort(url);
	printf("http_ws %d\n", 4);
	char *host = getUrlHost(url);
	printf("http_ws %d\n", 5);
	char *road = getUrlRoad(url);
	printf("http_ws %d\n", 6);
	ws->socket_state = 1;
	ws->onOpen = onOpen;
	ws->onMessage = onMessage;
	ws->onClose = onClose;
	ws->onError = onError;
	ws->send_buf = malloc(300);
	ws->send_len = 0;
	printf("http_ws %d\n", 7);
	ws->key = malloc(strlen(key) + 2);
	strcpy(ws->key, key);
	printf("http_ws %d\n", 8);

	memset(send_buf, '\0', 255);

	sprintf(ws->send_buf, "GET %s HTTP/1.1\r\nConnection:Upgrade\r\nHost:%s\r\nOrigin:null\r\nSec-WebSocket-Extensions:x-webkit-deflate-frame\r\nSec-WebSocket-Key:%s\r\nSec-WebSocket-Version:13\r\nUpgrade:websocket\r\n\r\n", road, host, key);
	printf("send %s", ws->send_buf);
	free(road);
	free(host);
	pthread_mutex_init(&(ws->lock), NULL);
	pthread_mutex_lock(&(ws->lock));
	pthread_mutex_unlock(&(ws->lock));
	thread_ws = 2;
	pthread_create(&thread_ws, NULL, (void *)client_ws, (void *)ws);
	return (int32)ws;
}

void writeShort(char *data, int index, int num) {
	data[index] = (char)((num & 0xff00) >> 8);
	data[index + 1] = (char)(num & 0xff);
}

void http_ws_send(int32 ws, char *text) {
	HTTP_WEBSOCKET *websocket = (HTTP_WEBSOCKET *)ws;
	if (ws == 0)
		return;
	int isMask = 1;
	char maskKey[4] = {0x66, 0x66, 0x66, 0x66};
	char temp1, temp2;

	char *payloadData = text;
	char *sendData = NULL;
	int FIN = 1;  //1 bit
	int opencode = 1;
	int total_len = 0;
	int payload_len = strlen(payloadData);
	int ptr = 0;
	total_len = payload_len + 2;
	if (payload_len > 125) {
		total_len += 2;
	}
	if (isMask == 1) {
		total_len += 4;
	}
	sendData = malloc(total_len);
	sendData[ptr] = (char)((FIN << 7) | opencode);
	ptr += 1;
	int mask = 1;

	if (payload_len < 126) {
		sendData[ptr++] = (char)((isMask << 7) | payload_len);

	} else if (payload_len < 65536) {
		sendData[ptr++] = (char)((isMask << 7) | 126);
		writeShort(sendData, ptr, payload_len);
		ptr += 2;
	}
	if (isMask == 1) {
		sendData[ptr++] = maskKey[0];
		sendData[ptr++] = maskKey[1];
		sendData[ptr++] = maskKey[2];
		sendData[ptr++] = maskKey[3];
		for (int i = 0, count = 0; i < payload_len; i++) {
			temp1 = maskKey[count];
			temp2 = payloadData[i];
			sendData[ptr++] = (char)(((~temp1) & temp2) | (temp1 & (~temp2)));
			count++;
			if (count >= 4)
				count = 0;
		}

	} else {
		for (int i = 0; i < payload_len; i++) {
			sendData[ptr++] = payloadData[i];
		}
	}

	printf("----------- 发送 %s", text);
	// socket_w(sendData);
	int write_len = writesocket(websocket->socket, sendData, total_len, 0);
	if (write_len != total_len) {
		printf("write 未完成 %d\n", write_len);
	}

	free(sendData);
}

//关闭websocket
void http_ws_exit(int32 ws) {
	if (ws == 0)
		return;
	HTTP_WEBSOCKET *websocket = (HTTP_WEBSOCKET *)ws;
	websocket->socket_state = 0;
	if (websocket->socket >= 0) {
		printf("关闭socket %d\n", websocket->socket);
		close_socket(websocket->socket);
		websocket->socket = -1;
	}
	if (thread_ws) {
		pthread_join(thread_ws, NULL);
		thread_ws = 0;
	}

	if (websocket->key) {
		free(websocket->key);
		websocket->key = NULL;
	}
	if (websocket->url) {
		free(websocket->url);
		websocket->url = NULL;
	}
	if (websocket->buffer) {
		buffer_free(websocket->buffer);
		websocket->buffer = NULL;
	}
	pthread_mutex_destroy(&(websocket->lock));

	free(websocket);
	websocket = NULL;
	printf("ws exit ok\n");
}

//释放定时器 释放内存
void http_exit(void) {
	socket_state = -1;
	// printf("http_exit 1\n");
	if (thread_http) {
		pthread_join(thread_http, NULL);
		thread_http = 0;
	}

	// printf("http_exit 2\n");
	if (timer_http) {
		timer_onHttpData(0);  //退出前先将事件执行完
		timerstop(timer_http);
		timerdel(timer_http);
		timer_http = 0;
	}
	// printf("http_exit 3\n");
	if (arr_websocket) {
		arr_free(arr_websocket);
		arr_websocket = NULL;
	}
	if (buffer_http) {
		buffer_free(buffer_http);
		buffer_http = NULL;
	}
	if (send_buf) {
		free(send_buf);
		send_buf = NULL;
	}
	// printf("http_exit 4\n");

	// closeNetwork();
}