#include "android.h"

/*
手机C编译模式 系统头文件
最后修改于：2019-11-16
*/

#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif


typedef int (*CMD)(char *text);
typedef int (*ROOTCMD)(char *text);
typedef void (*TOAST)(char *text,int type);
typedef char *(*GETDATAPATH)(char *datafile);
typedef void *(*READFILEFROMASSETS)(char *filename, int *len);
typedef void (*SETCONTEXTVIEW)(char* filename);
typedef int (*CREATEVIEW)(char* name);
typedef void (*CLEARVIEW)();
typedef void (*SETORIENTATION)(int orien);
typedef void (*SETVIEW)(int view,char* words);

typedef int (*FINDVIEWBYID)(int id);
typedef void (*ADDVIEW)(int layout,int view);
typedef void (*SETVISIBILITY)(int view,int visibility);
typedef void (*VIEW_SETTEXT)(int view,char* text);
typedef void (*CLOSEINPUT)();
typedef void (*EDIT_GOTO)(int edit,int start);
typedef void (*EDIT_SELECTION)(int edit,int start,int end);
typedef void (*EDIT_INSERT)(int edit,int start,char* text);
typedef void (*LOADURL)(int view,char *url);
typedef void (*VIDEOSTART)(int id);

typedef void (*VIDEOPAUSE)(int id);
typedef void (*VIDEOSEEKTO)(int id,int time);
typedef int (*SEEKBAR_GETPROGRESS)(int view);
typedef void (*SEEKBAR_SETPROGRESS)(int view,int progress);
typedef void (*SEEKBAR_SETMAX)(int view,int max);
typedef int (*INPUTMODE)();
typedef char (**CLIPGETTEXT)();
typedef void (*LIST_REMOVE)(int view,int pos);
typedef int (*LIST_GETSIZE)(int view);
typedef void (*LIST_NOTIFYDATA)(int view);




CMD cmd;
ROOTCMD rootCmd;
TOAST toast;
GETDATAPATH getDataPath;
READFILEFROMASSETS readFileFromAssets;
SETCONTEXTVIEW setContextView;
CREATEVIEW createView;
CLEARVIEW clearView;
SETORIENTATION setOrientation;
SETVIEW setView;

FINDVIEWBYID findViewById;
ADDVIEW addView;
SETVISIBILITY setVisibility;
VIEW_SETTEXT view_setText;
CLOSEINPUT closeInput;
EDIT_GOTO edit_goto;
EDIT_SELECTION edit_selection;
EDIT_INSERT edit_insert;
LOADURL loadUrl;
VIDEOSTART videoStart;
VIDEOPAUSE videoPause;
VIDEOSEEKTO videoSeekTo;
SEEKBAR_GETPROGRESS seekbar_getProgress;
SEEKBAR_SETPROGRESS seekbar_setProgress;
SEEKBAR_SETMAX seekbar_setMax;
INPUTMODE inputMode;
CLIPGETTEXT clipGetText;
LIST_REMOVE list_remove;
LIST_GETSIZE list_getSize;
LIST_NOTIFYDATA list_notifyData;

int android_add(char* name, void* ptr)
{
 if(!strcmp(name, "cmd"))
 {
 cmd=(CMD)ptr;
 }
 else if(!strcmp(name, "rootCmd"))
 {
 rootCmd=(ROOTCMD)ptr;
 }
 else if(!strcmp(name, "toast"))
 {
 toast=(TOAST)ptr;
 }
 else if(!strcmp(name, "getDataPath"))
 {
 getDataPath=(GETDATAPATH)ptr;
 }
 else if(!strcmp(name, "readFileFromAssets"))
 {
 readFileFromAssets=(READFILEFROMASSETS)ptr;
 }
 else if(!strcmp(name, "setContextView"))
 {
 setContextView=(SETCONTEXTVIEW)ptr;
 }
 else if(!strcmp(name, "createView"))
 {
 createView=(CREATEVIEW)ptr;
 }
 else if(!strcmp(name, "clearView"))
 {
 clearView=(CLEARVIEW)ptr;
 }
 else if(!strcmp(name, "setOrientation"))
 {
 setOrientation=(SETORIENTATION)ptr;
 }
 else if(!strcmp(name, "setView"))
 {
 setView=(SETVIEW)ptr;
 }
 
 if(!strcmp(name, "findViewById"))
 {
 findViewById=(FINDVIEWBYID)ptr;
 }
 else if(!strcmp(name, "addView"))
 {
 addView=(ADDVIEW)ptr;
 }
 else if(!strcmp(name, "setVisibility"))
 {
 setVisibility=(SETVISIBILITY)ptr;
 }
 else if(!strcmp(name, "view_setText"))
 {
 view_setText=(VIEW_SETTEXT)ptr;
 }
 else if(!strcmp(name, "closeInput"))
 {
 closeInput=(CLOSEINPUT)ptr;
 }
 else if(!strcmp(name, "edit_goto"))
 {
 edit_goto=(EDIT_GOTO)ptr;
 }
 else if(!strcmp(name, "edit_selection"))
 {
 edit_selection=(EDIT_SELECTION)ptr;
 }
 else if(!strcmp(name, "edit_insert"))
 {
 edit_insert=(EDIT_INSERT)ptr;
 }
 else if(!strcmp(name, "loadUrl"))
 {
 loadUrl=(LOADURL)ptr;
 }
 else if(!strcmp(name, "videoStart"))
 {
 videoStart=(VIDEOSTART)ptr;
 }
 
 if(!strcmp(name, "videoPause"))
 {
 videoPause=(VIDEOPAUSE)ptr;
 }
 else if(!strcmp(name, "videoSeekTo"))
 {
 videoSeekTo=(VIDEOSEEKTO)ptr;
 }
 else if(!strcmp(name, "seekbar_getProgress"))
 {
 seekbar_getProgress=(SEEKBAR_GETPROGRESS)ptr;
 }
 else if(!strcmp(name, "seekbar_setProgress"))
 {
 seekbar_setProgress=(SEEKBAR_SETPROGRESS)ptr;
 }
 else if(!strcmp(name, "seekbar_setMax"))
 {
 seekbar_setMax=(SEEKBAR_SETMAX)ptr;
 }
 else if(!strcmp(name, "inputMode"))
 {
 inputMode=(INPUTMODE)ptr;
 }
 else if(!strcmp(name, "clipGetText"))
 {
 clipGetText=(CLIPGETTEXT)ptr;
 }
 else if(!strcmp(name, "list_remove"))
 {
 list_remove=(LIST_REMOVE)ptr;
 }
 else if(!strcmp(name, "list_getSize"))
 {
 list_getSize=(LIST_GETSIZE)ptr;
 }
 else if(!strcmp(name, "list_notifyData"))
 {
 list_notifyData=(LIST_NOTIFYDATA)ptr;
 }
 else
 {
  //app_printf("未知函数%s\n",name);
 }
 
 
 return 0;
}


#ifdef __cplusplus
}
#endif


