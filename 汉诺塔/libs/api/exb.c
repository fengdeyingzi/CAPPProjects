

#include "base.h"
#include "exb.h"

/*
手机C编译模式 系统头文件 exb.c
最后修改于：2021-05-19
*/

#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif


SWITCHPATH switchPath;
FV_INIT fv_init;
FV_SETTYPE fv_settype;
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

LOADDEX loadDex;
LOADCLASS loadClass;
RUNCLASS runClass;
DEX_PUTSTRING dex_putString;

EX_CODING ex_coding;
TOUCH_ISDOWN touch_isdown;
TOUCH_GETX touch_getx;
TOUCH_GETY touch_gety;


int exb_add(char *name,void *ptr)
{
 if(!strcmp(name, "switchPath"))
 {
  switchPath=(SWITCHPATH)ptr;
 }
 if(!strcmp(name, "fv_init"))
 {
  fv_init = (FV_INIT)ptr;
 }
		if(!strcmp(name, "fv_settype"))
 {
 fv_settype=(FV_SETTYPE)ptr;
 }
 else if(!strcmp(name, "fv_begin"))
 {
 fv_begin=(FV_BEGIN)ptr;
 }
 else if(!strcmp(name,"fv_getpath"))
 {
  fv_getpath = (FV_GETPATH)ptr;
 }
 else if(!strcmp(name, "fv_end"))
 {
 fv_end=(FV_END)ptr;
 }
 else if(!strcmp(name, "setpadtype"))
 {
 setpadtype=(SETPADTYPE)ptr;
 }
 else if(!strcmp(name, "getkeypressed"))
 {
 getkeypressed=(GETKEYPRESSED)ptr;
 }
 else if(!strcmp(name, "setTextSize"))
 {
 setTextSize=(SETTEXTSIZE)ptr;
 }
 else if(!strcmp(name, "unZip"))
 {
 unZip=(UNZIP)ptr;
 }
 else if(!strcmp(name, "sensorOn"))
 {
 sensorOn=(SENSORON)ptr;
 }
 else if(!strcmp(name, "sensorStart"))
 {
 sensorStart=(SENSORSTART)ptr;
 }
 else if(!strcmp(name, "sensorStop"))
 {
 sensorStop=(SENSORSTOP)ptr;
 }
 else if(!strcmp(name, "sensorOff"))
 {
 sensorOff=(SENSOROFF)ptr;
 }
 else if(!strcmp(name, "loadDex"))
 {
 loadDex=(LOADDEX)ptr;
 }
 else if(!strcmp(name, "loadClass"))
 {
 loadClass=(LOADCLASS)ptr;
 }
 else if(!strcmp(name, "runClass"))
 {
 runClass=(RUNCLASS)ptr;
 }
 else if(!strcmp(name, "dex_putString"))
 {
 dex_putString=(DEX_PUTSTRING)ptr;
 }
 else if(!strcmp(name, "ex_coding"))
 {
 ex_coding=(EX_CODING)ptr;
 }
 else if(!strcmp(name,"touch_isdown")){
  touch_isdown = (TOUCH_ISDOWN)ptr;
 }
 else if(!strcmp(name, "touch_getx")){
  touch_getx = (TOUCH_GETX)ptr;
 }
 else if(!strcmp(name,"touch_gety")){
  touch_gety = (TOUCH_GETY)ptr;
 }
 
 
 return 0;
}

#ifdef __cplusplus
}
#endif

