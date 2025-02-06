#include <stdlib.h>
#include "../interpreter.h"
#include "base.h"
#include "mrc_base.h"
#include "picoc.h"

//打包模式
#ifdef C_RUN
//初始数据
const char mrc_base_Defs[] = "\
#define _VERSION 3100\r\n\
#define _VENDOR \"\xb7\xe7\xb5\xc4\xd3\xb0\xd7\xd3\"\r\n\
#define _PLATFORM \"android\"\r\n\
#define _RUN_MODE \"picoc\"\r\n\
typedef unsigned short uint16;\
typedef unsigned long uint32;\
typedef long int32;\
typedef unsigned char uint8;\
typedef char int8;\
typedef short int16;\
typedef struct{uint16 x;uint16 y;uint16 w;uint16 h;}rectst;\
typedef struct{uint8 r;uint8 g;uint8 b;}colorst;\
enum{KY_DOWN,KY_UP,MS_DOWN,MS_UP,MN_SLT,MN_RET,MR_DIALOG,MS_MOVE=12};\
enum{_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_STAR,_POUND,_UP,_DOWN,_LEFT,_RIGHT,_SLEFT=17,_SRIGHT,_MENU=17,_BACK,_SEND,_SELECT};\
enum{SEEK_SET,SEEK_CUR,SEEK_END};\
enum{IS_FILE=1,IS_DIR=2,IS_INVALID=8};\
enum{DLG_OK,DLG_CANCEL};\
enum{BM_OR, BM_XOR, BM_COPY, BM_NOT,BM_MERGENOT,BM_ANDNOT,BM_TRANS,BM_AND,BM_GRAY,BM_REVERSE};";
#else
//初始数据
const char mrc_base_Defs[] = "\
#define _VERSION 3100\r\n\
#define _DEBUG 1\r\n\
#define _VENDOR \"\xb7\xe7\xb5\xc4\xd3\xb0\xd7\xd3\"\r\n\
#define _PLATFORM \"android\"\r\n\
#define _RUN_MODE \"picoc\"\r\n\
typedef unsigned short uint16;\
typedef unsigned long uint32;\
typedef long int32;\
typedef unsigned char uint8;\
typedef char int8;\
typedef short int16;\
typedef struct{uint16 x;uint16 y;uint16 w;uint16 h;}rectst;\
typedef struct{uint8 r;uint8 g;uint8 b;}colorst;\
enum{KY_DOWN,KY_UP,MS_DOWN,MS_UP,MN_SLT,MN_RET,MR_DIALOG,MS_MOVE=12};\
enum{_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_STAR,_POUND,_UP,_DOWN,_LEFT,_RIGHT,_SLEFT=17,_SRIGHT,_MENU=17,_BACK,_SEND,_SELECT};\
enum{SEEK_SET,SEEK_CUR,SEEK_END};\
enum{IS_FILE=1,IS_DIR=2,IS_INVALID=8};\
enum{DLG_OK,DLG_CANCEL};\
enum{BM_OR, BM_XOR, BM_COPY, BM_NOT,BM_MERGENOT,BM_ANDNOT,BM_TRANS,BM_AND,BM_GRAY,BM_REVERSE};";
#endif


struct timerST{
    int32 timer;
    int32 data;
    char *callback;
    Picoc *picoc;
    struct timerST* next;
};
struct timerST *timerList=NULL;



/*
修改malloc和free函数
用链表进行管理

*/
extern intptr debugfile;
extern int CheckBaseCall(char *FuncName,struct ValueType *ReturnType,int NumParams);

//优化定时器
//#define XL_TIMER 1



void Lib_Malloc(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = mrc_malloc(Param[0]->Val->Integer);
}

void Lib_Free(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
	mrc_free(Param[0]->Val->Pointer);
	/*
	 char strnum[50];
    if(mpc_free(Param[0]->Val->Pointer) == -1)
		{
			if(debugfile)
     {
    	mrc_write(debugfile, FREE_ERROR, mrc_strlen(FREE_ERROR));
    	mrc_sprintf(strnum,"%d",Param[0]->Val->Pointer);
    	mrc_write(debugfile, strnum, mrc_strlen(strnum));
     }
			
		}
			*/
			
		
}

