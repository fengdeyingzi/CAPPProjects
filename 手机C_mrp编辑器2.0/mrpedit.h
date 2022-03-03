//��ѩ��PaPo��ֲ��װ
//ע:��ͷ�ļ���mrpedit�ĳ��Σ�ע����mrpedit�����Ǵ���õġ�
enum
{
 FILENAME=1,  //�ļ���
  APPNAME,  //Ӧ����
  CODE,      //���к�
  APPID, //APPID�ִ���ʽ
  APPVER, //Ӧ�ð汾�ִ�
  VENDER,   //����
  DESCRIP  //Ӧ������
 };
typedef struct
{
 char filename[24];  //�ļ��� 24
 char appname[48];   //Ӧ���� 48
 char code[34];      //���к� 34
 char appid[22];  //APPID�ִ���ʽ 22
 char appver[22]; //Ӧ�ð汾�ִ� 22
 char vender[80];    //���� 80
 char descrip[128];  //Ӧ������ 128
 } MRPINFO;
//��ȡmrp��Ϣ
MRPINFO *ReadMrpInfo(char*mrpname)
{
 MRPINFO *mrp= malloc(sizeof(MRPINFO));
 int32 mrpHandel;
 int32 appid, appver;
 char*buffer=malloc(128);
 mrpHandel = open(mrpname, 1);
// if(!mrpHandel) return;
 //1.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��28����ȡmrp��ʾ����22�ֽ�(����ȫΪ����)
 seek(mrpHandel, 28, SEEK_SET);
read(mrpHandel,mrp->filename, 24);
printf("��ʾ��:%s",mrp->filename);

 //2.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��16����ȡmrp�ڲ�����12�ֽڣ�����ȫΪӢ�ģ�
 seek(mrpHandel, 16, SEEK_SET);
 read(mrpHandel, mrp->appname, 12);
 printf("\n�ڲ���:%s",mrp->appname);
//3.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��52����ȡmrp���кţ�16�ֽڣ�����ȫ��Ӣ�ģ�
 seek(mrpHandel, 52, SEEK_SET);
 read(mrpHandel, mrp->code, 16);
 printf("\n���к�:%s",mrp->code);

 //4.��ȡAPPID
 seek(mrpHandel, 68, SEEK_SET);
 read(mrpHandel, &appid, 4);
 sprintf(mrp->appid,"%d",appid);
 printf("\nAPPID:%s",mrp->appid);
 //5.��ȡӦ�ð汾
 seek(mrpHandel, 72, SEEK_SET);
 read(mrpHandel,& appver, 4);
 sprintf(mrp->appver,"%d",appver);
 
 printf("\nӦ�ð汾:%s",mrp->appver);

 //6.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��88����ȡmrp���ߣ�38�ֽڣ�����ȫΪ���ģ�
 seek(mrpHandel, 88, SEEK_SET);
// memset(mrp.vender, 0, sizeof(mrp.vender));
 read(mrpHandel,mrp->vender, 38);
 printf("\n����:%s",mrp->vender);

 //7.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��128����ȡmrpӦ��˵����60�ֽ�
 seek(mrpHandel, 128, SEEK_SET);
// memset(mrp.descrip, 0, sizeof(mrp.descrip));
 read(mrpHandel,mrp->descrip, 60);
 printf("\nӦ��˵��:%s",mrp->descrip);

 close(mrpHandel); //��ȡ��ϣ��ر��ļ�
 return mrp;
};


int WriteMrpInfo(char*mrpname, MRPINFO *mrp)
{
int32 mrpHandel = 0, ret  = 0;
//��д��MRP�ļ����
//char* buffer=malloc(128);//��д�뻺��������
 int appid, appver;
 //��mrp�ļ�
 mrpHandel = open(mrpname, 4);
 if(!mrpHandel) return -1;
 //1.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��28��д��mrp��ʾ����22�ֽ�
 seek(mrpHandel, 28, SEEK_SET);
write(mrpHandel, mrp->filename, 22);

//2.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��16����ȡmrp�ڲ�����11�ֽ�
 seek(mrpHandel, 16, SEEK_SET);
write(mrpHandel, mrp->appname, 11);

 //3.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��52����ȡmrp���кţ�16�ֽ�
seek(mrpHandel, 52, SEEK_SET);
write(mrpHandel, mrp->code, 16);

 //4.дAPPID(������һ��68��һ��192)
seek(mrpHandel, 68, SEEK_SET);
write(mrpHandel, mrp->appid, 4);

 //5.дӦ�ð汾(���� ƫ�� 72, 196)
seek(mrpHandel, 72, SEEK_SET);
write(mrpHandel, mrp->appver, 4);

//6.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��88����ȡmrp���ߣ�38�ֽ�
seek(mrpHandel, 88, SEEK_SET);
write(mrpHandel, mrp->vender, 38);

 //7.�ӿ�ʼλ�ð�ָ���Ƶ�ƫ��128����ȡmrpӦ��˵����60�ֽ�

seek(mrpHandel, 128, SEEK_SET);
write(mrpHandel, mrp->descrip, 60);

close(mrpHandel);
return 0;
}

