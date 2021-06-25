/*
 * 扩展插件支持
 * 版权所有 (C) 2011-2012 eleqian
 * [7/24/2012]
 */

#include <mrc_base.h>
#include <mrc_exb.h>
//#include <aps_main.h>

#include "AppMain.h"
#include "PluginMgr.h"
#include "HexView.h"
#include "HexEdit.h"
#include "Menu.h"
#include "FileView.h"
#include "InfoPage.h"
#include "IniFile.h"
#include "LocalUI.h"
#include "KeyTimer.h"
#include "DrawLib.H"
#include "Functions.h"
#include "XString.h"

// 指定不再兼容的低版本插件版本
#define MIN_SUPPORT_APP_VERSION 2011

// 插件信息链表
typedef struct PluginFile_st
{
    int32 index;
    char app_name[24];
    char *file_name;
    char *description;
    struct PluginFile_st *next;
} PLUGIN_FILE_ST;

// 插件列表信息
typedef struct
{
    PLUGIN_FILE_ST *head;
    PLUGIN_FILE_ST *top;
    PLUGIN_FILE_ST *cur;
} PLUGINS_ST;

static mr_screenRectSt rectTitle, rectTool;  // 标题栏，工具栏
static mr_screenRectSt rectInfo, rectDesc;   // 信息栏，插件信息栏
static mr_screenRectSt rectList, rectScroll; // 文件列表，滚动条

static uint16 ButtonWidth; // 按钮宽度(工具栏)
static uint16 ItemHeight;  // 列表项高度
static int32 VisLines;     // 列表可显示项目数

static PLUGINS_ST PluginList;    // 插件列表
static int32 PluginCount;        // 文件总数
static int32 PluginUnloadTimer;  // 插件加载定时器
static int32 PluginBlockCount;   // 插件阻塞计数
static int32 PluginExtID;        // 插件加载ID
static int32 InputBoxID;         // 输入框ID

static char MainMrpName[MAX_PATH_LEN_A];    // 主程序路径
static char PluginMrpName[MAX_PATH_LEN_A];  // 当前插件路径

static void PM_ShowMsgA(char *sText, uint8 Refresh);

static int32 MyFileViewCb(const char *dir, const char *name);
static void MyInputCb(const char *str);
static void MyMenuItemCb(int32 data);
static void MyMenuCallback(int32 type);
static void MyInfoPageCb(int32 is_ok);
static void CheckPluginVersionCb(int32 version);
static void CheckPluginVersionCb1(int32 version);

