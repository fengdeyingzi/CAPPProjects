
/*
RC列表
读取rc字符序，unicode编码(大端)
res_lang0.rc文件
由RC编辑器生成
*/

#ifndef _RC_LIST_H_
#define _RC_LIST_H_

#include <base.h>
#include <android.h>


//结构体




typedef struct
{
 uint16 *id; //字符id
 char *text; //字符缓存
 int math;   //rc字符数量
 int coding;  //编码(unicode 1)
} RC_LIST;

//从assets目录读取RC文件，返回句柄
//参数：rc文件名，rc字符数量
int rc_read(char *filename,int math)
{
 RC_LIST *rclist=malloc(sizeof(RC_LIST));
 
 int len;
 char *buf = readFileFromAssets(filename,&len);
 if(len<=0)return 0;
// printf("%d\n",len);
 rclist->coding=1;
 rclist->math=math;
 rclist->id = (unsigned short*)buf;
 rclist->text = buf+ math*2;
 return (int)rclist;
}


//获取字符
//参数：rc句柄，字符id
char *rc_getText(int rc,int id)
{
 RC_LIST *rclist=(void*)rc;
 if(rclist==NULL)return NULL;
 //printf("%d\n",rclist->id[id]);
 if(id>=rclist->math)
  id = rclist->math-1;
 
 return rclist->text + rclist->id[id];
}

//获取gb编码字符串
int rc_getTextGb(int rc,int id,char *text)
{
 RC_LIST *rclist=(void*)rc;
 if(rclist==NULL)return -1;
 char *input= rclist->text + rclist->id[id];
 int input_len= wstrlen(input);
 int output_len;
 u2c( input, input_len, &text, &output_len);
 
 return 0;
}

//释放内存
int rc_free(int rc)
{
 RC_LIST *rclist=(void*)rc;
 
 if(rclist==NULL)return -1;
 free(rclist->id);
 free(rclist);
 return 0;
}



#endif