typedef struct _mrp_filelist
{
 char* filename; //�ļ���
 uint8 type;  //����
 int32 flen;  //�ļ�����
 int32 offset; //�ļ�ƫ��
 uint16 index; //�ļ����
 struct _mrp_filelist *next;
 struct _mrp_filelist *prev;
}*PMRPFILESINFO;
struct _mrp_filelist MRPFILESINFO;
int32 count;     //�ļ��б���
 PMRPFILESINFO pHead, pCur; //�ļ��б�����
#define L   sizeof(MRPFILESINFO)

//��ȡmrp�ļ��б�
int ReadMrpFiles(char*MrpN)
{
 int32 fd = 0;  
 int32 flStar = 0, flEnd = 0; //MRP �ļ��б���ֹλ��
 int32 fnLen = 0, fLen;  //mrp ���ļ�������,�ļ�����
 int32 fCount = 0;   //mrp ���ļ���Ŀ
 char mrphead[5];  //��֤mrp�ļ�ͷ
 char fName[64];  //�ļ���
 PMRPFILESINFO p = NULL;
 char*ntemp;
 int32 off;

 fd = open(MrpN, 4);
 if(!fd) return -1;

 //���ж��Ƿ�Ϊ��ȷ��MRP��ʽ
 seek(fd, 0, SEEK_SET);
 read(fd, mrphead, 4);
 if( strncmp(mrphead, "MRPG", 4) != 0)
 {
  close(fd);
  return -1;
 }

 //��ȡ�ļ��б��յ�λ��
 read(fd, &flEnd, 4);
 flEnd += 8;
 //��ȡ�ļ��б���ʼλ��
 seek(fd, 12, SEEK_SET);
 read(fd, &flStar, 4);
 
 //�����ļ�����ͷ���
  p = pCur = pHead =malloc(L);

 memset(pHead, 0, L);
 pHead->prev = NULL;
 pHead->next = NULL;
 fCount = 0;
 while(flStar < flEnd)
 {
  //1.��ȡ�ļ���
  seek(fd, flStar, SEEK_SET);
  read(fd, &fnLen, 4);   //��ȡ�ļ�������
  read(fd, fName, fnLen);   //��ȡ�ļ���
  ntemp = malloc(fnLen+1);
  memset(ntemp, 0, fnLen+1);
  memcpy(ntemp, fName, fnLen);
  p->filename = ntemp;
 // p->type = GetFileFormat(fName);  //��ȡ�ļ���ʽ

  //2.��ȡ�ļ����ȡ�ƫ��
  read(fd, &off, 4);
  read(fd, &fLen, 4);
  p->flen = fLen;
  p->offset = off;
  p->index = fCount; //��Ŵ�0��ʼ
  fCount++;   //ע��������ʵ��
 printf("\n%d %s len:%d %d ",fCount,ntemp,fLen,off);

  //3.׼����ȡ��һ���ļ�
  flStar = flStar + fnLen + 16; //�����¸��ļ�
  fnLen = 0;
  if(flStar < flEnd) //�����Ҫ�����û�е�ĩβ
  {
   PMRPFILESINFO tmp = p;

   p->next = malloc(L);
   p = p->next;
   memset(p, 0, L);
   p->prev = tmp;
   p->next = NULL;
  }
  }
 //��ȡ��ϼ�¼����
 close(fd);
 count = fCount;  //��¼�ļ���

 return 0;
}

