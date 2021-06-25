
//UTF-8转unicode
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
int head; //文件头0x04034b50
short version;//解压缩所需版本
short bit_flag;//通用比特标志位
short method; //压缩方式
short lasttime; //文件最后修改时间
short lastdate; //文件最后修改日期
int  crc32; //32位效验码
int  zipfilelen;//压缩文件大小
int  unzipfilelen;//未压缩文件大小
short  filename_len;//文件名长
short  field_len;//扩展段长
char* filename;//文件名
void*   field;//扩展段
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


