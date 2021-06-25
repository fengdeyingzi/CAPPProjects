/*
 * 程序通用函数代码
 * 版权所有 (C) 2011-2012 eleqian
 * [7/23/2012]
 */

#include "src/base.h"
#include "src/exb.h"
#include "src/android.h"
#include "mrc_base.h"

#include "Functions.h"
#include "XString.h"


// 磁盘空间结构体
typedef struct
{
    uint32 total;    // 总的大小
    uint32 tunit;    // 总大小的单位
    uint32 account;  // 剩余空间的大小
    uint32 unit;     // 剩余大小的单位
} T_DSM_FREE_SAPCE;

// 扩展接口声明
typedef void (*MR_PLAT_EX_CB)(uint8* output, int32 output_len);
extern int32 mrc_platEx(int32 code, uint8* input, int32 input_len, uint8** output, int32* output_len, MR_PLAT_EX_CB* cb);

/*---------------------------------------------------------------------------*/

//取得指定绝对目录文件大小
int32 FileLenInPath(const char *path, const char *name)
{
    int32 ret = 0;
/*
    if (NULL != path)
        Switch2Dir(path);
*/
    ret = app_getlen(name);
/*
    if (NULL != path)
        Switch2Dir(NULL);
*/
    return ret;
}

//在指定绝对目录打开文件
int32 OpenInPath(const char *path, const char *name, uint32 mode)
{
    int32 fd = 0;
    int32 ret = 0;
LOGI("检测路径");
#ifndef SDK_MOD  // 模拟器环境必然失败
    if (NULL != path)
        ret = Switch2Dir(path);
#endif
LOGI("mrc_open");
    if (0 == ret)
        fd = app_open(name, mode);
LOGI("置空");
#ifndef SDK_MOD
    if (NULL != path)
        Switch2Dir(NULL);
#endif

    return fd;
}

//读取文件
//参数：路径，文件名，读取位置，缓冲区，缓冲区大小
//返回：实际读取大小
int32 ReadFile(const char *dir, const char *file, int32 pos, uint8 *buf, int32 bufSize)
{
    int32 fd;
    int32 rSize = -1;

    memset(buf, 0, bufSize);
    fd = OpenInPath(dir, file, MR_FILE_RDONLY);
    if (fd > 0)
    {
        if (MR_SUCCESS == app_seek(fd, pos, SEEK_SET))
        {
            rSize = app_read(fd, buf, bufSize);
        }
        app_close(fd);
    }

    return rSize;
}

//保存文件
//参数：路径，文件名，读取位置，缓冲区，缓冲区大小
//返回：实际保存大小
int32 SaveFile(const char *dir, const char *file, int32 pos, uint8 *buf, int32 bufSize)
{
    int32 fd;
    int32 rSize = -1;

    fd = OpenInPath(dir, file, MR_FILE_RDWR | MR_FILE_CREATE);
    if (fd > 0)
    {
        app_seek(fd, pos, MR_SEEK_SET);
        rSize = app_write(fd, buf, bufSize);
        app_close(fd);
    }

    return rSize;
}

// 从mrp读取文本文件全部内容
char *ReadStringFromMrp(const char *name)
{
    char *gbstr;
    char *fbuf;
    int32 fsize;

//    fbuf = mrc_readFileFromMrp(name, &fsize, 0); //xldebug
    fbuf = readFileFromAssets(name, &fsize);
    LOGI("读取文件成功：%s", fbuf);
    if (NULL != fbuf)
    {
        gbstr = (char*)malloc(fsize + 1);
        memcpy(gbstr, fbuf, fsize);
        gbstr[fsize] = '\0';
//        mrc_freeFileData(fbuf, fsize); //xldebug
        free(fbuf);
    }
    else
    {
        return NULL;
    }

    return gbstr;
}

// 读取整个文件数据
// 参数：文件路径
// 返回值：非NULL-文件数据，需free；NULL-失败
void *ReadFileAll(const char* filename, uint32 *size)
{
    int32 ret, filelen, fd;
    void *data = NULL;

    filelen = app_getlen(filename);
    if (filelen <= 0)
        return NULL;

    fd = app_open(filename, MR_FILE_RDONLY);
    if (fd > 0)
    {
        data = (void *)malloc(filelen);
        if (NULL != data)
        {
            ret = app_read(fd, data, filelen);
            if (ret != filelen)
            {
                free(data);
                data = NULL;
            }
        }
    }

    app_close(fd);
    *size = filelen;

    return data;
}

