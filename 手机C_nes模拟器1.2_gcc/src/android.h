#ifndef _ANDROID_H_
#define _ANDROID_H_
#include "base.h"
#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
enum
{
VIEW_DOWN=20, //控件被按下
VIEW_UP=21 //控件被释放
};

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




extern CMD cmd;
extern ROOTCMD rootCmd;
extern TOAST toast;
extern GETDATAPATH getDataPath;
extern READFILEFROMASSETS readFileFromAssets;
extern SETCONTEXTVIEW setContextView;
extern CREATEVIEW createView;
extern CLEARVIEW clearView;
extern SETORIENTATION setOrientation;
extern SETVIEW setView;

extern FINDVIEWBYID findViewById;
extern ADDVIEW addView;
extern SETVISIBILITY setVisibility;
extern VIEW_SETTEXT view_setText;
extern CLOSEINPUT closeInput;
extern EDIT_GOTO edit_goto;
extern EDIT_SELECTION edit_selection;
extern EDIT_INSERT edit_insert;
extern LOADURL loadUrl;
extern VIDEOSTART videoStart;
extern VIDEOPAUSE videoPause;
extern VIDEOSEEKTO videoSeekTo;
extern SEEKBAR_GETPROGRESS seekbar_getProgress;
extern SEEKBAR_SETPROGRESS seekbar_setProgress;
extern SEEKBAR_SETMAX seekbar_setMax;
extern INPUTMODE inputMode;
extern CLIPGETTEXT clipGetText;
extern LIST_REMOVE list_remove;
extern LIST_GETSIZE list_getSize;
extern LIST_NOTIFYDATA list_notifyData;




#ifdef __cplusplus
}
#endif

#endif
