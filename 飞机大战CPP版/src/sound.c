
#include "base.h"
#include "sound.h"

/*
手机C 编译模式 系统头文件sound.h
最后修改于：2021-05-19
*/

/* 要使用以下所有接口请在你的代码中增加“#include "base.h"”和“#include "sound.h"” */


//系统没有预先定义以下结构

#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

SOUNDINIT soundinit;
SOUNDLOADFILE soundloadfile;
SOUNDPLAY soundplay;
SOUNDPAUSE soundpause;
SOUNDRESUME soundresume;
SOUNDSTOP soundstop;
SOUNDCLOSE soundclose;
SETVOLUME setvolume;
GETSOUNDTOTALTIME getsoundtotaltime;
GETSOUNDCURTIME getsoundcurtime;
GETSOUNDCURTIMEMS getsoundcurtimems;
SETPLAYTIME setplaytime;
SETPLAYPOS setplaypos;
GETDEVICESTATE getdevicestate;



int sound_add(char* name,void* ptr)
{
 if(!strcmp(name, "soundinit"))
 {
 soundinit=(SOUNDINIT)ptr;
 }
 else if(!strcmp(name, "soundloadfile"))
 {
 soundloadfile=(SOUNDLOADFILE)ptr;
 }
 else if(!strcmp(name, "soundplay"))
 {
 soundplay=(SOUNDPLAY)ptr;
 }
 else if(!strcmp(name, "soundpause"))
 {
 soundpause=(SOUNDPAUSE)ptr;
 }
 else if(!strcmp(name, "soundresume"))
 {
 soundresume=(SOUNDRESUME)ptr;
 }
 else if(!strcmp(name, "soundstop"))
 {
 soundstop=(SOUNDSTOP)ptr;
 }
 else if(!strcmp(name, "soundclose"))
 {
 soundclose=(SOUNDCLOSE)ptr;
 }
 else if(!strcmp(name, "setvolume"))
 {
 setvolume=(SETVOLUME)ptr;
 }
 else if(!strcmp(name, "getsoundtotaltime"))
 {
 getsoundtotaltime=(GETSOUNDTOTALTIME)ptr;
 }
 else if(!strcmp(name, "getsoundcurtime"))
 {
 getsoundcurtime=(GETSOUNDCURTIME)ptr;
 }
 else if(!strcmp(name, "getsoundcurtimems"))
 {
 getsoundcurtimems=(GETSOUNDCURTIMEMS)ptr;
 }
 else if(!strcmp(name, "setplaypos"))
 {
 setplaypos=(SETPLAYPOS)ptr;
 }
 else if(!strcmp(name, "setplaytime"))
 {
 setplaytime=(SETPLAYTIME)ptr;
 }
 else if(!strcmp(name, "getdevicestate"))
 {
 getdevicestate=(GETDEVICESTATE)ptr;
 }
 
 return 0;
}


#ifdef __cplusplus
}
#endif