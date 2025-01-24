
/*

手机C编译模式头文件
最后修改于 2020-06-03
*/
#include "base.h"
#include <windows.h>
#include <stdint.h>
// #include <stdlib.h>
// #include <string.h>
// #include <jni.h>
// vsprintf
// #include <stdarg.h>

#define TCC 1

#ifdef __cplusplus
#include <iostream>
extern "C"
{ // 因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
    // #include <base.h>
    /*
    base.h
    用于gcc编译

    最后修改时间 2018.6.19


    gcc编译静态库 资料
    http://m.blog.chinaunix.net/uid-261392-id-2138941.html





    */

    // GETJNIENV getJNIEnv;
    // GETCONTEXT getContext;
    // GETCACHEBITMAP getCacheBitmap;

    /*
    PRINTF printf;
    FREE free;
    MEMCPY memcpy;
    MEMMOVE memmove;
    STRCPY strcpy;
    STRNCPY strncpy;
    STRCAT strcat;
    STRNCAT strncat;
    MEMCMP memcmp;
    STRCMP strcmp;
    STRNCMP strncmp;
    MEMCHR memchr;
    MEMSET memset;
    STRLEN strlen;
    STRSTR strstr;

    ATOI atoi;
    STRTOUL strtoul;
    STRRCHR strrchr;
    */
    SPRINTF app_sprintf;
    GETSCREENWIDTH getScreenWidth;
    GETSCREENHEIGHT getScreenHeight;
#define SCRW (getScreenWidth())
#define SCRH (getScreenHeight())

    WSTRLEN wstrlen;
    SLEEP sleep;
    DRECT drect;
    DLINE dline;
    DPOINT dpoint;
    DPOINTEX dpointex;
    CLS cls;
    REF ref;
    DTEXT dtext;
    DTEXTEX dtextex;
    DTEXTRIGHT dtextright;
    EFFSETCON effsetcon;
    IMG img;
    SHADERECT shaderect;
    TEXTWH textwh;
    UNITEXTROW unitextrow;
    U2C u2c;
    C2U c2u;

    // 文件操作相关
    OPEN app_open;           //
    CLOSE app_close;         //
    FILESTATE app_filestate; //
    WRITE app_write;         //
    READ app_read;           //
    SEEK app_seek;           //
    GETLEN app_getlen;       //

    REMOVE app_remove; //
    RENAME app_rename; //
    MKDIR app_mkdir;   //
    RMDIR app_rmdir;   //

    FINDSTART findstart;
    FINDNEXT findnext;
    FINDSTOP findstop;
    DLGCREATE dlgcreate;
    DLGDEL dlgdel;
    DLGREF dlgref;
    TEXTCREATE textcreate;
    TEXTDEL textdel;
    TEXTREF textref;
    EDITCREATE editcreate;
    EDITGET editget;
    EDITDEL editdel;
    TIMERCREATE timercreate;
    TIMERDEL timerdel;
    TIMERSTOP timerstop;
    TIMERSTART timerstart;
    TIMERSETTIME timersettime;
    GETSCRBUF getscrbuf;
    GETSCRSIZE getscrsize;
    SETSCRSIZE setscrsize;
    EXIT app_exit;
    GETUPTIME getuptime;
    GETDATETIME getdatetime;
    SHAKE shake;
    SAND app_sand;
    RAND app_rand;
    PRINTF app_printf;
    SMS sms;
    LCD lcd;
    // JNIEnv *env;
    BMPSHOWFLIP bmpshowflip;

    /*
 * 将 GBK 字符串转换为 Unicode 字符串（大端）
 * 输入:
 *   cp: 输入的 GBK 字符串
 *   err: 若为非 NULL，则在转换出错时返回出错字符的索引
 *   size: 输出的 Unicode 字符串长度（以字符为单位）
 * 输出:
 *   err: 若为非 NULL，则在转换出错时返回出错字符的索引
 *   size: 输出的 Unicode 字符串长度
 * 返回:
 *   NULL: 转换出错
 *   其他: Unicode 字符串指针（需调用者释放内存）
 */
uint16* mrc_c2u(char* cp, int32* err, int32* size) {
    if (cp == NULL) {
        if (err) *err = -1;
        return NULL;
    }

    // 获取输入字符串的长度
    int gbk_len = (int)strlen(cp);
    if (gbk_len == 0) {
        if (size) *size = 0;
        return NULL;
    }

    // 计算转换后的 Unicode 字符串长度
    int unicode_len = MultiByteToWideChar(CP_ACP, 0, cp, gbk_len, NULL, 0);
    if (unicode_len == 0) {
        if (err) *err = -1;
        return NULL;
    }

    // 分配内存存储 Unicode 字符串（包括终止符）
    uint16_t* unicode_str = (uint16_t*)malloc((unicode_len + 1) * sizeof(uint16_t));
    if (unicode_str == NULL) {
        if (err) *err = -1;
        return NULL;
    }

    // 将 GBK 转换为 UTF-16（小端）
    int result = MultiByteToWideChar(CP_ACP, 0, cp, gbk_len, (LPWSTR)unicode_str, unicode_len);
    if (result == 0) {
        free(unicode_str);
        if (err) *err = -1;
        return NULL;
    }

    // 添加终止符
    unicode_str[unicode_len] = 0;

    // 将小端 UTF-16 转换为大端 UTF-16
    for (int i = 0; i < unicode_len; i++) {
        uint16_t value = unicode_str[i];
        printf("%x\r\n", value);
        unicode_str[i] = ((value & 0xFF) << 8) | ((value >> 8) & 0xFF);
    }

    // 设置输出参数
    if (size) *size = unicode_len;
    if (err) *err = 0;

    return unicode_str;
}

/*
 * 将 Unicode 字符串（大端）转换为 GBK 编码
 * 输入:
 *   input: 输入的 Unicode 字符串（大端）
 *   input_len: 输入的 Unicode 字符串长度（以字节为单位）
 *   output: 输出的 GBK 字符串缓冲区（由调用者分配和管理）
 *   output_len: 输出缓冲区的长度（以字节为单位）
 * 返回:
 *   MR_SUCCESS: 转换成功
 *   MR_FAILED: 转换失败
 */
int32 mrc_unicodeToGb2312(uint8* input, int32 input_len, uint8** output, int32* output_len) {
    if (input == NULL || output == NULL || output_len == NULL || *output_len == 0) {
        printf("mrc_unicodeToGb2312 convert is null\r\n");
        return MR_FAILED;
    }

    // 检查输入长度是否为偶数（UTF-16 每个字符占 2 字节）
    if (input_len % 2 != 0) {
        printf("mrc_unicodeToGb2312 len error\r\n");
        return MR_FAILED;
    }

    // 将大端 UTF-16 转换为小端 UTF-16
    int32 unicode_len = input_len / 2;
    uint16* unicode_str = (uint16*)malloc(input_len);
    if (unicode_str == NULL) {
        printf("mrc_unicodeToGb2312 malloc error\r\n");
        return MR_FAILED;
    }

    for (int i = 0; i < unicode_len; i++) {
        uint16 value = ((uint16)input[2 * i] << 8) | (uint16)input[2 * i + 1];
        unicode_str[i] = value;
    }

    // 计算转换后的 GBK 字符串长度
    int gbk_len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)unicode_str, unicode_len, NULL, 0, NULL, NULL);
    if (gbk_len == 0) {
        free(unicode_str);
        printf("mrc_unicodeToGb2312 gbk len is zero\r\n");
        return MR_FAILED;
    }

    // 检查输出缓冲区是否足够大
    if (*output_len < gbk_len) {
        free(unicode_str);
        printf("mrc_unicodeToGb2312 output_len < gbk_len\r\n");
        return MR_FAILED;
    }

    // 将 UTF-16（小端）转换为 GBK
    int result = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)unicode_str, unicode_len, (LPSTR)*output, *output_len, NULL, NULL);
    free(unicode_str);

    if (result == 0) {
        printf("mrc_unicodeToGb2312 result = 0\r\n");
        return MR_FAILED;
    }

    // 设置输出长度
    *output_len = gbk_len;

    return MR_SUCCESS;
}

    /*
    接口初始化
    name 函数名
    ptr 函数指针
    */
    int base_add(char *name, void *ptr)
    {

        if (!strcmp(name, "printf"))
        {
            app_printf = (PRINTF)ptr;
        }
        else if (!strcmp(name, "sprintf"))
        {
            app_sprintf = (SPRINTF)ptr;
        }
        /*
        else if(!strcmp(name, "free"))
        {
        free=ptr;
        }
        else if(!strcmp(name, "memcpy"))
        {
        memcpy=ptr;
        }
        else if(!strcmp(name, "memmove"))
        {
        memmove=ptr;
        }
        else if(!strcmp(name, "strcpy"))
        {
        strcpy=ptr;
        }
        else if(!strcmp(name, "strncpy"))
        {
        strncpy=ptr;
        }
        else if(!strcmp(name, "strcat"))
        {
        strcat=ptr;
        }
        else if(!strcmp(name, "strncat"))
        {
        strncat=ptr;
        }
        else if(!strcmp(name, "memcmp"))
        {
        memcmp=ptr;
        }
        else if(!strcmp(name, "strcmp"))
        {
        strcmp=ptr;
        }
        else if(!strcmp(name, "strncmp"))
        {
        strncmp=ptr;
        }
        else if(!strcmp(name, "memchr"))
        {
        memchr=ptr;
        }
        else if(!strcmp(name, "memset"))
        {
        memset=ptr;
        }
        else if(!strcmp(name, "strlen"))
        {
        strlen=ptr;
        }
        else if(!strcmp(name, "strstr"))
        {
        strstr=ptr;
        }

        else if(!strcmp(name, "atoi"))
        {
        atoi=ptr;
        }
        else if(!strcmp(name, "strtoul"))
        {
        strtoul=ptr;
        }
        else if(!strcmp(name, "strrchr"))
        {
        strrchr=ptr;
        }
        else
        */
       
       
        if (!strcmp(name, "getScreenWidth"))
        {
            getScreenWidth = (GETSCREENWIDTH)ptr;
        }
        if (!strcmp(name, "getScreenHeight"))
        {
            getScreenHeight = (GETSCREENHEIGHT)ptr;
        }
        if (!strcmp(name, "wstrlen"))
        {
            wstrlen = (WSTRLEN)ptr;
        }
        else if (!strcmp(name, "u2c"))
        {
            u2c = (U2C)ptr;
        }
        else if (!strcmp(name, "c2u"))
        {
            c2u = (C2U)ptr;
        }

        else if (!strcmp(name, "sleep"))
        {
            sleep = (SLEEP)ptr;
        }

        else if (!strcmp(name, "drect"))
        {
            drect = (DRECT)ptr;
        }
        else if (!strcmp(name, "dline"))
        {
            dline = (DLINE)ptr;
        }
        else if (!strcmp(name, "dpoint"))
        {
            dpoint = (DPOINT)ptr;
        }
        else if (!strcmp(name, "dpointex"))
        {
            dpointex = (DPOINTEX)ptr;
        }
        else if (!strcmp(name, "cls"))
        {
            cls = (CLS)ptr;
        }
        else if (!strcmp(name, "ref"))
        {
            ref = (REF)ptr;
        }
        else if (!strcmp(name, "dtext"))
        {
            dtext = (DTEXT)ptr;
        }
        else if (!strcmp(name, "dtextex"))
        {
            dtextex = (DTEXTEX)ptr;
        }
        else if (!strcmp(name, "dtextright"))
        {
            dtextright = (DTEXTRIGHT)ptr;
        }
        else if (!strcmp(name, "effsetcon"))
        {
            effsetcon = (EFFSETCON)ptr;
        }
        else if (!strcmp(name, "img"))
        {
            img = (IMG)ptr;
        }
        else if (!strcmp(name, "shaderect"))
        {
            shaderect = (SHADERECT)ptr;
        }
        else if (!strcmp(name, "textwh"))
        {
            textwh = (TEXTWH)ptr;
        }
        else if (!strcmp(name, "unitextrow"))
        {
            unitextrow = (UNITEXTROW)ptr;
        }
        // 文件操作
        else if (!strcmp(name, "open"))
        {
            app_open = (OPEN)ptr;
        }

        else if (!strcmp(name, "close"))
        {
            app_close = (CLOSE)ptr;
        }
        else if (!strcmp(name, "filestate"))
        {
            app_filestate = (FILESTATE)ptr;
        }
        else if (!strcmp(name, "write"))
        {
            app_write = (WRITE)ptr;
        }

        else if (!strcmp(name, "read"))
        {
            app_read = (READ)ptr;
        }
        else if (!strcmp(name, "seek"))
        {
            app_seek = (SEEK)ptr;
        }
        else if (!strcmp(name, "getlen"))
        {
            app_getlen = (GETLEN)ptr;
        }
        else if (!strcmp(name, "remove"))
        {
            app_remove = (REMOVE)ptr;
        }
        else if (!strcmp(name, "rename"))
        {
            app_rename = (RENAME)ptr;
        }
        else if (!strcmp(name, "mkdir"))
        {
            app_mkdir = (MKDIR)ptr;
        }
        else if (!strcmp(name, "rmdir"))
        {
            app_rmdir = (RMDIR)ptr;
        }
        else if (!strcmp(name, "findstart"))
        {
            findstart = (FINDSTART)ptr;
        }
        else if (!strcmp(name, "findnext"))
        {
            findnext = (FINDNEXT)ptr;
        }
        else if (!strcmp(name, "findstop"))
        {
            findstop = (FINDSTOP)ptr;
        }
        else if (!strcmp(name, "dlgcreate"))
        {
            dlgcreate = (DLGCREATE)ptr;
        }
        else if (!strcmp(name, "dlgdel"))
        {
            dlgdel = (DLGDEL)ptr;
        }
        else if (!strcmp(name, "dlgref"))
        {
            dlgref = (DLGREF)ptr;
        }
        else if (!strcmp(name, "textcreate"))
        {
            textcreate = (TEXTCREATE)ptr;
        }
        else if (!strcmp(name, "textdel"))
        {
            textdel = (TEXTDEL)ptr;
        }
        else if (!strcmp(name, "textref"))
        {
            textref = (TEXTREF)ptr;
        }
        else if (!strcmp(name, "editcreate"))
        {
            editcreate = (EDITCREATE)ptr;
        }
        else if (!strcmp(name, "editget"))
        {
            editget = (EDITGET)ptr;
        }
        else if (!strcmp(name, "editdel"))
        {
            editdel = (EDITDEL)ptr;
        }
        else if (!strcmp(name, "timercreate"))
        {
            timercreate = (TIMERCREATE)ptr;
        }
        else if (!strcmp(name, "timerdel"))
        {
            timerdel = (TIMERDEL)ptr;
        }
        else if (!strcmp(name, "timerstop"))
        {
            timerstop = (TIMERSTOP)ptr;
        }
        else if (!strcmp(name, "timerstart"))
        {
            timerstart = (TIMERSTART)ptr;
        }
        else if (!strcmp(name, "timersettime"))
        {
            timersettime = (TIMERSETTIME)ptr;
        }
        else if (!strcmp(name, "getscrbuf"))
        {
            getscrbuf = (GETSCRBUF)ptr;
        }
        else if (!strcmp(name, "getscrsize"))
        {
            getscrsize = (GETSCRSIZE)ptr;
        }
        else if (!strcmp(name, "setscrsize"))
        {
            setscrsize = (SETSCRSIZE)ptr;
        }

        else if (!strcmp(name, "exit"))
        {
            app_exit = (EXIT)ptr;
        }

        else if (!strcmp(name, "getuptime"))
        {
            getuptime = (GETUPTIME)ptr;
        }
        else if (!strcmp(name, "getdatetime"))
        {
            getdatetime = (GETDATETIME)ptr;
        }
        else if (!strcmp(name, "shake"))
        {
            shake = (SHAKE)ptr;
        }
        else if (!strcmp(name, "sand"))
        {
            app_sand = (SAND)ptr;
        }
        else if (!strcmp(name, "rand"))
        {
            app_rand = (RAND)ptr;
        }
        else if (!strcmp(name, "sms"))
        {
            sms = (SMS)ptr;
        }
        else if (!strcmp(name, "lcd"))
        {
            lcd = (LCD)ptr;
        }
        else if (!strcmp(name, "bmpshowflip"))
        {
            bmpshowflip = (BMPSHOWFLIP)ptr;
        }

        return 1;
    }

#ifdef __cplusplus
}
#endif