/*---------------------------------------------------------------------------*/

//从文件查找数据位置
//参数：文件名，开始查找偏移，查找数据，数据大小
//返回：找到的位置
int32 FindFromFile(const char *dir, const char *file, int32 offset, uint8 *data, int32 size)
{
    int32 ret = -1;
    int32 fd;

    fd = OpenInPath(dir, file, MR_FILE_RDONLY);
    if (0 == fd)
        return ret;

    ret = FindFromFileByHandle(fd, offset, data, size);

    app_close(fd);

    return ret;
}

//从文件查找数据位置-句柄版
//参数：文件句柄，文件偏移，查找数据，数据大小
//返回：找到的位置
int32 FindFromFileByHandle(int32 fd, int32 offset, uint8 *data, int32 size)
{
    uint32 *bad_char_skip;
    uint8 *databuf = NULL, *pfind;
    int32 bufUsed, readPos;
    int32 ret = -1;

    if (0 == fd)
        return ret;

    readPos = offset;
    databuf = (uint8 *)malloc(DATA_BUFFER_SIZE_NORMAL);
    memset(databuf, 0, DATA_BUFFER_SIZE_NORMAL);

    bad_char_skip = (uint32 *)malloc(256 * sizeof(uint32));
    ret = BMH_BuildTable(bad_char_skip, 256, data, size);

    while (1)
    {
        app_seek(fd, readPos, MR_SEEK_SET);
        bufUsed = app_read(fd, databuf, DATA_BUFFER_SIZE_NORMAL);
        if (bufUsed <= 0)
            break;

        pfind = BMH_Ex(bad_char_skip, databuf, bufUsed, data, size);
        if (NULL != pfind)
        {
            ret = readPos + (pfind - databuf);
            break;
        }

        readPos += (DATA_BUFFER_SIZE_NORMAL - size + 1);
    }

    TRYFREE(bad_char_skip);
    TRYFREE(databuf);

    return ret;
}

/*---------------------------------------------------------------------------*/

//复制文件
//参数：源文件路径，目标文件路径
int32 CopyFile(const char *srcFile, const char *destFile)
{
    int32 ifd, ofd; //源文件和目标文件句柄
    int32 ret = MR_FAILED, copySize;

    copySize = app_getlen(srcFile);
    if (copySize < 0)
        return MR_FAILED;

    ifd = app_open(srcFile, MR_FILE_RDONLY); //打开源文件(只读)
    ofd = app_open(destFile, MR_FILE_WRONLY | MR_FILE_CREATE); //打开目标文件(不存在创建)

    if(ifd != 0 && ofd != 0) //打开文件都成功
    {
        app_seek(ifd, 0, MR_SEEK_SET);
        app_seek(ofd, 0, MR_SEEK_SET);

        ret = CopyFileByHandle(ifd, ofd, copySize);
    }

    TRYCLOSE(ifd); //关闭源文件
    TRYCLOSE(ofd); //关闭目标文件

    return ret; 
}

//复制文件-绝对路径版
//参数：源文件路径，目标文件路径
int32 CopyFileFullPath(const char *srcPath, const char *destPath, const char *srcFile, const char *destFile)
{
    int32 ofd = 0, ifd = 0; //源文件和目标文件句柄
    int32 ret = MR_FAILED, copySize;

    copySize = FileLenInPath(srcPath, srcFile);
    if (copySize < 0)
        return MR_FAILED;

    ifd = OpenInPath(srcPath, srcFile, MR_FILE_RDONLY); //打开源文件(只读)
    ofd = OpenInPath(destPath, destFile, MR_FILE_WRONLY | MR_FILE_CREATE); //打开目标文件(不存在创建)

    if(ifd != 0 && ofd != 0) //打开文件都成功
    {
        app_seek(ifd, 0, MR_SEEK_SET);
        app_seek(ofd, 0, MR_SEEK_SET);

        ret = CopyFileByHandle(ifd, ofd, copySize);
    }

    TRYCLOSE(ofd); //关闭目标文件
    TRYCLOSE(ifd); //关闭源文件

    return ret;     
}

