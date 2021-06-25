/*
 * Hex编辑
 * 版权所有 (C) 2011-2012 eleqian
 * [7/21/2012]
 */

#include "mrc_base.h"
#include "src/base.h"

#include "HexEdit.h"
#include "HexView.h"
#include "AppMain.h"
#include "KeyTimer.h"
#include "DrawLib.h"
#include "Functions.h"
#include "LocalUI.h"
#include "src/android.h"

// Hex编辑动作枚举
enum
{
    HE_ACTION_NONE,
    HE_ACTION_FIND,
    HE_ACTION_WRITE,
    HE_ACTION_COMPARE,

    HE_ACTION_MAX
};

static rectst rectTool;     // 工具栏
static rectst rectVCmdAll;  // 按键区域
static rectst rectVCmd[16];  // 屏幕虚拟按键

static uint8 VCmdClass;     // 屏幕虚拟按键序号
static uint16 ButtonWidth;  // 按钮宽度(工具栏)

static char LastInput[MAX_INPUT_BUF_SIZE];     // 上次输入
static uint8 ToFindData[512];   // 查找内容
static uint8 ToWriteData[512];  // 替换内容
static int32 ToFindSize;        // 替换大小
static int32 ToWriteSize;       // 替换大小
static uint8 CompareMode;       // 比较模式
static uint8 LastAction;        // 上次动作

static void DrawVButton(uint8 cIndex, uint8 pIndex, uint8 Refresh);

// 初始化虚拟按钮大小和位置
int32 HE_Init( void )
{
    int16 i;
    int32 fw, fh;
    uint16 cmdHeight, cmdWidth;
    int16 scnWidth, scnHeight;

    GetScreenSize16(&scnWidth, &scnHeight);
    GetTextSizeW("\x65\x87\x67\x2c\x0\x0", &fw, &fh); //"文本"
    ButtonWidth = (uint16)fw + 8;

    rectTool.x = 0;
    rectTool.w = scnWidth;
    rectTool.h = (uint16)fh + 4;
    rectTool.y = scnHeight - rectTool.h;
    rectVCmdAll.x = 0;
    rectVCmdAll.w = scnWidth;
    rectVCmdAll.h = (uint16)(fh + 1) * AppDatas.InfoCount + 3; 
    rectVCmdAll.y = scnHeight - rectTool.h - rectVCmdAll.h - 1;

    cmdWidth = (rectVCmdAll.w ) / 8;
    cmdHeight = (rectVCmdAll.h - 2) / 2;

    for (i = 0; i < 16; i++)
    {
		if(i<8)
		{
		rectVCmd[i].x = cmdWidth*i;
    rectVCmd[i].y = rectVCmdAll.y + 1;
        }
		else
	    {
		rectVCmd[i].x = cmdWidth*(i-8);
    rectVCmd[i].y = rectVCmdAll.y + cmdHeight+2;
     
		}
        rectVCmd[i].w = cmdWidth;
        rectVCmd[i].h = cmdHeight;
    }

    /*
    rectVCmd[1].x = cmdWidth*i;
    rectVCmd[1].y = rectVCmdAll.y + rectVCmdAll.h - cmdHeight - 1;
	

    rectVCmd[2].x = r;
    rectVCmd[2].y = rectVCmdAll.y + (rectVCmdAll.h - cmdHeight) / 2;

    rectVCmd[3].x = rectVCmdAll.x + rectVCmdAll.w - cmdWidth - 1;
    rectVCmd[3].y = rectVCmdAll.y + (rectVCmdAll.h - cmdHeight) / 2;
*/
    return 0;
}

// 虚拟按键结束
int32 HE_End(void)
{
    return 0;
}

// 重绘
int32 HE_Draw(uint8 refresh)
{
    HV_DrawTitle(refresh);
    HV_DrawHexAll(1, refresh);
    HV_DrawInfo(refresh);
    HV_DrawPageButton(3, 0, refresh);
    HE_DrawToolBar(0, refresh);
    DrawVButton(VCmdClass, -1, refresh);

    return 0;
}

