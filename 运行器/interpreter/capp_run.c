/*
** platform.c: implements of platform.h
** 
** Copyright (C) 2007-2008 SKY-MOBI AS.  All rights reserved.
**
** Create date: 2007-12-27 by wandonglin
**
** This file is part of the simple gui library.
** It may not be redistributed under any circumstances.
*/

//#include "window.h"

#include "platform.h"
#include "interpreter.h"

#include "base.h"
#include "mrc_base.h"
#include "dsm.h"
#include "picoc.h"
//#include "application.h"
//#include "mainwnd.h"

#define PICINITSUC 0x01
#define PLATRUMMODE 0x02

//int SCREEN_WIDTH;
//int SCREEN_HEIGHT;
int32 _code;
int32 _p0;
int32 _p1;
char suc;
//解释器是否处于运行状�?
int32 isRun;
int32 picoc_resume(void);
int32 picoc_pause(void);
extern void SafeExit_capp();

//运行文件路径
char run_filename[300];
Picoc picoc;






int CheckBaseCall(char *FuncName,struct ValueType *ReturnType,int NumParams)
{
    struct Value *FuncValue = NULL;

    if(FuncName==NULL) return -1;
    if (!VariableDefined(&picoc,TableStrRegister(&picoc,FuncName)))
		 //%s未定�?
        ProgramFailNoParser(&picoc, "%s()\xce\xb4\xb6\xa8\xd2\xe5\x0",FuncName);

    VariableGet(&picoc,NULL, TableStrRegister(&picoc,FuncName), &FuncValue);
    if (FuncValue->Typ->Base != TypeFunction)
		 //无法使用%s
        ProgramFailNoParser(&picoc, "\xce\xde\xb7\xa8\xca\xb9\xd3\xc3%s",FuncName);

    if (FuncValue->Val->FuncDef.ReturnType == ReturnType)
    {
        if (FuncValue->Val->FuncDef.NumParams != NumParams) return -1;
    }else return -1;

    return 0;
}

int PicocCallInit(void)
{
    if(CheckBaseCall("event",&(picoc.IntType),3)
		|| CheckBaseCall("init",&(picoc.IntType),0)
    || CheckBaseCall("pause",&(picoc.IntType),0)
    || CheckBaseCall("resume",&(picoc.IntType),0)
	//	|| CheckBaseCall("exitApp",&IntType,0)
		)
		{
					// an_Toast("\xb3\xcc\xd0\xf2\xb3\xf6\xb4\xed\x0",1);
					printf("PicocCallInit %s","程序出错");
					return -1;
		}

		
		
    VariableDefinePlatformVar(&picoc,NULL, "_code", &(picoc.IntType), (union AnyValue *)&_code, FALSE);
    VariableDefinePlatformVar(&picoc,NULL, "_p0", &(picoc.IntType), (union AnyValue *)&_p0, FALSE);
    VariableDefinePlatformVar(&picoc,NULL, "_p1", &(picoc.IntType), (union AnyValue *)&_p1, FALSE);
    VariableDefinePlatformVar(&picoc,NULL, "_ret", &(picoc.IntType), (union AnyValue *)&FuncRet, TRUE);

    return 0;
}

//通过路径获取文件�? 需要释放内�?
static char* getFileName(char *path)
{
		int i=0;
		int end=-1;
		int len = strlen(path);
		char *filename = malloc(len+1);
		memset(filename,0,len+1);
		for(i=0;i<len;i++)
		{
				if(path[i]=='/' || path[i]=='\\')
						end=i;
				
		}
		strcpy(filename,path+end+1);
		return filename;
}

//未使�? 可能有bug
void PicocRun_capp()
{

		    
		    strcpy(run_filename, dsm_getRunName());
		    // an_clearView();
				printf("申请内存");
        PicocInitialise(&picoc,HEAP_SIZE);
				printf("申请内存heap");
				// _SET_BIT(suc,PICINITSUC);
				/*
        if (PicocPlatformSetExitPoint())
        {
            SafeExit_capp();
            return;
        }
*/
        
        PicocPlatformScanFile(&picoc,(const char*)run_filename);
        if(PicocCallInit())
            SafeExit_capp();
        else
				{
					isRun=TRUE;
            PicocParse(" ", "_ret=init();", strlen("_ret=init();"), TRUE, TRUE, FALSE);
				}
}

