
#ifndef _READ_TEXT_H_
#define _READ_TEXT_H_

#include "base.h"
#include "android.h"
//读取文本数据
char *text_read(char *filename)
{
 int len;
 char *text;
 len=getlen(filename);
 if(len<=0)return NULL;
 text=(char *)malloc(len+1);
 int f=open(filename,1);
 if(f)
 {
  read(f,text,len);
  text[len]=0;
  close(f);
 }
 return text;
}


//从assets读取文本
char *text_readFromAssets(char *filename)
{
 int len=0;
 char *buf=readFileFromAssets(filename,&len);



 char *text=NULL;
 if(len>0)
 {
  text=malloc(len+1);
  memcpy(text,buf,len);
  *(text+len)=0;
 }
 free(buf);
 return text;
}


#endif