//复制文件-扩展版
//参数：源文件路径，目标文件路径，源文件开始位置，目标文件开始位置，复制大小
int32 CopyFileEx(const char *srcFile, const char *destFile, uint32 srcPos, uint32 destPos, uint32 copySize)
{
    int32 ifd, ofd; //源文件和目标文件句柄
    int32 ret = MR_FAILED;

    ifd = app_open(srcFile, MR_FILE_RDONLY); //打开源文件(只读)
    ofd = app_open(destFile, MR_FILE_WRONLY | MR_FILE_CREATE); //打开目标文件(不存在创建)

    if (ifd != 0 && ofd != 0) //打开文件都成功
    {
        app_seek(ifd, srcPos, MR_SEEK_SET);
        app_seek(ofd, destPos, MR_SEEK_SET);

        ret = CopyFileByHandle(ifd, ofd, copySize);
    }

    TRYCLOSE(ifd); //关闭源文件
    TRYCLOSE(ofd); //关闭目标文件

    return ret;
}

//复制文件-句柄版
//参数：源文件句柄，目标文件句柄，复制大小
int32 CopyFileByHandle(int32 ifd, int32 ofd, uint32 copySize)
{
    uint8 *dataBuf = NULL; //文件读写缓冲
    int32 size_read, size_write; //本次读写大小
    uint32 size_to_read, size_copied; //需要读取大小，总复制大小
    int32 ret;

    if(0 == ifd || 0 == ofd) //句柄无效
        return MR_FAILED;

    dataBuf = (uint8*)malloc(DATA_BUFFER_SIZE_NORMAL);
    if (NULL == dataBuf) //内存不足
        return MR_FAILED;

    memset(dataBuf, 0, DATA_BUFFER_SIZE_NORMAL);
    size_copied = 0;
    ret = MR_SUCCESS;

    while (copySize > size_copied) //直到复制完成
    {
        size_to_read = MIN(DATA_BUFFER_SIZE_NORMAL, copySize - size_copied);

        size_read = app_read(ifd, dataBuf, size_to_read); //读取文件
        if (size_read <= 0)
        {
            ret = MR_FAILED;
            break;
        }

        size_write = app_write(ofd, dataBuf, size_read); //写文件
        if (size_write <= 0 || size_write != size_read)
        {
            ret = MR_FAILED;
            break;
        }

        size_copied += size_read;
    }

    TRYFREE(dataBuf); //释放内存

    return ret;
}

/*---------------------------------------------------------------------------*/

// 向文件添加指定大小的'\0'字节
int32 WriteZeroToFile(int32 fd, int32 size)
{
    int32 count, ret;
    uint8 *buf = NULL;

    if (fd <= 0 || size <= 0)
        return -1;

    buf = (uint8*)malloc(DATA_BUFFER_SIZE_NORMAL);
    if (NULL == buf)
        return -1;

    memset(buf, 0, DATA_BUFFER_SIZE_NORMAL);

    for (count = size / DATA_BUFFER_SIZE_NORMAL; count > 0; count--)
    {
        app_write(fd, buf, DATA_BUFFER_SIZE_NORMAL);
    }

    ret = app_write(fd, buf, size % DATA_BUFFER_SIZE_NORMAL);
    TRYFREE(buf);

    return ret < 0 ? ret : size;
}

// 移动文件数据
// 参数：句柄，开始位置偏移，移动距离，移动数据大小
int32 MoveFileData(int32 fd, int32 offset_begin, int32 dist_move, int32 size_to_move)
{
    uint8 *dataBuf = NULL;        // 文件读写缓冲
    int32 size_read, size_write;  // 本次读写大小
    int32 size_to_read;           // 需要读取大小
    int32 offset_read;            // 读取数据位置
    int32 ret = MR_SUCCESS;       // 返回值

    if (0 == fd || 0 == size_to_move)
        return MR_FAILED;

    dataBuf = (uint8*)malloc(DATA_BUFFER_SIZE_NORMAL);
    if (NULL == dataBuf)
        return MR_FAILED;

    while (size_to_move > 0)
    {
        // 读取文件
        size_to_read = MIN(DATA_BUFFER_SIZE_NORMAL, size_to_move);
        offset_read = offset_begin + size_to_move - size_to_read;
        app_seek(fd, offset_read, MR_SEEK_SET);
        size_read = app_read(fd, dataBuf, size_to_read);
        if (size_read <= 0)
        {
            ret = MR_FAILED;
            break;
        }

        // 写文件
        app_seek(fd, offset_read + dist_move, MR_SEEK_SET);
        size_write = app_write(fd, dataBuf, size_read);
        if (size_write <= 0 || size_write != size_read)
        {
            ret = MR_FAILED;
            break;
        }

        size_to_move -= size_read;
    }

    TRYFREE(dataBuf);

    return ret;
}

