#ifndef __FDT_H__
#define __FDT_H__

#include "mrc_base.h"
#include "src/base.h"

#define READ_UINT32_LE(p) \
    (((uint32)(((uint8*)(p))[0])) \
    + ((uint32)(((uint8*)(p))[1]) << 8) \
    + ((uint32)(((uint8*)(p))[2]) << 16) \
    + ((uint32)(((uint8*)(p))[3]) << 24))

#define READ_UINT16_LE(p) \
    (((uint16)(((uint8*)(p))[0])) \
    + ((uint16)(((uint8*)(p))[1]) << 8))

// This is the format of the contents of the deTime field in the direntry
// structure.
// We don't use bitfields because we don't know how compilers for
// arbitrary machines will lay them out.
#define DT_2SECONDS_MASK 0x1F // seconds divided by 2
#define DT_2SECONDS_SHIFT 0
#define DT_MINUTES_MASK 0x7E0 // minutes
#define DT_MINUTES_SHIFT 5
#define DT_HOURS_MASK 0xF800 // hours
#define DT_HOURS_SHIFT 11

// This is the format of the contents of the deDate field in the direntry
// structure.
#define DD_DAY_MASK 0x1F // day of month
#define DD_DAY_SHIFT 0
#define DD_MONTH_MASK 0x1E0 // month
#define DD_MONTH_SHIFT 5
#define DD_YEAR_MASK 0xFE00 // year - 1980
#define DD_YEAR_SHIFT 9

//文件目录项的文件属性位
#define AM_RDO 0x01 //只读文件
#define AM_HID 0x02 //隐藏文件
#define AM_SYS 0x04 //系统文件
#define AM_VOL 0x08 //卷标
#define AM_LFN 0x0F //长文件名字段
#define AM_DIR 0x10 //文件夹
#define AM_ARC 0x20 //归档文件

// Number of chars per winentry
#define WIN_ENTRY_CHARS 13

// number of directory entries in one sector
#define DIRENTRIES_PER_SECTOR 0x10 //when the bpbBytesPerSec=512

#define MAX_LONG_NAME_SIZE 262 /* 26*n+2 n=10 */

// 标准目录项结构
typedef struct
{
    uint8 deName[8]; // filename, blank filled
#define SLOT_EMPTY 0x00 // slot has never been used
#define SLOT_E5 0x05 // the real value is 0xE5
#define SLOT_DELETED 0xE5 // file in this slot deleted
#define SLOT_DIR 0x2E // a directorymmm
    uint8 deExtension[3]; // extension, blank filled
    uint8 deAttributes; // file attributes
#define ATTR_NORMAL 0x00 // 普通文件
#define ATTR_READONLY 0x01 // 只读文件
#define ATTR_HIDDEN 0x02 // 隐藏文件
#define ATTR_SYSTEM 0x04 // 系统文件
#define ATTR_VOLUME 0x08 // 卷标
#define ATTR_LONG_FILENAME 0x0F // 长文件名标志
#define ATTR_DIRECTORY 0x10 // 文件夹文件
#define ATTR_ARCHIVE 0x20 // 新的或者归档文件
    uint8 deLowerCase; // NT VFAT lower case flags (set to zero)
#define LCASE_BASE 0x08 // filename base in lower case
#define LCASE_EXT 0x10 // filename extension in lower case
    uint8 deCHundredth; // hundredth of seconds in CTime
    uint8 deCTime[2]; // create time
    uint8 deCDate[2]; // create date
    uint8 deADate[2]; // access date
    uint8 deHighClust[2]; // high bytes of cluster number
    uint8 deMTime[2]; // last update time
    uint8 deMDate[2]; // last update date
    uint8 deStartCluster[2]; // starting cluster of file
    uint8 deFileSize[4]; // size of file in bytes
} direntry;

// 长文件名目录项结构
typedef struct
{
    uint8 weCnt;
#define WIN_LAST 0x40
#define WIN_CNT 0x3f
    uint8 wePart1[10];
    uint8 weAttributes;
#define ATTR_WIN 0x0f
    uint8 weReserved1;
    uint8 weChksum;
    uint8 wePart2[12];
    uint8 weReserved2[2];
    uint8 wePart3[4];
} winentry;

// 文件信息结构体
typedef struct
{
    uint8 F_ShortName[13]; // 短文件名
    uint8 F_Name[MAX_LONG_NAME_SIZE]; // 真实文件名，Unicode小端编码
    uint32 F_Size; // 文件大小
    uint8 F_Attr; // 文件属性
    mr_datetime F_TCreate; // 创建日期时间
    mr_datetime F_TModify; // 修改日期时间
    mr_datetime F_TAccess; // 访问日期(无时间)
} FileInfoStruct;

// 文件搜索回调
// 参数：文件信息
// 返回值：0-成功，1-退出搜索
typedef int32 (*FDT_Search_Cb)(FileInfoStruct *FileInfo);

// 搜索目标文件夹下面的文件
// 参数：目录路径，回调函数(允许NULL以获取文件数,返回1退出搜索)
// 返回值：文件的个数,-1为失败
int32 FDT_Search(const char *dir, FDT_Search_Cb CbFunc);

#endif
