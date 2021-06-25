/*
 * 主程序菜单头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/4/2012]
 */

#ifndef __MENUFUNC_H__
#define __MENUFUNC_H__

#include "Menu.h"

PMENU_LINK MainMenu_InitItems(void);
void MainMenu_SetChecked(uint8 Index1, uint8 Index2, uint8 Index3, uint8 IsChecked);
void MainMenu_SetEnabled(uint8 Index1, uint8 Index2, uint8 Index3, uint8 IsEnabled);
int32 MainMenu_GetData(uint8 Index1, uint8 Index2, uint8 Index3);

// 以下函数为菜单回调，尽量不要外部调用

void M_RedoRecent(int32 data);

void M_SetFont(int32 data);
void M_SetInfo(int32 data);
void M_SetColor(int32 data);
void M_SetPopMenu(int32 data);
void M_SetEndian(int32 data);
void M_SetUserDir(int32 data);

void M_FileView(int32 data);
void M_DirView(int32 data);
void M_FVUserDir(int32 data);
void M_FileClose(int32 data);
void M_FVRecent(int32 data);
//void M_CreateFile(int32 data);
//void M_FileCopy(int32 data);
//void M_FileRename(int32 data);
//void M_FileDel(int32 data);

void M_PageUp(int32 data);
void M_PageDown(int32 data);
void M_PageHome(int32 data);
void M_PageEnd(int32 data);
void M_GotoOffset(int32 data);

void M_FindData(int32 type);
void M_FindNext(int32 data);

void M_WriteData(int32 type);
void M_WriteNext(int32 data);

void M_CF_File(int32 data);
void M_CompareSame(int32 data);
void M_CompareDiff(int32 data);
void M_CompareNext(int32 data);

void M_AddData(int32 data);
void M_DelData(int32 data);
void M_Data2File(int32 data);

void M_PluginMgr(int32 data);
void M_PluginDir(int32 data);

void M_ShowNew(int32 data);
void M_ShowHelp(int32 data);
void M_ShowAbout(int32 data);
void M_ExitApp(int32 data);

#endif  // __MENUFUNC_H__
