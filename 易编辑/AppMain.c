/*
 * 程序主代码文件
 * 版权所有 (C) 2011-2012 eleqian
 * [7/21/2012]
 */

#include "mrc_base.h"
//#include <mrc_skyfont.h>
#include "src/exb.h"
#include "src/android.h"
#include "AppMain.h"
#include "HexView.h"
#include "HexEdit.h"
#include "Menu.h"
#include "MainMenu.h"
#include "FileView.h"
#include "PluginMgr.h"
#include "InfoPage.h"
#include "LocalUI.h"
#include "Functions.h"
#include "DrawLib.h"

#include "IniFile.h"

// 最大程序状态历史记录
#define APPSTATE_STACK_SIZE 8

static APPSTATE_ENUM AppStateStack[APPSTATE_STACK_SIZE];  // 状态栈
static APPSTATE_ENUM AppState;  // 程序状态
static int32 AppStateIndex;     // 状态栈当前位置

APPDATAS_ST AppDatas;  // 程序运行全局数据
int32 AppInitState;    // 程序初始化状态

char *skinfile="eles/ehex/skin0.ini";
/*---------------------------------------------------------------------------*/

// 初始化
int32 Main_Init(void)
{
    int32 ret;
    uint8 color_type = AppColor.type;
LOGI("INIT");
    DrawLib_Init();
    DrawLib_SetColor(color_type);
    DrawLib_SetFont(AppDatas.AppFont);

    // 初始程序状态
    AppState = APPSTATE_HEXVIEW;
    AppStateIndex = 0;

    // 初始化屏幕信息
    AppDatas.ScnWidth = ScreenWidth;
    AppDatas.ScnHeight = ScreenHeight;
    AppDatas.ScnBuf = ScreenBuf;

    // 初始化Hex编辑数据
    memset(AppDatas.HDatas, 0, sizeof(HEX_VIEW_ST) * 2);
    AppDatas.HDataCur = &AppDatas.HDatas[0];
    AppDatas.HIndex = 0;

    // 初始化其它模块
    ret = String_Init();
    if (ret != 0)
        AppInitState = -1;
    ret = HV_Init();
   // LOGI("11111");
    if (ret != 0)
        AppInitState = -1;
    ret = HE_Init();
   // LOGI("11111");
    if (ret != 0)
        AppInitState = -1;
    ret = Menu_Init();
   // LOGI("11111");
    if (ret != 0)
        AppInitState = -1;
    ret = FileView_Init();
  //  LOGI("11111");
    if (ret != 0)
        AppInitState = -1;
    ret = InfoPage_Init();
   // LOGI("11111");
    if (ret != 0)
        AppInitState = -1;
  //XL  ret = PM_Init();
   // LOGI("11111");
    if (ret != 0)
        AppInitState = -1;

    AppDatas.MainMenu = MainMenu_InitItems();
    if (ret != 0)
        AppInitState = -1;

    StartShowTime();
   // LOGI("11111");
    if (AppInitState != -1)
        AppInitState = 0;

    return AppInitState;
}

// 程序结束
int32 Main_End(void)
{
    HV_Draw(0);
  //  HV_ShowMsgA("正在退出……", 0);
	    HV_ShowMsgA("\xd5\xfd\xd4\xda\xcd\xcb\xb3\xf6\xa1\xad\xa1\xad", 0);
    RefreshScreen();

    Menu_Destroy(AppDatas.MainMenu);
    StopShowTime();
    HV_End();
    HE_End();
  //XL  PM_End();
    Menu_End();
    InfoPage_End();
    FileView_End();
    DrawLib_End();
    String_End();

    TRYFREE(AppDatas.HDatas[0].DataBuffer);
    TRYFREE(AppDatas.HDatas[0].HexBuffer);
    TRYFREE(AppDatas.HDatas[1].DataBuffer);
    TRYFREE(AppDatas.HDatas[1].HexBuffer);

    return 0;
}