//运行mpc
void PicocRun(int32 data)
{
    printf("picocRun %d\n",data);
		// char *filename = getFileName(dsm_getRunC());
		// strcpy(run_filename,filename);
		// free(filename);
    if(!data)
    {

				
        cls(0,0,0);
				printf("clearScreen");
				//启动运行
        dtext("启动运行",0,0,0,255,0,0,1);
				printf("drawText");
        ref(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				printf("refreshScreen");
				
				
				
       data=timercreate();
       timerstart(data,1000,data,PicocRun,FALSE);
				
    }
    else
    {
        timerdel(data);
        data = 0;
        strcpy(run_filename,dsm_getRunName());
		    // an_clearView();
				mrc_printf("申请内存\n");
        PicocInitialise(HEAP_SIZE);
				mrc_printf("申请内存heap\n");
				
        if (PicocPlatformSetExitPoint())
        {
          mrc_printf("退�?");
            SafeExit_capp();
            return;
        }
        mrc_printf("加载文件 %s",run_filename);
        PicocPlatformScanFile((const char*)run_filename);
        mrc_printf("加载2");
        if(PicocCallInit())
            SafeExit_capp();
        else
				{
					isRun=TRUE;
                    // Picoc *pc, const char *FileName, const char *Source, int SourceLen, int RunIt, int CleanupNow, int CleanupSource, int EnableDebugger
            PicocParse(" ", "_ret=init();", strlen("_ret=init();"), TRUE, TRUE, FALSE);
				}
    }

}


int32 picoc_init(void)
{
	 //删除print.txt
	 PlatformInit(&picoc);
	 isRun=FALSE;
  //  if(strlen(run_filename)==0)
	//  {
	//  strcpy(run_filename,  "c/temp.c");
	//  }
	 
	//  momo_init();
	// ad_drawTextUTF("启动运行", 0,0,0,255,0,1);
	 printf("mpc运行器启动\n");
  // mrc_refreshScreen(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	//  log_c("启动运行","");
	// mrc_sleep(100);
	 PicocRun(0);
	 //mrc_sleep(1000);
	
	 //由于目前不支持定时器，故再调用一次加载mpc
//	 PicocRun(1);
	 return 0;
}

int32 picoc_event(int32 code, int32 param0, int32 param1)
{

        if(isRun)
        {
            _code=code;
            _p0=param0;
            _p1=param1;

            if (PicocPlatformSetExitPoint())
            {
                SafeExit_capp();
                return FuncRet;
            }
            PicocParse(" ", "_ret=event(_code,_p0,_p1);", strlen("_ret=event(_code,_p0,_p1);"), TRUE, TRUE, FALSE);
        }

     return 0;

}

int32 picoc_pause(void)
{	

		// printf("mrc_pause");
       
            if (PicocPlatformSetExitPoint())
            {
                SafeExit_capp();
                return FuncRet;
            }
            PicocParse(" ", "_ret=pause();", strlen("_ret=pause();"), TRUE, TRUE, FALSE);
        
        return 0;
    

}

int32 picoc_resume(void)
{

			// printf("mrc_resume");
            if (PicocPlatformSetExitPoint())
            {
                SafeExit_capp();
                return FuncRet;
            }
            PicocParse(" ", "_ret=resume();", strlen("_ret=resume();"), TRUE, TRUE, FALSE);
   
    return 0;
}


//退出解释器
void SafeExit_capp()
{
        printf("mrc_exit_capp");
        isRun=FALSE;
		    printf("%s","mrc_exit");
		    mrc_exit();
    
}

//退出解释器
void SafeExit(int32 data)
{
    suc=0;
    if(!data)
    {
			  
        cls(0,0,0);
				//结束运行
        dtext("\xbd\xe1\xca\xf8\xd4\xcb\xd0\xd0\x00",0,0,0,255,0,0,1);
        ref(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
				
				
				
				
				
				
        data=timercreate();
        timerstart(data,800,data,SafeExit,FALSE);
				/*
				mrc_sleep(800);
				SafeExit(1);*/
        return;
    }
    else
    {
        //mrc_timerDelete(data);
				//出错时停止定时器
	 //  mrc_timerDeleteAll();
	 //释放内存
        PicocCleanup(&picoc); //测试，如果出错就删除此行
        isRun=FALSE;
		printf("%s","mrc_exit");
		mrc_exit();
    }
}

int32 picoc_exitApp(void)
{
	//调用用户应用功能
	//int r;
	//增加exitApp
	/*
if(_IS_SET_BIT(suc,PICINITSUC))
        {
					
            if (PicocPlatformSetExitPoint())
            {
                SafeExit(1);
                return FuncRet;
            }
						if(CheckBaseCall("exitApp",&IntType,0))
		      {
					an_Toast("\xb3\xcc\xd0\xf2\xb3\xf6\xb4\xed\x0",1);
					log_c("PicocCallInit","程序出错");
					return -1;
		      }
            PicocParse(" ", "_ret=exitApp();", strlen("_ret=exitApp();"), TRUE, TRUE, FALSE);
        }
				*/
       
				
				
				
				
    //PlatformCleanup();//关闭打印文件
			 //释放内存
        PicocCleanup(&picoc);
        isRun=FALSE;
	//	SafeExit_capp(); //释放解释�?
		//mrc_timerDelete(data);
				//出错时停止定时器
	 //  mrc_timerDeleteAll();

		
		/*
		由于已经释放内存，没必要添加这个
		   if (PicocPlatformSetExitPoint())
            {
                SafeExit(0);
                return FuncRet;
            }
		*/
	//SGL_SuspendDrawing();
//	r = ExitApplication();
	
	//终止sky GUI�?
	//SGL_Terminate();
/*
#if !OMIT_NETWORK_MODULE
	//终止网络模块

	mrc_Socket_Terminate();
	mrc_Http_Terminate();
#endif   */

	//return r;
	return 0;
}

