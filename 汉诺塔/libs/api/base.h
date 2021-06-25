#ifndef _BASE_H_
#define _BASE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>
//vsprintf
#include <stdarg.h>

#define TCC 1


//#include <base.h>
/*
base.h
����gcc����

����޸�ʱ�� 2018.6.19


gcc���뾲̬�� ����
http://m.blog.chinaunix.net/uid-261392-id-2138941.html





*/

//ϵͳ�汾����������ĸ��£����ܻ������Щ�������ꡢ���͵Ȳ�һ�¶��������г���
//������Դ�����ж�ϵͳ�汾�Ƿ���ͬ
#define _VERSION 3100


typedef unsigned short uint16; //�з���16bit����
typedef unsigned long int uint32; //�޷���32bit����
typedef long int int32; //�з���32bit����
typedef unsigned char uint8; //�޷���8bit����
typedef signed char int8; //�з���8bit����
typedef signed short int16; //�з���16bit����

//��������Ϊ�󲿷�ϵͳ�����ķ���ֵ��û����ϵͳ�ڶ��壬�����Ҫ��Щ�궨����������ͷ�ļ��ж���
#define MR_SUCCESS 0 //�ɹ�
#define MR_FAILED -1 //ʧ��
#define MR_IGNORE 1 //������
#define MR_WAITING 2 //�첽(������)ģʽ

//#define NULL (void*)0
#define TRUE 1
#define FALSE 0


//��������ֵ��δ�������������Ҳ����ʹ�ã�����֪�����ֵ��
enum {
_0, //���� 0
_1, //���� 1
_2, //���� 2
_3, //���� 3
_4, //���� 4
_5, //���� 5
_6, //���� 6
_7, //���� 7
_8, //���� 8
_9, //���� 9
_STAR, //���� *
_POUND, //���� #
_UP, //���� ��
_DOWN, //���� ��
_LEFT, //���� ��
_RIGHT, //���� ��
_SLEFT=17, //���� �����
_SRIGHT, //���� �����
_MENU=17, //�˵���
_BACK, //���ؼ�
_SEND, //���� ������
_SELECT //���� ȷ��/ѡ����������м���ȷ�ϼ���������Ϊ�ü���
};

//�����¼��������¼����Լ����壩
enum {
KY_DOWN, //��������
KY_UP, //�����ͷ�
MS_DOWN, //��갴��
MS_UP, //����ͷ�
MN_SLT, //�˵�ѡ��
MN_RET, //�˵�����
MR_DIALOG, //�Ի���
MS_MOVE=12 //����ƶ�
};

enum {
DLG_OK, //�Ի���/�ı���ȵ�"ȷ��"�������(ѡ��)
DLG_CANCEL //�Ի���/�ı���ȵ�"ȡ��"("����")�������(ѡ��)
};
/*
enum {
SEEK_SET, //���ļ���ʼ��ʼ
SEEK_CUR, //�ӵ�ǰλ�ÿ�ʼ
SEEK_END //���ļ�ĩβ��ʼ
};
*/
enum {
IS_FILE=1, //�ļ�
IS_DIR=2, //Ŀ¼
IS_INVALID=8, //��Ч(���ļ�����Ŀ¼)
};

typedef struct {
uint16 x;
uint16 y;
uint16 w;
uint16 h;
}rectst;

typedef struct {
uint8 r;
uint8 g;
uint8 b;
}colorst;

typedef JNIEnv *(*GETJNIENV)();
typedef jobject (*GETCONTEXT)();
typedef jobject (*GETCACHEBITMAP)();

typedef int (*GETSCREENWIDTH)();
typedef int (*GETSCREENHEIGHT)();
typedef void (*PRINTF)(const char *format,...);
typedef void (*FREE)(void *address);
typedef void *(*MEMCPY)(void *dest, void *src, unsigned int count);
typedef void *(*MEMMOVE)(void *dest, const void *src, unsigned int count);
typedef char *(*STRCPY)(char *dest,char *src);
typedef char *(*STRNCPY)(char *dest, char *src, int32 n);
typedef char *(*STRCAT)(char *dest,char *src);
typedef char *(*STRNCAT)(char *dest,char *src,int n);
typedef int (*MEMCMP)(void *buf1, void *buf2, unsigned int count);