// 绘制虚拟按键
// 参数：组：0 - 全部，1 - 0-3， 2 - 4-7， 3 - 8-B，4 - C-F
//       按键按下序号：0 - 3
static void DrawVButton(uint8 cIndex, uint8 pIndex, uint8 refresh)
{
    char *cText[16];

    switch(cIndex)
    {
    case 1:
        cText[0] = "\x0\x30\x0\x0";
        cText[1] = "\x0\x31\x0\x0";
        cText[2] = "\x0\x32\x0\x0";
        cText[3] = "\x0\x33\x0\x0";
		cText[4] = "\x0\x34\x0\x0";
		cText[5] = "\x0\x35\x0\x0";
		cText[6] = "\x0\x36\x0\x0";
		cText[7] = "\x0\x37\x0\x0";
		cText[8] = "\x0\x38\x0\x0";
		cText[9] = "\x0\x39\x0\x0";
		cText[10] = "\x0\x41\x0\x0";
		cText[11] = "\x0\x42\x0\x0";
		cText[12] = "\x0\x43\x0\x0";
		cText[13] = "\x0\x44\x0\x0";
		cText[14] = "\x0\x45\x0\x0";
		cText[15] = "\x0\x46\x0\x0";
        break;
    case 2:
        cText[0] = "\x0\x30\x0\x0";
        cText[1] = "\x0\x31\x0\x0";
        cText[2] = "\x0\x32\x0\x0";
        cText[3] = "\x0\x33\x0\x0";
		cText[4] = "\x0\x34\x0\x0";
		cText[5] = "\x0\x35\x0\x0";
		cText[6] = "\x0\x36\x0\x0";
		cText[7] = "\x0\x37\x0\x0";
		cText[8] = "\x0\x38\x0\x0";
		cText[9] = "\x0\x39\x0\x0";
		cText[10] = "\x0\x41\x0\x0";
		cText[11] = "\x0\x42\x0\x0";
		cText[12] = "\x0\x43\x0\x0";
		cText[13] = "\x0\x44\x0\x0";
		cText[14] = "\x0\x45\x0\x0";
		cText[15] = "\x0\x46\x0\x0";
   
        break;
    case 3:
        cText[0] = "\x0\x30\x0\x0";
        cText[1] = "\x0\x31\x0\x0";
        cText[2] = "\x0\x32\x0\x0";
        cText[3] = "\x0\x33\x0\x0";
		cText[4] = "\x0\x34\x0\x0";
		cText[5] = "\x0\x35\x0\x0";
		cText[6] = "\x0\x36\x0\x0";
		cText[7] = "\x0\x37\x0\x0";
		cText[8] = "\x0\x38\x0\x0";
		cText[9] = "\x0\x39\x0\x0";
		cText[10] = "\x0\x41\x0\x0";
		cText[11] = "\x0\x42\x0\x0";
		cText[12] = "\x0\x43\x0\x0";
		cText[13] = "\x0\x44\x0\x0";
		cText[14] = "\x0\x45\x0\x0";
		cText[15] = "\x0\x46\x0\x0";
   
        break;
    case 4:
        cText[0] = "\x0\x30\x0\x0";
        cText[1] = "\x0\x31\x0\x0";
        cText[2] = "\x0\x32\x0\x0";
        cText[3] = "\x0\x33\x0\x0";
		cText[4] = "\x0\x34\x0\x0";
		cText[5] = "\x0\x35\x0\x0";
		cText[6] = "\x0\x36\x0\x0";
		cText[7] = "\x0\x37\x0\x0";
		cText[8] = "\x0\x38\x0\x0";
		cText[9] = "\x0\x39\x0\x0";
		cText[10] = "\x0\x41\x0\x0";
		cText[11] = "\x0\x42\x0\x0";
		cText[12] = "\x0\x43\x0\x0";
		cText[13] = "\x0\x44\x0\x0";
		cText[14] = "\x0\x45\x0\x0";
		cText[15] = "\x0\x46\x0\x0";
   
        break;
    default:
        cText[0] = "\x0\x30\x0\x0";
        cText[1] = "\x0\x31\x0\x0";
        cText[2] = "\x0\x32\x0\x0";
        cText[3] = "\x0\x33\x0\x0";
		cText[4] = "\x0\x34\x0\x0";
		cText[5] = "\x0\x35\x0\x0";
		cText[6] = "\x0\x36\x0\x0";
		cText[7] = "\x0\x37\x0\x0";
		cText[8] = "\x0\x38\x0\x0";
		cText[9] = "\x0\x39\x0\x0";
		cText[10] = "\x0\x41\x0\x0";
		cText[11] = "\x0\x42\x0\x0";
		cText[12] = "\x0\x43\x0\x0";
		cText[13] = "\x0\x44\x0\x0";
		cText[14] = "\x0\x45\x0\x0";
		cText[15] = "\x0\x46\x0\x0";
   
        break;
    }

    ClearRect(rectVCmdAll);
	int i;
 for(i=0;i<16;i++)
 {
	    DrawButtonW(rectVCmd[i], cText[i],1, (i == pIndex) ? 1:0); 
 }
 //   DrawButtonW(rectVCmd[0], cText[0], 1, (0 == pIndex) ? 1 : 0);
 //   DrawButtonW(rectVCmd[1], cText[1], 1, (1 == pIndex) ? 1 : 0);
 //   DrawButtonW(rectVCmd[2], cText[2], 1, (2 == pIndex) ? 1 : 0);
  //  DrawButtonW(rectVCmd[3], cText[3], 1, (3 == pIndex) ? 1 : 0);

    DrawRoundBorder(rectVCmdAll);

    if (refresh)
        RefreshRect(rectVCmdAll);
}

