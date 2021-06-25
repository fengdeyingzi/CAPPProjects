/*
 * 文件目录表解析 v1.02
 * 版权所有 (C) 2012 eleqian
 * [4/11/2012]
 */

// 直接读取文件目录表的优势与缺点
// 优势：能获取文件时间、属性等更多信息；能优化文件遍历速度；支持Unicode字符
// 缺点：不适用于所有机型，貌似在MTK有效，展讯无效；不支持写入

#include <mrc_base.h>

#include "FDT.h"
#include "Functions.h"

// 全局变量区域
static uint8 LongNameBuffer[MAX_LONG_NAME_SIZE]; //长文件名的缓存区
static int32 LongNameFlag = 0; //是否存在长文件名的标志
static uint8 *FDTData = NULL; // FAT数据
static uint32 FDTSize = 0;     // FAT大小

// 转换记录项信息
static void ConvDirentruyItem(FileInfoStruct *Desti, direntry *Source)
{
    int32 i, j, t;
    uint16 u16data;

    // 复制文件大小和属性
    Desti->F_Size = READ_UINT32_LE(Source->deFileSize);
    Desti->F_Attr = Source->deAttributes;

    // 转换文件创建日期时间
    u16data = READ_UINT16_LE(Source->deCTime);
    Desti->F_TCreate.second = (uint8)((u16data & DT_2SECONDS_MASK) >> DT_2SECONDS_SHIFT) * 2 + Source->deCHundredth / 100;
    Desti->F_TCreate.minute = (uint8)((u16data & DT_MINUTES_MASK) >> DT_MINUTES_SHIFT);
    Desti->F_TCreate.hour = (uint8)((u16data & DT_HOURS_MASK) >> DT_HOURS_SHIFT);
    u16data = READ_UINT16_LE(Source->deCDate);
    Desti->F_TCreate.day = (uint8)((u16data & DD_DAY_MASK) >> DD_DAY_SHIFT);
    Desti->F_TCreate.month = (uint8)((u16data & DD_MONTH_MASK) >> DD_MONTH_SHIFT);
    Desti->F_TCreate.year = (uint16)((u16data & DD_YEAR_MASK) >> DD_YEAR_SHIFT) + 1980;

    // 转换文件修改日期时间
    u16data = READ_UINT16_LE(Source->deMTime);
    Desti->F_TModify.second = (uint8)((u16data & DT_2SECONDS_MASK) >> DT_2SECONDS_SHIFT) * 2;
    Desti->F_TModify.minute = (uint8)((u16data & DT_MINUTES_MASK) >> DT_MINUTES_SHIFT);
    Desti->F_TModify.hour = (uint8)((u16data & DT_HOURS_MASK) >> DT_HOURS_SHIFT);
    u16data = READ_UINT16_LE(Source->deMDate);
    Desti->F_TModify.day = (uint8)((u16data & DD_DAY_MASK) >> DD_DAY_SHIFT);
    Desti->F_TModify.month = (uint8)((u16data & DD_MONTH_MASK) >> DD_MONTH_SHIFT);
    Desti->F_TModify.year = (uint16)((u16data & DD_YEAR_MASK) >> DD_YEAR_SHIFT) + 1980;

    // 转换文件访问日期(不存在时间)
    Desti->F_TAccess.second = 0;
    Desti->F_TAccess.minute = 0;
    Desti->F_TAccess.hour = 0;
    u16data = READ_UINT16_LE(Source->deADate);
    Desti->F_TAccess.day = (uint8)((u16data & DD_DAY_MASK) >> DD_DAY_SHIFT);
    Desti->F_TAccess.month = (uint8)((u16data & DD_MONTH_MASK) >> DD_MONTH_SHIFT);
    Desti->F_TAccess.year = (uint16)((u16data & DD_YEAR_MASK) >> DD_YEAR_SHIFT) + 1980;

    // 复制文件名

    // 从短文件名末尾开始找空格
    for (t = 7; t > 0; t--)
    {
        if (Source->deName[t] != '\x20')
            break;
    }

    // 复制短文件名
    for (i = 0; i <= t; i++)
    {
        if ((Source->deLowerCase & LCASE_BASE) && (Source->deName[i] >= 'A' && Source->deName[i] <= 'Z'))
            Desti->F_ShortName[i] = Source->deName[i] + 0x20;  // 转换为小写
        else
            Desti->F_ShortName[i] = Source->deName[i];
    }

    // 存在扩展名，复制
    if (Source->deExtension[0] != '\x20')
    {
        Desti->F_ShortName[i++] = '.'; // 加入"."

        // 从扩展名末尾开始找空格
        for (t = 2; t > 0; t--)
        {
            if (Source->deExtension[t] != '\x20')
                break;
        }

        // 复制扩展名
        for (j = 0; j <= t; j++)
        {
            if ((Source->deLowerCase & LCASE_EXT) && (Source->deExtension[j] >= 'A' && Source->deExtension[j] <= 'Z'))
                Desti->F_ShortName[i + j] = Source->deExtension[j] + 0x20;  // 转换为小写
            else
                Desti->F_ShortName[i + j] = Source->deExtension[j];
        }

        i += j;
    }

    Desti->F_ShortName[i] = '\0'; // 加入结束符

    if (0 != LongNameFlag) // 存在长文件名
    {
        LongNameBuffer[MAX_LONG_NAME_SIZE - 1] = 0;
        LongNameBuffer[MAX_LONG_NAME_SIZE - 2] = 0;

        // 复制长文件名
        for (i = 0; i < MAX_LONG_NAME_SIZE; i++)
            Desti->F_Name[i] = LongNameBuffer[i];
    }
    else // 短文件名
    {
        // 转换为Unicode
        for (i = 0; i < 12; i++)
        {
            Desti->F_Name[i * 2] = Desti->F_ShortName[i];
            Desti->F_Name[i * 2 + 1] = '\0';
        }
    }
}