// 绘制主窗口，参数：是否刷新
int32 Main_Draw(uint8 refresh)
{
    // 初始化中，不显示
    if (AppInitState == 1)
    {
        return -1;
    }

	ClearScreen();

    switch (AppState)
    {
    case APPSTATE_HEXVIEW:
		
        HV_Draw(0);
        break;
    case APPSTATE_HEXEDIT:
		
        HE_Draw(0);
        break;
    case APPSTATE_MENU:
		
        Menu_Draw(0);
        break;
    case APPSTATE_FILEVIEW:
		
        FileView_Draw(0);
        break;
    case APPSTATE_INFOPAGE:
        InfoPage_Draw(0);
        break;
    case APPSTATE_PLUGIN_MGR:
    //XL    PM_Draw(0);
        break;
    case APPSTATE_PLUGIN_RUN:
      //XL  Plugin_Redraw(0);
        break;
    case APPSTATE_LOCALUI:
        return 0;
    default:
        return 0;
    }

	if (refresh)
        RefreshScreen();

    return 0;
}

/*---------------------------------------------------------------------------*/

// 改变程序状态
int32 SetAppState(APPSTATE_ENUM newState, int32 refresh)
{
    if (newState == AppState) // 相同状态，不改变
    {
        Main_Draw((uint8)refresh);
        return 0;
    }
    else if (APPSTATE_RETURN == newState) // 返回上个状态
    {
        // 状态栈非空
        if (AppStateIndex > 0)
        {
            AppState = AppStateStack[AppStateIndex];
            AppStateIndex--;

            // 取消阻塞插件的运行
            if (APPSTATE_PLUGIN_RUN == AppState)
            {
             //XL   Plugin_UnBlock();
            }
        }
        else
        {
            AppState = APPSTATE_HEXVIEW;
        }
    }
    else if (APPSTATE_NORMAL == newState) // 返回初始状态
    {
        AppStateIndex = 0;
        AppState = APPSTATE_HEXVIEW;
    }
    else // 设置新状态
    {
        // 状态栈未满
        if (AppStateIndex < APPSTATE_STACK_SIZE - 1)
        {
            AppStateIndex++;
            AppStateStack[AppStateIndex] = AppState;

            // 阻塞插件的运行，以便主程序接受事件和绘制界面
            if (APPSTATE_PLUGIN_RUN == AppState)
            {
             //XL   Plugin_Block();
            }
        }
        else
        {
            AppStateIndex = 0;
        }

        AppState = newState;
    }

    Main_Draw((uint8)refresh);

    return 0;
}

// 取得程序状态
APPSTATE_ENUM GetAppState(void)
{
    return AppState;
}

/*---------------------------------------------------------------------------*/

// 根据信息类型计算信息数
static void CalcInfoCount(void)
{
    uint32 iType;
    int32 count = 0;

    //判断信息数
    iType = AppDatas.InfoType;

    while (iType)
    {
        if (iType & 0x1)
            count++;

        iType >>= 1;
    }

    if (count < 2)
        AppDatas.InfoCount = 2;
    else
        AppDatas.InfoCount = (uint16)count;
}

// 设置显示信息类型
int32 SetInfoType(uint32 type)
{
    uint8 index1, index2;

    switch (type)
    {
    case VIEWTYPE_MASK_UINT8: index1 = 1; index2 = 1; break;
    case VIEWTYPE_MASK_INT8: index1 = 1; index2 = 2; break;
    case VIEWTYPE_MASK_UINT16: index1 = 1; index2 = 3; break;
    case VIEWTYPE_MASK_INT16: index1 = 1; index2 = 4; break;
    case VIEWTYPE_MASK_UINT32: index1 = 1; index2 = 5; break;
    case VIEWTYPE_MASK_INT32: index1 = 1; index2 = 6; break;
    case VIEWTYPE_MASK_UCS2BE: index1 = 2; index2 = 1; break;
    case VIEWTYPE_MASK_UCS2LE: index1 = 2; index2 = 2; break;
    case VIEWTYPE_MASK_GB2312: index1 = 2; index2 = 3; break;
    case VIEWTYPE_MASK_UTF8: index1 = 2; index2 = 4; break;
    default: return -1;
    }

    AppDatas.InfoType ^= type;

    CalcInfoCount();

    HV_Init();
    HE_Init();

    MainMenu_SetChecked(4, index1, index2, (AppDatas.InfoType & type) ? 1 : 0);
    Main_Draw(1);

    return 0;
}