void Lib_U2c(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger = mrc_unicodeToGb2312(Param[0]->Val->Pointer,Param[1]->Val->Integer,Param[2]->Val->Pointer,Param[3]->Val->Pointer);
}

void Lib_Memcpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = memcpy(Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer);
}

void Lib_Memmove(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = memmove(Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->UnsignedInteger);
}

void Lib_Strcpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = strcpy(Param[0]->Val->Pointer,Param[1]->Val->Pointer);
}

void Lib_Strncpy(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = strncpy((char *)Param[0]->Val->Pointer, (char *)Param[1]->Val->Pointer, Param[2]->Val->Integer);
}

void Lib_Strcat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = strcat((char *)Param[0]->Val->Pointer,(char *)Param[1]->Val->Pointer);
}

void Lib_Strncat(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = strncat((char *)Param[0]->Val->Pointer,(char *)Param[1]->Val->Pointer,Param[2]->Val->Integer);
}

void Lib_Memcmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{   
    ReturnValue->Val->Integer = memcmp(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->Integer);
}

void Lib_Strcmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = strcmp((char *)Param[0]->Val->Pointer,(char *)Param[1]->Val->Pointer);
}

void Lib_Strncmp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{ 
    ReturnValue->Val->Integer = strncmp((char *)Param[0]->Val->Pointer,(char *)Param[1]->Val->Pointer,Param[2]->Val->Integer);
}

void Lib_Memchr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = memchr(Param[0]->Val->Pointer, Param[1]->Val->Character, Param[2]->Val->UnsignedInteger);
}

void Lib_Memset(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = memset(Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->UnsignedInteger);
}

void Lib_Strlen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{    
    ReturnValue->Val->UnsignedInteger = strlen((char *)Param[0]->Val->Pointer);
}

void Lib_Strstr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = strstr((char *)Param[0]->Val->Pointer,(char *)Param[1]->Val->Pointer);
}

void Lib_Atoi(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer = atoi((const char*)Param[0]->Val->Pointer);
}

void Lib_Strtoul(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->UnsignedLongInteger = strtoul((const char*)Param[0]->Val->Pointer, Param[1]->Val->Pointer,Param[2]->Val->Integer);
}

void Lib_StrrChr(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer = (void *)strrchr((char *)Param[0]->Val->Pointer,Param[1]->Val->Integer);
}

void Lib_Exit(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
//  an_clearView();
    PlatformExit(Parser->pc,0);
//     mrc_exit();
}

void Lib_Open(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_open(Param[0]->Val->Pointer,Param[1]->Val->UnsignedLongInteger);
}

void Lib_Close(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_close(Param[0]->Val->LongInteger);
}

void Lib_FileState(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_fileState(Param[0]->Val->Pointer);
}

void Lib_Write(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_write(Param[0]->Val->LongInteger,Param[1]->Val->Pointer,Param[2]->Val->UnsignedLongInteger);
}

void Lib_Read(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_read(Param[0]->Val->LongInteger,Param[1]->Val->Pointer,Param[2]->Val->UnsignedLongInteger);
}

void Lib_ReadAll(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= my_readAllEx(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->Pointer);
}

void Lib_Seek(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Integer= mrc_seek(Param[0]->Val->LongInteger,Param[1]->Val->Integer,Param[2]->Val->Integer);
}

void Lib_GetLen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_getLen((const char*)Param[0]->Val->Pointer);
}

void Lib_Remove(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_remove((const char*)Param[0]->Val->Pointer);
}

void Lib_Rename(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_rename((const char*)Param[0]->Val->Pointer, (const char*)Param[1]->Val->Pointer);
}

void Lib_MkDir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_mkDir(Param[0]->Val->Pointer);
}

void Lib_RmDir(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_rmDir(Param[0]->Val->Pointer);
}

void Lib_FindStart(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_findStart(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->UnsignedLongInteger);
}

void Lib_FindGetNext(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_findGetNext(Param[0]->Val->LongInteger,Param[1]->Val->Pointer,Param[2]->Val->UnsignedLongInteger);
}

void Lib_FindStop(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= mrc_findStop(Param[0]->Val->LongInteger);
}


void Lib_DrawTextEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{

    // ReturnValue->Val->LongInteger = mrc_drawTextEx(Param[0]->Val->Pointer,
    //     Param[1]->Val->ShortInteger, Param[2]->Val->ShortInteger, 
    //     *(mr_screenRectSt*)Param[3]->Val->Pointer,*(mr_colourSt*)Param[4]->Val->Pointer, 
    //     Param[5]->Val->Integer, Param[6]->Val->Integer);
}