// 搜索目标文件夹下面的文件
// 参数：目录路径，回调函数(返回1退出搜索)
// 返回值：文件的个数,-1为失败
int32 FDT_Search(const char *dir, FDT_Search_Cb CbFunc)
{
    int32 ret; //返回值
    int32 count = 0; // 文件计数
    int32 npos; // 长文件名缓冲区偏移量
    uint32 offset; // 数据偏移
    uint8 *p; // 长文件名缓冲区写入位置指针
    direntry *pitem = 0; // 标准目录项
    winentry *plfn = 0;   // 长文件名项
    FileInfoStruct FileInfo; // 结果文件信息

    // 读取文件目录表数据，不适用于所有机型
    FDTData = ReadFileAll(dir, &FDTSize);
    if (NULL == FDTData)
        return -1;

    LongNameFlag = 0; // 清空长文件名标志

    for (offset = 0; offset < FDTSize; offset += 32)
    {
        pitem = (direntry*)(&FDTData[offset]);

        // 忽略已删除文件、"."、".."
        if ((pitem->deName[0] == 0x0) || (pitem->deName[0] == 0xe5) 
            || ((pitem->deName[0] == 0x2E) && (pitem->deName[1] == 0x20))
            || ((pitem->deName[0] == 0x2E) && (pitem->deName[1] == 0x2E) && (pitem->deName[2] == 0x20)))
        {
            continue;
        }
        else // 找到一个合法文件.
        {
            if (pitem->deAttributes == ATTR_LONG_FILENAME) // 长文件名项
            {
                plfn = (winentry*)(&FDTData[offset]);
                npos = 26 *((plfn->weCnt - 1) & WIN_CNT);

                if (npos < MAX_LONG_NAME_SIZE - 25)
                {
                    // 复制长文件名
                    p = &LongNameBuffer[npos];
                    for (npos = 0; npos < 10; npos++)
                        *p++ = plfn->wePart1[npos];
                    for (npos = 0; npos < 12; npos++)
                        *p++ = plfn->wePart2[npos];
                    for (npos = 0; npos < 4; npos++)
                        *p++ = plfn->wePart3[npos];
                    if (plfn->weCnt & WIN_LAST)
                        *p = *(p + 1) = 0;
                    if (plfn->weCnt & WIN_CNT)
                        LongNameFlag = 1;
                }
            }
            else // 标准项
            {
                count++; // 文件数增加

                // 存在回调函数才回调
                if (NULL != CbFunc)
                {
                    ConvDirentruyItem(&FileInfo, pitem); // 转换信息

                    // 每取得一个完整文件名进行回调
                    ret = CbFunc(&FileInfo);
                    if (1 == ret) // 退出搜索
                        break;;
                }

                LongNameFlag = 0; // 清空长文件名
            }
        }
    }

    if (NULL != FDTData)
        free(FDTData);

    return count;
}