// 剪切文件为新文件
// 参数：源文件，目标文件，开始位置，大小
// 备注：当目标文件存在时添加数据到末尾
int32 CutDataToFile(const char *srcfile, const char *desfile, uint32 offset, uint32 size)
{
    int32 ret;
    int32 desPos = 0;

    if (MR_IS_FILE == mrc_fileState(desfile))
    {
        desPos = app_getlen(desfile);
        if (desPos < 0)
            desPos = 0;
    }

    ret = CopyFileEx(srcfile, desfile, offset, desPos, size);

    return ret;
}

/*---------------------------------------------------------------------------*/

//比较文件 - 句柄版
//参数：文件句柄1，文件句柄2，比较模式
//返回：结果位置，失败时小于0
int32 CompareFileByHandle(int32 fd1, int32 fd2, int32 cmode)
{
    uint8 *srcBuffer = NULL, *destBuffer = NULL; // 文件缓冲
    uint32 sbufUsed = 0, dbufUsed = 0;           // 缓冲区大小使用大小
    int32 cmpSize = 0, resultPos = -1;
    int32 i = 0;

    if(fd1 == 0 || fd2 == 0) // 文件句柄无效
        return resultPos;

    // 分配缓冲区内存
    srcBuffer = (uint8*)malloc(DATA_BUFFER_SIZE_NORMAL);
    destBuffer = (uint8*)malloc(DATA_BUFFER_SIZE_NORMAL);

    // 内存申请失败
    if (NULL == srcBuffer || NULL == destBuffer)
    {
        TRYFREE(srcBuffer);
        TRYFREE(destBuffer);
        return -2;
    }

    memset(srcBuffer, 0, DATA_BUFFER_SIZE_NORMAL);
    memset(destBuffer, 0, DATA_BUFFER_SIZE_NORMAL);

    // 每次比较一个缓冲区直到完成
    do {
        sbufUsed = app_read(fd1, srcBuffer, DATA_BUFFER_SIZE_NORMAL); // 读取文件
        dbufUsed = app_read(fd2, destBuffer, DATA_BUFFER_SIZE_NORMAL);

        // 只比较都存在的偏移位置数据
        cmpSize = MIN(dbufUsed, sbufUsed);
        if (cmpSize <= 0)
            break;

        if (CMP_MODE_EQUAL == cmode) // 比较相同
        {
            for (i = 0; i < cmpSize; i++)
            {
                if (*(srcBuffer + i) == *(destBuffer + i))
                {
                    resultPos = i;
                    break;
                }
            }
        }
        else if (CMP_MODE_DIFFER == cmode) // 比较不同
        {
            for (i = 0; i < cmpSize; i++)
            {
                if (*(srcBuffer + i) != *(destBuffer + i))
                {
                    resultPos = i;
                    break;
                }
            }
        }
        else if (CMP_MODE_SMALLER == cmode) // 比较小于
        {
            for (i = 0; i < cmpSize; i++)
            {
                if (*(srcBuffer + i) < *(destBuffer + i))
                {
                    resultPos = i;
                    break;
                }
            }
        }
        else if (CMP_MODE_GREATER == cmode) // 比较大于
        {
            for (i = 0; i < cmpSize; i++)
            {
                if (*(srcBuffer + i) > *(destBuffer + i))
                {
                    resultPos = i;
                    break;
                }
            }
        }

        if (resultPos >= 0) // 比较完成
            break;

    } while (DATA_BUFFER_SIZE_NORMAL == sbufUsed && DATA_BUFFER_SIZE_NORMAL == dbufUsed);

    // 释放内存
    TRYFREE(srcBuffer);
    TRYFREE(destBuffer);

    return resultPos;     
}

