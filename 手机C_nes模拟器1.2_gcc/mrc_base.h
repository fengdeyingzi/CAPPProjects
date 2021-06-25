
#ifndef _XL_BASE_
#define _XL_BASE_
#include "base.h"


enum {
MR_KEY_PRESS, //��������
MR_KEY_RELEASE, //�����ͷ�
MR_MOUSE_DOWN, //��갴��
MR_MOUSE_UP, //����ͷ�
MR_MENU_SELECT, //
MR_MENU_RETURN, //
MR_DIALOG_EVENT, //
MR_EVENT01, //
MR_EXIT_EVENT, //
MR_EVENT02, //
MR_LOCALUI_EVENT, //
MR_OSD_EVENT, //
MR_MOUSE_MOVE, //
MR_ERROR_EVENT, //*13ִ���쳣ͨ������¼���֪ͨ
MR_PHB_EVENT,//
MR_SMS_OP_EVENT,//
MR_SMS_GET_SC,//
MR_DATA_ACCOUNT_EVENT,//
MR_MOTION_EVENT,//

MR_TIMER_EVENT = 1001,
    MR_NET_EVENT
};

enum {
   MR_KEY_0,               //���� 0
   MR_KEY_1,               //���� 1
   MR_KEY_2,               //���� 2
   MR_KEY_3,               //���� 3
   MR_KEY_4,               //���� 4
   MR_KEY_5,               //���� 5
   MR_KEY_6,               //���� 6
   MR_KEY_7,               //���� 7
   MR_KEY_8,               //���� 8
   MR_KEY_9,               //���� 9
   MR_KEY_STAR,            //���� *
   MR_KEY_POUND,           //���� #
   MR_KEY_UP,              //���� ��
   MR_KEY_DOWN,            //���� ��
   MR_KEY_LEFT,            //���� ��
   MR_KEY_RIGHT,           //���� ��
   MR_KEY_POWER,           //���� �һ���
   MR_KEY_SOFTLEFT,        //���� �����
   MR_KEY_SOFTRIGHT,       //���� �����
   MR_KEY_SEND,            //���� ������
   MR_KEY_SELECT,          //���� ȷ��/ѡ����������м���ȷ�ϼ���������Ϊ�ü���
   MR_KEY_VOLUME_UP,          //���� �����
   MR_KEY_VOLUME_DOWN,          //���� �����
   MR_KEY_NONE             //���� ����
};
enum {
//   BM_OR,         //SRC .OR. DST*   ��͸��Ч��
//   BM_XOR,        //SRC .XOR. DST*
//   BM_COPY,       //DST = SRC*      ����
//   BM_NOT,        //DST = (!SRC)*
//   BM_MERGENOT,   //DST .OR. (!SRC)
//   BM_ANDNOT,     //DST .AND. (!SRC)
   BM_TRANSPARENT //͸��ɫ����ʾ��ͼƬ�ĵ�һ�����أ����Ͻǵ����أ���͸��ɫ
//   BM_AND,
//   BM_GRAY,
//   BM_REVERSE
};


typedef struct
{
   uint32 width;                  //��Ļ��
   uint32 height;                 //��Ļ��
   uint32 bit;                    //��Ļ������ȣ���λbit
}mr_screeninfo;


typedef struct {
   uint16            x;
   uint16            y;
   uint16            w;
   uint16            h;
}mr_screenRectSt;

typedef struct {
   uint8            r;
   uint8            g;
   uint8            b;
}mr_colourSt;


/*
typedef struct
{
   uint16 year;                 //��
   uint8  month;                //��
   uint8  day;                  //��
   uint8  hour;                 //ʱ��24Сʱ��
   uint8  minute;               //��
   uint8  second;               //��
}mr_datetime;
*/

#define mrc_free free

int mrc_getScreenInfo(mr_screeninfo * screeninfo)
{
screeninfo->width=SCRW;
screeninfo->height=SCRH;
return 0;
}


char *mrc_strrchr(char *start,char c)
{
return strrchr(start,c);
}

long mrc_wstrlen(char *text)
{
return wstrlen(text);
}

void mrc_memset(void *s, int ch, unsigned n)
{
 memset(s,ch,n);
 
}

void *mrc_memcpy(void *dest, void *src, unsigned int count)
{
 return memcpy(dest,src,count);
}

long mrc_open(char *filename, int mode)
{
return open(filename,mode);
}

long mrc_close(long f)
{
return close(f);

}

 long mrc_fileState(char *filename)
 {
 return filestate(filename);
 }

long mrc_write(long f,void *p,long l)
{
return write(f,p,l);
}

long mrc_read(long f,void *p,long l)
{

return read(f,p,l);
}

long mrc_seek(long f,long pos,int mod)
{

return seek(f,pos,mod);
}

long mrc_getLen(char *filename)
{

return getlen(filename);
}

long mrc_remove(char *filename)
{
return remove(filename);
}

long mrc_rename(char *oldname,char *newname)
{
return rename(oldname,newname);
}
 
long mrc_mkDir(char *name)
{
return mkdir(name);
}

long mrc_rmDir(char *name)
{
return rmdir(name);
}
/*
long mrc_findStart(char *file,char *buffer,long len)
{
return filestart(file,buffer,len);
}*/

long mrc_findGetNext(long handler, char *buffer, long len)
{

return findnext(handler,buffer,len);
}
long mrc_findStop(long handler)
{
return findstop(handler);
}

/********************************��ͼ�ӿ�********************************/

long mrc_drawText(char *text,int x,int y,uint8 r,uint8 g,uint8 b,int is_unicode, uint16 font)
{
return dtext(text,x,y,r,g,b,is_unicode,font);
}