/*---------------------------------------------------------------------------*/

// 保存修改数据
// 参数：新数据
int32 HE_SaveValue(uint8 NewValue)
{
    uint8 NewData;

    if ((AppDatas.HDataCur->FileSize <= 0 
        || AppDatas.HDataCur->DataBufOffset < 0) 
        || (AppDatas.HDataCur->DataBufOffset > AppDatas.HDataCur->DataBufUsed)
        || (AppDatas.HDataCur->DataBufUsed <= 0))
        return 0;

    NewData = AppDatas.HDataCur->DataBuffer[AppDatas.HDataCur->DataBufOffset];

    if (0 == AppDatas.HDataCur->CurPos.X % 2)
    {
        NewData = (NewValue << 4) | (NewData & 0x0f);
        //Data2Hex(&NewValue, 1, &AppDatas.HDataCur->HexBuffer[AppDatas.HDataCur->DataBufOffset * 2], 1);
        AppDatas.HDataCur->HexBuffer[AppDatas.HDataCur->DataBufOffset * 2] = ArrInt2Hex[NewValue];
    }
    else
    {
        NewData = (NewData & 0xf0) | NewValue;
        //Data2Hex(&NewValue, 1, &AppDatas.HDataCur->HexBuffer[AppDatas.HDataCur->DataBufOffset * 2 + 1], 1);
        AppDatas.HDataCur->HexBuffer[AppDatas.HDataCur->DataBufOffset * 2 + 1] = ArrInt2Hex[NewValue];
    }

    AppDatas.HDataCur->DataBuffer[AppDatas.HDataCur->DataBufOffset] = NewData;
    SaveFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA, 
        AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset, &NewData, 1);

    if (1 == AppDatas.HDataCur->CurPos.X % 2)
    {
        HV_GotoFileOffset(AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset + 1);
    }
    else
    {
        HV_DrawFocus(AppDatas.HDataCur->CurPos, 2, 1);
        AppDatas.HDataCur->CurPos.X++;
    }

    return 0;
}