typedef int (*STRCMP)(const char *s1,const char * s2);
typedef int (*STRNCMP)(char *str1, char *str2, int maxlen);
typedef void *(*MEMCHR)(void *buf, char ch, unsigned count);
typedef void *(*MEMSET)(void *s, int ch, unsigned n);
typedef uint32 (*STRLEN)(char *s);
typedef char *(*STRSTR)(char *str1, char *str2);
typedef int (*SPRINTF)(char *str, char *format, ...);
typedef int (*ATOI)(const char *nptr);


typedef uint32 (*STRTOUL)(const char *nptr,char **endptr,int base);
typedef char *(*STRRCHR)(char *str, char c);
typedef int32 (*WSTRLEN)(char *s);
typedef int32 (*U2C)(uint8* input, int32 input_len, uint8** output, int32* output_len);
typedef uint16* (*C2U)(char *cp, int32 *err, int32 *size);

typedef void (*SLEEP)(int ms);
typedef void (*DRECT)(int16 x, int16 y, int16 w, int16 h, uint8 r, uint8 g, uint8 b);
typedef void (*DLINE)(int16 x1, int16 y1, int16 x2, int16 y2, uint8 r, uint8 g, uint8 b);
typedef void (*DPOINT)(int16 x, int16 y, uint16 nativecolor);
typedef void (*DPOINTEX)(int16 x, int16 y, int32 r, int32 g, int32 b);
typedef void (*CLS)(int32 r, int32 g, int32 b);
typedef void (*REF)(int16 x, int16 y, uint16 w, uint16 h);
typedef int32 (*DTEXT)(char* pcText, int16 x, int16 y, uint8 r, uint8 g, uint8 b, int is_unicode, uint16 font);
typedef int32 (*DTEXTEX)(char* pcText, int16 x, int16 y, rectst rect, colorst color, int flag, uint16 font);

typedef int32 (*DTEXTRIGHT)(char* pcText, int16 x, int16 y, rectst rect, colorst color, int flag, uint16 font);
typedef void (*EFFSETCON)(int16 x, int16 y, int16 w, int16 h, int16 perr, int16 perg, int16 perb);
typedef int (*IMG)(char* filename, int x,int y);
typedef void (*SHADERECT)(int x, int y, int w, int h, int32 pixelA, int32 pixelB, int mode);


typedef int32 (*U2C)(uint8* input, int32 input_len,
 uint8** output, int32* output_len);
typedef int32 (*TEXTWH)(char* peText, int is_unicode, uint16 font, int32* w,int32* h);
typedef int32 (*UNITEXTROW)(uint16* pcText,uint16 font, int32 w);


//�ļ�����
typedef int32 (*OPEN)(const char* filename,  uint32 mode);
typedef int32 (*CLOSE)(int32 f);
typedef int32 (*FILESTATE)(const char* filename);
typedef int32 (*WRITE)(int32 f,void *p,uint32 len);
typedef int32 (*READ)(int32 f,void *p,uint32 len);
typedef int32 (*SEEK)(int32 f, int32 pos, int method);
typedef int32 (*GETLEN)(const char* filename);
typedef int32 (*REMOVE)(const char* filename);
typedef int32 (*RENAME)(const char* oldname, const char* newname);

typedef int32 (*MKDIR)(const char* name);
typedef int32 (*RMDIR)(const char* name);
typedef int32 (*FINDSTART)(const char* name, char* buffer, uint32 len);
typedef int32 (*FINDNEXT)(int32 search_handle, char* buffer, uint32 len);
typedef int32 (*FINDSTOP)(int32 search_handle);



typedef int32 (*DLGCREATE)(const char * title, const char * text, int32 type);
typedef int32 (*DLGDEL)(int32 dialog);
typedef int32 (*DLGREF)(int32 dialog, const char * title, const char * text, int32 type);
typedef int32 (*TEXTCREATE)(const char * title, const char * text, int32 type);
typedef int32 (*TEXTDEL)(int32 text);
typedef int32 (*TEXTREF)(int32 handle, const char * title, const char * text);
typedef int32 (*EDITCREATE)(const char * title, const char * text, int32 type, int32 max_size);
typedef int32 (*EDITDEL)(int32 edit);


