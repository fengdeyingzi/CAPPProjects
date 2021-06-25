/*
 * 本地控件头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/4/2012]
 */

#ifndef __LOCALUI_H__
#define __LOCALUI_H__

// 最大输入字符数
// 大多数手机不支持255以上
#define MAX_INPUT_TEXT_LEN  (255)

// 编辑框缓冲区大小
#define MAX_INPUT_BUF_SIZE  (MAX_INPUT_TEXT_LEN * 2 + 2)

typedef void (*INPUT_CB)(const char *inputStr);

int32 ShowInput(char *stitle, char *stext, int32 type, int32 max_size, INPUT_CB cbFunc);

int32 LocalDialogEvent(int32 KeyCode);

#endif // __LOCALUI_H__
