#include <base.h>
#include <exb.h>
#include <android.h>
#include "mrpedit.h"
#include "coding.h"
#include "filename.h"
//�����ļ�
char *filename;
//����Ŀ¼
char*path="SPACE/";
char *unpath="MRPDATA/";

MRPINFO *mrpinfo;

int edit_filename,edit_appname,edit_code,edit_appid,edit_appver,edit_vender,edit_descrip;
int isOpen;
char text[300];

int init(void)
{
//����ȫ������printf�����Ϣ
//��ȡmrp��Ϣ
mrpinfo=NULL;
filename=malloc(300);
mkdir(unpath);
isOpen=FALSE;
//fv_init(0);
//fv_begin("");

/*
ReadMrpInfo(file);
//д��mrp��Ϣ,1��Ŀ���ļ�
WriteMrpInfo("pack.mrp");
//��ȡmrp�ڲ��ļ��б�1 Ŀ���ļ�
 ReadMrpFiles(file);
//��ѹȫ����1 Ŀ���ļ��� 2 ����Ŀ¼��3��0Ϊ��ѹ������Ϊ���
ExtractAll (file,path,0);
//���mrp1,���ݽṹ��2 Ŀ���ļ���3 ����Ŀ¼��4 �����ļ�
PackagedMrp(pHead,file,path,"abc.mrp");
//�ͷ�ʹ���ڴ�
FreeFileData();
ShowMsg("������...!�뵽printf.txt�鿴",0);
*/

setContextView("main.xml");
edit_filename=findViewById(FILENAME);
 edit_appname=findViewById(APPNAME);
 edit_code=findViewById(CODE);
 edit_appid=findViewById(APPID);
 edit_appver=findViewById(APPVER);
 edit_vender=findViewById(VENDER);
 edit_descrip= findViewById(DESCRIP);
//softInput (edit_appname);

    return 0;
}

//��ȡmrp��Ϣ




int event(int type, int p1, int p2)
{
char *un;
    if(KY_DOWN == type)
    {
        switch(p1)
        {
        case _SRIGHT:
        if(mrpinfo!=NULL)
        free(mrpinfo);
        mrpinfo=NULL;
        free(filename);
            exit();
            break;
        case _1:
            break;
        }
    }

else if(type==10)
{
 if(p1==0)
 {
 strcpy(filename,fv_getpath());
 if(!impactName(filename,".mrp"))
 {
  toast("����mrp�ļ�",0);
  fv_end(); return 0;
 }
 fv_end();
 if(mrpinfo!=NULL)free(mrpinfo);
 mrpinfo=ReadMrpInfo(filename);
 //���õ��༭��
 
 un=gbToUn(mrpinfo->filename);
 view_setText(edit_filename,un);
 free(un);
 un=gbToUn(mrpinfo->appname);
 view_setText(edit_appname,un);
 free(un);
 un=gbToUn(mrpinfo->code);
 view_setText(edit_code,un);
 free(un);
 un=gbToUn(mrpinfo->appid);
 view_setText(edit_appid,un);
 free(un);
 un=gbToUn(mrpinfo->appver);
 view_setText(edit_appver,un);
 free(un);
 un=gbToUn(mrpinfo->vender);
 view_setText(edit_vender,un);
 free(un);
 un=gbToUn(mrpinfo->descrip);
 view_setText(edit_descrip,un);
 free(un);
 isOpen=TRUE;
 }
}

 else if(type==VIEW_UP)
 {
  if(p1==101)
  {
   fv_init(0);
fv_begin("");
  }
  else if(p1==102)//����
  {
   if(!isOpen)
   {
    toast("û�д��ļ�",0);
    return 0;
   }
   un=view_getText(edit_filename);
   char *temp;
   strcpy(mrpinfo->filename,temp=unToGb(un));
   free(temp);
   un=view_getText(edit_appname);
   strcpy(mrpinfo->appname,temp=unToGb(un));
   free(temp);
   un=view_getText(edit_code);
   strcpy(mrpinfo->code,temp=unToGb(un));
   free(temp);
   un=view_getText(edit_appid);
   strcpy(mrpinfo->appid,temp=unToGb(un));
   free(temp);
   un=view_getText(edit_appver);
   strcpy(mrpinfo->appver,temp=unToGb(un));
   free(temp);
   un=view_getText(edit_vender);
   strcpy(mrpinfo->vender,temp=unToGb(un));
   free(temp);
   un=view_getText(edit_descrip);
   strcpy(mrpinfo->descrip,temp=unToGb(un));
   free(temp);
   if(WriteMrpInfo(filename,mrpinfo)==0)
   {
    toast("����ɹ�",0);
   }
  }
  
  else if(p1==103)
  {
   if(!isOpen)
   {
    toast("û�д��ļ�",0);
    return 0;
   }
   ExtractAll(filename,unpath,1);
   sprintf(text,"�ɹ���ѹ��%sĿ¼��",unpath);
   toast(text,0);
   
  }
  
 }
    return 0;
}

int pause(void)
{
    return 0;
}

int resume(void)
{
    return 0;
}

void ShowMsg(char *Msg,int is_uni)
{
 int w,h;uint16 x,y;
 textwh(Msg,FALSE,0,&w,&h);
 if(w<SCRW)x=(SCRW-w)>>1;
 y=(SCRH-h)>>1;
 effsetcon(x-5,y-5,w+10,h+10,100,100,100);
 DrawVoidRect(x-5,y-5,w+10,h+10,255,0,0);
 dtext(Msg,x,y,255,255,250,is_uni,0);
 ref(x-5,y-5,w+10,h+10);
}
//�����ľ���
void DrawVoidRect(uint16 x,uint16 y,uint16 w,uint16 h,uint8 r,uint8 g,uint8 b)
{
 dline(x,y,x,y+h-1,r,g,b);
 dline(x+1,y,x+w-2,y,r,g,b);
 dline(x+w-1,y,x+w-1,y+h-1,r,g,b);
 dline(x+1,y+h-1,x+w-2,y+h-1,r,g,b);
}