// 设置字体
int32 SetAppFont(uint16 NewFont)
{
    AppDatas.AppFont = NewFont;

    DrawLib_SetFont(AppDatas.AppFont);

    HV_Init();
    HE_Init();
    Menu_Init();
    InfoPage_Init();
    FileView_Init();
//XL    PM_Init();

    MainMenu_SetChecked(4, 3, 1, (MR_FONT_SMALL == AppDatas.AppFont) ? 1 : 0);
    MainMenu_SetChecked(4, 3, 2, (MR_FONT_MEDIUM == AppDatas.AppFont) ? 1 : 0);
    MainMenu_SetChecked(4, 3, 3, (MR_FONT_BIG == AppDatas.AppFont) ? 1 : 0);
    //MainMenu_SetChecked(4, 3, 4, (MR_FONT_SIZE12 == AppDatas.AppFont) ? 1 : 0);

    if (HV_IsFileOpen())
    {
        int32 old_offset;

        RefreshTrigger();
        old_offset = HV_GetFileOffset();
        HV_GotoFileOffset(0);
        HV_GotoFileOffset(old_offset);
        RefreshUnTrigger();
    }

    Menu_Refresh(0);
    Main_Draw(1);

    return 0;
}

// 改变颜色设置
int32 SetAppColors(void)
{
    uint8 index, i;
    uint8 newtype = AppColor.type;

    for (i = 0; i < 8; i++)
    {
        index = (uint8)MainMenu_GetData(4, 4, i + 1);
        if (index == AppColor.type)
        {
            break;
        }
    }

    MainMenu_SetChecked(4, 4, i + 1, 0);

    do {
        newtype++;
        if (newtype > 7)
        {
            newtype = 0;
        }
        DrawLib_SetColor(newtype);
    } while (AppColor.type != newtype);

    for (i = 0; i < 8; i++)
    {
        index = (uint8)MainMenu_GetData(4, 4, i + 1);
        if (index == AppColor.type)
        {
            break;
        }
    }

    MainMenu_SetChecked(4, 4, i + 1, 1);
    Main_Draw(1);

    return 0;
}

// 打开上次的文件
void OpenLastFile(void)
{
    const char *setFile = "eles/eHex/config.ini";
    int32 begin, offset;
    int32 win_index;

    IniOpenFile(setFile);
    IniGetString("File", "Path1", AppDatas.HDatas[0].FilePath);
    IniGetString("File", "File1", AppDatas.HDatas[0].FileNameA);
    IniGetString("File", "Path2", AppDatas.HDatas[1].FilePath);
    IniGetString("File", "File2", AppDatas.HDatas[1].FileNameA);

    // 避免多次刷新
    RefreshTrigger();

    // 窗口1
    if (0 != AppDatas.HDatas[0].FilePath[0] && 0 != AppDatas.HDatas[0].FileNameA[0])
    {
        begin = IniGetInteger("Other", "Begin1", 0);
        offset = IniGetInteger("Other", "Offset1", 0);

        HV_SwitchWindow(0);
        HV_OpenFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA);

        // 定位焦点位置
        HV_GotoFileOffset(offset);

        // 定位显示开始位置
        AppDatas.HDataCur->DataShowBegin = begin - AppDatas.HDataCur->FileReadBegin;
        HV_GotoFileOffset(offset);
    }

    // 窗口2
    if (0 != AppDatas.HDatas[1].FilePath[0] && 0 != AppDatas.HDatas[1].FileNameA[0])
    {
        begin = IniGetInteger("Other", "Begin2", 0);
        offset = IniGetInteger("Other", "Offset2", 0);

        HV_SwitchWindow(1);
        HV_OpenFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA);

        // 定位焦点位置
        HV_GotoFileOffset(offset);

        // 定位显示开始位置
        AppDatas.HDataCur->DataShowBegin = begin - AppDatas.HDataCur->FileReadBegin;
        HV_GotoFileOffset(offset);
    }

    win_index = IniGetInteger("Other", "WinIndex", 0);
    HV_SwitchWindow(win_index);

    RefreshUnTrigger();

    IniCloseFile();
}