// 保存数据
int32 HE_SaveData(uint8 *DataBuf, int32 bufSize)
{
    if (AppDatas.HDataCur->DataBufOffset < 0 
        || AppDatas.HDataCur->DataBufOffset > AppDatas.HDataCur->DataBufUsed 
        || 0 == AppDatas.HDataCur->DataBufUsed)
        return 0;

    SaveFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA, 
        AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset, DataBuf, bufSize);
    AppDatas.HDataCur->DataBufUsed = ReadFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA,
        AppDatas.HDataCur->FileReadBegin, AppDatas.HDataCur->DataBuffer, DATA_BUFFER_SIZE);
    Data2Hex(AppDatas.HDataCur->DataBuffer, AppDatas.HDataCur->DataBufUsed, AppDatas.HDataCur->HexBuffer, HEX_BUFFER_SIZE);
    AppDatas.HDataCur->FileSize = FileLenInPath(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA);

    return 0;
}

// 数值按字节序保存进数组并返回字节数
static int32 NumToBytes(uint32 num, uint8 *bytes)
{
    int32 size = 0;

    if (0 == AppDatas.BigEndian)
    {
        // 小端字节序
        if (num & 0xffff0000)
        {
            // 4个字节
            bytes[0] = (uint8)(num & 0xff);
            bytes[1] = (uint8)((num >> 8) & 0xff);
            bytes[2] = (uint8)((num >> 16) & 0xff);
            bytes[3] = (uint8)((num >> 24) & 0xff);
            size = 4;
        }
        else if (num & 0xff00)
        {
            // 2个字节
            bytes[0] = (uint8)(num & 0xff);
            bytes[1] = (uint8)((num >> 8) & 0xff);
            size = 2;
        }
        else
        {
            // 1个字节
            *bytes = (uint8)num;
            size = 1;
        }
    } 
    else
    {
        // 大端字节序
        if (num & 0xffff0000)
        {
            // 4个字节
            bytes[0] = (uint8)((num >> 24) & 0xff);
            bytes[1] = (uint8)((num >> 16) & 0xff);
            bytes[2] = (uint8)((num >> 8) & 0xff);
            bytes[3] = (uint8)(num & 0xff);
            size = 4;
        }
        else if (num & 0xff00)
        {
            // 2个字节
            bytes[0] = (uint8)((num >> 8) & 0xff);
            bytes[1] = (uint8)(num & 0xff);
            size = 2;
        }
        else
        {
            // 1个字节
            bytes[0] = (uint8)num;
            size = 1;
        }
    }

    return size;
}

