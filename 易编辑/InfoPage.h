/*
 * 信息页显示头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/2/2012]
 */

#ifndef __INFOPAGE_H__
#define __INFOPAGE_H__
#include "src/base.h"
// 信息页标记位
#define INFOPAGE_FLAG_BUTTON_OK    0x1  // 有确定按钮
#define INFOPAGE_FLAG_FREE_TITLE   0x2  // 需要释放标题数据
#define INFOPAGE_FLAG_FREE_CONTENT 0x4  // 需要释放文本数据
#define INFOPAGE_FLAG_CONTENT_GB   0x8  // 文本数据为GB编码(默认unicode)

// 回调函数类型
typedef void (*INFOPAGE_CBF)(int32 is_ok);

int32 InfoPage_Init(void);
int32 InfoPage_End(void);
int32 InfoPage_Draw(uint8 refresh);
int32 InfoPage_Event(int32 type, int32 p1, int32 p2);

// 显示信息
// 参数：标题(gb)，内容(默认UCS2BE)，标志，回调(可为NULL)
int32 InfoPage_Show(char *title, char *content, int32 flag, INFOPAGE_CBF cb);

// 设置工具栏按钮文字
// 必须在InfoPage_Show之后调用，只对此次显示有效
int32 InfoPage_SerToolBarText(const char *wStrL, const char *sStrR);

#endif // __INFOPAGE_H__
