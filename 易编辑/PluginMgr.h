/*
 * 插件支持头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/4/2012]
 */

#ifndef __PLUGINMGR_H__
#define __PLUGINMGR_H__

//#include <aps_main.h>

// 包含宏定义和类型枚举等
#include "Plugin.h"

// 插件库初始化
int32 PM_Init(void);

// 插件系统释放
int32 PM_End(void);

// 刷新插件列表显示
int32 PM_Draw(uint8 refresh);

// 插件管理器事件
int32 PM_Event(int32 code, int32 p0, int32 p1);

// 显示插件浏览界面
int32 PM_Show(void);

// 搜索插件
int32 PM_Search(void);

// 清除插件列表
int32 PM_CleanList(void);

// 加载指定文件名插件
int32 Plugin_Load(char *pluginmrp);

// 释放已加载插件
void Plugin_Unload(void);

// 阻塞插件事件
void Plugin_Block(void);

// 恢复插件事件
void Plugin_UnBlock(void);

// 刷新插件显示
void Plugin_Redraw(uint8 refresh);

#endif // __PLUGINMGR_H__