/*
* 易编辑主程序接口定义
* p0 - 一级消息类型(接口分类)
* p1 - 二级消息类型或函数参数
* p2 - 函数参数
* p3 - 函数参数
* p4 - 函数参数
* p5 - 函数参数
*/
static int32 MainRecvAppEventEx(int32 p0, int32 p1, int32 p2, int32 p3, int32 p4,int32 p5)
{
    switch (p0)
    {
    case MAIN_EXT_FUNC_RETURN:
        Plugin_Unload();
        break;

    case MAIN_EXT_FUNC_QUERY:  // 信息查询
        switch (p1)
        {
        case EXT_FUNC_QUERY_PLUGIN_ID:
            return PluginExtID;
        case EXT_FUNC_QUERY_APP_ID:
            return AppDatas.AppId;
        case EXT_FUNC_QUERY_MAIN_VERSION:
            return AppDatas.AppVer;
        case EXT_FUNC_QUERY_MAIN_NAME:
            return (int32)MainMrpName;
        case EXT_FUNC_QUERY_PLGUIN_NAME:
            return (int32)PluginMrpName;
        case EXT_FUNC_QUERY_ARG_FILENAME:
            if (0 != p2)  // 暂时兼容旧版本，以后将删除
                return (int32)strcpy((char*)p2, AppDatas.HDataCur->FileNameA);
            else
                return (int32)AppDatas.HDataCur->FileNameA;
        case EXT_FUNC_QUERY_ARG_FILEPATH:
            if (0 != p2)
                return (int32)strcpy((char*)p2, AppDatas.HDataCur->FilePath);
            else
                return (int32)AppDatas.HDataCur->FilePath;
        case EXT_FUNC_QUERY_ARG_FILESIZE:
            return HV_GetFileSize();
        case EXT_FUNC_QUERY_ARG_FILEOFFET:
            return HV_GetFileOffset();
        case EXT_FUNC_QUERY_FONT:
            return AppDatas.AppFont;
        case EXT_FUNC_QUERY_SKIN_TYPE:
            return AppColor.type;
        case EXT_FUNC_QUERY_SKIN_COLOR:
            switch (p2)
            {
            case SKIN_COLOR_BACK_MORMAL:
                return (int32)AppColor.back_normal;
            case SKIN_COLOR_BACK_LIGHT:
                return (int32)AppColor.back_light;
            case SKIN_COLOR_BACK_DEEP:
                return (int32)AppColor.back_deep;
            case SKIN_COLOR_TEXT_NORMAL:
                return (int32)AppColor.text_normal;
            case SKIN_COLOR_TEXT_LIGHT:
                return (int32)AppColor.text_light;
            case SKIN_COLOR_TEXT_FOCUS:
                return (int32)AppColor.text_focus;
            case SKIN_COLOR_TEXT_DISABLE:
                return (int32)AppColor.text_disabled;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;

    case MAIN_EXT_FUNC_CONTROL:  // 主程序控制
        switch (p1)
        {
        case EXT_FUNC_CONTROL_OPENFILE:
            return HV_OpenFile((char*)p2, (char*)p3);
        case EXT_FUNC_CONTROL_CLOSEFILE:
            return HV_CloseFile();
        case EXT_FUNC_CONTROL_SWITCH_WINDOW:
            return HV_SwitchWindow(p2);
        case EXT_FUNC_CONTROL_GOTO_OFFSET:
            return HV_GotoFileOffset(p2);
        case EXT_FUNC_CONTROL_FIND_DATA:
            return HE_FindData(p2, (void*)p3, p4);
        case EXT_FUNC_CONTROL_SAVE_DATA:
            return HE_WriteData(p2, (void*)p3, p4);
        case EXT_FUNC_CONTROL_INSTERT_DATA:
            return HE_InsertData((uint8*)p2, p3);
        case EXT_FUNC_CONTROL_DELETE_DATA:
            return HE_DeleteData(p2);
        case EXT_FUNC_CONTROL_REDRAW:
            return Main_Draw((uint8)p2);
        default:
            break;
        }
        break;

    case MAIN_EXT_FUNC_DRAW:  // 界面绘制
        switch (p1)
        {
        case EXT_FUNC_DRAW_CLS:
            ClearScreen();
            break;
        case EXT_FUNC_DRAW_REFRESH:
            RefreshScreen();
            break;
        case EXT_FUNC_DRAW_CLEAR_RECT:
            ClearRect(*(mr_screenRectSt*)p2);
            break;
        case EXT_FUNC_DRAW_REFRESH_RECT:
            RefreshRect(*(mr_screenRectSt*)p2);
            break;
        case EXT_FUNC_DRAW_HLINE:
            DrawHLine((int16)p2, (int16)p3, (int16)p4, (int16)p5);
            break;
        case EXT_FUNC_DRAW_VLINE:
            DrawVLine((int16)p2, (int16)p3, (int16)p4, (int16)p5);
            break;
        case EXT_FUNC_DRAW_ROUND_BORDER:
            {
                mr_screenRectSt *rect = (mr_screenRectSt *)p2;
                DrawRoundBorderEx(rect->x, rect->y, rect->w, rect->h, (uint32)p3);
            }
            break;
        case EXT_FUNC_DRAW_FILL_RECT:
            DrawFillRect(*(mr_screenRectSt*)p2, (uint32)p3);
            break;
        case EXT_FUNC_DRAW_SHADE_RECT:
            DrawShadeRect(*(mr_screenRectSt*)p2);
            break;
        case EXT_FUNC_DRAW_TEXT_SCREENW:
            DrawTextScreenW((char*)p2, (int16)p3, (int16)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_SCREENA:
            DrawTextScreenA((char*)p2, (int16)p3, (int16)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_LINESW:
            DrawTextLinesW(*(mr_screenRectSt*)p2, (char*)p3, (uint32)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_LINESA:
            DrawTextLinesA(*(mr_screenRectSt*)p2, (char*)p3, (uint32)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_MIDW:
            DrawTextMidW(*(mr_screenRectSt*)p2, (char*)p3, (uint32)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_MIDA:
            DrawTextMidA(*(mr_screenRectSt*)p2, (char*)p3, (uint32)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_MID_LEFTW:
            DrawTextMidLeftW(*(mr_screenRectSt*)p2, (char*)p3, (uint32)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_MID_LEFTA:
            DrawTextMidLeftA(*(mr_screenRectSt*)p2, (char*)p3, (uint32)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_MID_RIGHTW:
            DrawTextMidRightW(*(mr_screenRectSt*)p2, (char*)p3, (uint32)p4);
            break;
        case EXT_FUNC_DRAW_TEXT_MID_RIGHTA:
            DrawTextMidRightA(*(mr_screenRectSt*)p2, (char*)p3, (uint32)p4);
            break;
        case EXT_FUNC_DRAW_TITLEBARW:
            DrawNormalTitleBarW(*(mr_screenRectSt*)p2, (char*)p3);
            break;
        case EXT_FUNC_DRAW_TOOLBARW:
            DrawNormalToolBarW(*(mr_screenRectSt*)p2, (char*)p3, (char*)p4, (uint8)p5);
            break;
        default:
            break;
        }
        break;

    case MAIN_EXT_FUNC_STRING:  // 字符串相关
        switch (p1)
        {
        case EXT_FUNC_STR_STRICMP:
            return stricmp((char*)p2, (char*)p3);
        case EXT_FUNC_STR_STRNICMP:
            return strnicmp((char*)p2, (char*)p3, p4);
        case EXT_FUNC_STR_STRDUP:
            return (int32)strdup((char*)p2);
        case EXT_FUNC_STR_STRRCHR:
            return (int32)strrchr((char*)p2, (int)p3);
        case EXT_FUNC_STR_UCASE:
            return (int32)strupr((char*)p2);
        case EXT_FUNC_STR_LCASE:
            return (int32)strlwr((char*)p2);

        case EXT_FUNC_STR_WSTRLEN:
            return wstrlen((char*)p2);
        case EXT_FUNC_STR_WSTRCMP:
            return wstrcmp((char*)p2, (char*)p3);
        case EXT_FUNC_STR_WSTRDUP:
            return (int32)wstrdup((char*)p2);
        case EXT_FUNC_STR_WSTRCPY:
            return (int32)wstrcpy((char*)p2, (char*)p3);
        case EXT_FUNC_STR_WSTRNCPY:
            return (int32)wstrncpy((char*)p2, (char*)p3, p4);
        case EXT_FUNC_STR_WSTRCAT:
            return (int32)wstrcat((char*)p2, (char*)p3);

        case EXT_FUNC_STR_WITOA:
            return (int32)witoa(p2);
        case EXT_FUNC_STR_WATOI:
            return watoi((char*)p2);
        case EXT_FUNC_STR_ASC2UNI:
            return Asc2Uni((char*)p2, (char*)p3, p4);
        case EXT_FUNC_STR_UNI2ASC:
            return Uni2Asc((char*)p2, (char*)p3, p4);
        case EXT_FUNC_STR_GB2UNI:
            return GBToUni((char*)p2, (char*)p3, p4);
        case EXT_FUNC_STR_UNI2GB:
            return UniToGB((char*)p2, (char*)p3, p4);
        case EXT_FUNC_STR_UTF82UNI:
            return UTF8ToUni((char*)p2, (char*)p3, p4);
        case EXT_FUNC_STR_UNI2UTF8:
            return UniToUTF8((char*)p2, (char*)p3, p4);
        case EXT_FUNC_STR_STRC2U:
            return (int32)strc2u((char*)p2);
        case EXT_FUNC_STR_STRU2C:
            return (int32)stru2c((char*)p2);
        case EXT_FUNC_STR_BMH:
            return (int32)BMH((void*)p2, (uint32)p3, (void*)p4, (uint32)p5);
        default:
            break;
        }
        break;

    case MAIN_EXT_FUNC_UTILE:  // 实用函数
        switch (p1)
        {
        case EXT_FUNC_ULTILE_REG_EVENT_FUNC:
            return aps_main_regEntry(PluginExtID, p2);
        case EXT_FUNC_ULTILE_GETCURDIR:
            return GetCurDir((char*)p2);
        case EXT_FUNC_ULTILE_SWITCHDIR:
            return Switch2Dir((char*)p2);
        case EXT_FUNC_ULTILE_COPYFILE:
            return CopyFile((char*)p2, (char*)p3);
        case EXT_FUNC_ULTILE_COPYFILE_PATH:
            return CopyFileFullPath((char*)p2, (char*)p3, (char*)p4, (char*)p5);
        case EXT_FUNC_ULTILE_COPYFILE_HANDLE:
            return CopyFileByHandle(p2, p3, p4);
        case EXT_FUNC_ULTILE_FINDFROM_HANDLE:
            return FindFromFileByHandle(p2, p3, (uint8*)p4, p5);
        case EXT_FUNC_ULTILE_HEX2DATA:
            return Hex2Data((uint8*)p2, p3, (uint8*)p4, p5);
        case EXT_FUNC_ULTILE_DATA2HEX:
            return Data2Hex((uint8*)p2, p3, (uint8*)p4, p5);
        case EXT_FUNC_ULTILE_MAKE_DIR:
            return MakeDirEx((char*)p2);
        case EXT_FUNC_ULTILE_REMOVE_DIR:
            return RemoveDirEx((char*)p2);
        case EXT_FUNC_ULTILE_CONV_DIR2SYS:
            return ConvPath2Sys((char*)p2, (char*)p3, (char*)p4);
        case EXT_FUNC_ULTILE_FIX_DIR:
            return (int32)FixPath((char*)p2, (char)p3);
        case EXT_FUNC_ULTILE_CHECK_VERSION:
            if (p2 > AppDatas.AppVer) { 
                // 主程序版本过低
                // 使用定时器是为了等待插件加载完成，否则不能进行操作
                PluginUnloadTimer = mrc_timerCreate();
                mrc_timerStart(PluginUnloadTimer, 10, p2, CheckPluginVersionCb, 0);
                return 0;
            } else if (p2 < MIN_SUPPORT_APP_VERSION) {
                // 插件不再兼容(主程序不再兼容低版本插件)
                PluginUnloadTimer = mrc_timerCreate();
                mrc_timerStart(PluginUnloadTimer, 10, p2, CheckPluginVersionCb1, 0);
                return 0;
            } else {
                return 1;
            }
            break;
        case EXT_FUNC_ULTILE_LOG:
            WLog((char*)p2, p3);
            break;
        default:
            break;;
        }
        break;

    case MAIN_EXT_FUNC_INIFILE:  // ini配置
        switch (p1)
        {
        case EXT_FUNC_INIFILE_OPEN:
            return IniOpenFile((char*)p2);
        case EXT_FUNC_INIFILE_CLOSE:
            return IniCloseFile();
        case EXT_FUNC_INIFILE_GET_STRING:
            return IniGetString((char*)p2, (char*)p3, (char*)p4);
        case EXT_FUNC_INIFILE_SET_STRING:
            return IniSetString((char*)p2, (char*)p3, (char*)p4);
        case EXT_FUNC_INIFILE_GET_INT:
            return IniGetInteger((char*)p2, (char*)p3, (int)p4);
        case EXT_FUNC_INIFILE_SET_INT:
            return IniSetInteger((char*)p2, (char*)p3, (int)p4);
        case EXT_FUNC_INIFILE_GET_BOOL:
            return IniGetBool((char*)p2, (char*)p3, (int)p4);
        case EXT_FUNC_INIFILE_SET_BOOL:
            return IniSetBool((char*)p2, (char*)p3, (int)p4);
        }

    case MAIN_EXT_FUNC_INPUTBOX:  // 编辑框
        InputBoxID = p1;
        ShowInput((char*)p2, (char*)p3, p4, p5, MyInputCb);
        break;

    case MAIN_EXT_FUNC_FILEVIEW:  // 文件浏览
        return FileView_Show((char*)p1, (char*)p2, p3, MyFileViewCb);
        break;

    case MAIN_EXT_FUNC_INFOPAGE:  // 信息显示
        switch (p1)
        {
        case EXT_FUNC_INFOPAGE_SHOW:
            return InfoPage_Show((char*)p2, (char*)p3, p4, MyInfoPageCb);
        case EXT_FUNC_INFOPAGE_SET_TOOLBAR:
            return InfoPage_SerToolBarText((char*)p2, (char*)p3);
        default:
            break;
        }
        break;

    case MAIN_EXT_FUNC_MENU:  // 菜单
        switch (p1)
        {
        case EXT_FUNC_MENU_ADD:
            return (int32)Menu_Add((PMENU_LINK)p2, (char*)p3, MyMenuItemCb, p4, p5);
        case EXT_FUNC_MENU_SHOW:
            return Menu_Show((PMENU_LINK)p2, MyMenuCallback, (int16)p3, (int16)p4, p5);
        case EXT_FUNC_MENU_DESTROY:
            return Menu_Destroy((PMENU_LINK)p2);
        default:
            break;
        }
        break;

    default:
        break;
    }

    return MR_SUCCESS;
}

// 输入框回调
static void MyInputCb(const char *str)
{
    mrc_extSendAppEventEx(PluginExtID, PLUGIN_EXT_MSG_INPUT, InputBoxID, (int32)str, 0, 0, 0);
}

// 文件浏览回调
static int32 MyFileViewCb(const char *dir, const char *name)
{
    mrc_extSendAppEventEx(PluginExtID, PLUGIN_EXT_MSG_FILEVIEW, (int32)dir, (int32)name, 0, 0, 0);

    return 0;
}

// 信息页回调
static void MyInfoPageCb(int32 is_ok)
{
    mrc_extSendAppEventEx(PluginExtID, PLUGIN_EXT_MSG_INFOPAGE, is_ok, 0, 0, 0, 0);
}

// 菜单回调
static void MyMenuItemCb(int32 id)
{
    mrc_extSendAppEventEx(PluginExtID, PLUGIN_EXT_MSG_MENU, EXT_FUNC_MENU_SELECT, id, 0, 0, 0);
}

static void MyMenuCallback(int32 type)
{
    if (MENU_CALLBACK_CANCLE == type)    {
        mrc_extSendAppEventEx(PluginExtID, PLUGIN_EXT_MSG_MENU, EXT_FUNC_MENU_CANCLE, 0, 0, 0, 0);
    } else {
        mrc_extSendAppEventEx(PluginExtID, PLUGIN_EXT_MSG_MENU, EXT_FUNC_MENU_DRAWBACK, type, 0, 0, 0);
    }
}

// 检查主程序与插件版本是否兼容
static void CheckPluginVersionCb(int32 version)
{
    char info[128];

    Plugin_Unload();
    sprintf(info, "主程序版本过低！\n当前程序版本: %d\n要求最低版本: %d\n", AppDatas.AppVer, version);
    InfoPage_Show("版本错误", info, EXT_INFOPAGE_FLAG_CONTENT_GB, NULL);
    mrc_timerDelete(PluginUnloadTimer);
}

// 检查主程序与插件版本是否兼容1
static void CheckPluginVersionCb1(int32 version)
{
    char info[128];

    Plugin_Unload();
    sprintf(info, "插件版本过低！\n当前程序版本: %d\n插件要求版本: %d\n", AppDatas.AppVer, version);
    InfoPage_Show("版本错误", info, EXT_INFOPAGE_FLAG_CONTENT_GB, NULL);
    mrc_timerDelete(PluginUnloadTimer);
}

/*------------------------------------------------------------------*/

// 计算CRC16
static uint16 crc16(uint8 *buf, uint32 length)
{
    uint16 shift, data, val;
    uint32 i;

    shift = 0xffff;
    data = *buf;

    for (i = 0; i < length; i++)
    {
        if ((i & 0xf) == 0)
            data = (*buf++) << 8;
        val = shift ^ data;
        shift = shift << 1;
        data = data << 1;
        if (val & 0x8000)
            shift = shift ^ 0x1021;
    }

    return shift;
}

// 根据MRP名计算插件ID
// 参数：mrp名称
static int32 CaclExtIDByName(char *name)
{
    int32 crc;
    int32 fd;
    char sname[24];

    fd = mrc_open(name, MR_FILE_RDONLY);
    if (0 == fd)
        return -1;

    mrc_seek(fd, 28, MR_SEEK_SET);
    mrc_read(fd, sname, 24);
    mrc_close(fd);

    crc = crc16((uint8*)sname, strlen(sname));
    crc |= 0x10000;

    return crc;
}

/*------------------------------------------------------------------*/

// 释放插件
void Plugin_Unload(void)
{
#ifndef SDK_MOD
    Switch2Dir("Z");
    aps_main_unloadExt(PluginExtID, 1);
    PluginExtID = 0;
    SetAppState(APPSTATE_RETURN, 1);
#endif
}

// 载入插件
// 参数：插件mrp名称
int32 Plugin_Load(char *pluginmrp)
{
    int32 ret = 0;

#ifndef SDK_MOD
    sprintf(PluginMrpName, "%s/%s", PLUGIN_FOLDER, pluginmrp);
    PluginExtID = CaclExtIDByName(pluginmrp);
    SetAppState(APPSTATE_PLUGIN_RUN, 0);
    ret = aps_main_loadExt(PluginExtID, pluginmrp, PLUGIN_FOLDER, PLUGIN_EXT_NAME);
    if (ret == -1)
    {
        SetAppState(APPSTATE_RETURN, 0);
        PM_ShowMsgA("插件加载失败！", 1);
        return -1;
    }

#else

#if 0
    ChangeAppState(APPSTATE_PLUGIN_RUN, 1);
#else
    PM_ShowMsgA("模拟器暂不支持插件加载！", 1);
#endif

#endif

    return ret;
}

// 刷新插件显示
void Plugin_Redraw(uint8 refresh)
{
    mrc_extSendAppEventEx(PluginExtID, PLUGIN_EXT_MSG_REDRAW, refresh, 0, 0, 0, 0);
}

// 阻塞插件
void Plugin_Block(void)
{
    if (0 == PluginBlockCount && 0 != PluginExtID)
    {
        aps_main_blockKeyEvent(PluginExtID);
    }

    PluginBlockCount++;
}

// 取消阻塞插件
void Plugin_UnBlock(void)
{
    if (PluginBlockCount < 0)
    {
        PluginBlockCount = 0;
        return;
    }

    if (1 == PluginBlockCount && 0 != PluginExtID)
    {
        aps_main_unblockKeyEvent(PluginExtID);
        Plugin_Redraw(1);
    }

    PluginBlockCount--;
}

/*-----------------------------------------------------------------*/

// 初始化“控件”位置
static void InitRects(void)
{
    int16 scnWidth, scnHeight;

    GetTextSizeW16("\x65\x87\x67\x2c\x0\x0", (int16*)&ButtonWidth, (int16*)&ItemHeight); //"文本"
    GetScreenSize16(&scnWidth, &scnHeight);

    ItemHeight += 4;
    ButtonWidth += 8;

    if (ItemHeight < 16)
        ItemHeight = 16;

    // 设定控件位置信息
    rectTitle.x = 0; rectTitle.y = 0; rectTitle.w = scnWidth; rectTitle.h = ItemHeight;
    rectTool.x = 0; rectTool.y = scnHeight - ItemHeight; rectTool.w = scnWidth; rectTool.h = ItemHeight;
    rectInfo.x = 0; rectInfo.y = rectTitle.h; rectInfo.w = scnWidth; rectInfo.h = ItemHeight;
    rectDesc.x = 0; rectDesc.w = scnWidth; rectDesc.h = (uint16)(ItemHeight * 3 - 6); rectDesc.y = scnHeight - rectTool.h - rectDesc.h - 1;
    rectList.x = 0; rectList.y = rectInfo.y + rectInfo.h + 1; rectList.w = scnWidth - 5; rectList.h = scnHeight - rectTitle.h - rectTool.h - rectInfo.h - rectDesc.h - 3;
    rectScroll.x = scnWidth - 5; rectScroll.y = rectList.y; rectScroll.w = 5; rectScroll.h = rectList.h;

    VisLines = rectList.h / ItemHeight;
}

// 绘制标题栏
static void PM_DrawTitleBar(char *Title, uint8 Refresh)
{
    DrawNormalTitleBarW(rectTitle, Title);

    if (Refresh)
        RefreshRect(rectTitle);
}

// 绘制底部工具栏
// 参数：状态：0 - 普通，1 - 左软键，2 - 右软键
static void PM_DrawToolBar(uint8 state, uint8 refresh)
{
    // 载入 / 返回
    DrawNormalToolBarW(rectTool, "\x8f\x7d\x51\x65\x0\x0", "\x8f\xd4\x56\xde\x0\x0", state);

    if (refresh)
        RefreshRect(rectTool);
}

//绘制文件列表
int32 PM_Draw(uint8 refresh)
{
    PLUGIN_FILE_ST *fNode = NULL;
    mr_screenRectSt tRect;
    char fInfo[32] = {0};

    ClearScreen();

    PM_DrawTitleBar("\x62\x69\x5c\x55\x63\xd2\x4e\xf6\x0\x0", 0);
    PM_DrawToolBar(0, 0);

    /*------------------------------------------------------------*/
    // 列表
    tRect.x = rectList.x + 2; tRect.y = rectList.y + 2; tRect.w = rectList.w - 4; tRect.h = ItemHeight;

    fNode = PluginList.top;

    // 绘制各个列表项
    while (NULL != fNode)
    {
        if (fNode == PluginList.cur) // 焦点项
            DrawShadeRect(tRect);

        DrawTextMidLeftA(tRect, fNode->app_name, AppColor.text_normal);

        tRect.y += ItemHeight;

        if (tRect.y + tRect.h >= rectList.y + rectList.h)
            break;

        fNode = fNode->next;
    }

    DrawRoundBorder(rectList);

    /*------------------------------------------------------------*/
    // 信息栏
    DrawFillRect(rectInfo, AppColor.back_light);
    DrawRoundBorder(rectInfo);

    // 文件信息
    if (PluginCount <= 0)
    {
        DrawTextMidLeftA(rectInfo, "无插件", AppColor.text_normal);
    }
    else
    {
        DrawTextMidLeftA(rectInfo, PluginList.cur->file_name, AppColor.text_normal);
        sprintf(fInfo, "%d/%d", PluginList.cur->index, PluginCount);
        DrawTextMidRightA(rectInfo, fInfo, AppColor.text_normal);
    }

    tRect.x = rectDesc.x + 2;
    tRect.y = rectDesc.y + 2;
    tRect.w = rectDesc.w - 4;
    tRect.h = rectDesc.h - 4;

    // 插件信息
    if (PluginCount <= 0)
    {
        DrawTextLinesA(tRect, "请将插件放到eles/plugins/文件夹。", AppColor.text_normal);
    }
    else
    {
        DrawTextLinesA(tRect, PluginList.cur->description, AppColor.text_normal);
    }

    DrawRoundBorder(rectDesc);

    /*------------------------------------------------------------*/
    //滚动条
    if (PluginCount > VisLines)
    {
        int16 sclY, sclH;

        sclY = (int16)(rectScroll.y + 1 + (rectScroll.h - 2) * (PluginList.top->index - 1) / PluginCount);
        sclH = (int16)((rectScroll.h - 2) * VisLines / PluginCount);
        DrawFillRectEx(rectScroll.x + 1, sclY, rectScroll.w - 1, sclH, AppColor.back_deep);
        DrawHLine(rectScroll.x + 2, rectScroll.x + rectScroll.w - 2, sclY - 1, AppColor.back_deep);
        DrawHLine(rectScroll.x + 2, rectScroll.x + rectScroll.w - 2, sclY + sclH, AppColor.back_deep);
    }

    if (refresh)
        RefreshScreen();

    return 0;
}

// 显示提示信息
static void PM_ShowMsgA(char *sText, uint8 Refresh)
{
    mr_screenRectSt tRect;

    tRect.x = rectDesc.x + 2;
    tRect.y = rectDesc.y + 2;
    tRect.w = rectDesc.w - 4;
    tRect.h = rectDesc.h - 4;

    ClearRect(rectDesc);
    DrawTextLinesA(tRect, sText, AppColor.text_focus);
    DrawRoundBorder(rectDesc); //边框

    if (Refresh > 0)
        RefreshRect(rectDesc);
}

// 释放插件文件列表
int32 PM_CleanList(void)
{
    PLUGIN_FILE_ST *tPlg = PluginList.head, *tPlg1;

    while (NULL != tPlg)
    {
        TRYFREE(tPlg->file_name);
        TRYFREE(tPlg->description);
        tPlg1 = tPlg;
        tPlg = tPlg->next;
        TRYFREE(tPlg1);
    }

    PluginList.head = NULL;
    PluginList.cur = NULL;
    PluginList.top = NULL;

    return 0;
}

// 搜索插件目录所有插件
int32 PM_Search(void)
{
    int32 findHwnd, fd;
    int32 count, mrpid;
    char *fBuffer = NULL;
    char *pluginfile;
    char temp[64];
    PLUGIN_FILE_ST *nItem, *tItem;

    PM_CleanList();

    fBuffer = (char*)malloc(MAX_PATH_LEN_A);
    pluginfile = (char*)malloc(MAX_PATH_LEN_A); 

    findHwnd = mrc_findStart(PLUGIN_FOLDER, fBuffer, MAX_PATH_LEN_A);
    if (findHwnd > 0) // 非空文件夹
    {
        // 遍历所有文件夹和文件
        do {
            // 方便退出
            do {
                // 文件名无效
                if ((fBuffer[0] == 0x0)
                    || ((fBuffer[0] == 0x2E) && (fBuffer[1] == 0x0))
                    || ((fBuffer[0] == 0x2E) && (fBuffer[1] == 0x2E) && (fBuffer[2] == 0x0)))
                {
                    break;
                }
                else
                {
                    sprintf(pluginfile, "%s/%s", PLUGIN_FOLDER, fBuffer);
                    fd = mrc_open(pluginfile, MR_FILE_RDONLY);
                    if (0 == fd)
                        break;

                    // 检验appid
                    mrc_seek(fd, 68, MR_SEEK_SET);
                    mrc_read(fd, temp, 4);
                    mrpid = (int32)readLittleEndianUint32((uint8*)temp);
                    if (mrpid != AppDatas.AppId)
                    {
                        mrc_close(fd);
                        break;
                    }

                    // 取得信息
                    nItem = (PLUGIN_FILE_ST*)malloc(sizeof(PLUGIN_FILE_ST));
                    nItem->file_name = strdup(fBuffer);

                    mrc_seek(fd, 28, MR_SEEK_SET);
                    mrc_read(fd, nItem->app_name, 24);
                    mrc_seek(fd, 128, MR_SEEK_SET);
                    mrc_read(fd, temp, 64);
                    mrc_close(fd);
                    nItem->description = strdup(temp);

                    tItem = PluginList.head;

                    // 按名称排序
                    while (NULL != tItem) 
                    {
                        if (stricmp(tItem->app_name, nItem->app_name) > 0)
                        {
                            break;
                        }
                        tItem = tItem->next;
                    }

                    // 插入
                    if (tItem == PluginList.head)
                    {
                        // 新项应该为链表头或者链表为空
                        nItem->next = PluginList.head;
                        PluginList.head = nItem;
                    }
                    else
                    {
                        PLUGIN_FILE_ST *pItem;

                        pItem = PluginList.head;
                        while (NULL != pItem && pItem->next != tItem)
                            pItem = pItem->next;

                        nItem->next = pItem->next;
                        pItem->next = nItem;
                    }
                }
            } while (0);

            // 查找下一个
        } while (MR_SUCCESS == mrc_findGetNext(findHwnd, fBuffer, MAX_PATH_LEN_A));

        // 结束查找
        mrc_findStop(findHwnd);
    }

    PluginList.cur = PluginList.top = PluginList.head;

    for (count = 1, tItem = PluginList.head; tItem != NULL; count++, tItem = tItem->next)
    {
        tItem->index = count;
    }

    PluginCount = count - 1;

    TRYFREE(pluginfile);
    TRYFREE(fBuffer);

    return PluginCount;
}

// 显示插件浏览界面
int32 PM_Show(void)
{
    HV_ShowMsgA("扫描插件……", 1);
    PM_Search();
    HV_ShowMsgA(NULL, 0);
    SetAppState(APPSTATE_PLUGIN_MGR, 1);

    return 0;
}

// 插件系统初始化
int32 PM_Init(void)
{
    InitRects();
    MakeDir(PLUGIN_FOLDER);
    strcpy(MainMrpName, mrc_getPackName());

    PluginCount = 0;
    PluginBlockCount = 0;
    InputBoxID = 0;
    PluginExtID = 0;

 //XL   aps_main_regEntry(APS_EXT_ID_APP, MainRecvAppEventEx);

    return 0;
}

// 插件系统释放
int32 PM_End(void)
{
    PM_CleanList();

    return 0;
}

/*------------------------------------------------------------------*/

static uint8 IsScrolling; //是否滚动条在滚动

// 根据纵坐标改变列表
// 参数：纵坐标,是否触屏抬起
static void PM_FocusByPos(int32 Y, uint8 IsUp)
{
    static uint8 IsFirstPress = 1; //是否第一次点击，避免在点一次就进入
    PLUGIN_FILE_ST *fNode = NULL;
    int32 lIndex;

    if (NULL == PluginList.top)
        return;

    lIndex = (int16)(Y - rectList.y) / ItemHeight + PluginList.top->index;

    //定位焦点项
    fNode = PluginList.head;
    while(fNode && fNode->index != lIndex)
    {
        fNode = fNode->next;
    }

    if (NULL != fNode)
    {
        if (PluginList.cur == fNode && 1 == IsUp) //再次选择
        {
            if (0 == IsFirstPress)
                PM_Event(MR_KEY_RELEASE, MR_KEY_SELECT, 0);
            else
                IsFirstPress = 0;
        }
        else if (PluginList.cur != fNode)
        {
            IsFirstPress = 1;
            PluginList.cur = fNode; //选中
            PM_Draw(1);
        }
    }
}

// 改变滚动条
// 参数：新纵坐标，是否触屏抬起
static void PM_ChangeScroll(int32 NewY, uint8 IsUp)
{
    int16 ScrollM;

    IsScrolling = 1 - IsUp;
    ScrollM = rectScroll.y + 1 + (rectScroll.h - 2) / 2;

    if (0 == IsUp)
    {
        if (NewY > ScrollM)
        {
            PM_Event(MR_KEY_PRESS, MR_KEY_DOWN, 0);
        }
        else
        {
            PM_Event(MR_KEY_PRESS, MR_KEY_UP, 0);
        }
    }
    else
    {
        if (NewY > ScrollM)
        {
            PM_Event(MR_KEY_RELEASE, MR_KEY_DOWN, 0);
        }
        else
        {
            PM_Event(MR_KEY_RELEASE, MR_KEY_UP, 0);
        }
    }
}

// 根据序号取得文件节点
// 参数：序号
// 返回：节点
static PLUGIN_FILE_ST *PM_GetNodeByIndex(int16 index)
{
    PLUGIN_FILE_ST *fNode = NULL;

    fNode = PluginList.head;
    while (NULL != fNode && fNode->index != index)
    {
        fNode = fNode->next;
    }

    if (NULL == fNode)
        fNode = PluginList.head;

    return fNode;
}

// 列表上下移动
static void PM_ListUpDown(int32 lines)
{
    PLUGIN_FILE_ST *fNode = NULL;
    int32 NewIndex = 0;

    if (NULL == PluginList.top || NULL == PluginList.cur || 0 == lines)
        return;

    //定位首项
    NewIndex = PluginList.top->index + lines;

    if (lines < 0) //向上滚动
    {
        if (NewIndex < 1)
            NewIndex = 1;
    }
    else //向下滚动
    {
        if (NewIndex + VisLines > PluginCount) //超出范围
        {
            if (PluginCount > VisLines)
                NewIndex = (int16)(PluginCount - VisLines + 1);
            else
                NewIndex = 1;
        }
    }

    fNode = PluginList.head;
    while (NULL != fNode && fNode->index != NewIndex)
    {
        fNode = fNode->next;
    }
    PluginList.top = fNode;

    //定位焦点项
    NewIndex = PluginList.cur->index;

    if (PluginList.cur->index < PluginList.top->index)
        NewIndex = PluginList.top->index;

    if (PluginList.cur->index > PluginList.top->index + VisLines - 1)
        NewIndex = PluginList.top->index + (int16)VisLines - 1;

    fNode = PluginList.head;
    while (NULL != fNode && fNode->index != NewIndex)
    {
        fNode = fNode->next;
    }
    PluginList.cur = fNode;

    PM_Draw(1);
}

// 列表上下滚动
static void PM_ListScroll(int32 lines)
{
    PLUGIN_FILE_ST *tItem;
    int32 new_index, old_index;

    if (PluginCount <= 0 || 0 == lines)
        return;

    old_index = PluginList.cur->index;
    new_index = old_index + lines;

    if (lines < 0)  // 向上
    {
        if (new_index < 1)  // 到顶部
        {
            if (-1 == lines)  // 只滚动一行时允许循环到底部
            {
                for (tItem = PluginList.head; tItem->next != NULL; tItem = tItem->next)
                    ;
                PluginList.cur = tItem;

                for (tItem = PluginList.head; tItem->index <= PluginCount - VisLines; tItem = tItem->next)
                    ;
                PluginList.top = tItem;
            }
            else
            {
                new_index = 1;
                PluginList.top = PluginList.cur = PluginList.head;
            }
        }
        else
        {
            // 查找新焦点
            for (tItem = PluginList.head;  NULL != tItem; tItem = tItem->next)
            {
                if (tItem->index == new_index)
                {
                    break;
                }
            }

            PluginList.cur = tItem;

            // 需要改变首行显示
            if (new_index < PluginList.top->index)
            {
                PluginList.top = tItem;
            }
        }
    }
    else  // 向下
    {
        if (new_index > PluginCount)  // 到底部
        {
            if (1 == lines)  // 只滚动一行时允许循环到顶部
            {
                new_index = 1;
                PluginList.top = PluginList.cur = PluginList.head;
            }
            else
            {
                for (tItem = PluginList.head; tItem->next != NULL; tItem = tItem->next)
                    ;
                PluginList.cur = tItem;

                for (tItem = PluginList.head; tItem->index <= PluginCount - VisLines; tItem = tItem->next)
                    ;
                PluginList.top = tItem;
            }
        }
        else
        {
            // 查找新焦点
            for (tItem = PluginList.head;  NULL != tItem; tItem = tItem->next)
            {
                if (tItem->index == new_index)
                {
                    break;
                }
            }

            PluginList.cur = tItem;

            // 需要改变首行显示
            if (new_index >= PluginList.top->index + VisLines)
            {
                for (tItem = PluginList.head; tItem->index <= new_index - VisLines; tItem = tItem->next)
                    ;
                PluginList.top = tItem;
            }
        }
    }

    PM_Draw(1);
}

// 插件管理器事件
int32 PM_Event(int32 type, int32 p1, int32 p2)
{
    static int16 InputIndex; //按键输入序号
    static POINT_ST MousePos; //触屏按下位置

    switch (type)
    {
    case MR_KEY_PRESS: // 选择列表项
        switch(p1)
        {
        case MR_KEY_UP: // 上
        case MR_KEY_VOLUME_UP:
            KeyTimerStart(-1, PM_ListScroll);
            break;
        case MR_KEY_DOWN: // 下
        case MR_KEY_VOLUME_DOWN:
            KeyTimerStart(1, PM_ListScroll);
            break;
        case MR_KEY_LEFT: // 左/上翻页
            KeyTimerStart(-VisLines, PM_ListScroll);
            break;
        case MR_KEY_RIGHT: // 右/下翻页
            KeyTimerStart(VisLines, PM_ListScroll);
            break;
        case MR_KEY_SOFTLEFT:
            PM_DrawToolBar(1, 1);
            break;
        case MR_KEY_SOFTRIGHT:
            PM_DrawToolBar(2, 1);
            break;
        default:
            return MR_IGNORE;
        }
        break;
    case MR_KEY_RELEASE:
        switch(p1)
        {
        case MR_KEY_UP:
        case MR_KEY_DOWN:
        case MR_KEY_LEFT:
        case MR_KEY_RIGHT:
        case MR_KEY_VOLUME_UP:
        case MR_KEY_VOLUME_DOWN:
            KeyTimerStop();
            break;
        case MR_KEY_SOFTLEFT:
            PM_DrawToolBar(0, 1);
        case MR_KEY_SELECT: //OK
            if (PluginCount > 0)
                Plugin_Load(PluginList.cur->file_name);
            break;
        case MR_KEY_SOFTRIGHT: //取消浏览
            SetAppState(APPSTATE_RETURN, 1);
            break;
        case MR_KEY_POUND: //转到序号
            if (InputIndex > 0 && InputIndex <= PluginCount)
            {
                PluginList.top = PM_GetNodeByIndex((PluginCount > VisLines + InputIndex) ?
                    InputIndex : (int16)(PluginCount - VisLines + 1));
                PluginList.cur = PM_GetNodeByIndex(InputIndex);
                PM_Draw(1);
                InputIndex = 0;
            }
            break;
        default:
            if (p1 >= MR_KEY_0 && p1 <= MR_KEY_9) //键盘输入序号
            {
                InputIndex = InputIndex * 10 + (int16)p1;
                if (InputIndex > PluginCount)
                    InputIndex = 0;
                return MR_SUCCESS;
            }
            return MR_IGNORE;
            break;
        }
        break;
    case MR_MOUSE_UP: //触屏抬起
        {
            if (1 == IsScrolling) //滚动条
            {
                PM_ChangeScroll(p2, 1);
            }
            else if (MousePos.X - p1 > (int32)rectList.w / 3) //向左滑动
            {
                PM_ListScroll(-VisLines);
            }
            else if (p1 - MousePos.X > (int32)rectList.w / 3) //向右滑动
            {
                PM_ListScroll(VisLines);
            }
            else if (MousePos.Y - (int16)p2 > ItemHeight) //向上滑动
            {
                PM_ListUpDown((MousePos.Y - (int16)p2) / ItemHeight);
            }
            else if ((int16)p2 - MousePos.Y > ItemHeight) //向下滑动
            {
                PM_ListUpDown((MousePos.Y - (int16)p2) / ItemHeight);
            }
            else if (p2 >= rectTool.y && p2 < rectTool.y + rectTool.h)
            {
                if (p1 < ButtonWidth)
                {
                    PM_Event(MR_KEY_RELEASE, MR_KEY_SOFTLEFT, 0);
                }
                else if (p1 >= rectTool.w - ButtonWidth)
                {
                    PM_Event(MR_KEY_RELEASE, MR_KEY_SOFTRIGHT, 0);
                }
            }
            else if (p2 >  rectList.y && p2 < rectList.y + rectList.h)
            {
                if (p1 < rectList.x + rectList.w - 4) //列表
                {
                    PM_FocusByPos(p2, 1);
                }
            }
        }
        break;
    case MR_MOUSE_DOWN: //触屏按下
        {
            MousePos.X = (int16)p1;
            MousePos.Y = (int16)p2;

            if (p2 >= rectTool.y && p2 < rectTool.y + rectTool.h)
            {
                if (p1 < ButtonWidth)
                {
                    PM_Event(MR_KEY_PRESS, MR_KEY_SOFTLEFT, 0);
                }
                else if (p1 >= rectTool.w - ButtonWidth)
                {
                    PM_Event(MR_KEY_PRESS, MR_KEY_SOFTRIGHT, 0);
                }
            }
            else if (p2 >  rectList.y && p2 < rectList.y + rectList.h)
            {
                if (p1 < rectList.x + rectList.w - 4) //列表
                {
                    PM_FocusByPos(p2, 0);
                }
                else //滚动条
                {
                    PM_ChangeScroll(p2, 0);
                }
            }
        }
        break;
    case MR_MOUSE_MOVE:
        {
            int16 lines;

            lines = (int16)((p2 - MousePos.Y) / ItemHeight);

            if (0 != lines) // 滑动
            {
                PM_ListUpDown(-lines);
                MousePos.Y += lines * ItemHeight;
            }
        }
        break;
    }

    return MR_SUCCESS;
}