typedef int32 (*TIMERCREATE)(void);
typedef void (*TIMERDEL)(int32 t);
typedef void (*TIMERSTOP)(int32 t);
typedef void (*timerCB)(int32 data);
typedef int32 (*TIMERSTART)(int32 t, int32 time, int32 data, timerCB f, int32 loop);
typedef int32 (*TIMERSETTIME)(int32 t, int32 time);


typedef uint16 *(*GETSCRBUF)(void);
typedef void (*GETSCRSIZE)(int32 *w,int32 *h);
typedef void (*SETSCRSIZE)(int32 w, int32 h);


typedef void (*EXIT)(void);
typedef int32 (*GETUPTIME)(void);
typedef void (*WAP)(void);


typedef struct
{
uint16 year; //��
uint8 month; //��
uint8 day; //��
uint8 hour; //ʱ��24Сʱ��
uint8 minute; //��
uint8 second; //��
}mr_datetime;

typedef int32 (*GETDATETIME)(mr_datetime* datetime);
typedef int32 (*SHAKE)(int32 ms);
typedef void (*SAND)(uint32 seed);
typedef uint32 (*RAND)(void);
typedef int32 (*SMS)(char* pNumber, char*pContent, int32 flags);
typedef int32 (*LCD)(char CanSleep);



/*
typedef void (*DRECT)(int x,int y,int w,int h);
typedef void (*DLINE)(int x1,int x2,int y1,int y2);
typedef void (*CLS)(int r,int g,int b);
typedef void (*REF)(int x,int y,int w,int h);
*/


GETJNIENV getJNIEnv;
GETCONTEXT getContext;
GETCACHEBITMAP getCacheBitmap;

/*
PRINTF printf;
FREE free;
MEMCPY memcpy;
MEMMOVE memmove;
STRCPY strcpy;
STRNCPY strncpy;
STRCAT strcat;
STRNCAT strncat;
MEMCMP memcmp;
STRCMP strcmp;
STRNCMP strncmp;
MEMCHR memchr;
MEMSET memset;
STRLEN strlen;
STRSTR strstr;

ATOI atoi;
STRTOUL strtoul;
STRRCHR strrchr;
*/
SPRINTF app_sprintf;
GETSCREENWIDTH getScreenWidth;
GETSCREENHEIGHT getScreenHeight;
#define SCRW (getScreenWidth())
#define SCRH (getScreenHeight())

WSTRLEN wstrlen;
SLEEP sleep;
DRECT drect;
DLINE dline;
DPOINT dpoint;
DPOINTEX dpointex;
CLS cls;
REF ref;
DTEXT dtext;
DTEXTEX dtextex;
DTEXTRIGHT dtextright;
EFFSETCON effsetcon;
IMG img;
SHADERECT shaderect;
TEXTWH textwh;
UNITEXTROW unitextrow;
U2C u2c;
C2U c2u;

//�ļ��������
OPEN app_open; //
CLOSE app_close; //
FILESTATE app_filestate; //
WRITE app_write; //
READ app_read; //
SEEK app_seek; //
GETLEN app_getlen; //

REMOVE app_remove; //
RENAME app_rename; //
MKDIR app_mkdir; //
RMDIR app_rmdir; //


FINDSTART findstart;
FINDNEXT findnext;
FINDSTOP findstop;
DLGCREATE dlgcreate;
DLGDEL dlgdel;
DLGREF dlgref;
TEXTCREATE textcreate;
TEXTDEL textdel;
TEXTREF textref;
EDITCREATE editcreate;
EDITDEL editdel;
TIMERCREATE timercreate;
TIMERDEL timerdel;
TIMERSTOP timerstop;
TIMERSTART timerstart;
TIMERSETTIME timersettime;
GETSCRBUF getscrbuf;
GETSCRSIZE getscrsize;
SETSCRSIZE setscrsize;
EXIT app_exit;
GETUPTIME getuptime;
GETDATETIME getdatetime;
SHAKE shake;
SAND app_sand;
RAND app_rand;
PRINTF app_printf;
SMS sms;
LCD lcd;
WAP wap;
JNIEnv *env;