//����ת�Ƶ�����
void Focus2List(int32 curIndex)
{
 if(pCur == NULL) pCur = pHead;
 if(pCur->index < curIndex){   //ǰ��
  while(pCur->index != curIndex)
   pCur = pCur->next;
 }else if(pCur->index > curIndex){ //����
  while(pCur->index != curIndex)
   pCur = pCur->prev;
 }else
  pCur = pCur;
 
 sprintf(LabelCaption, "%d/%d  Offset=%d, Length=%d", curIndex+1, count, pCur->offset, pCur->flen);
}
//��������ɾ��һ��
void Dele(int32 index)
{
 int i;
 PMRPFILESINFO p1, p2;

 //1.ɾ��������
 if(index == 0) 
 {
  p1 = pHead;
  pCur = pHead = pHead->next;
  pHead->prev = NULL;
  free(p1->filename);
  free(p1);
  p1 = pHead;
  i = 0;
  while(p1){
   p1->index = i++;
   p1 = p1->next;
  }
  return;
 }

 //2.ɾ���м����β��
 p1 = pHead;
 for(i=0; i<index-1; i++)
  p1 = p1->next;   //�ҵ�ɾ���ڵ��ǰһ��
 if(p1->next->next == NULL) //˵������Ϊ����β
 {
  p2 = p1->next;
  p1->next = NULL;
  pCur = p1;
 }else //�м�ڵ�
 {
  p2 = p1->next;
  pCur = p1->next = p2->next;
  p1->next->prev = p1;
  i = p1->index;
  while(p1){
   p1->index = i++;
   p1 = p1->next;
  }
 }
 free(p2->filename);
 free(p2);
}

//��ȡ�б���ص�
void AddFileToList1(int index)
{
 PMRPFILESINFO ptmp = pCur;

 if (!pRowData || index<0 || index > count - 1) //�����������
  return;

 //��ǰ��ý��������
 if(ptmp == NULL) ptmp = pHead;

 //��ȡ��ǰ����
 if(ptmp->index < index){   //ǰ��
  while(ptmp->index != index)
   ptmp = ptmp->next;
 }else if(ptmp->index > index){ //����
  while(ptmp->index != index)
   ptmp = ptmp->prev;
 }else
  ptmp = ptmp;

}


//�ͷ��ļ������ڴ�
void FreeFileData(void)
{
 PMRPFILESINFO p1, p2 ;
 p1 = pHead;
 while(1)
 {
 if(p1!=0)
 {
  printf("\n�ͷ�����:%s",p1->filename);
  free(p1->filename);
  p2 = p1->next;
  free(p1);
  p1 = p2;}
  else
  {
  break;  
  }
 }
 pCur = pHead = NULL;
 count = 0;
}

uint8 *buf;
int32 len,f;

//mkdir("c/����");
void unpack(char*mrp,char*in,char*out)
{
    buf=NULL;
    readfilefrommrp(mrp,in,&buf,&len,0);
    f=open(out,12);
    write(f,buf,len);
    close(f);
    free(buf);
}

int upMrpFiles(char*name,char*path, int isUnZip)
{
int imrp;
char buf[100];
ReadMrpFiles(name);
PMRPFILESINFO p1, p2 ;
p1 = pHead;
if(filestate(path)!=2)
{
mkdir(path);}
while(imrp!=count)
{
  sprintf(buf,"%s%s",path,p1->filename);
 unpack(name,p1->filename,buf);
printf("\n%s",buf);
  p2 = p1->next;
  p1 = p2;

++imrp;
}
return 0;}

//�������MRP�ļ�
int UnPackFileFromMrp(PMRPFILESINFO p,char*Mname, char*tofile)
{


 int32 mrphd, filehd;
 int32 off, r;
 char*buf;
 int32 buflen = 10*1024;
 int32 total;

//if(!p || !tofile || p->flen < 0) return -1;

 //��Դ�ļ���Ŀ���ļ�
 mrphd = open(Mname, 4);
 if(!mrphd) return -1;
 filehd = open(tofile, 4|8);
 if(!filehd){
  close(mrphd);
  return -1;
 }

 //���仺����
 buf = malloc(buflen);
/* if(!buf){
  close(mrphd);
  close(filehd);
  return -1;
 }*/

 //��ʼ��ȡ�ļ�
 off = p->offset; //�ļ���ʼλ��
 seek(mrphd, off, SEEK_SET);
 seek(filehd, 0, SEEK_SET);
 total = p->flen; //�ܹ�Ҫ��ȡ�ĳ���
 while(total>0)
 {
    memset(buf,0,buflen);
  r= read(mrphd, buf,(buflen<=total)?buflen:total);
  write(filehd, buf, r);
  total -= r;
   printf("\n%s����:%d",tofile,total);

 }
 free(buf);
 //��д��Ϲر��ļ�
 close(mrphd);
 close(filehd);

 return 0;
}

