/*
 * Hex编辑头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [7/8/2012]
 */

#ifndef __HEXEDIT_H__
#define __HEXEDIT_H__

// Hex编辑输入数据类型
enum
{
    HE_INPUT_DATA_TYPE_LAST,

    HE_INPUT_DATA_TYPE_HEX,
    HE_INPUT_DATA_TYPE_UCS2BE,
    HE_INPUT_DATA_TYPE_UCS2LE,
    HE_INPUT_DATA_TYPE_GB2312,
    HE_INPUT_DATA_TYPE_UTF8,
    HE_INPUT_DATA_TYPE_NUM,
    HE_INPUT_DATA_TYPE_DATA,

    HE_INPUT_DATA_TYPE_MAX
};

// 文件比较方式
enum
{
    HE_COMPARE_SAME,
    HE_COMPARE_DIFFERENT,

    HE_COMPARE_MAX
};

int32 HE_Init(void);
int32 HE_End(void);
int32 HE_Draw(uint8 refresh);
int32 HE_Event(int32 code, int32 p1, int32 p2);

// 保存值到当前位置
// 参数：当前光标位置新值(0-F)
int32 HE_SaveValue(uint8 NewValue);

// 保存数据到当前位置
// 参数：新数据缓冲区，缓冲区大小
int32 HE_SaveData(uint8 *DataBuf, int32 bufSize);

// 插入数据
// 参数：数据(为NULL时写入0)，数据大小
int32 HE_InsertData(uint8 *data, int32 size);

// 删除数据
// 参数：删除大小
int32 HE_DeleteData(int32 size);

// 获取上次输入内容，不需释放
char *HE_GetLastInput(void);

// 查找数据
// 参数：输入类型，内容
int32 HE_FindInput(int32 type, const char *inStr);

int32 HE_FindData(int32 type, void *data, int32 len);

// 写入数据
// 参数：输入类型，内容
int32 HE_WriteInput(int32 type, const char *inStr);

int32 HE_WriteData(int32 type, void *data, int32 len);

// 比较两个文件
int32 HE_Compare(void);

// 设置比较模式
int32 HE_SetCompareMode(int32 mode);

// 重复上次操作
int32 HE_RedoAction(void);

#endif // __HEXEDIT_H__