// 查找输入数据
int32 HE_FindInput(int32 type, const char *inStr)
{
    int32 slen;
    int32 findPos;
LOGI("FindInput 1");
    if (HE_INPUT_DATA_TYPE_LAST != type)
    {
        if (NULL == inStr)
            return -1;
        slen = wstrlen(inStr);
        if (slen <= 0)
            return -1;

        memcpy(LastInput, inStr, slen + 2);

        switch (type)
        {
        case HE_INPUT_DATA_TYPE_HEX:
            {
                int32 sLenA = slen / 2;
                char *sHexA;

                sHexA = (char*)malloc(sLenA + 1);
                Uni2Asc(inStr, sHexA, sLenA + 1);
                ToFindSize = Hex2Data((uint8*)sHexA, sLenA, ToFindData, sizeof(ToFindData));
                TRYFREE(sHexA);
            }
            break;
        case HE_INPUT_DATA_TYPE_NUM:
            {
                ToFindSize = NumToBytes((uint32)watoi(inStr), ToFindData);
            }
            break;
        case HE_INPUT_DATA_TYPE_UCS2BE:
            {
                memcpy(ToFindData, inStr, slen + 2);
                ToFindSize = slen;
            }
            break;
        case HE_INPUT_DATA_TYPE_UCS2LE:
            {
                memcpy(ToFindData, inStr, slen + 2);
                SwapBytes(ToFindData, sizeof(ToFindData));
                ToFindSize = slen;
            }
            break;
        case HE_INPUT_DATA_TYPE_GB2312:
            {
                ToFindSize = UniToGB(inStr, (char*)ToFindData, sizeof(ToFindData));
            }
            break;
        case HE_INPUT_DATA_TYPE_UTF8:
            {
                ToFindSize = UniToUTF8(inStr, (char*)ToFindData, sizeof(ToFindData));
            }
            break;
        default:
            ToFindSize = -1;
            break;
        }
    }
    LOGI("FindInput 1");
    if (ToFindSize <= 0)
    {
         HV_ShowMsgA("\xc7\xeb\xcf\xc8\xca\xe4\xc8\xeb\xb2\xe9\xd5\xd2\xc4\xda\xc8\xdd\xa3\xa1", 1);
   	//   HV_ShowMsgA("请先输入查找内容！", 1);
        return -1;
    }
    LOGI("FindInput 1");
    LastAction = HE_ACTION_FIND;
    HV_ShowMsgA("\xd5\xfd\xd4\xda\xb2\xe9\xd5\xd2\xa3\xac\xc7\xeb\xb5\xc8\xb4\xfd\xa1\xad\xa1\xad", 1);
   // HV_ShowMsgA("正在查找，请等待……", 1);
    findPos = FindFromFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA,
        HV_GetFileOffset() + 1, ToFindData, ToFindSize);
    LOGI("FindInput 1");
    if (findPos > 0)
    {
        HV_GotoFileOffset(findPos);
        HV_ShowMsgA(NULL, 1);
    }
    else
    {
		        HV_ShowMsgA("\xb2\xe9\xd5\xd2\xca\xfd\xbe\xdd\xce\xb4\xd5\xd2\xb5\xbd\xa3\xa1", 1);
      //  HV_ShowMsgA("查找数据未找到！", 1);
    }
    LOGI("FindInput 1");
    return 0;
}

// 查找数据
int32 HE_FindData(int32 type, void *data, int32 len)
{
    if (HE_INPUT_DATA_TYPE_DATA == type)
    {
        memcpy(ToFindData, data, len);
        ToFindSize = len;
        return HE_FindInput(HE_INPUT_DATA_TYPE_LAST, NULL);
    }
    else
    {
        return HE_FindInput(type, data);
    }
}

// 写入输入数据
int32 HE_WriteInput(int32 type, const char *inStr)
{
    int32 slen;

    if (HE_INPUT_DATA_TYPE_LAST != type)
    {
        if (NULL == inStr)
            return -1;
        slen = wstrlen(inStr);
        if (slen <= 0)
            return -1;

        memcpy(LastInput, inStr, slen + 2);

        switch (type)
        {
        case HE_INPUT_DATA_TYPE_HEX:
            {
                int32 sLenA = slen / 2;
                char *sHexA;

                sHexA = (char*)malloc(sLenA + 1);
                Uni2Asc(inStr, sHexA, sLenA + 1);
                ToWriteSize = Hex2Data((uint8*)sHexA, sLenA, ToWriteData, sizeof(ToWriteData));
                TRYFREE(sHexA);
            }
            break;
        case HE_INPUT_DATA_TYPE_NUM:
            {
                ToWriteSize = NumToBytes((uint32)watoi(inStr), ToWriteData);
            }
            break;
        case HE_INPUT_DATA_TYPE_UCS2BE:
            {
                memcpy(ToWriteData, inStr, slen + 2);
                ToWriteSize = slen;
            }
            break;
        case HE_INPUT_DATA_TYPE_UCS2LE:
            {
                memcpy(ToWriteData, inStr, slen + 2);
                SwapBytes(ToWriteData, sizeof(ToWriteData));
                ToWriteSize = slen;
            }
            break;
        case HE_INPUT_DATA_TYPE_GB2312:
            {
                ToWriteSize = UniToGB(inStr, (char*)ToWriteData, sizeof(ToWriteData));
            }
            break;
        case HE_INPUT_DATA_TYPE_UTF8:
            {
                ToWriteSize = UniToUTF8(inStr, (char*)ToWriteData, sizeof(ToWriteData));
            }
            break;
        default:
            ToWriteSize = -1;
            return -1;
            break;
        }
    }

    if (ToWriteSize <= 0)
    {
	  HV_ShowMsgA("\xc7\xeb\xcf\xc8\xca\xe4\xc8\xeb\xd0\xb4\xc8\xeb\xc4\xda\xc8\xdd\xa3\xa1", 1);
       // HV_ShowMsgA("请先输入写入内容！", 1);
        return -1;
    }

    LastAction = HE_ACTION_WRITE;

    HE_SaveData(ToWriteData, ToWriteSize);
  HV_ShowMsgA("\xd0\xb4\xc8\xeb\xcd\xea\xb3\xc9\xa3\xa1", 1);
   // HV_ShowMsgA("写入完成！", 1);

    return 0;
}

