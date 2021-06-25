
#ifndef _CODING_H_
#define _CODING_H_
#include <base.h>
/*
编码转换
转换后获得的字符串，需要用free函数释放内存

*/



#include <base.h>

//gb编码转unicode 返回的字符串需要释放内存
char *gbToUn(char *text)
{
 int32 len;
 return (char*)c2u(text, NULL, &len);
 
 
}

//unicode编码转gb 返回的字符串需要释放内存
char *unToGb(char *text)
{
 char *input= text;
int32 input_len= wstrlen(input);
 char *output= (char*)malloc(input_len+2);
 printf("input_len %d\n",input_len);
 int32 output_len;
 u2c( (unsigned char*)input, input_len, (unsigned char **)&output, &output_len);
 return output;
}



#endif