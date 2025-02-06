
#ifndef _SOUND_H_
#define _SOUND_H_
#include "base.h"

/* 要使用以下所有接口请在你的代码中增加“#include "base.h"”和“#include "sound.h"” */

#ifdef __cplusplus
#include <iostream>
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

//系统没有预先定义以下结构

typedef struct
{
int32 pos;
}T_DSM_AUDIO_POS;



typedef int32 (*SOUNDINIT)(int32 type);
typedef int32 (*SOUNDLOADFILE)(int32 type, char* filename);
typedef int32 (*SOUNDPLAY)(int32 type, int32 block, int32 loop);
typedef int32 (*SOUNDPAUSE)(int32 type);
typedef int32 (*SOUNDRESUME)(int32 type);
typedef int32 (*SOUNDSTOP)(int32 type);
typedef int32 (*SOUNDCLOSE)(int32 type);
typedef int32 (*SETVOLUME)(int32 volume);
typedef int32 (*GETSOUNDTOTALTIME)(int32 type, uint8** p);;
typedef int32 (*GETSOUNDCURTIME)(int32 type, uint8** p);
typedef int32 (*GETSOUNDCURTIMEMS)(int32 type, uint8** p);
typedef int32 (*SETPLAYPOS)(int32 type,T_DSM_AUDIO_POS* pos);
typedef int32 (*SETPLAYTIME)(int32 type,T_DSM_AUDIO_POS* pos);
typedef int32 (*GETDEVICESTATE)(int32 type);

extern SOUNDINIT soundinit;
extern SOUNDLOADFILE soundloadfile;
extern SOUNDPLAY soundplay;
extern SOUNDPAUSE soundpause;
extern SOUNDRESUME soundresume;
extern SOUNDSTOP soundstop;
extern SOUNDCLOSE soundclose;
extern SETVOLUME setvolume;
extern GETSOUNDTOTALTIME getsoundtotaltime;
extern GETSOUNDCURTIME getsoundcurtime;
extern GETSOUNDCURTIMEMS getsoundcurtimems;
extern SETPLAYTIME setplaytime;
extern SETPLAYPOS setplaypos;
extern GETDEVICESTATE getdevicestate;

extern int sound_add(char* name,void* ptr);

#ifdef __cplusplus
}
#endif


#endif