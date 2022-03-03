#include <base.h>
#include <exb.h>
#include <android.h>
#include "mrpedit.h"
#include "coding.h"
#include "filename.h"
//操作文件
char *filename;
//工作目录
char*path="SPACE/";
char *unpath="MRPDATA/";

MRPINFO *mrpinfo;

int edit_filename,edit_appname,edit_code,edit_appid,edit_appver,edit_vender,edit_descrip;
int isOpen;
char text[300];

int init(void)
{
//以下全部都用printf输出信息
//读取mrp信息
mrpinfo=NULL;
filename=malloc(300);
mkdir(unpath);
isOpen=FALSE;
//fv_init(0);
//fv_begin("");

/*
ReadMrpInfo(file);
//写入mrp信息,1，目标文件
WriteMrpInfo("pack.mrp");
//读取mrp内部文件列表，1 目标文件
 ReadMrpFiles(file);
//解压全部，1 目标文件， 2 工作目录，3，0为解压，其他为解包
ExtractAll (file,path,0);
//打包mrp1,数据结构，2 目标文件，3 工作目录，4 生成文件
PackagedMrp(pHead,file,path,"abc.mrp");
//释放使用内存
FreeFileData();
ShowMsg("输出完成...!请到printf.txt查看",0);
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

//读取mrp信息




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
  toast("不是mrp文件",0);
  fv_end(); return 0;
 }
 fv_end();
 if(mrpinfo!=NULL)free(mrpinfo);
 mrpinfo=ReadMrpInfo(filename);
 //设置到编辑框
 
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
  else if(p1==102)//保存
  {
   if(!isOpen)
   {
    toast("没有打开文件",0);
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
    toast("保存成功",0);
   }
  }
  
  else if(p1==103)
  {
   if(!isOpen)
   {
    toast("没有打开文件",0);
    return 0;
   }
   ExtractAll(filename,unpath,1);
   sprintf(text,"成功解压到%s目录下",unpath);
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
//画空心矩形
void DrawVoidRect(uint16 x,uint16 y,uint16 w,uint16 h,uint8 r,uint8 g,uint8 b)
{
 dline(x,y,x,y+h-1,r,g,b);
 dline(x+1,y,x+w-2,y,r,g,b);
 dline(x+w-1,y,x+w-1,y+h-1,r,g,b);
 dline(x+1,y+h-1,x+w-2,y+h-1,r,g,b);
}

