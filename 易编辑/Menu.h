/*
 * 程序菜单头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [7/24/2012]
 */

#ifndef __MENU_H_
#define __MENU_H_
#include "src/base.h"
#define MENU_FLAG_ENABLE   0x1L   // 有效
#define MENU_FLAG_CHECK    0x2L   // 选中
#define MENU_FLAG_AUTOFOLD 0x4L   // 自动关闭
#define MENU_FLAG_UNICODE  0x8L   // 文本为unicode(默认gb2312)
#define MENU_FLAG_ACTIVE   0x10L  // 激活
#define MENU_FLAG_VISIBLE  0x20L  // 可见

// 普通菜单状态
#define MENU_FLAG_NORMAL   (MENU_FLAG_ENABLE | MENU_FLAG_AUTOFOLD)

// 菜单显示标志
#define MENU_SHOW_FLAG_NO_TOOLBAR  0x1  // 不显示工具栏
#define MENU_SHOW_FLAG_INDEX       0x2  // 显示菜单序号

// 菜单回调类型
#define MENU_CALLBACK_DRAWBACK  0x0
#define MENU_CALLBACK_REFRESH   0x1
#define MENU_CALLBACK_CANCLE    0x2

// 最大菜单层数
#define MENU_MAX_LAYER 3

// 菜单文本最大字节数(转换为unicode计算)
#define MENU_MAX_TITLE_LEN  20

// 标志位设置
#define MENU_SET_FLAG(m,f)      do{(m)->Flag |= (f);}while(0)
// 标志位清除
#define MENU_CLEAR_FLAG(m,f)    do{(m)->Flag &= ~(f);}while(0)
// 标志位设置+清除
#define MENU_SET_FLAG_EX(m,f,s) do{if(s){(m)->Flag |= (f);}else{(m)->Flag &= ~(f);}}while(0)
// 标志位读取
#define MENU_GET_FLAG(m,f)      ((m)->Flag & (f))

// 菜单回调函数类型
typedef void (*MENU_CBF)(int32 data);

// 菜单项目信息
typedef struct Menu_st 
{
	char Title[MENU_MAX_TITLE_LEN];  // 显示文字
    uint8 Index;                     // 在同级菜单序号,从1开始
    uint8 Children;                  // 子菜单数
    uint32 Flag;                     // 标志
    int32 Data;                      // 附加数据
	MENU_CBF CBFunc;                 // 回调函数
	struct Menu_st *Before;          // 上一菜单项
	struct Menu_st *Next;            // 下一菜单项
    struct Menu_st *Parent;          // 父菜单项
	struct Menu_st *Child;           // 第一个子菜单项
} MENU_LINK, *PMENU_LINK;

int32 Menu_Init(void);
int32 Menu_End(void);
int32 Menu_Draw(uint8 refresh);
int32 Menu_Event(int32 code, int32 p0, int32 p1);

int32 Menu_Show(PMENU_LINK menu, MENU_CBF cb, int16 x, int16 y, int32 flag);
int32 Menu_Destroy(PMENU_LINK menu);

PMENU_LINK Menu_Add(PMENU_LINK mParent, char *sTitle, MENU_CBF CBFunc, int32 data, int32 flag);
PMENU_LINK Menu_GetByIndex(PMENU_LINK mParent, uint8 Index);

int32 Menu_DrawEx(uint8 DrawBack, uint8 refresh);
int32 Menu_Refresh(uint8 redraw);

int32 Menu_Before(PMENU_LINK menu, uint8 refresh);
int32 Menu_Next(PMENU_LINK menu, uint8 rfresh);
int32 Menu_Expand(PMENU_LINK mParent);
int32 Menu_Fold(PMENU_LINK mParent);
int32 Menu_Hide(void);

PMENU_LINK Menu_GetActive(void);
uint8 Menu_IsEnable(PMENU_LINK menu);
uint8 Menu_IsCheck(PMENU_LINK menu);

int32 Menu_SetActive(PMENU_LINK menu);
int32 Menu_SetEnable(PMENU_LINK menu, uint8 enable);
int32 Menu_SetCheck(PMENU_LINK menu, uint8 check);
int32 Menu_SetShowFlag(int32 flag);

#endif  // __MENU_H_
