/*
 * 通用函数头文件
 * 版权所有 (C) 2011-2012 eleqian
 * [7/8/2012]
 */

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "FileIO.h"
#include "XString.h"

// 数据缓冲区大小-普通
#define DATA_BUFFER_SIZE_NORMAL     (16 * 1024) 

// 数据缓冲区大小-小型
#define DATA_BUFFER_SIZE_SMALL      (4 * 1024) 

//最小值
#ifndef MIN
# define MIN(a,b) (((a)<(b))?(a):(b))
#endif

//最大值
#ifndef MAX
# define MAX(a,b) (((a)>(b))?(a):(b))
#endif

//释放动态申请内存
//#ifndef TRYFREE
# define TRYFREE(p) \
    if (NULL != (p)) \
    { \
        free(p); \
        (p) = NULL; \
    }
//#endif

//关闭文件
//#ifndef TRYCLOSE
# define TRYCLOSE(fd) \
    if (0 != (fd)) \
    { \
        app_close(fd); \
        (fd) = 0; \
    }
//#endif

// 文件比较类型
enum
{
    CMP_MODE_EQUAL,
    CMP_MODE_DIFFER,
    CMP_MODE_SMALLER,
    CMP_MODE_GREATER,

    CMP_MODE_MAX
};

int32 ReadFile(const char *dir, const char *file, int32 pos, uint8 *buf, int32 bufSize);
int32 SaveFile(const char *dir, const char *file, int32 pos, uint8 *buf, int32 bufSize);

int32 CopyFile(const char *srcFile, const char *destFile);
int32 CopyFileEx(const char *srcFile, const char *destFile, uint32 srcPos, uint32 destPos, uint32 copySize);
int32 CopyFileFullPath(const char *srcPath, const char *destPath, const char *srcFile, const char *destFile);
int32 CopyFileByHandle(int32 ifd, int32 ofd, uint32 copySize);

// 写入size大小的0字节
// 参数：文件句柄，写入字节数
int32 WriteZeroToFile(int32 fd, int32 size);

// 移动文件数据
// 参数：句柄，开始位置偏移，移动距离，移动数据大小
int32 MoveFileData(int32 fd, int32 offset_begin, int32 dist_move, int32 size_to_move);

int32 CutDataToFile(const char *srcfile, const char *desfile, uint32 offset, uint32 size);

int32 CompareFileByHandle(int32 fd1, int32 fd2, int32 mode);
int32 CompareFile(char *srcPath, char *destPath, char *srcFile, char *destFile, uint32 cmpPos, int32 mode);

int32 FindFromFile(const char *dir, const char *file, int32 offset, uint8 *data, int32 size);
int32 FindFromFileByHandle(int32 fd, int32 offset, uint8 *data, int32 size);

char *ReadStringFromMrp(const char *name);
void *ReadFileAll(const char* filename, uint32 *size);

char *FixPath(char *path, char sep);
int32 MakeDir(const char *newdir);
int32 MakeDirEx(const char *newdir);
int32 RemoveDir(const char* dirName);
int32 RemoveDirEx(const char *dir);
int32 GetCurDir(char *strDir);
int32 Switch2Dir(const char *strDisk);
int32 ConvPath2Sys(const char *path, const char *name, char *out);
int64 GetDiskSize(const char *strDisk, uint8 Type);
char *GetTempFileName(void);

int32 OpenInPath(const char *path, const char *name, uint32 mode);
int32 FileLenInPath(const char *path, const char *name);

int32 GetAppId(void);
int32 GetAppVer(void);

void SwapBytes(uint8 *data, int32 size);
void DecodeStr(uint8 *strByte, uint8 XorByte);
void Color2ST(uint32 uColor, colorst *tColor);
void WLog(const char *text, int32 value);

#define LogPos() WLog(__FILE__, __LINE__);

#endif  // __FUNCTIONS_H__