//比较文件
//参数：参考文件路径，比较文件路径，参考文件，比较文件，开始比较位置，比较模式
//返回：结果位置
int32 CompareFile(char *srcPath, char *destPath, char *srcFile, char *destFile, uint32 cmpPos, int32 cmpMode)
{
    int32 fd_dest_file = 0, fd_src_file = 0; //参考文件和比较文件句柄
    int32 resultPos = -1;

    fd_src_file = OpenInPath(srcPath, srcFile, MR_FILE_RDONLY); //打开源文件(只读)
    fd_dest_file = OpenInPath(destPath, destFile, MR_FILE_RDONLY);

    if (fd_src_file != 0 && fd_dest_file != 0) //打开文件都成功
    {
        app_seek(fd_src_file, cmpPos, MR_SEEK_SET);
        app_seek(fd_dest_file, cmpPos, MR_SEEK_SET);

        resultPos = CompareFileByHandle(fd_src_file, fd_dest_file, cmpMode);
    }

    // 关闭文件
    TRYCLOSE(fd_src_file);
    TRYCLOSE(fd_dest_file);

    return resultPos >= 0 ? cmpPos + resultPos : resultPos;
}

/*---------------------------------------------------------------------------*/

// 整理路径，将分隔符统一为sep，并清除连续的多个
// 参数：路径(必须可读写)
char *FixPath(char *path, char sep)
{
    char *p, *q;
    int flag = 0;

    if (NULL == path)
        return NULL;

    for (p = q = path; '\0' != *p; p++)
    {
        if ('\\' == *p || '/' == *p)
        {
            if (0 == flag)
                *q++ = sep;
            flag = 1;
        }
        else
        {
            *q++ = *p;
            flag = 0;
        }
    }

    *q = '\0';

    return path;
}

// 获取当前路径名
// 参数：结果缓冲区
int32 GetCurDir(char *strDir)
{
    int32 ret = MR_FAILED, len = 0;
    uint8 *pDir = NULL;

    if (NULL == strDir)
        return MR_FAILED;

    *strDir = '\0';
    strcpy(strDir,fv_getpath());
//xldebug

/*
#ifdef WIN32
    return MR_FAILED;
#endif

    ret = mrc_platEx(1204, (uint8*)"Y", 1, &pDir, &len, NULL);
    if (MR_SUCCESS == ret)
    {
        memcpy(strDir, pDir, len + 1);
        TRYFREE(pDir);
        ret = len;
    }
*/

    return ret;
}

//切换目录
//参数：路径，NULL切换到上次目录
int32 Switch2Dir(const char* strDir)
{
    static char lastDir[MAX_PATH_LEN_A];
    int32 slen, ret;
    LOGI("switchPath %s", strDir);
//    switchPath(strDir);
/* //xldebug
#ifdef WIN32
    return MR_FAILED;
#endif

    if (NULL != strDir)
    {
		LOGI("getCurDir");
        GetCurDir(lastDir);
        slen = strlen(strDir);
		LOGI("mrc_platEx");
        ret = mrc_platEx(1204, (uint8*)ConvertPathSeparator(strDir), slen, NULL, NULL, NULL);
    }
    else
    {
        if ('\0' == lastDir[0])
            lastDir[0] = 'Z';
        slen = strlen(lastDir);
        ret = mrc_platEx(1204, (uint8*)lastDir, slen, NULL, NULL, NULL);
    }
    */

    return 0;
}

// 转换绝对路径为相对mythroad的路径
// 如果不在mythroad目录内返回失败并设置输出为空串
// 返回：0成功 -1失败
int32 ConvPath2Sys(const char *path, const char *name, char *out)
{
    char *curdir, *fullpath;
    int32 slen, ret;

    if (NULL ==path || NULL == name)
    {
        *out = '\0';
        return -1;
    }

    curdir = (char *)malloc(MAX_PATH_LEN_A);
    GetCurDir(curdir);
    FixPath(curdir, '/');
    fullpath = (char *)malloc(MAX_PATH_LEN_A);
    sprintf(fullpath, "%s/%s", path, name);
    FixPath(fullpath, '/');

    slen = strlen(curdir);

    if (0 == strnicmp(curdir, fullpath, slen))
    {
        if ('/' == fullpath[slen])
            slen++;
        strcpy(out, fullpath + slen);
        ret = 0;
    }
    else
    {
        *out = '\0';
        ret = -1;
    }

    TRYFREE(curdir);
    TRYFREE(fullpath);

    return ret;
}