// 读取程序设置
int32 ReadAppSet(void)
{
    const char *setFile = "eles/eHex/config.ini";
    int32 oldver;
    int32 ret;

    AppDatas.AppId = GetAppId();
    AppDatas.AppVer = GetAppVer();

    IniOpenFile(setFile);

    AppDatas.InfoType = IniGetInteger("Main", "InfoType", 0x0160L);
    AppDatas.AppFont = IniGetInteger("Main", "FontType", MR_FONT_MEDIUM);
    AppColor.type = IniGetInteger("Main", "SkinType", 0);
    AppDatas.AutoOpen = IniGetBool("Main", "AutoOpen", 0);
    AppDatas.PopMenu = IniGetBool("Main", "PopMenu", 1);
    AppDatas.MenuIndex = IniGetBool("Main", "MenuIndex", 1);
    AppDatas.PageButton = IniGetBool("Main", "PageButton", 1);
#ifdef MR_SPREADTRUM_MOD
    AppDatas.BigEndian = IniGetBool("Main", "BigEndian", 1);;
#else
    AppDatas.BigEndian = IniGetBool("Main", "BigEndian", 0);;
#endif

    // 检查是否更新了版本
    oldver = IniGetInteger("Main", "Version", 0);
    if (oldver < AppDatas.AppVer)
    {
        AppDatas.Updated = 1;
    }
    else
    {
        AppDatas.Updated = 0;
    }

    ret = IniGetString("File", "UserDir", AppDatas.UserDir);
    if (!ret || AppDatas.UserDir[0] == '\0')
        memcpy(AppDatas.UserDir, "C:\\", 4);

    ret = IniGetString("File", "Recent", AppDatas.Recent);
    if (!ret || AppDatas.Recent[0] == '\0')
        memcpy(AppDatas.Recent, "C:\\", 4);

    {
        char *input;

        input = (char *)malloc(M_MAX_INTVAL_BUFFER_SIZE);
        *input = '\0';
        ret = IniGetString("Other", "LastInput", input);
        if (ret)
            GBToUni(input, HE_GetLastInput(), 512);
        TRYFREE(input);
    }

    IniCloseFile();

    // 校正无效设置
    if (AppDatas.InfoType >= 0x4000L)
        AppDatas.InfoType = 0x0160L;

    if (AppDatas.AppFont > 2)
        AppDatas.AppFont = MR_FONT_MEDIUM;

    if (AppColor.type > 7)
        AppColor.type = 0;

    // 计算信息数
    CalcInfoCount();
if(filestate(skinfile)!=MR_IS_FILE)
	{
	char *string=ReadStringFromMrp("skin0.ini");
	int32 f=app_open(skinfile,12);
	app_write(f,string,strlen(string));
	app_close(f);
	free(string);
	}
    return 0;
}

// 保存程序设置
int32 WriteAppSet(void)
{
    char cfgFile[32] = {0}; //"eles/eHex/config.ini";
    char infotypehex[16];

    strcat(cfgFile, "eles/eHex");
    MakeDir(cfgFile);
    strcat(cfgFile, "/config.ini");

    IniOpenFile(cfgFile);
    IniClearContent();

    IniSetInteger("Main", "Version", AppDatas.AppVer);
    sprintf(infotypehex, "%#010x", AppDatas.InfoType);
    IniSetString("Main", "InfoType", infotypehex);
    //IniSetInteger("Main", "InfoType", AppDatas.InfoType);
    IniSetInteger("Main", "FontType", AppDatas.AppFont);
    IniSetInteger("Main", "SkinType", AppColor.type);
    IniSetBool("Main", "AutoOpen", AppDatas.AutoOpen);
    IniSetBool("Main", "PopMenu", AppDatas.PopMenu);
    IniSetBool("Main", "MenuIndex", AppDatas.MenuIndex);
    IniSetBool("Main", "BigEndian", AppDatas.BigEndian);;
    IniSetBool("Main", "PageButton", AppDatas.PageButton);;

    IniSetString("File", "UserDir", AppDatas.UserDir);
    IniSetString("File", "Recent", AppDatas.Recent);

    if (AppDatas.AutoOpen)
    {
        IniSetString("File", "Path1", AppDatas.HDatas[0].FilePath);
        IniSetString("File", "File1", AppDatas.HDatas[0].FileNameA);
        IniSetString("File", "Path2", AppDatas.HDatas[1].FilePath);
        IniSetString("File", "File2", AppDatas.HDatas[1].FileNameA);

        IniSetInteger("Other", "Begin1", AppDatas.HDatas[0].FileReadBegin + AppDatas.HDatas[0].DataShowBegin);
        IniSetInteger("Other", "Begin2", AppDatas.HDatas[1].FileReadBegin + AppDatas.HDatas[1].DataShowBegin);
        IniSetInteger("Other", "Offset1", AppDatas.HDatas[0].FileReadBegin + AppDatas.HDatas[0].DataBufOffset);
        IniSetInteger("Other", "Offset2", AppDatas.HDatas[1].FileReadBegin + AppDatas.HDatas[1].DataBufOffset);
        IniSetInteger("Other", "WinIndex", AppDatas.HIndex);
    }

    {
        char *input;

        input = stru2c(HE_GetLastInput());
        IniSetString("Other", "LastInput", input);
        TRYFREE(input);
    }

    IniCloseFile();

    return 0;
}

