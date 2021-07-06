#ifndef _ANDROID_H_
#define _ANDROID_H_
#include "base.h"
#ifdef __cplusplus
#include <iostream>

/*
手机C编译模式 系统头文件
最后修改于：2021-06-03
*/
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
typedef int32 (*CREATEVIEW)(char* name);
typedef void (*CLEARVIEW)();
typedef void (*SETORIENTATION)(int orien);
typedef void (*SETVIEW)(int32 view,char* words);
typedef void (*SETTITLE)(char *title);

typedef int32 (*FINDVIEWBYID)(int id);
typedef void (*ADDVIEW)(int32 layout,int32 view);
typedef void (*SETVISIBILITY)(int32 view,int visibility);
typedef void (*VIEW_SETTEXT)(int32 view,char* text);
typedef void (*CLOSEINPUT)();
typedef void (*EDIT_GOTO)(int32 edit,int start);
typedef void (*EDIT_SELECTION)(int32 edit,int start,int end);
typedef void (*EDIT_INSERT)(int32 edit,int start,char* text);
typedef void (*LOADURL)(int32 view,char *url);
typedef void (*VIDEOSTART)(int32 id);

typedef void (*VIDEOPAUSE)(int32 id);
typedef void (*VIDEOSEEKTO)(int32 id,int time);
typedef int (*SEEKBAR_GETPROGRESS)(int32 view);
typedef void (*SEEKBAR_SETPROGRESS)(int32 view,int progress);
typedef void (*SEEKBAR_SETMAX)(int32 view,int max);
typedef int (*INPUTMODE)();
typedef char (**CLIPGETTEXT)();
typedef void (*LIST_REMOVE)(int32 view,int pos);
typedef int (*LIST_GETSIZE)(int32 view);
typedef void (*LIST_NOTIFYDATA)(int32 view);
typedef char* (*EX_CALL)(char *action, char *text);
typedef void (*SETVIEW)(int32 view,char *text);



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
extern SETTITLE setTitle;

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
extern EX_CALL ex_call;
extern SETVIEW setView;



#ifdef __cplusplus
}
#endif

#endif