//���MRP�ļ�
int ExtractMrpFiles(PMRPFILESINFO p,char*Mname,char*path, int isUnZip)
{
 char*filebuf = NULL;  //��ѹ�ļ�����
 int32 filelen = 0;  //��ѹ�ļ�����
 int32 fd = 0;
 char name[128]; //����ѹ�ļ���

 //��֤������ȷ��
 //if(!p) return FAILED;
 //���Ŀ¼
 if(2!= filestate(path)) mkdir(path);

 //��ѹ�ļ���
 sprintf(name, "%s%s", path, p->filename);

 //��ѹ/����ļ�
 if(isUnZip) //��ѹ�ļ�
 {
 //��ѹ�ļ���
 sprintf(name, "%s%s", path, p->filename);

  if(0 == readfilefrommrp(Mname, p->filename, &filebuf, &filelen, 0))
  {
   fd = open(name,4|8);
   if(!fd){
    free(filebuf);
    return -1;
   }
   seek(fd, 0, SEEK_SET);
   write(fd, filebuf, filelen);
   close(fd);
   free(filebuf);

   return 0;
  }else
   return -1;
 }else //����ļ�
 {
  //��ѹ�ļ���
 sprintf(name, "%s%s", path, p->filename);

  return UnPackFileFromMrp(p,Mname ,name);
 }



 return 0;
}


//���/��ѹȫ��
void ExtractAll(char*name,char*path,int UnZip)
{
 int scount = 0;
 char buf[100];
 char*uni;
 ReadMrpFiles(name);
 PMRPFILESINFO p = pHead;

 while(scount!=count)
 {

   ExtractMrpFiles(p,name,path, UnZip);
    scount++;
  p = p->next;
 }

}