long mrc_drawTextEx(char* pcText, int16 x, int16 y, mr_screenRectSt mr_rect, mr_colourSt mr_color, int flag, uint16 font)
{

return dtextex(pcText,x,y,(rectst*)&mr_rect,(colorst*)&mr_color,flag,font);
}
/*
long mrc_drawTextRight(char *pcText,int x, int y, mr_screenRectSt rect,mr_colourSt color,int flag,uint16 font)
{
return dtextright(pcText,x,y,(rectst*)&rect,(colorst*)&color,flag,font);
}*/


unsigned short *mrc_c2u(char *cp, int32 *err, int32 *size)
{

return c2u(cp,err,size);
}


long mrc_textWidthHeight(char* pcText, int is_unicode, uint16 font, int32* w, int32* h)
{
return textwh(pcText,is_unicode,font,w,h);
}

/*
long mrc_unicodeTextRow(uint16 *pcText,uint16 font,int32 w)
{
return unitextrow(pcText,font,w);
}*/




void mrc_drawRect(int16 x, int16 y, int16 w, int16 h, uint8 r, uint8 g, uint8 b)
{
drect(x,y,w,h,r,g,b);
}

void mrc_drawLine(int16 x1, int16 y1, int16 x2, int16 y2, uint8 r, uint8 g, uint8 b)
{
dline(x1,y1,x2,y2,r,g,b);
}

void mrc_drawPointEx(int16 x, int16 y, int32 r, int32 g, int32 b)
{
dpointex(x,y,r,g,b);
}

void mrc_drawPoint(int16 x, int16 y, uint16 nativecolor)
{
dpoint(x,y,nativecolor);
}

void mrc_clearScreen(long r,long g,long b)
{
cls(r,g,b);
}



void mrc_refreshScreen(int16 x, int16 y, uint16 w, uint16 h)
{
ref(x,y,w,h);
}

void mrc_EffSetCon(int16 x, int16 y, int16 w, int16 h, int16 perr, int16 perg, int16 perb)
{
effsetcon(x,y,w,h,perr,perg,perb);
}



/********************************���ػ�UI�ӿ�********************************/
/*

#define menucreate mrc_menuCreate

#define menuset mrc_menuSetItem

#define menushow mrc_menuShow
#define menudel mrc_menuRelease

#define menuref mrc_menuRefresh
#define dlgcreate mrc_dialogCreate

#define dlgdel mrc_dialogRelease
#define dlgref mrc_dialogRefresh
#define textcreate mrc_textCreate
#define textdel mrc_textRelease
#define textref mrc_textRefresh



#define editcreate mrc_editCreate
#define editdel mrc_editRelease

#define editget mrc_editGetText
*/
int mrc_editCreate( char * title,  char * text, int32 type, int32 max_size)
{
return editcreate(title,text,type,max_size);
}

int mrc_editRelease(int32 edit)
{
return editdel(edit);
}


char* mrc_editGetText(int32 edit)
{
return editget(edit);
}

/********************************�����ӿ�********************************/
void mrc_exit()
{
exit();
}

long mrc_getUptime()
{
return getuptime();
}




long mrc_getDatetime(mr_datetime* datetime)
{
return getdatetime((void*)datetime);
}
/*
long mrc_getMemoryRemain()
{
return getmemremain();
}
*/
long mrc_startShake(long time)
{
return shake(time);
}
/*
long mrc_getSysMem()
{
return getsysmem();
}
*/
//#define readfilefrommrp mrc_readFileFromMrpEx
/*
void * mrc_readFileFromMrp( char* filename, int32 *filelen, int32 lookfor)
{
readmrpfile(filename,(void *)filelen);
}
*/

//#define freefiledata mrc_freeFileData
//#define freeorigin mrc_freeOrigin
/*
int32 mrc_unicodeToGb2312(uint8* input, int32 input_len, uint8** output, int32* output_len)
{
return u2c(input,input_len,output,output_len);
}
*/
/*
int mrc_runMrp(char* mrp_name,char* file_name,char* parameter)
{
runmrp(mrp_name,file_name);
return 0;
}
*/
//#define getparentpath mrc_GetParentPath

//#define sand mrc_sand

long mrc_rand()
{
return rand();
}

long mrc_sendSms(char* pNumber, char *pContent, int32 flags)
{
return (long)sms(pNumber,pContent,flags);
}

//#define sms mrc_sendSms

void mrc_LCDCanSleep(char c)
{
lcd(c);
}
void mrc_sleep(uint32 ms)
{
sleep(ms);
}


// ���º���������mrc_bmp.h�ļ���//////////////////////////////////////


uint16 *w_getScreenBuffer()
{
return getscrbuf();
}

//#define getscrsize mrc_getScreenSize
//#define setscrsize mrc_setScreenSize


/*
int bitmapShowFlip(uint16* p, int16 x, int16 y, uint16 mw, uint16 w, uint16 h, uint16 rop, 
int16 sx, int16 sy, uint16 transcolor)
{
return bmpshowflip(p,x, y,mw,w,h,rop,sx,sy,transcolor);
}*/


//#define readall my_readAllEx
//extern void mrc_connectWAP(char* wap);
//#define wap mrc_connectWAP

/********************************��ʱ���ӿ�********************************/

long mrc_timerCreate()
{
return timercreate();
}

void mrc_timerDelete(long time)
{
 timerdel(time);
}

void mrc_timerStop(long time)
{
 timerstop(time);
}

#define mrc_timerStart timerstart

long mrc_timerSetTimeEx(long t,long time)
{
return timersettime(t,time);
}



#endif