// 写入数据
int32 HE_WriteData(int32 type, void *data, int32 len)
{
    if (HE_INPUT_DATA_TYPE_DATA == type)
    {
        memcpy(ToWriteData, data, len);
        ToWriteSize = len;
        return HE_WriteInput(HE_INPUT_DATA_TYPE_LAST, NULL);
    }
    else
    {
        return HE_WriteInput(type, data);
    }
}

// 比较文件数据
int32 HE_Compare(void)
{
    int32 cmpPos;
    PHEX_VIEW_ST data1, data2;

    data1 = &AppDatas.HDatas[AppDatas.HIndex];
    data2 = &AppDatas.HDatas[1 - AppDatas.HIndex];

    if (data2->FileSize <= 0)
    {
	  HV_ShowMsgA("\xc7\xeb\xcf\xc8\xd4\xda\xc1\xed\xd2\xbb\xb4\xb0\xbf\xda\xb4\xf2\xbf\xaa\xce\xc4\xbc\xfe\xa3\xa1(\xd7\xf7\xce\xaa\xb2\xce\xbf\xbc\xce\xc4\xbc\xfe)", 1);
     //   HV_ShowMsgA("请先在另一窗口打开文件！(作为参考文件)", 1);
        return -1;
    }

    LastAction = HE_ACTION_COMPARE;
    HV_ShowMsgA("\xd5\xfd\xd4\xda\xb1\xc8\xbd\xcf\xa3\xac\xc7\xeb\xb5\xc8\xb4\xfd\xa1\xad\xa1\xad", 1);
 //   HV_ShowMsgA("正在比较，请等待……", 1);
    cmpPos = CompareFile(data2->FilePath, data1->FilePath, 
        data2->FileNameA, data1->FileNameA, HV_GetFileOffset() + 1, CompareMode);

    if (cmpPos >= 0)
    {
        HV_GotoFileOffset(cmpPos);
        HV_ShowMsgA(NULL, 1);
    }
    else
    {
        HV_ShowMsgA("\xce\xb4\xd5\xd2\xb5\xbd\xb7\xfb\xba\xcf\xcc\xf5\xbc\xfe\xb5\xc4\xca\xfd\xbe\xdd\xa3\xa1", 1);
    //    HV_ShowMsgA("未找到符合条件的数据！", 1);
    }

    return 0;
}

// 重复上次操作
int32 HE_RedoAction(void)
{
    if (HV_IsFileOpen())
    {
        switch (LastAction)
        {
        case HE_ACTION_FIND:
            HE_FindInput(HE_INPUT_DATA_TYPE_LAST, NULL);
            break;
        case HE_ACTION_WRITE:
            HE_WriteInput(HE_INPUT_DATA_TYPE_LAST, NULL);
            break;
        case HE_ACTION_COMPARE:
            HE_Compare();
            break;
        default:
            return -1;
            break;
        }

        return 0;
    }

    return -1;
}

// 设置比较模式
int32 HE_SetCompareMode(int32 mode)
{
    if (mode == 1)
    {
        CompareMode = 1;
    }
    else
    {
        CompareMode = 0;
    }

    return 0;
}