/*---------------------------------------------------------------------------*/

// 截屏回调
void SnapScreenCb(const char *name_w)
{
    // 在mrc_bmp.h
    extern int32 mrc_PrintScreen(char *filename);

    char *name_a = NULL;

    name_a = stru2c(name_w);
//XL    mrc_PrintScreen(name_a);
    TRYFREE(name_a);
}

// 截屏
int32 SnapScreen(void)
{
    char *name_w, *name_a;
    char *path = "eles/SnapPic";

    MakeDir(path);
    name_a = (char*)malloc(MAX_PATH_LEN_A);

    if (HV_IsFileOpen())
    {
        sprintf(name_a, "%s/%s.bmp", path, AppDatas.HDataCur->FileNameA);
    }
    else
    {
        mr_datetime t_dt;

        getdatetime(&t_dt);
        sprintf(name_a, "%s/%d%02d%02d-%02d%02d.bmp", path, 
            t_dt.year, t_dt.month, t_dt.day, t_dt.hour, t_dt.minute);
    }

    name_w = strc2u(name_a);
    TRYFREE(name_a);
    ShowInput("截图文件名", name_w, MR_EDIT_ANY, MAX_FILENAME_LEN_A / 2, SnapScreenCb);
    TRYFREE(name_w);

    return 0;
}

/*---------------------------------------------------------------------------*/

