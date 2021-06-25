

#ifndef _UNICODE_H_
#define _UNICODE_H_

#include "coding.h"

//复制unicode编码字符串，返回的字符串需要手动free
char *un_copy(char *text)
{
 int len= wstrlen(text)+2;
 char *temp= malloc(len);
 memcpy(temp,text,len);
 return temp;
}


char *un_atoi(char *text)
{
 char *temp=unToGb(text);
 int num=atoi(temp);
 free(temp);
 return num;
}












#endif