void Lib_DrawTextRight(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_drawTextRight(Param[0]->Val->Pointer, 
    //     Param[1]->Val->ShortInteger, Param[2]->Val->ShortInteger, 
    //     *(mr_screenRectSt*)Param[3]->Val->Pointer,*(mr_colourSt*)Param[4]->Val->Pointer, 
    //     Param[5]->Val->Integer, Param[6]->Val->Integer);
}





void Lib_C2u(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Pointer = mrc_c2u((char*)Param[0]->Val->Pointer, (int32*)Param[1]->Val->Pointer, (int32*)Param[2]->Val->Pointer);
}

void Lib_TextWidthHeight(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= textwh(Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->UnsignedShortInteger, (int32*)Param[3]->Val->Pointer, (int32*)Param[4]->Val->Pointer);
}


void Lib_EffSetCon(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    effsetcon(Param[0]->Val->ShortInteger, Param[1]->Val->ShortInteger, Param[2]->Val->ShortInteger, Param[3]->Val->ShortInteger,
        Param[4]->Val->ShortInteger, Param[5]->Val->ShortInteger, Param[6]->Val->ShortInteger);
}

void Lib_WstrLen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= wstrlen(Param[0]->Val->Pointer);
}

void Lib_UnicodeTextRow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_unicodeTextRow(Param[0]->Val->Pointer,Param[1]->Val->UnsignedShortInteger,Param[2]->Val->LongInteger);
}

void Lib_MenuCreate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger = mrc_menuCreate(Param[0]->Val->Pointer,Param[1]->Val->ShortInteger);
}

void Lib_MenuSet(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_menuSetItem(Param[0]->Val->LongInteger,Param[1]->Val->Pointer,Param[2]->Val->LongInteger);
}

void Lib_MenuShow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_menuShow(Param[0]->Val->LongInteger);
}
void Lib_MenuDel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_menuRelease(Param[0]->Val->LongInteger);
}

void Lib_MenuRef(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger=  mrc_menuRefresh(Param[0]->Val->LongInteger);
}

void Lib_DlgCreate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_dialogCreate(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->LongInteger);
}

void Lib_DlgDel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_dialogRelease(Param[0]->Val->LongInteger);
}

void Lib_DlgRef(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_dialogRefresh(Param[0]->Val->LongInteger,Param[1]->Val->Pointer,Param[2]->Val->Pointer,Param[3]->Val->LongInteger);
}

void Lib_TextCreate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_textCreate(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->LongInteger);
}

void Lib_TextDel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_textRelease(Param[0]->Val->LongInteger);
}

void Lib_TextRef(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_textRefresh(Param[0]->Val->LongInteger,Param[1]->Val->Pointer,Param[2]->Val->Pointer);
}

void Lib_EditCreate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_editCreate(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->LongInteger,Param[3]->Val->LongInteger);
}

void Lib_EditDel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_editRelease(Param[0]->Val->LongInteger);
}

void Lib_EditGet(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Pointer= (char*)mrc_editGetText(Param[0]->Val->LongInteger);
}

void Lib_GetUptime(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= getuptime();
}

void Lib_Sleep(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
#if defined(WIN32) || defined(LINUX)
    ReturnValue->Val->LongInteger= mrc_sleep(Param[0]->Val->UnsignedLongInteger);
#endif
}

void Lib_GetDateTime(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= getdatetime(Param[0]->Val->Pointer);
}

void Lib_GetMemRemain(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->UnsignedLongInteger= mrc_getMemoryRemain();
}


void Lib_Shake(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_startShake(Param[0]->Val->LongInteger);
}


void Lib_GetSysMem(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_getSysMem();
}

void Lib_RunMrp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_runMrp(Param[0]->Val->Pointer,Param[1]->Val->Pointer,NULL);
}
/*
void Lib_GetParentPath(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->Pointer= mrc_GetParentPath();
}
*/
void Lib_Sand(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    sand(Param[0]->Val->UnsignedLongInteger);
}


void Lib_Rand(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->UnsignedLongInteger= rand();
}