// 程序事件
int32 Main_Event(int32 type, int32 p1, int32 p2)
{
    int32 ret = MR_IGNORE;

    // 截屏操作，高优先级
    if ((MR_KEY_RELEASE == type && MR_KEY_SEND == p1) ||
        (MR_MOUSE_DOWN == type && p2 < 10))
    {
        SnapScreen();
        return MR_SUCCESS;
    }

    switch (AppState)
    {
    case APPSTATE_HEXVIEW: // Hex查看状态
        ret = HV_Event(type, p1, p2);
        break;
    case APPSTATE_HEXEDIT: //Hex编辑状态
        ret = HE_Event(type, p1, p2);
        break;
    case APPSTATE_MENU: //显示菜单状态
        ret = Menu_Event(type, p1, p2);
        break;
    case APPSTATE_FILEVIEW: //文件浏览界面
        ret = FileView_Event(type, p1, p2);
        break;
    case APPSTATE_INFOPAGE:  // 信息页
        ret = InfoPage_Event(type, p1, p2);
        break;
    case APPSTATE_PLUGIN_MGR: //插件浏览界面
   //XL     ret = PM_Event(type, p1, p2);
        break;
    case APPSTATE_PLUGIN_RUN:
        break;
    case APPSTATE_LOCALUI: //本地控件事件
        switch (type)
        {
        case MR_DIALOG_EVENT: //对话框事件（编辑框）
            ret = LocalDialogEvent(p1);
            break;
        case MR_LOCALUI_EVENT: //本地窗口事件
            break;
        }
        break;
    default:
        ret = MR_IGNORE;
        break;;
    }

    if (MR_IGNORE == ret)  // 其它窗口未处理的事件
    {
        switch (type)
        {
        case MR_KEY_RELEASE:
            switch (p1)
            {
            case MR_KEY_STAR:
                SetAppColors();  // 切换皮肤
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }

    }

    return MR_SUCCESS;
}

/*---------------------------------------------------------------------------*/

// 该函数在应用启动时被mythroad平台调用
int32 init(void)
{
//		mr_screeninfo scrinfo;
//
//	mrc_getScreenInfo(&scrinfo);
	int SCREEN_WIDTH=SCRW;
	int SCREEN_HEIGHT=SCRH;
	
	setscrsize(320,320*SCREEN_HEIGHT/SCREEN_WIDTH);
	switchPath("c");
	
    AppInitState = 1;
    
    ReadAppSet();
    
    Main_Init();
    if (-1 == AppInitState)
    {
        ClearScreen();
        DrawTextScreenA("程序初始化失败！", 2, 2);
        
        RefreshScreen();
        app_exit();


        return MR_SUCCESS;
    }

    OpenLastFile();
    
    Main_Draw(1);

    // 进行了版本更新
    if (AppDatas.Updated)
    {
        
        M_ShowNew(0);
    }
    

    return MR_SUCCESS;
}

// 该函数在应用退出时被mythroad平台调用
int32 exitApp(void)
{
    if (0 == AppInitState)
    {
        AppState = APPSTATE_HEXVIEW;
        Main_End();
    }

    WriteAppSet();

    return 0;
}

#ifdef SDK_MOD  // 模拟器环境

// 该函数在应用运行期间，每当mythroad平台收到事件时被调用
int32 mrc_appEvent(int32 code, int32 param0, int32 param1)
{
    return Main_Event(code, param0, param1);
}

// 该函数在应用暂停时被mythroad平台调用
int32 mrc_appPause(void)
{
    return MR_SUCCESS;
}

// 该函数在应用恢复运行时被mythroad平台调用
int32 mrc_appResume(void)
{
    Main_Draw(1);

    return MR_SUCCESS;
}

#elif 0  // 使用plugin=app参数编译

// 该函数在应用运行期间，每当mythroad平台收到事件时被调用
int32 mrc_appEvent(int32 code, int32 param0, int32 param1)
{
    return Main_Event(code, param0, param1);
}

// 该函数在应用暂停时被mythroad平台调用
int32 mrc_appPause(void)
{
    return MR_SUCCESS;
}

// 该函数在应用恢复运行时被mythroad平台调用
int32 mrc_appResume(void)
{
    Main_Draw(1);

    return MR_SUCCESS;
}

// 不需要mrp校验时避免链接失败
int32 mrc_verifyMrpCertificate_V1(const char *mrpName)
{
    return 0;
}

#else  // 使用plugin=appdev参数编译

// 该函数在应用运行期间，每当mythroad平台收到事件时被调用
int32 event(int32 code, int32 param0, int32 param1)
{
	char *filename;
	if(code==10 && param0==0) //文件浏览器返回事件
	{
		//char path[300];
		//char name[300];
		//filename=fv_getpath();
		//strncpy(path,filename,strrchr(filename,'/')-filename);
		//strcpy(name,strrchr(filename,'/'));
		//FileView_Hide(path,name);
		//AppDatas.HDataCur->FilePath=NULL;
		//sprintf(AppDatas.HDataCur->FileNameA,filename);
		//FileView_Hide	(NULL,filename);
		
		HV_OpenFile("c:/",fv_getpath());
		  //      HV_GotoFileOffset(1);
			//	HV_OpenFile
		//toast(path,0);
		toast(fv_getpath(),0);
		
	}
    return Main_Event(code, param0, param1);
}

// 该函数在应用暂停时被mythroad平台调用
int32 pause(void)
{
    return MR_SUCCESS;
}

// 该函数在应用恢复运行时被mythroad平台调用
int32 resume(void)
{
    Main_Draw(1);

    return MR_SUCCESS;
}

int32 mrc_extRecvAppEvent(int32 app,int32 code,int32 param0,int32 param1)
{
    return MR_SUCCESS;
}

int32 mrc_extRecvAppEventEx(int32 code, int32 p0, int32 p1, int32 p2, int32 p3, int32 p4,int32 p5)
{
    return MR_SUCCESS;
}

#endif