#define FULLNAME_LEN 200  //�����ļ�������
#define HEADBUF_LEN  240  //mrpͷ������
#define WRITEBUF_LEN 20*1024 //�ļ���д���峤��
//���MRPʵ��
int PackagedMrp(PMRPFILESINFO p,char*Mname,char*WorkDir,char*tofile)
{
 PMRPFILESINFO p1;  //����
 int32 tomrpfd;   //���浽����MRP���ļ����
 int32 delmrpfd;   //��ǰ�����MRP�ļ����
 int32 tempfd;   //����д����ļ����
 int32 flistlen;   //mrp�ڲ��ļ��б��ֳ���
 int32 len, templ;  //��ȡһ������
 uint8 buf[100];   //�Ի������ݻ���
 char fullname[FULLNAME_LEN];   //�����ļ���
 char mrphead[HEADBUF_LEN];    //mrp�ļ�ͷ������
 char*pwbuf;    //д�ļ��Ļ�����
 char*pflistbuf;   //���ļ��б������ݶ�ȡ���ڴ淽���޸��б���

 //2.��Դ�ļ���Ŀ���ļ�
 if(filestate(tofile) == 1)
  remove(tofile);
 delmrpfd = open(Mname,4);
 tomrpfd = open(tofile, 4|8);
 if(delmrpfd == 0 || tomrpfd == 0)
  goto ERROR;  //ʧ�ܵ�һ���ļ�ʧ��

 //3.дͷ��

 seek(delmrpfd, 0, SEEK_SET);
 read(delmrpfd, mrphead, 240);
 seek(tomrpfd, 0, SEEK_SET);
 write(tomrpfd, mrphead, 240);

 //3.д�ļ��б� ����д�ļ��б�����


 int32 wklen = strlen(WorkDir);

 //���������ļ��б�ĳ���
 p1 = pHead;
 if(p1!=NULL)
 {
  char buf2[13] ; //�������հ�
  char*tempn;
  flistlen = 0;
  memset(fullname, 0, FULLNAME_LEN);
  memcpy(fullname, WorkDir, wklen);
  while(p1!=NULL)
  {
  
   memset(&fullname[wklen], 0, FULLNAME_LEN - wklen - 2); //-2��Խ��
   len = strlen(p1->filename);  //�ļ�����
   memcpy(&fullname[wklen], p1->filename, len);

   //�����б���ͬʱҪ�����ļ��Ƿ����
   if(filestate(fullname)==1&&len<FULLNAME_LEN)
   {
  //   printf("\n+++++");

    templ = len + 1;
    write(tomrpfd, &templ, 4);  //д�ļ�����
    tempn = p1->filename;
    write(tomrpfd, tempn, len);  //д�ļ���
    write(tomrpfd, buf2, 13); 
    flistlen += len + 17;
   }
   p1 = p1->next;
  }
 }else
  goto ERROR; 

 //4.д�ļ� ����д���ļ�������


 p1 = pHead;
 if(p1!=NULL)
 {
  char*pt1;
  int32 r = 0, l = 0, curpos = 0;//��ǰ�ļ���дָ��
 // int32 wklen = strlen(WorkDir); //WorkDir����

  pwbuf =malloc(WRITEBUF_LEN); //�����д����
  memset(pwbuf, 0, WRITEBUF_LEN);
  
  pflistbuf = malloc(flistlen); //����һƬ�ڴ��������ļ��б�������
  seek(tomrpfd, 240, SEEK_SET);
  read(tomrpfd, pflistbuf, flistlen);  //�ļ�ָ���ֵ���ĩβŶ
  pt1 = pflistbuf;
  curpos = 240 + flistlen; //��¼��ǰ��дλ��

  memset(fullname, 0, FULLNAME_LEN);
  memcpy(fullname, WorkDir, wklen);
  while(p1!=NULL)
  {
   memset(&fullname[wklen], 0, FULLNAME_LEN - wklen - 2); //-2��Խ��
   len = strlen(p1->filename);  //�ļ�����
   memcpy(&fullname[wklen], p1->filename, len);
   printf("\n����ļ�: %s",fullname);  
  if(filestate(fullname) == 1)
{
    memcpy(&l, pt1, 4);   //�ӻ�������ȡ�ļ������ȱ��浽i
    write(tomrpfd, pt1, l+4); //д�ļ��� tomrpfd
    curpos += (4+l);    //��¼�ļ�ָ��
    pt1 += 4;  //������ƫ��4�ֽڵ��ļ�����
    pt1 += l;  //������ƫ�Ƽ����ļ�������,��д���ļ����ݳ���

    len = getlen(fullname);  //��ȡ�ļ��ֽ���
    write(tomrpfd, &len, 4); //д���ļ��ֽ��� tomrpfd
    curpos += 4;     //��¼�ļ�ָ��

    memcpy(pt1, &curpos, 4); //���ļ�ƫ�Ƽ�¼���ļ��б���
    pt1 += 4;      //������ƫ�Ƽ�4�ֽڣ���д���ļ����ݳ���
    memcpy(pt1, &len, 4);  //���ļ����ȼ�¼���ļ��б���
    pt1 += 8;      //������ƫ�Ƽ�8�ֽڣ����ݳ��Ⱥ�4�����ֽ�

    tempfd = open(fullname,4); //OK����д�ļ������ˣ��ȴ��ļ�
    if(tempfd == 0) //���ļ�ʧ��
    {
     free(pflistbuf);
     free(pwbuf);
     goto ERROR;
    }
    r= read(tempfd, pwbuf, WRITEBUF_LEN); //ѭ����д�ļ�
    while(r)
    {
  write(tomrpfd, pwbuf, r); //tomrpfd
     curpos += r;
     memset(pwbuf,0,WRITEBUF_LEN);
 r = read(tempfd, pwbuf,WRITEBUF_LEN);
    }
    close(tempfd);
    tempfd = 0;
    }//if(
   
   p1 = p1->next; //�����Ƶ���һ���ļ�
  }//while(p1)

  //�ļ���д���ˣ������Ĺ���
  //1.�����ļ��б�����
  seek(tomrpfd, 240, SEEK_SET);
  write(tomrpfd, pflistbuf, flistlen);

  //2.����ͷ������
  seek(tomrpfd, 4, SEEK_SET); //4-8MRP���ݿ�ʼλ��+8
  l = 240 + flistlen + 8;
  write(tomrpfd, &l, 4);
  seek(tomrpfd, 8, SEEK_SET); //8-12mrp�ļ����ֽ���
  write(tomrpfd, &curpos, 4);

  //3.�ͷ�һ������
  free(pflistbuf);
  free(pwbuf);
 }else
  goto ERROR; 

 //5.�����ɣ��ƺ�
 free(pwbuf);

 //�ر��ļ����
 close(delmrpfd);
 close(tomrpfd);
 
 return 0;

ERROR: //��������
 {
  close(delmrpfd);
  close(tomrpfd);
  return -1;
 }
}
// CopyFile �ļ����ƺ���
//srcfile Դ�ļ�,destĿ���ļ�
int CopyFile(char*srcfile,char*destfile)
{
 char*buffer;     //�ļ���д����
 int32 fd_dest_file = 0, fd_src_file = 0; //Ŀ���ļ���Դ�ļ����
 int32 ret, size, r, w=0;
 buffer=malloc(20*1024); //���仺�����ڴ�

 //��ȡԴ�ļ���С
 size =getlen(srcfile); 

 //��Դ�ļ�(ֻ��)
 fd_src_file =open(srcfile, 1); 

 //��Ŀ���ļ�(�����ڴ���)
 fd_dest_file = open(destfile,4|8); 
 
 if(fd_src_file != 0 && fd_dest_file != 0) //���ļ����ɹ�
 {
 
  r = read(fd_src_file, buffer,20*1024);   //��ȡ�ļ�

  while(r != 0)//�����ȡ���ֽ�����Ϊ0,�����д�ļ�
  {
   w += write(fd_dest_file, buffer, r);

   r = read(fd_src_file, buffer,r);
  }

  ret = close(fd_src_file); //�ر�Դ�ļ�
  ret = close(fd_dest_file); //�ر�Ŀ���ļ�  
  free(buffer);

  //֪ͨ���ɹ����һ���ļ�
printf("\n����:%s->%s�ɹ�",srcfile,destfile);
  return 0;  //���Ƴɹ�
 }else  //ִ������˵��Դ/Ŀ���ļ���ʧ��
 {  
  //���ﲻȷ���ĸ��ļ���ʧ�ܣ��������ж���
  if(fd_dest_file != 0) 
   ret = close(fd_dest_file); //�ر�Ŀ���ļ�  
  else 

  if(fd_src_file != 0) 
   ret = close(fd_src_file); //�ر�Դ�ļ�
  else

  free(buffer);

  return -1;     
 }
}