// 创建多层目录，仅支持相对路径
// 成功返回0，失败返回-1
int32 MakeDir(const char *newdir)
{
    char *strBuf = NULL;
    char *p = NULL;
    int32 len = 0;

    if (NULL == newdir || '\0' == *newdir) 
        return -1;

    strBuf = strdup(newdir);
    FixPath(strBuf, '/');
    len = strlen(strBuf);

    // 消除最后的分隔符
    if ('/' == strBuf[len - 1])
        strBuf[len - 1] = '\0';

    // 循环创建
    for (p = strBuf + 1; p < strBuf + len; p++)
    {
        // 查找下一层目录
        while(('\0' != *p) && ('/' != *p)) 
            p++;
        *p = '\0';

        if (MR_IS_FILE == mrc_fileState(strBuf)) // 如果有同名文件，Kill
            mrc_remove(strBuf);
        if (MR_IS_DIR != mrc_fileState(strBuf)) // 如果无文件夹，Make
            mrc_mkDir(strBuf);
        if (MR_IS_DIR != mrc_fileState(strBuf)) // 创建失败
        {
            TRYFREE(strBuf);
            return -1;
        }

        *p = '/';
    }

    TRYFREE(strBuf);
    return 0;
}

// 创建多层目录，自动判断绝对和相对路径
// 成功返回0，失败返回-1
int32 MakeDirEx(const char *newdir)
{
    char *dir1;
    int32 ret;

    if (NULL == newdir) 
        return -1;

    dir1 = strdup(newdir);
    FixPath(dir1, '/');

    if (':' == dir1[1])
    {
        char disk[4] = "";

        // 绝对路径
        memcpy(disk, dir1, 3);
        ret = Switch2Dir(disk);
        if (0 == ret)
            ret = MakeDir(dir1 + 3);
        Switch2Dir(NULL);
    }
    else
    {
        // 相对路径
        ret = MakeDir(dir1);
    }

    TRYFREE(dir1);

    return ret;
}

// 递归删除文件夹下的所有文件
// 参数：文件夹(相对路径)
// 返回：成功或失败
int32 RemoveDir(const char* dirName)
{
    char *fullName;
    char *fileName;
    int32 ret = MR_FAILED;

    if (NULL == dirName)
        return MR_FAILED;    

    fullName = (char *)malloc(MAX_PATH_LEN_A);
    fileName = (char *)malloc(MAX_FILENAME_LEN_A);

    if (NULL != fullName && NULL != fileName)
    {
        int32 dirNameLen;

        memset(fullName, 0, MAX_PATH_LEN_A);
        memset(fileName, 0, MAX_FILENAME_LEN_A);
        strcpy(fullName, dirName);
        dirNameLen = strlen(dirName);

        if (fullName[dirNameLen - 1] != '/')
        {
            // 准备拼接目录下的子文件或子目录
            fullName[dirNameLen] = '/';
            dirNameLen++;
        }

        if (filestate(dirName) == MR_IS_DIR)
        {
            int32 fd;
            int32 result = MR_FAILED;

            // 搜索初始化
            fd = findstart(dirName, fileName, MAX_FILENAME_LEN_A);
            if (fd > 0) // 搜索句柄有效
            {
                result = MR_SUCCESS;
                while (result == MR_SUCCESS)
                {
                    // 忽略"."、".."
                    if (!((fileName[0] == '\0')
                        || (fileName[0] == '.' && fileName[1] == '\0')
                        || (fileName[0] == '.' && fileName[1] == '.' && fileName[2] == '\0')))
                    {
                        int32 length = strlen(fileName);

                        strcpy(&fullName[dirNameLen], fileName);
                        fullName[dirNameLen + length] = '\0';

                        if (filestate(fullName) == MR_IS_FILE)
                        {
                            // 文件类型，删除文件
                            ret = app_remove(fullName);
                        }
                        else if (filestate(fullName) == MR_IS_DIR)
                        {
                            // 文件夹类型，递归删除子文件夹
                            ret = RemoveDir(fullName);
                        }
                    }
                    memset(fileName, 0, sizeof(fileName));
                    result = findstart(fd, fileName, MAX_FILENAME_LEN_A);
                }
                findstop(fd);
            }

            // 进行一次其它位置搜索，否则不能删除文件夹
            fd = findstart("", fileName, MAX_FILENAME_LEN_A);
            findstop(fd);
            ret = mrc_rmDir(dirName);
        }
    }

    TRYFREE(fullName);
    TRYFREE(fileName);

    return ret;
}

