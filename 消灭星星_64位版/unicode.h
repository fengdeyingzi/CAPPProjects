

#ifndef _UNICODE_H_
#define _UNICODE_H_

#include "coding.h"

//����unicode�����ַ��������ص��ַ�����Ҫ�ֶ�free
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