// 返回上次输入内容
char *HE_GetLastInput(void)
{
    return LastInput;
}

// 插入数据
int32 HE_InsertData(uint8 *data, int32 size)
{
    int32 fd;
    int32 fOffset, fSize;

    fOffset = AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset;
    fSize = AppDatas.HDataCur->FileSize;

    // 打开文件
    fd = OpenInPath(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA, MR_FILE_RDWR);

    // 移动后半部分数据
    MoveFileData(fd, fOffset, size, fSize - fOffset + 1);

    // 写入内容
    app_seek(fd, fOffset, SEEK_SET);
    if (NULL == data)
    {
        WriteZeroToFile(fd, size);
    }
    else
    {
        app_write(fd, data, size);
    }

    // 关闭文件
    app_close(fd);

    // 重新打开文件
    HV_OpenFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA);
    HV_GotoFileOffset(fOffset);

    return 0;
}

// 删除数据
int32 HE_DeleteData(int32 size)
{
    int32 fOffset, fSize;
    char *tempFile = GetTempFileName();

    fOffset = AppDatas.HDataCur->FileReadBegin + AppDatas.HDataCur->DataBufOffset;
    fSize = AppDatas.HDataCur->FileSize;

    Switch2Dir(AppDatas.HDataCur->FilePath);

    // 复制前半部分数据到临时文件
    CopyFileEx(AppDatas.HDataCur->FileNameA, tempFile, 0, 0, fOffset);

    // 复制后半部分数据到临时文件
    CopyFileEx(AppDatas.HDataCur->FileNameA, tempFile, fOffset + size, fOffset, fSize - fOffset - size);

    // 替换原文件
    mrc_remove(AppDatas.HDataCur->FileNameA);
    mrc_rename(tempFile, AppDatas.HDataCur->FileNameA);

    Switch2Dir(NULL);

    TRYFREE(tempFile);

    // 重新打开文件
    HV_OpenFile(AppDatas.HDataCur->FilePath, AppDatas.HDataCur->FileNameA);
    HV_GotoFileOffset(fOffset);

    return 0;
}

/*---------------------------------------------------------------------------*/

// 方向键输入回调
static void myInputKeyCb(int32 data)
{
    HE_SaveValue((VCmdClass - 1) * 4 + (uint8)data - 1);
}

// 数字键直接输入值回调
static void myInputValueCb(int32 data)
{
    HE_SaveValue((uint8)data);
}

// Hex编辑状态按键UP
static int32 HE_DoKeyUp(int32 KeyCode)
{
    KeyTimerStop();

	switch(KeyCode)
	{
    case MR_KEY_UP:
        VCmdClass = (VCmdClass == 0 ? 1 : 0);
        DrawVButton(VCmdClass, -1, 1);
        break;
    case MR_KEY_DOWN:
        VCmdClass = (VCmdClass == 0 ? 2 : 0);
        DrawVButton(VCmdClass, -1, 1);
        break;
    case MR_KEY_LEFT:
        VCmdClass = (VCmdClass == 0 ? 3 : 0);
        DrawVButton(VCmdClass, -1, 1);
        break;
    case MR_KEY_RIGHT:
        VCmdClass = (VCmdClass == 0 ? 4 : 0);
        DrawVButton(VCmdClass, -1, 1);
        break;
    case MR_KEY_SELECT:
    case MR_KEY_SOFTLEFT:
        HV_GotoNextHex();
        break;
    case MR_KEY_SOFTRIGHT:
        if (0 == VCmdClass)
        {
            SetAppState(APPSTATE_RETURN, 1);
        }
        else
        {
            VCmdClass = 0;
            HE_DrawToolBar(0, 1);
            DrawVButton(0, 4, 1);
        }
        break;
    default:
	DrawVButton(VCmdClass, -1, 1);
        return MR_IGNORE;
    }

    return MR_SUCCESS;
}

