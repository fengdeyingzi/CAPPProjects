#ifndef _C_EXB_H_
#define _C_EXB_H_

#include "./base.h"
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




typedef char* (*EX_CODING)(char *text, int len, char *coding, char *tocoding);

SWITCHPATH switchPath;
FV_INIT fv_init;
FV_SETTYPE fv_setype;
FV_BEGIN fv_begin;
FV_GETPATH fv_getpath;
FV_END fv_end;
SETPADTYPE setpadtype;
GETKEYPRESSED getkeypressed;
SETTEXTSIZE setTextSize;
UNZIP unZip;
SENSORON sensorOn;
SENSORSTART sensorStart;
SENSORSTOP sensorStop;
SENSOROFF sensorOff;



EX_CODING ex_coding;

int exb_add(char *name,void *ptr)
{
 if(!strcmp(name, "switchPath"))
 {
  switchPath=ptr;
 }
 if(!strcmp(name, "fv_init"))
 {
  fv_init = ptr;
 }
		if(!strcmp(name, "fv_setype"))
 {
 fv_setype=ptr;
 }
 else if(!strcmp(name, "fv_begin"))
 {
 fv_begin=ptr;
 }
 else if(!strcmp(name,"fv_getpath"))
 {
  fv_getpath = ptr;
 }
 else if(!strcmp(name, "fv_end"))
 {
 fv_end=ptr;
 }
 else if(!strcmp(name, "setpadtype"))
 {
 setpadtype=ptr;
 }
 else if(!strcmp(name, "getkeypressed"))
 {
 getkeypressed=ptr;
 }
 else if(!strcmp(name, "setTextSize"))
 {
 setTextSize=ptr;
 }
 else if(!strcmp(name, "unZip"))
 {
 unZip=ptr;
 }
 else if(!strcmp(name, "sensorOn"))
 {
 sensorOn=ptr;
 }
 else if(!strcmp(name, "sensorStart"))
 {
 sensorStart=ptr;
 }
 else if(!strcmp(name, "sensorStop"))
 {
 sensorStop=ptr;
 }
 else if(!strcmp(name, "sensorOff"))
 {
 sensorOff=ptr;
 }

 else if(!strcmp(name, "ex_coding"))
 {
 ex_coding=ptr;
 }
 
 return 0;
}



#endif