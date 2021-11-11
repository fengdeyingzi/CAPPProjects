#ifndef _C_EXB_H_
#define _C_EXB_H_


#include "base.h"
#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

//#define fv_init
#define fv_setType fv_settype
#define fv_beginView fv_begin
#define fv_getPath fv_getpath
//#define fv_end
#define getKeyPressed getkeypressed
#define setPadType setpadtype
#define setTextSize mrc_setTextSize
//#define unZip
//#define mrc_motionSensorPowerOff
//#define mrc_motionSensorStopListen
//#define mrc_motionSensorStart
typedef void (*SWITCHPATH)(char *name);
typedef int (*FV_INIT)(int type);
typedef int (*FV_SETTYPE)(char *text,int type);
typedef int (*FV_BEGIN)(char *path);
typedef char* (*FV_GETPATH)();
typedef int (*FV_END)();
typedef void (*SETPADTYPE)(int type);
typedef int (*GETKEYPRESSED)(int32 key);
typedef void (*SETTEXTSIZE)(int font,int size);
typedef void (*UNZIP)(char *filename, char *path);
typedef int (*SENSORON)();
typedef int (*SENSORSTART)(int sensor);
typedef int (*SENSORSTOP)();
typedef int (*SENSOROFF)();

typedef int32 (*LOADDEX)(char *filename);
typedef 
int32 (*LOADCLASS)(int32 loader, char *classname);
typedef 
int32 (*RUNCLASS)(int32 obj);
typedef 
char* (*DEX_PUTSTRING)(int obj,char *data);


typedef char* (*EX_CODING)(char *text,int len, char *coding, char *tocoding);
typedef int (*TOUCH_ISDOWN)(int id);
typedef int (*TOUCH_GETX)(int id);
typedef int (*TOUCH_GETY)(int id);

extern SWITCHPATH switchPath;
extern FV_INIT fv_init;
extern FV_SETTYPE fv_settype;
extern FV_BEGIN fv_begin;
extern FV_GETPATH fv_getpath;
extern FV_END fv_end;
extern SETPADTYPE setpadtype;
extern GETKEYPRESSED getkeypressed;
extern SETTEXTSIZE setTextSize;
extern UNZIP unZip;
extern SENSORON sensorOn;
extern SENSORSTART sensorStart;
extern SENSORSTOP sensorStop;
extern SENSOROFF sensorOff;

extern LOADDEX loadDex;
extern LOADCLASS loadClass;
extern RUNCLASS runClass;
extern DEX_PUTSTRING dex_putString;

extern EX_CODING ex_coding;
extern TOUCH_ISDOWN touch_isdown;
extern TOUCH_GETX touch_getx;
extern TOUCH_GETY touch_gety;


#ifdef __cplusplus
}
#endif

#endif