//�궨���油ԭ�к���
#define exit app_exit
#define sand app_sand
//#define rand app_rand
#define printf app_printf
#define sprintf app_sprintf

#define open(a,b) app_open(a,b) //
#define close(a) app_close(a) //
#define filestate app_filestate //
#define write(a,b,c) app_write(a,b,c) //
#define read(f,a,b) app_read(f,a,b) //
#define seek(f,a,b) app_seek(f,a,b) //
#define getlen(a) app_getlen(a) //

#define remove app_remove 
#define rename(a,b) app_rename(a,b) //
#define mkdir(a) app_mkdir(a) //
#define rmdir(a) app_rmdir(a) //





/*
�ӿڳ�ʼ��
name ������
ptr ����ָ��
*/
int base_add(char* name,void* ptr)
{
 
	if(!strcmp(name, "printf"))
 {
 app_printf=ptr;
 }
 else if(!strcmp(name, "sprintf"))
 {
 app_sprintf=ptr;
 }
 /*
 else if(!strcmp(name, "free"))
 {
 free=ptr;
 }
 else if(!strcmp(name, "memcpy"))
 {
 memcpy=ptr;
 }
 else if(!strcmp(name, "memmove"))
 {
 memmove=ptr;
 }
 else if(!strcmp(name, "strcpy"))
 {
 strcpy=ptr;
 }
 else if(!strcmp(name, "strncpy"))
 {
 strncpy=ptr;
 }
 else if(!strcmp(name, "strcat"))
 {
 strcat=ptr;
 }
 else if(!strcmp(name, "strncat"))
 {
 strncat=ptr;
 }
 else if(!strcmp(name, "memcmp"))
 {
 memcmp=ptr;
 }
 else if(!strcmp(name, "strcmp"))
 {
 strcmp=ptr;
 }
 else if(!strcmp(name, "strncmp"))
 {
 strncmp=ptr;
 }
 else if(!strcmp(name, "memchr"))
 {
 memchr=ptr;
 }
 else if(!strcmp(name, "memset"))
 {
 memset=ptr;
 }
 else if(!strcmp(name, "strlen"))
 {
 strlen=ptr;
 }
 else if(!strcmp(name, "strstr"))
 {
 strstr=ptr;
 }
 
 else if(!strcmp(name, "atoi"))
 {
 atoi=ptr;
 }
 else if(!strcmp(name, "strtoul"))
 {
 strtoul=ptr;
 }
 else if(!strcmp(name, "strrchr"))
 {
 strrchr=ptr;
 }
 else
 */
 if(!strcmp(name,"getJNIEnv"))
 {
  getJNIEnv = ptr;
 }
 if(!strcmp(name,"getContext"))
 {
  getContext = ptr;
 }
 if(!strcmp(name, "getCacheBitmap"))
 {
  getCacheBitmap = ptr;
 }
 if(!strcmp(name,"getScreenWidth"))
 {
  getScreenWidth = ptr;
 }
 if(!strcmp(name,"getScreenHeight"))
 {
  getScreenHeight = ptr;
 }
  if(!strcmp(name, "wstrlen"))
 {
 wstrlen=ptr;
 }
 else if(!strcmp(name,"u2c"))
 {
		 u2c = ptr;
 }
 else if(!strcmp(name,"c2u"))
 {
		 c2u= ptr;
 }
 
 else if(!strcmp(name, "sleep"))
 {
 sleep=ptr;
 }
 
 else if(!strcmp(name, "drect"))
 {
 drect=ptr;
 }
 else if(!strcmp(name, "dline"))
 {
 dline=ptr;
 }
 else if(!strcmp(name, "dpoint"))
 {
 dpoint=ptr;
 }
 else if(!strcmp(name, "dpointex"))
 {
 dpointex=ptr;
 }
 else if(!strcmp(name, "cls"))
 {
 cls=ptr;
 }
 else if(!strcmp(name, "ref"))
 {
 ref=ptr;
 }
 else if(!strcmp(name, "dtext"))
 {
 dtext=ptr;
 }
 else if(!strcmp(name, "dtextex"))
 {
 dtextex=ptr;
 }
 else if(!strcmp(name, "dtextright"))
 {
 dtextright=ptr;
 }
 else if(!strcmp(name, "effsetcon"))
 {
 effsetcon=ptr;
 }
 else if(!strcmp(name, "img"))
 {
 img=ptr;
 }
 else if(!strcmp(name, "shaderect"))
 {
 shaderect=ptr;
 }
 else if(!strcmp(name, "textwh"))
 {
 textwh=ptr;
 }
 else if(!strcmp(name, "unitextrow"))
 {
 unitextrow=ptr;
 }
 //�ļ�����
 else if(!strcmp(name, "open"))
 {
 app_open=ptr;
 }
 
 else if(!strcmp(name, "close"))
 {
 app_close=ptr;
 }
 else 
 if(!strcmp(name, "filestate"))
 {
 app_filestate=ptr;
 }
 else if(!strcmp(name, "write"))
 {
 app_write=ptr;
 }
 
 else if(!strcmp(name, "read"))
 {
 app_read=ptr;
 }
 else if(!strcmp(name, "seek"))
 {
 app_seek=ptr;
 }
 else if(!strcmp(name, "getlen"))
 {
 app_getlen=ptr;
 }
 else if(!strcmp(name, "remove"))
 {
 app_remove=ptr;
 }
 else if(!strcmp(name, "rename"))
 {
 app_rename=ptr;
 }
 else if(!strcmp(name, "mkdir"))
 {
 app_mkdir=ptr;
 }
 else if(!strcmp(name, "rmdir"))
 {
 app_rmdir=ptr;
 }
 else if(!strcmp(name, "findstart"))
 {
 findstart=ptr;
 }
 else if(!strcmp(name, "findnext"))
 {
 findnext=ptr;
 }
 else if(!strcmp(name, "findstop"))
 {
 findstop=ptr;
 }
 else if(!strcmp(name, "dlgcreate"))
 {
 dlgcreate=ptr;
 }
 else if(!strcmp(name, "dlgdel"))
 {
 dlgdel=ptr;
 }
 else if(!strcmp(name, "dlgref"))
 {
 dlgref=ptr;
 }
 else if(!strcmp(name, "textcreate"))
 {
 textcreate=ptr;
 }
 else if(!strcmp(name, "textdel"))
 {
 textdel=ptr;
 }
 else if(!strcmp(name, "textref"))
 {
 textref=ptr;
 }
 else if(!strcmp(name, "editcreate"))
 {
 editcreate=ptr;
 }
 else if(!strcmp(name, "editdel"))
 {
 editdel=ptr;
 }
 else if(!strcmp(name, "timercreate"))
 {
 timercreate=ptr;
 }
 else if(!strcmp(name, "timerdel"))
 {
 timerdel=ptr;
 }
 else if(!strcmp(name, "timerstop"))
 {
 timerstop=ptr;
 }
 else if(!strcmp(name, "timerstart"))
 {
 timerstart=ptr;
 }
 else if(!strcmp(name, "timersettime"))
 {
 timersettime=ptr;
 }
 else if(!strcmp(name, "getscrbuf"))
 {
 getscrbuf=ptr;
 }
 else if(!strcmp(name, "getscrsize"))
 {
 getscrsize=ptr;
 }
 else if(!strcmp(name, "setscrsize"))
 {
 setscrsize=ptr;
 }
 
 else if(!strcmp(name, "exit"))
 {
 app_exit=ptr;
 }
 
 else if(!strcmp(name, "getuptime"))
 {
 getuptime=ptr;
 }
 else if(!strcmp(name, "getdatetime"))
 {
 getdatetime=ptr;
 }
 else if(!strcmp(name, "shake"))
 {
 shake=ptr;
 }
 else if(!strcmp(name, "sand"))
 {
 app_sand=ptr;
 }
 else if(!strcmp(name, "rand"))
 {
 app_rand=ptr;
 }
 else if(!strcmp(name, "sms"))
 {
 sms=ptr;
 }
 else if(!strcmp(name, "lcd"))
 {
 lcd=ptr;
 }
 else if(!strcmp(name,"wap"))
 {
  wap = ptr;
 }
	return 1;
}







#endif