void Lib_SendSms(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    extern int32 mrc_sendSms(char* pNumber, char*pContent, int32 flags);
    // ReturnValue->Val->Integer= mrc_sendSms(Param[0]->Val->Pointer,Param[1]->Val->Pointer,Param[2]->Val->Integer);
}

void Lib_Lcd(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_LCDCanSleep(Param[0]->Val->Character);
}

void Lib_GetScrBuf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Pointer= w_getScreenBuffer();
}

void Lib_SetScrBuf(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // w_setScreenBuffer(Param[0]->Val->Pointer);
}

void Lib_GetScrSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // mrc_getScreenSize(Param[0]->Val->Pointer,Param[1]->Val->Pointer);
}

void Lib_SetScrSize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // mrc_setScreenSize(Param[0]->Val->Integer,Param[1]->Val->Integer);
}

void Lib_BmpShowFlip(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_bitmapShowFlip(Param[0]->Val->Pointer,
    //     Param[1]->Val->ShortInteger,
    //     Param[2]->Val->ShortInteger,
    //     Param[3]->Val->UnsignedShortInteger,
    //     Param[4]->Val->UnsignedShortInteger,
    //     Param[5]->Val->UnsignedShortInteger,
    //     Param[6]->Val->UnsignedShortInteger,
    //     Param[7]->Val->ShortInteger,
    //     Param[8]->Val->ShortInteger,
    //     Param[9]->Val->UnsignedShortInteger);
}


void Lib_BmpShowEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_bitmapShowExTrans(Param[0]->Val->Pointer,
    //     Param[1]->Val->ShortInteger,
    //     Param[2]->Val->ShortInteger,
    //     Param[3]->Val->UnsignedShortInteger,
    //     Param[4]->Val->UnsignedShortInteger,
    //     Param[5]->Val->UnsignedShortInteger,
    //     Param[6]->Val->UnsignedShortInteger,
    //     Param[7]->Val->ShortInteger,
    //     Param[8]->Val->ShortInteger,
    //     Param[9]->Val->UnsignedShortInteger);
}

void Lib_Wap(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // extern void mrc_connectWAP(char* wap);
    // mrc_connectWAP(Param[0]->Val->Pointer);
}

void Lib_FreeFileData(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // mrc_freeFileData(Param[0]->Val->Pointer,Param[1]->Val->LongInteger);
}
/*
void Lib_FreeOrigin(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    mrc_freeOrigin(Param[0]->Val->Pointer,Param[1]->Val->LongInteger);
}
*/
void TimerCb(int32 data)//
{
    struct timerST *list=timerList;
		
    char Source[256];
    char *ptr=NULL;
    Picoc *picoc=NULL;

    while(list != NULL)
    {
        if(list->timer == data)
        {
            FuncRet=list->data;//
            ptr = list->callback;
            picoc = list->picoc;
            break;
        }
        list=list->next;
    }
    if(CheckBaseCall(ptr,&(picoc->VoidType),1))
    {
        timerstop(data);
        return;
    }
		//优化，直接把ptr传过去，不sprintf了
		#ifdef XL_TIMER
						log_c("定时器",ptr);
		    PicocParse(" ", ptr, strlen(ptr), TRUE, TRUE, FALSE);

		#else	
    sprintf(Source,"%s(_ret);",ptr);
    PicocParse(picoc," ", Source, strlen(Source), TRUE, TRUE, FALSE,TRUE);
		#endif
}
void Lib_TimerCreate(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    int32 timer;
    timer = timercreate();
    if(timer)
    {
        struct timerST *NewNode;
        
        NewNode=mrc_malloc(sizeof(struct timerST));
        NewNode->next=timerList;
        NewNode->timer=timer;
        NewNode->picoc = Parser->pc;
        NewNode->callback=NULL;
        timerList=NewNode;
    }
    ReturnValue->Val->LongInteger = timer;
}

void Lib_TimerDel(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{   
    int32 timer=Param[0]->Val->LongInteger;
    struct timerST *list=timerList;
    struct timerST *prev=timerList;

    while(list != NULL)
    {
        if(list->timer == timer)
        {
            if(list==timerList)
                timerList=timerList->next;
            else
                prev->next=list->next;
            if(list->callback) mrc_free(list->callback);
            mrc_free(list);
            break;
        }
        prev=list;
        list=list->next;
    }
    timerdel(timer);
}

void Lib_TimerStop(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    timerstop(Param[0]->Val->LongInteger);
}

void Lib_TimerStart(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    int32 timer = Param[0]->Val->LongInteger;
    char *callback=Param[3]->Val->Pointer;
    struct timerST *list=timerList;

    while(list != NULL)
    {
        if(list->timer == timer)
        {
            list->data = Param[2]->Val->LongInteger;
						#ifdef XL_TIMER
						list->callback=mrc_malloc(strlen(callback)+8);
						mrc_memset(list->callback,0,strlen(callback)+8);
            mrc_sprintf(list->callback, "%s(_ret);" ,callback);
						
						#else
            list->callback=mrc_malloc(strlen(callback)+1);
            strcpy(list->callback,callback);
						#endif
            break;
        }
        list=list->next;
    }
    ReturnValue->Val->LongInteger= timerstart(timer,Param[1]->Val->LongInteger,timer,TimerCb,Param[4]->Val->LongInteger);
}

void Lib_TimerSetTime(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    ReturnValue->Val->LongInteger= timersettime(Param[0]->Val->LongInteger,Param[1]->Val->LongInteger);
}

void Lib_DrawImg(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->Integer= DrawIMG(Param[0]->Val->Pointer,Param[1]->Val->Integer,Param[2]->Val->Integer);
}

void Lib_ShadeRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // DrawShadeRect(Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer,Param[4]->Val->LongInteger,Param[5]->Val->LongInteger,Param[6]->Val->Integer);
}




/*
void Lib_(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
ReturnValue->Val->LongInteger= mrc_fileState(Param[0]->Val->Pointer);
}

void Lib_(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
ReturnValue->Val->LongInteger= mrc_fileState(Param[0]->Val->Pointer);
}
*/


void Lib_ReadFileFromMrp(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)
{
    // ReturnValue->Val->LongInteger= mrc_readFileFromMrpEx(Param[0]->Val->Pointer,
    //     Param[1]->Val->Pointer,
    //     Param[2]->Val->Pointer,
    //     Param[3]->Val->Pointer,
    //     Param[4]->Val->LongInteger);
}

void Lib_ClearScreen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    cls(Param[0]->Val->Integer, Param[1]->Val->Integer, Param[2]->Val->Integer);
}

