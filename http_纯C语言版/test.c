#include "httpclient.h"
#include <stdio.h>
#include <stdlib.h>


void drawInfo(char *text){
    printf("%s\n",text);
}

void http_onProgress(int32 pos) {
	char temp[100];
	sprintf(temp, "获取中 %d", pos);
	drawInfo(temp);
}
void http_onSuccess(int32 ip, char *data, char *body) {
	drawInfo(body);
}

void http_onError(int32 err) {
	drawInfo("获取出错");
}


int main() {
	// init_socket();
	//server_entry();
	// client_entry("GET /index.php HTTP/1.1\r\nHost:app.yzjlb.net\r\n\r\n\r\n");
    http_init();
    http_getData("http://app.yzjlb.net/", http_onProgress, http_onSuccess, http_onError);
	return 0;
}