
#ifndef _SOUND_H_
#define _SOUND_H_
#include "./base.h"

/* 要使用以下所有接口请在你的代码中增加“#include "base.h"”和“#include "sound.h"” */


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
 soundinit=ptr;
 }
 else if(!strcmp(name, "soundloadfile"))
 {
 soundloadfile=ptr;
 }
 else if(!strcmp(name, "soundplay"))
 {
 soundplay=ptr;
 }
 else if(!strcmp(name, "soundpause"))
 {
 soundpause=ptr;
 }
 else if(!strcmp(name, "soundresume"))
 {
 soundresume=ptr;
 }
 else if(!strcmp(name, "soundstop"))
 {
 soundstop=ptr;
 }
 else if(!strcmp(name, "soundclose"))
 {
 soundclose=ptr;
 }
 else if(!strcmp(name, "setvolume"))
 {
 setvolume=ptr;
 }
 else if(!strcmp(name, "getsoundtotaltime"))
 {
 getsoundtotaltime=ptr;
 }
 else if(!strcmp(name, "getsoundcurtime"))
 {
 getsoundcurtime=ptr;
 }
 else if(!strcmp(name, "getsoundcurtimems"))
 {
 getsoundcurtimems=ptr;
 }
 else if(!strcmp(name, "setplaypos"))
 {
 setplaypos=ptr;
 }
 else if(!strcmp(name, "setplaytime"))
 {
 setplaytime=ptr;
 }
 else if(!strcmp(name, "getdevicestate"))
 {
 getdevicestate=ptr;
 }
 
 return 0;
}


#endif