void Lib_refreshScreen(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    ref(Param[0]->Val->ShortInteger, Param[1]->Val->ShortInteger, Param[2]->Val->ShortInteger, Param[3]->Val->ShortInteger);
}

void Lib_drawRect(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    drect(Param[0]->Val->ShortInteger, Param[1]->Val->ShortInteger, Param[2]->Val->ShortInteger, Param[3]->Val->ShortInteger,
        Param[4]->Val->Character, Param[5]->Val->Character, Param[6]->Val->Character);
}

void Lib_drawLine(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    dline(Param[0]->Val->ShortInteger, Param[1]->Val->ShortInteger, Param[2]->Val->ShortInteger, Param[3]->Val->ShortInteger,
        Param[4]->Val->Character, Param[5]->Val->Character, Param[6]->Val->Character);
}

void Lib_DrawPoint(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    dpoint(Param[0]->Val->ShortInteger, Param[1]->Val->ShortInteger, 
        Param[2]->Val->ShortInteger);
}

void Lib_drawPointEx(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    dpointex(Param[0]->Val->ShortInteger, Param[1]->Val->ShortInteger, 
        Param[2]->Val->ShortInteger, Param[3]->Val->ShortInteger, Param[4]->Val->ShortInteger);
}

void Lib_drawText(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) 
{
    dtext((char*)Param[0]->Val->Pointer, Param[1]->Val->ShortInteger, Param[2]->Val->ShortInteger, 
        Param[3]->Val->Character, Param[4]->Val->Character, Param[5]->Val->Character,
        Param[6]->Val->Integer, Param[7]->Val->UnsignedShortInteger);
}

//#define _VENDOR \"\xb7\xe7\xb5\xc4\xd3\xb0\xd7\xd3\" \n\
////////////////////////////////////////////////////////////////////
//void (*Func)(struct ParseState *Parser, struct Value *, struct Value **, int);
struct LibraryFunction mrc_base_Functions[110];