// 删除目录及其子目录和文件，自动判断绝对和相对路径
// 成功返回0，失败返回-1
int32 RemoveDirEx(const char *dir)
{
    char *dir1;
    int32 ret;

    if (NULL == dir) 
        return -1;

    dir1 = strdup(dir);
    FixPath(dir1, '/');

    if (':' == dir1[1])
    {
        char disk[4] = "";

        // 绝对路径
        memcpy(disk, dir1, 3);
        ret = Switch2Dir(disk);
        if (0 == ret)
            ret = RemoveDir(dir1 + 3);
        Switch2Dir(NULL);
    }
    else
    {
        // 相对路径
        ret = RemoveDir(dir1);
    }

    TRYFREE(dir1);

    return ret;
}

//取得磁盘空间大小
//参数：盘符，大小类型：0 - 总大小，1 - 剩余大小
//返回：大小，-1失败
int64 GetDiskSize(const char* strDisk, uint8 Type)
{
    T_DSM_FREE_SAPCE *getInfo = NULL;
    //MR_PLAT_EX_CB cb = NULL;
    int32 output_len = 0;
    int32 ret;
//xldebug
/*
    ret = mrc_platEx(1305, (uint8*)strDisk, 1, (uint8**)&getInfo, &output_len, NULL);
    if (MR_SUCCESS == ret)
    {
        if (0 == Type)
        {
            return (int64)getInfo->total * (int64)getInfo->tunit;
        }
        else if (1 == Type)
        {
            return (int64)getInfo->account * (int64)getInfo->unit;
        }


    }
*/
    return -1;
}

// 取得程序ID
int32 GetAppId(void)
{
    int32 appid = 1001;
//    char *pMrpName = mrc_getPackName(); //xldebug

//    mrc_GetMrpInfo(pMrpName, MRP_APPID, (uint8*)&appid, sizeof(int32));

    return appid;
}

// 取得程序版本
int32 GetAppVer(void)
{
    int32 appver = 0;
//    char *pMrpName = mrc_getPackName(); //xldebug

//    mrc_GetMrpInfo(pMrpName, MRP_APPVER, (uint8*)&appver, sizeof(int32));

    return appver;
}

/*---------------------------------------------------------------------------*/

// 获取一个临时文件名，需free
char *GetTempFileName(void)
{
    char name[16] = "";
    uint32 temp;

    app_sand(getuptime());

    do {
        temp = app_rand();
        sprintf(name, "%d.tmp", temp);
    } while (MR_IS_INVALID != mrc_fileState(name));

    return strdup(name);
}

// 交换前后字节顺序
void SwapBytes(uint8 *data, int32 size)
{
    uint32 i;
    uint8 tByte;

    for (i = 0; i < size; i += 2)
    {
        tByte = data[i];
        data[i] = data[i + 1];
        data[i + 1] = tByte;
    }
}

// 进行简单加密字符的解密
// 参数：字符串，异或字节
void DecodeStr(uint8 *strBytes, uint8 XorByte)
{
    uint8 *p = strBytes;

    while (0 != *p)
        *p++ ^= XorByte;
}

// 颜色值转换为结构
void Color2ST(uint32 uColor, colorst *tColor)
{
    tColor->r = (uint8)(uColor >> 16) & 0xff;
    tColor->g = (uint8)(uColor >> 8) & 0xff;
    tColor->b = (uint8)(uColor & 0xff);
}

// 记录日志
void WLog(const char *text, int32 value)
{
    int32 fd, slen;
    char tStr[16];

    fd = app_open("ehexlog.txt", MR_FILE_RDWR | MR_FILE_CREATE);
    app_seek(fd, 0, MR_SEEK_END);
    app_write(fd, (void*)text, strlen(text));
    slen = sprintf(tStr, "\t%d\r\n", value);
    app_write(fd, tStr, slen);
    app_close(fd);
}