// Hex编辑状态按键DOWN
static int32 HE_DoKeyDown(int32 KeyCode)
{
	switch(KeyCode)
	{
		/*
    case MR_KEY_UP:
        DrawVButton(VCmdClass, 0, 1);
        if (VCmdClass != 0)
            KeyTimerStart(1, myInputKeyCb);
        break;
    case MR_KEY_DOWN:
        DrawVButton(VCmdClass, 1, 1);
        if (VCmdClass != 0)
            KeyTimerStart(2, myInputKeyCb);
        break;
    case MR_KEY_LEFT:
        DrawVButton(VCmdClass, 2, 1);
        if (VCmdClass != 0)
            KeyTimerStart(3, myInputKeyCb);
        break;
    case MR_KEY_RIGHT:
        DrawVButton(VCmdClass, 3, 1);
        if (VCmdClass != 0)
            KeyTimerStart(4, myInputKeyCb);
        break;
		*/
    case MR_KEY_0:
    case MR_KEY_1:
    case MR_KEY_2:
    case MR_KEY_3:
    case MR_KEY_4:
    case MR_KEY_5:
    case MR_KEY_6:
    case MR_KEY_7:
    case MR_KEY_8:
    case MR_KEY_9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			DrawVButton(VCmdClass, KeyCode, 1);
        KeyTimerStart(KeyCode, myInputValueCb);
        break;
    case MR_KEY_SELECT:
    case MR_KEY_SOFTLEFT:
        HE_DrawToolBar(1, 1);
        break;
    case MR_KEY_SOFTRIGHT:
        HE_DrawToolBar(2, 1);
        break;
    default:
        return MR_IGNORE;
    }

    return MR_SUCCESS;
}

// 触屏操作
static int32 HE_DoMouse(int32 X, int32 Y, uint8 IsMouseDown)
{
    if (X >= rectVCmdAll.x && X < rectVCmdAll.x + rectVCmdAll.w && Y>= rectVCmdAll.y && Y <= rectVCmdAll.y + rectVCmdAll.h)
    {
        uint8 i;
        int32 key;

        for(i = 0; i < 16; i++)
        {
            if (X >= rectVCmd[i].x && X < rectVCmd[i].x + rectVCmd[i].w && Y>= rectVCmd[i].y && Y <= rectVCmd[i].y + rectVCmd[i].h)
            {
                key = i;
                return HE_Event(IsMouseDown ? MR_KEY_PRESS : MR_KEY_RELEASE, key, 0);
                break;
            }
        }
    }
    else if (Y >= rectTool.y && Y < rectTool.y + rectTool.h)
    {
        if (X < ButtonWidth)
        {
            return HE_Event(IsMouseDown ? MR_KEY_PRESS : MR_KEY_RELEASE, MR_KEY_SOFTLEFT, 0);
        }
        else if (X >= rectTool.w - ButtonWidth)
        {
            return HE_Event(IsMouseDown ? MR_KEY_PRESS : MR_KEY_RELEASE, MR_KEY_SOFTRIGHT, 0);
        }
    }
    else
    {
        if (0 == IsMouseDown)
        {
            return HE_DoKeyUp(MR_KEY_SOFTRIGHT);
        }
        else
        {
            return HE_DoKeyDown(MR_KEY_SOFTRIGHT);
        }
    }

    return MR_IGNORE;
}

// 虚拟按钮事件
int32 HE_Event(int32 code, int32 p1, int32 p2)
{
    int32 ret;

    switch (code)
    {
    case MR_KEY_PRESS:
        ret = HE_DoKeyDown(p1);
        break;
    case MR_KEY_RELEASE:
        ret = HE_DoKeyUp(p1);
        break;
    case MR_MOUSE_DOWN:
        ret = HE_DoMouse(p1, p2, 1);
        break;
    case MR_MOUSE_UP:
        ret = HE_DoMouse(p1, p2, 0);
        break;
    case MR_MOUSE_MOVE:
        ret = MR_SUCCESS;
        break;
    default:
        ret = MR_IGNORE;
        break;
    }

    return ret;
}
