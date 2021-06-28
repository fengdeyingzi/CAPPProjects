
#ifndef _CODING_H_
#define _CODING_H_

#include <base.h>

//gb±àÂë×ªunicode
char *gbToUn(char *text)
{
 int32 len;
 return (char*)c2u(text, NULL, &len);
 
 
}

//unicode±àÂë×ªgb
char *unToGb(char *text)
{
 char *input= text;
int32 input_len= wstrlen(input);
 char *output= malloc(input_len+2);
 printf("input_len %d\n",input_len);
 int32 output_len;
 u2c( input, input_len, &output, &output_len);
 return output;
}



#endif