//�滻/�����ļ�����
int ChangeFile(char*Cname,char*path,int32 index,int mode)
 {
  //��ȡ�ļ�����,�ڴ˴�����ļ��滻�����
  if(pHead!=0)
  {
  int32 i,c;
  char*name, fullname;
  char buf[128]; //��ż��뵽temp���ļ���
 char buf2[128]; //MRP�����ļ���Ӧ����ʱ�ļ���
   PMRPFILESINFO p = pHead,pc=pHead ,pc1,p2;

   //1.��ȡ�ļ����������ļ���
//�������ļ�·��
  fullname = Cname; //��ȡ�ļ�·����
   if(!fullname) break;   
   while(1)
   {
   if(c==index)
   {
   name=pc->filename; 
    break;
   }
  pc1 = pc->next;
  pc = pc1;
   c++;
   }
  // name = ExtractFileName(fullname); //��ȡ�ļ���
   if(!name) break;

   //2.��������ļ����Ƶ�����Ŀ¼(�������ͬ���ļ��أ�)
   sprintf(buf, "%s%s",path, name);
   if(1== filestate(buf)) remove(buf); //�Ѵ�����ɾ��֮
   CopyFile(fullname, buf, NULL); //���ļ����Ƶ�����Ŀ¼

   //3.��������
 if(mode == 0) //�滻ģʽ���滻Ӧ�����ļ�����ͬŶ
   {
  sprintf(buf2, "%s%s", path, p->filename);
    remove(buf2);
  rename(buf, buf2); //�ٽ�������ļ�����OK
  //  free(name);   //�ͷŶ��ļ���
   }else  //����ģʽ
   {
    PMRPFILESINFO tmp;

    //�����ļ��ṹ�ڴ�
    tmp = malloc(L);
    memset(tmp, 0, L);
  tmp->filename = name;//ֱ��ʹ�ò��Ҷ��ļ���������ڴ�
    tmp->flen = -1;
    tmp->offset = -1;

    if(pCur->index !=index) 
     Focus2List(index);

    if(pCur->index == 0)
    { //ͷ��
     pHead->prev = tmp;
     pHead = tmp;
     tmp->next = pCur;
     tmp->prev = NULL;
     i = 0;    //�ض����
     while(tmp)
     {
      tmp->index = i++;
      tmp = tmp->next;
     }
    }
    else
    {
    //�м���
     p2 = pCur->prev;
     pCur->prev = tmp;
     p2->next = tmp;
     tmp->next = pCur;
     tmp->prev = p2;
     i = tmp->index = pCur->index;
     while(tmp)
     {
      tmp->index = i++;
      tmp = tmp->next;
     }
    }
    count += 1;   //�ļ�������1
   }
 }
}