/*
 * 程序框架头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/3/2012]
 */

#ifndef __APPMAIN_H__
#define __APPMAIN_H__

#include "HexView.h"
#include "Menu.h"

// 广告位ID
//#define APP_ADVBAR_ID        8000158

// 程序状态枚举
typedef enum 
{
    APPSTATE_NORMAL,       // 直接返回初始状态
    APPSTATE_RETURN,       // 返回上个状态

    APPSTATE_HEXVIEW,      // Hex查看
    APPSTATE_HEXEDIT,      // Hex编辑
    APPSTATE_MENU,         // 菜单显示
    APPSTATE_FILEVIEW,     // 文件浏览
    APPSTATE_INFOPAGE,     // 信息显示
    APPSTATE_LOCALUI,      // 本地UI(编辑框)
    APPSTATE_PLUGIN_MGR,   // 插件管理
    APPSTATE_PLUGIN_RUN,   // 插件运行

    APPSTATE_MAX
} APPSTATE_ENUM;

// 程序数据结构体
typedef struct
{
    int32 AppId;      // ID
    int32 AppVer;     // 版本
    uint32 InfoType;  // 信息类型(按位设置)
    uint16 InfoCount; // Hex信息数
    uint16 AppFont;   // 字体
    uint8 BigEndian;  // 字节序
    uint8 PopMenu;    // 快捷键弹菜单
    uint8 MenuIndex;  // 显示菜单序号
    uint8 AutoOpen;   // 自动打开上次文件
    uint8 PageButton; // 显示翻页按钮
    uint8 Updated;    // 程序进行了更新
    uint16 *ScnBuf;   // 屏幕缓冲区
    uint16 ScnWidth;  // 屏幕宽
    uint16 ScnHeight; // 屏幕高

    HEX_VIEW_ST HDatas[2]; // 所有窗口的Hex数据
    HEX_VIEW_ST *HDataCur; // 当前窗口Hex数据
    int32 HIndex;          // 当前显示窗口序号

    PMENU_LINK MainMenu;   // 主菜单

    char UserDir[MAX_PATH_LEN_A]; // 常用目录
    char Recent[MAX_PATH_LEN_A];  // 最近打开文件
} APPDATAS_ST;

extern APPDATAS_ST AppDatas;
extern int32 AppInitState;

int32 Main_Init(void);
int32 Main_End(void);
int32 Main_Draw(uint8 refresh);
int32 Main_Event(int32 type, int32 p1, int32 p2);

APPSTATE_ENUM GetAppState(void);
int32 SetAppState(APPSTATE_ENUM NewState, int32 refresh);

int32 ReadAppSet(void);
int32 WriteAppSet(void);

int32 SetAppFont(uint16 font);
int32 SetInfoType(uint32 type);
//int32 SetAppColors(void);

int32 SnapScreen(void);

#endif // __APPMAIN_H__
