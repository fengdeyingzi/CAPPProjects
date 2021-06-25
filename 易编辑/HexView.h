/*
 * HEX查看头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [6/4/2012]
 */

#ifndef __HEXVIEW_H__
#define __HEXVIEW_H__

#include "FileIO.h"

// 数据缓冲区大小
#define DATA_BUFFER_SIZE     (16 * 1024) 

// Hex字符缓冲区大小
#define HEX_BUFFER_SIZE      (DATA_BUFFER_SIZE * 2)

// 数据缓冲区边界大小(避免频繁刷新)
#define DATA_BUF_SIDE_SIZE   (512)

// 信息查看类型
#define VIEWTYPE_MASK_UINT8     0x1L
#define VIEWTYPE_MASK_INT8      0x2L
#define VIEWTYPE_MASK_UINT16    0x4L
#define VIEWTYPE_MASK_INT16     0x8L
#define VIEWTYPE_MASK_UINT32    0x10L
#define VIEWTYPE_MASK_INT32     0x20L
#define VIEWTYPE_MASK_UCS2BE    0x40L
#define VIEWTYPE_MASK_UCS2LE    0x80L
#define VIEWTYPE_MASK_GB2312    0x100L
#define VIEWTYPE_MASK_UTF8      0x200L

// 光标移动类型
enum
{
    OFFSET_SEEK_LINE_UP,
    OFFSET_SEEK_LINE_DOWN,
    OFFSET_SEEK_BYTE_LAST,
    OFFSET_SEEK_BYTE_NEXT,
    OFFSET_SEEK_PAGE_UP,
    OFFSET_SEEK_PAGE_DOWN,
    OFFSET_SEEK_BEGIN,
    OFFSET_SEEK_END,

    OFFSET_SEEK_MAX
};

// 坐标结构体
typedef struct 
{
    int16 X;  // X坐标
    int16 Y;  // Y坐标
} POINT_ST;

// Hex显示数据结构体
typedef struct
{
    char FileNameA[MAX_FILENAME_LEN_A];  // 文件名-gb2312
    char FileNameW[MAX_FILENAME_LEN_W];  // 文件名-unicode
    char FilePath[MAX_PATH_LEN_A];       // 文件路径

    uint8 *DataBuffer; // 文件数据
    uint8 *HexBuffer;  // Hex数据

    int32 FileSize;       // 文件总大小
    int32 FileReadBegin;  // 读取文件偏移
    int32 DataBufUsed;    // 缓冲区已用大小
    int32 DataShowBegin;  // 开始显示偏移
    int32 DataBufOffset;  // 光标处偏移
    POINT_ST CurPos;      // 当前光标位置
} HEX_VIEW_ST, *PHEX_VIEW_ST;

extern const uint8 ArrInt2Hex[17];
extern const uint8 ArrChar2Int[256];

int32 HV_Init(void);
int32 HV_End(void);
int32 HV_Draw(uint8 refresh);
int32 HV_Event(int32 type, int32 p1, int32 p2);

// 各种绘制
void HV_DrawTitle(uint8 refresh);
void HE_DrawToolBar(uint8 state, uint8 refresh);
void HV_DrawHexAll(uint8 ShowFocus, uint8 refresh);
void HV_DrawFocus(POINT_ST dPos, uint8 FocusType, uint8 refresh);
void HV_DrawInfo(uint8 refresh);
void HV_DrawPageButton(uint8 index, uint8 state, uint8 refresh);

// 显示信息
int32 HV_ShowMsgA(char *sText, uint8 refresh);

// 切换显示窗口
// 参数：序号(0或1，-1表示当前窗口另一个)
int32 HV_SwitchWindow(int32 index);

// 打开文件
// 参数：路径，文件名
int32 HV_OpenFile(const char *dir, const char *name);

// 关闭文件
int32 HV_CloseFile(void);

// 返回当前窗口是否打开文件
int32 HV_IsFileOpen(void);

// 取得当前文件大小
int32 HV_GetFileSize(void);

// 返回开始显示位置的文件偏移
int32 HV_GetFileShowOffset(void);

// 取得当前文件偏移
int32 HV_GetFileOffset(void);

// 取得当前数据缓冲区偏移
int32 HV_GetDataOffset(void);

// 转到文件地址
// 参数：位置
int32 HV_GotoFileOffset(int32 fPos);

// 移动光标到下个Hex字符
void HV_GotoNextHex(void);

// 改变当前数据偏移
// 参数：改变方式
void HV_ChangeDataOffset(int32 type);

// 格式化数据为Hex字符串
// 参数：原始数据，数据大小，Hex缓冲区，缓冲区大小
int32 Data2Hex(uint8 *data, int32 dataSize, uint8 *hexBuf, int32 bufSize);

// Hex字符串转换为数据
// 参数：Hex缓冲区，缓冲区大小，数据缓冲区，缓冲区大小
int32 Hex2Data(uint8 *hex, int32 hexSize, uint8 *dataBuf, int32 bufSize);

int32 StartShowTime(void);
int32 StopShowTime(void);

#endif // __HEXVIEW_H__
