
/*

手机C编译模式头文件
最后修改于 2020-06-03
*/
#include "base.h"
//#include <stdlib.h>
//#include <string.h>
#include <jni.h>
//vsprintf
//#include <stdarg.h>

#define TCC 1

#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
//#include <base.h>
/*
base.h
用于gcc编译

最后修改时间 2018.6.19


gcc编译静态库 资料
http://m.blog.chinaunix.net/uid-261392-id-2138941.html





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

//文件操作相关
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
EDITGET editget;
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
JNIEnv *env;
BMPSHOWFLIP bmpshowflip;


/*
接口初始化
name 函数名
ptr 函数指针
*/
int base_add(char* name,void* ptr)
{
 
	if(!strcmp(name, "printf"))
 {
 app_printf=(PRINTF)ptr;
 }
 else if(!strcmp(name, "sprintf"))
 {
 app_sprintf=(SPRINTF)ptr;
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
  getJNIEnv = (GETJNIENV)ptr;
 }
 if(!strcmp(name,"getContext"))
 {
  getContext = (GETCONTEXT)ptr;
 }
 if(!strcmp(name, "getCacheBitmap"))
 {
  getCacheBitmap = (GETCACHEBITMAP)ptr;
 }
 if(!strcmp(name,"getScreenWidth"))
 {
  getScreenWidth = (GETSCREENWIDTH)ptr;
 }
 if(!strcmp(name,"getScreenHeight"))
 {
  getScreenHeight = (GETSCREENHEIGHT)ptr;
 }
  if(!strcmp(name, "wstrlen"))
 {
 wstrlen=(WSTRLEN)ptr;
 }
 else if(!strcmp(name,"u2c"))
 {
		 u2c = (U2C)ptr;
 }
 else if(!strcmp(name,"c2u"))
 {
		 c2u= (C2U)ptr;
 }
 
 else if(!strcmp(name, "sleep"))
 {
 sleep=(SLEEP)ptr;
 }
 
 else if(!strcmp(name, "drect"))
 {
 drect=(DRECT)ptr;
 }
 else if(!strcmp(name, "dline"))
 {
 dline=(DLINE)ptr;
 }
 else if(!strcmp(name, "dpoint"))
 {
 dpoint=(DPOINT)ptr;
 }
 else if(!strcmp(name, "dpointex"))
 {
 dpointex=(DPOINTEX)ptr;
 }
 else if(!strcmp(name, "cls"))
 {
 cls=(CLS)ptr;
 }
 else if(!strcmp(name, "ref"))
 {
 ref=(REF)ptr;
 }
 else if(!strcmp(name, "dtext"))
 {
 dtext=(DTEXT)ptr;
 }
 else if(!strcmp(name, "dtextex"))
 {
 dtextex=(DTEXTEX)ptr;
 }
 else if(!strcmp(name, "dtextright"))
 {
 dtextright=(DTEXTRIGHT)ptr;
 }
 else if(!strcmp(name, "effsetcon"))
 {
 effsetcon=(EFFSETCON)ptr;
 }
 else if(!strcmp(name, "img"))
 {
 img=(IMG)ptr;
 }
 else if(!strcmp(name, "shaderect"))
 {
 shaderect=(SHADERECT)ptr;
 }
 else if(!strcmp(name, "textwh"))
 {
 textwh=(TEXTWH)ptr;
 }
 else if(!strcmp(name, "unitextrow"))
 {
 unitextrow=(UNITEXTROW)ptr;
 }
 //文件操作
 else if(!strcmp(name, "open"))
 {
 app_open=(OPEN)ptr;
 }
 
 else if(!strcmp(name, "close"))
 {
 app_close=(CLOSE)ptr;
 }
 else 
 if(!strcmp(name, "filestate"))
 {
 app_filestate=(FILESTATE)ptr;
 }
 else if(!strcmp(name, "write"))
 {
 app_write=(WRITE)ptr;
 }
 
 else if(!strcmp(name, "read"))
 {
 app_read=(READ)ptr;
 }
 else if(!strcmp(name, "seek"))
 {
 app_seek=(SEEK)ptr;
 }
 else if(!strcmp(name, "getlen"))
 {
 app_getlen=(GETLEN)ptr;
 }
 else if(!strcmp(name, "remove"))
 {
 app_remove=(REMOVE)ptr;
 }
 else if(!strcmp(name, "rename"))
 {
 app_rename=(RENAME)ptr;
 }
 else if(!strcmp(name, "mkdir"))
 {
 app_mkdir=(MKDIR)ptr;
 }
 else if(!strcmp(name, "rmdir"))
 {
 app_rmdir=(RMDIR)ptr;
 }
 else if(!strcmp(name, "findstart"))
 {
 findstart=(FINDSTART)ptr;
 }
 else if(!strcmp(name, "findnext"))
 {
 findnext=(FINDNEXT)ptr;
 }
 else if(!strcmp(name, "findstop"))
 {
 findstop=(FINDSTOP)ptr;
 }
 else if(!strcmp(name, "dlgcreate"))
 {
 dlgcreate=(DLGCREATE)ptr;
 }
 else if(!strcmp(name, "dlgdel"))
 {
 dlgdel=(DLGDEL)ptr;
 }
 else if(!strcmp(name, "dlgref"))
 {
 dlgref=(DLGREF)ptr;
 }
 else if(!strcmp(name, "textcreate"))
 {
 textcreate=(TEXTCREATE)ptr;
 }
 else if(!strcmp(name, "textdel"))
 {
 textdel=(TEXTDEL)ptr;
 }
 else if(!strcmp(name, "textref"))
 {
 textref=(TEXTREF)ptr;
 }
 else if(!strcmp(name, "editcreate"))
 {
 editcreate=(EDITCREATE)ptr;
 }
 else if(!strcmp(name, "editget"))
 {
  editget=(EDITGET)ptr;
 }
 else if(!strcmp(name, "editdel"))
 {
 editdel=(EDITDEL)ptr;
 }
 else if(!strcmp(name, "timercreate"))
 {
 timercreate=(TIMERCREATE)ptr;
 }
 else if(!strcmp(name, "timerdel"))
 {
 timerdel=(TIMERDEL)ptr;
 }
 else if(!strcmp(name, "timerstop"))
 {
 timerstop=(TIMERSTOP)ptr;
 }
 else if(!strcmp(name, "timerstart"))
 {
 timerstart=(TIMERSTART)ptr;
 }
 else if(!strcmp(name, "timersettime"))
 {
 timersettime=(TIMERSETTIME)ptr;
 }
 else if(!strcmp(name, "getscrbuf"))
 {
 getscrbuf=(GETSCRBUF)ptr;
 }
 else if(!strcmp(name, "getscrsize"))
 {
 getscrsize=(GETSCRSIZE)ptr;
 }
 else if(!strcmp(name, "setscrsize"))
 {
 setscrsize=(SETSCRSIZE)ptr;
 }
 
 else if(!strcmp(name, "exit"))
 {
 app_exit=(EXIT)ptr;
 }
 
 else if(!strcmp(name, "getuptime"))
 {
 getuptime=(GETUPTIME)ptr;
 }
 else if(!strcmp(name, "getdatetime"))
 {
 getdatetime=(GETDATETIME)ptr;
 }
 else if(!strcmp(name, "shake"))
 {
 shake=(SHAKE)ptr;
 }
 else if(!strcmp(name, "sand"))
 {
 app_sand=(SAND)ptr;
 }
 else if(!strcmp(name, "rand"))
 {
 app_rand=(RAND)ptr;
 }
 else if(!strcmp(name, "sms"))
 {
 sms=(SMS)ptr;
 }
 else if(!strcmp(name, "lcd"))
 {
 lcd=(LCD)ptr;
 }
 else if(!strcmp(name, "bmpshowflip"))
 {
  bmpshowflip = (BMPSHOWFLIP)ptr;
 }
 
	return 1;
}





#ifdef __cplusplus
}
#endif

