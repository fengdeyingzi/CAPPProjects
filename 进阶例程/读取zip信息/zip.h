
//UTF-8תunicode
void fu(char *p,char *a)
{
while(*p!=0)
{
if(*p<0x80)
{*a=0;*(a+1)=*p;p+=1;}else{
if(*p<0xe0)
{
*a=(*p&0x1c)>>2;*(a+1)=((*p&3)<<6)+(*(p+1)&0x3f);
p+=2;}else{
*a=((*p&0xf)<<4)+((*(p+1)&0x3c)>>2);*(a+1)=((*(p+1)&3)<<6)+(*(p+2)&0x3f);
p+=3;
}
}
a+=2;
}
*a=0;*(a+1)=0;
}



typedef struct
{
int head; //�ļ�ͷ0x04034b50
short version;//��ѹ������汾
short bit_flag;//ͨ�ñ��ر�־λ
short method; //ѹ����ʽ
short lasttime; //�ļ�����޸�ʱ��
short lastdate; //�ļ�����޸�����
int  crc32; //32λЧ����
int  zipfilelen;//ѹ���ļ���С
int  unzipfilelen;//δѹ���ļ���С
short  filename_len;//�ļ�����
short  field_len;//��չ�γ�
char* filename;//�ļ���
void*   field;//��չ��
} ZIPHEAD;




void *readziphead(char *filename)
{
 ZIPHEAD *ziphead=malloc(sizeof(ZIPHEAD));
 int f=open(filename,12);
 if(f==-1)
 {
  return NULL;
 }
 int len;
 //read(f,ziphead,30);
 
 read(f,&ziphead->head,4);
 //printf("%d",len);
 read(f,&(ziphead-> version), 2);
 read(f,&ziphead->bit_flag,2);
 read(f,&ziphead->method,2);
 read(f,&ziphead->lasttime,2);
 read(f,&ziphead->lastdate,2);
 read(f,&ziphead->crc32,4);
 read(f,&ziphead->zipfilelen,4);
 read(f,&ziphead->unzipfilelen,4);
 read(f,&ziphead->filename_len,2);
 read(f,&ziphead->field_len,2);
 
 
 
 ziphead->filename=malloc(ziphead->filename_len+1);
 *(ziphead->filename+ziphead->filename_len)=0;
 read(f,ziphead->filename,ziphead->filename_len);
 
 close(f);
 return ziphead;
}


