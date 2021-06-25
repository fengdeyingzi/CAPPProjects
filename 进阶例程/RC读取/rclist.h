
/*
RC�б�
��ȡrc�ַ���unicode����(���)
res_lang0.rc�ļ�
��RC�༭������
*/

#ifndef _RC_LIST_H_
#define _RC_LIST_H_

#include <base.h>
#include <android.h>


//�ṹ��




typedef struct
{
 uint16 *id; //�ַ�id
 char *text; //�ַ�����
 int math;   //rc�ַ�����
 int coding;  //����(unicode 1)
} RC_LIST;

//��assetsĿ¼��ȡRC�ļ������ؾ��
//������rc�ļ�����rc�ַ�����
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


//��ȡ�ַ�
//������rc������ַ�id
char *rc_getText(int rc,int id)
{
 RC_LIST *rclist=(void*)rc;
 if(rclist==NULL)return NULL;
 //printf("%d\n",rclist->id[id]);
 if(id>=rclist->math)
  id = rclist->math-1;
 
 return rclist->text + rclist->id[id];
}

//��ȡgb�����ַ���
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

//�ͷ��ڴ�
int rc_free(int rc)
{
 RC_LIST *rclist=(void*)rc;
 
 if(rclist==NULL)return -1;
 free(rclist->id);
 free(rclist);
 return 0;
}



#endif