static void AddString(void* func, char *proto_type)
{
 static uint32 index=0;
 if(index<100)
 {
	mrc_base_Functions[index].Func= func;
	mrc_base_Functions[index].Prototype= proto_type;
	index++;
 }
}



void mrc_base_SetupFunc(Picoc *pc)
{
	AddString(Lib_ClearScreen, "void cls(int,int,int);");

    		AddString(Lib_refreshScreen, "void ref(int,int,int,int);");

    		AddString(Lib_drawRect, "void drect(int,int,int,int,int,int,int);");

    		AddString(Lib_drawLine, "void dline(int,int,int,int,int,int,int);");

    		AddString(Lib_drawPointEx, "void dpointex(int,int,int,int,int);");

    		AddString(Lib_drawText, "int dtext(char*,int,int,int,int,int,int,int);");

    		AddString(LibSPrintf, "char* sprintf(char*,char*,...);");

    AddString(Lib_BmpShowFlip, "int bmpshowflip(uint16*,int16,int16,uint16,uint16,uint16,uint16,int16,int16,uint16);");
    AddString(Lib_BmpShowEx, "int bmpshowex(uint16*,int16,int16,uint16,uint16,uint16,uint16,int16,int16,uint16);");

		        AddString(Lib_GetUptime, "int getuptime();");
		
    AddString(Lib_Malloc, "void* malloc(int);");
 
    AddString(Lib_Free,"void free(void*);");

    AddString(Lib_U2c, "int u2c(char*,int,char**,int*);");
    		AddString(Lib_Memcpy, "void* memcpy(void*,void*,uint32);");

    		AddString(Lib_Memmove, "void* memmove(void*,void*,uint32);");

    	AddString(Lib_Strcpy, "char* strcpy(char*,char*);");

    		AddString(Lib_Strncpy,"char* strncpy(char*,char*,int);");

    		AddString(Lib_Strcat, "char* strcat(char*,char*);");

    	AddString(Lib_Strncat, "char* strncat(char*,char*,int);");

    		AddString(Lib_Memcmp, "int memcmp(void*,void*,uint32);");

    	AddString(Lib_Strcmp, "int strcmp(char*,char*);");

    	AddString(Lib_Strncmp, "int strncmp(char*,char*,int);");

    	AddString(Lib_Memchr,  "void *memchr(void*,char,uint32);");

    	AddString(Lib_Memset, "void *memset(void*,int,uint32);");

    		AddString(Lib_Strlen, "uint32 strlen(char*);");

    		AddString(Lib_Strstr, "char* strstr(char*,char*);");

    		AddString(LibPrintf, "void printf(char*,...);");

    		AddString(Lib_Atoi, "int atoi(char*);");

    		AddString(Lib_Strtoul,"long strtoul(char*,char**,int);");

//  
    		AddString(Lib_StrrChr, "char* strrchr(char*,char);");

    		AddString(Lib_Exit, "void exit();");

    		
    		AddString(Lib_Open, "int open(char*,int);");

    	AddString(Lib_Close, "int close(int);");


		AddString(Lib_FileState, "int filestate(char*);");

    	AddString(Lib_Write, "int write(int,void*,int);");

    		AddString(Lib_Read, "int read(int,void*,int);");

    		AddString(Lib_ReadAll, "int readall(char*,char*,int);");

    	AddString(Lib_Seek, "int seek(int,int,int);");

    	AddString(Lib_GetLen, "int getlen(char*);");

    		AddString(Lib_Remove, "int remove(char*);");

    	AddString(Lib_Rename, "int rename(char*,char*);");

    		AddString(Lib_MkDir, "int mkdir(char*);");

    		AddString(Lib_RmDir, "int rmdir(char*);");

    		AddString(Lib_FindStart, "int findstart(char*,char*,int);");

    		AddString(Lib_FindGetNext, "int findnext(int,char*,int);");

    	AddString(Lib_FindStop, "int findstop(int);");


        AddString(Lib_DrawTextEx, "int dtextex(char*,short,short,rectst*,colorst*,int,short);");

    		AddString(Lib_C2u, "unsigned short* c2u(char*,int*,int*);");


      AddString(Lib_TextWidthHeight, "int textwh(char*,int,int,int*,int*);");
    	AddString(Lib_DrawPoint, "void dpoint(int,int,int);");

    		AddString(Lib_EffSetCon, "void effsetcon(int16,int16,int16,int16,int16,int16,int16);");

    		AddString(Lib_WstrLen, "int wstrlen(char*);");


    AddString(Lib_UnicodeTextRow, "int unitextrow(uint16*,int,int);");
		AddString(Lib_MenuCreate, "int menucreate(char*,int16);");

    		AddString(Lib_MenuSet, "int menuset(int,char*,int);");

    	AddString(Lib_MenuShow, "int menushow(int);");

    		AddString(Lib_MenuDel, "int menudel(int);");

    		AddString(Lib_MenuRef, "int menuref(int);");

    		AddString(Lib_DlgCreate, "int dlgcreate(char*,char*,int);");

    		AddString(Lib_DlgDel, "int dlgdel(int);");

  		AddString(Lib_DlgRef, "int dlgref(int,char*,char*,int);");

    	AddString(Lib_TextCreate, "int textcreate(char*,char*,int);");

      AddString(Lib_TextDel, "int textdel(int);");

    		AddString(Lib_TextRef, "int textref(int,char*,char*);");

   		AddString(Lib_EditCreate, "int editcreate(char*,char*,int,int);");

    		AddString(Lib_EditDel, "int editdel(int);");

    		AddString(Lib_EditGet, "char* editget(int);");



	    	AddString(Lib_Sleep, "int sleep(uint32);");

        AddString(Lib_GetDateTime, "int getdatetime(void*);");
		


        AddString(Lib_Shake, "int shake(int);");

        AddString(Lib_ReadFileFromMrp,    "int readfilefrommrp(char*,char*,uint8**,long*,int);");


        AddString(Lib_DrawTextRight, "int dtextright(char*,short,short,rectst*,colorst*,int,uint16);");
//    mrc_base_Functions[68].Func = Lib_GetMemRemain;
//    mrc_base_Functions[68].Prototype = "uint32 getmemremain();";

//    mrc_base_Functions[85].Func = Lib_FreeOrigin;
//    mrc_base_Functions[85].Prototype = "void freeorigin(void*,int);";


//    mrc_base_Functions[70].Func = Lib_GetSysMem;
//    mrc_base_Functions[70].Prototype = "int getsysmem();";
//    mrc_base_Functions[72].Func = Lib_GetParentPath;
//    mrc_base_Functions[72].Prototype = "char* getparentpath();";


      AddString(Lib_RunMrp, "int runmrp(char*,char*);");

      AddString(Lib_SendSms, "int sms(char*,char*,int);");

//    
AddString(Lib_Sand, "void sand(uint32);");
//    
AddString(Lib_Rand, "uint32 rand();");


AddString(Lib_Lcd, "int lcd(char);");

AddString(Lib_GetScrBuf, "uint16 *getscrbuf();");

AddString(Lib_SetScrBuf, "void setscrbuf(uint16*);");

AddString(Lib_GetScrSize, "void getscrsize(int*,int*);");


AddString(Lib_SetScrSize, "void setscrsize(int,int);");
AddString(Lib_Wap, "void wap(char*);");

 		AddString(Lib_FreeFileData, "void freefiledata(void*,int);" );


    		AddString(Lib_TimerCreate, "int32 timercreate();");
		AddString(Lib_TimerDel,  "void timerdel(int32);");

    		AddString(Lib_TimerStop, "void timerstop(int32);");

 
		AddString(Lib_TimerStart, "int timerstart(int32,long,long,char*,int);");

    
		AddString(Lib_TimerSetTime, "int timersettime(int32,long);");

    
		AddString(Lib_DrawImg, "int img(char*,int,int);");

    
		AddString(Lib_ShadeRect, "void shaderect(int,int,int,int,long,long,int);");
//        AddString(Lib_GetMemRemain, "unsigned int memory();");
    
		
		AddString(NULL, NULL);
/*
    mrc_base_Functions[].Func = Lib_;
    mrc_base_Functions[].Prototype = NULL;

    mrc_base_Functions[].Func = Lib_;
    mrc_base_Functions[].Prototype = NULL;

    mrc_base_Functions[].Func = NULL;
    mrc_base_Functions[].Prototype = NULL;

    mrc_base_Functions[].Func = NULL;
    mrc_base_Functions[].Prototype = NULL;
    */
}
