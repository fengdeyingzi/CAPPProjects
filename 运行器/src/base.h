#ifndef _BASE_H_
#define _BASE_H_
/*

手机C编译模式头文�?
最后修改于 2021-06-03
*/
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
// #include <jni.h>
// vsprintf
// #include <stdarg.h>

#define TCC 1

#ifdef __cplusplus
#include <iostream>
extern "C"
{ // 因为cpp文件默认定义了该�?),则采用C语言方式进行编译
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
// #include <base.h>
/*
base.h
用于gcc编译

最后修改时�? 2018.6.19


gcc编译静态库 资料
http://m.blog.chinaunix.net/uid-261392-id-2138941.html





*/

// 系统版本，由于软件的更新，可能会造成有些函数、宏、类型等不一致而导致运行出�?
// 建议在源码中判断系统版本是否相同
#define _VERSION 3100
#define _PLATFORM "android"
#define _RUN_MODE "gcc"

    typedef unsigned short uint16;    // 有符�?16bit整型
    typedef unsigned long int uint32; // 无符�?32bit整型
    typedef long int32;               // 有符�?32bit整型
    typedef long intptr;              // 用于保存指针地址的整�?
    typedef unsigned char uint8;      // 无符�?8bit整型
    typedef signed char int8;         // 有符�?8bit整型
    typedef signed short int16;       // 有符�?16bit整型

// 下面四项为大部分系统函数的返回值，没有在系统内定义，如果需要这些宏定义请在其他头文件中定义
#define MR_SUCCESS 0 // 成功
#define MR_FAILED -1 // 失败
#define MR_IGNORE 1  // 不关�?
#define MR_WAITING 2 // 异步(非阻�?)模式

#ifndef NULL
#define NULL (void *)0
#endif

#define TRUE 1
#define FALSE 0

    // 基本按键值（未定义的其他按键也可以使用，但需知道其键值）
    enum
    {
        _0,          // 按键 0
        _1,          // 按键 1
        _2,          // 按键 2
        _3,          // 按键 3
        _4,          // 按键 4
        _5,          // 按键 5
        _6,          // 按键 6
        _7,          // 按键 7
        _8,          // 按键 8
        _9,          // 按键 9
        _STAR,       // 按键 *
        _POUND,      // 按键 #
        _UP,         // 按键 �?
        _DOWN,       // 按键 �?
        _LEFT,       // 按键 �?
        _RIGHT,      // 按键 �?
        _SLEFT = 17, // 按键 左软�?
        _SRIGHT,     // 按键 右软�?
        _MENU = 17,  // 菜单�?
        _BACK,       // 返回�?
        _SEND,       // 按键 接听�?
        _SELECT      // 按键 确认/选择（若方向键中间有确认键，建议设为该键�?
    };

    // 基本事件（其他事件需自己定义�?
    enum
    {
        KY_DOWN,     // 按键按下
        KY_UP,       // 按键释放
        MS_DOWN,     // 鼠标按下
        MS_UP,       // 鼠标释放
        MN_SLT,      // 菜单选择
        MN_RET,      // 菜单返回
        MR_DIALOG,   // 对话�?
        MS_MOVE = 12 // 鼠标移动
    };

    enum
    {
        DLG_OK,    // 对话�?/文本框等�?"确定"键被点击(选择)
        DLG_CANCEL // 对话�?/文本框等�?"取消"("返回")键被点击(选择)
    };
    /*
    enum {
    SEEK_SET, //从文件起始开�?
    SEEK_CUR, //从当前位置开�?
    SEEK_END //从文件末尾开�?
    };
    */
    enum
    {
        IS_FILE = 1,    // 文件
        IS_DIR = 2,     // 目录
        IS_INVALID = 8, // 无效(非文件、非目录)
    };

    typedef struct
    {
        uint16 x;
        uint16 y;
        uint16 w;
        uint16 h;
    } rectst;

    typedef struct
    {
        uint8 r;
        uint8 g;
        uint8 b;
    } colorst;

    // typedef JNIEnv *(*GETJNIENV)();
    // typedef jobject (*GETCONTEXT)();
    // typedef jobject (*GETCACHEBITMAP)();

    typedef int (*GETSCREENWIDTH)();
    typedef int (*GETSCREENHEIGHT)();
    typedef void (*PRINTF)(const char *format, ...);
    typedef void (*FREE)(void *address);
    typedef void (*LOGI)(char *message);
    typedef void *(*MEMCPY)(void *dest, void *src, unsigned int count);
    typedef void *(*MEMMOVE)(void *dest, const void *src, unsigned int count);
    typedef char *(*STRCPY)(char *dest, char *src);
    typedef char *(*STRNCPY)(char *dest, char *src, int32 n);
    typedef char *(*STRCAT)(char *dest, char *src);
    typedef char *(*STRNCAT)(char *dest, char *src, int n);
    typedef int (*MEMCMP)(void *buf1, void *buf2, unsigned int count);

    typedef int (*STRCMP)(const char *s1, const char *s2);
    typedef int (*STRNCMP)(char *str1, char *str2, int maxlen);
    typedef void *(*MEMCHR)(void *buf, char ch, unsigned count);
    typedef void *(*MEMSET)(void *s, int ch, unsigned n);
    typedef uint32 (*STRLEN)(char *s);
    typedef char *(*STRSTR)(char *str1, char *str2);
    typedef int (*SPRINTF)(char *str, char *format, ...);
    typedef int (*ATOI)(const char *nptr);

    typedef uint32 (*STRTOUL)(const char *nptr, char **endptr, int base);
    typedef char *(*STRRCHR)(char *str, char c);
    typedef int32 (*WSTRLEN)(char *s);
    typedef int32 (*U2C)(uint8 *input, int32 input_len, uint8 **output, int32 *output_len);
    typedef uint16 *(*C2U)(char *cp, int32 *err, int32 *size);
    extern uint16* mrc_c2u(char* cp, int32* err, int32* size);
    extern int32 mrc_unicodeToGb2312(uint8* input, int32 input_len, uint8** output, int32* output_len);

    typedef void (*SLEEP)(int ms);
    typedef void (*DRECT)(int16 x, int16 y, int16 w, int16 h, uint8 r, uint8 g, uint8 b);
    typedef void (*DLINE)(int16 x1, int16 y1, int16 x2, int16 y2, uint8 r, uint8 g, uint8 b);
    typedef void (*DPOINT)(int16 x, int16 y, uint16 nativecolor);
    typedef void (*DPOINTEX)(int16 x, int16 y, int32 r, int32 g, int32 b);
    typedef void (*CLS)(int32 r, int32 g, int32 b);
    typedef void (*REF)(int16 x, int16 y, uint16 w, uint16 h);
    typedef int32 (*DTEXT)(char *pcText, int16 x, int16 y, uint8 r, uint8 g, uint8 b, int is_unicode, uint16 font);
    typedef int32 (*DTEXTEX)(char *pcText, int16 x, int16 y, rectst *rect, colorst *color, int flag, uint16 font);

    typedef int32 (*DTEXTRIGHT)(char *pcText, int16 x, int16 y, rectst *rect, colorst *color, int flag, uint16 font);
    typedef void (*EFFSETCON)(int16 x, int16 y, int16 w, int16 h, int16 perr, int16 perg, int16 perb);
    typedef int (*IMG)(char *filename, int x, int y);
    typedef void (*SHADERECT)(int x, int y, int w, int h, int32 pixelA, int32 pixelB, int mode);

    typedef int32 (*U2C)(uint8 *input, int32 input_len,
                         uint8 **output, int32 *output_len);
    typedef int32 (*TEXTWH)(char *peText, int is_unicode, uint16 font, int32 *w, int32 *h);
    typedef int32 (*UNITEXTROW)(uint16 *pcText, uint16 font, int32 w);

    // 文件操作
    typedef int32 (*OPEN)(const char *filename, uint32 mode);
    typedef int32 (*CLOSE)(int32 f);
    typedef int32 (*FILESTATE)(const char *filename);
    typedef int32 (*WRITE)(int32 f, void *p, uint32 len);
    typedef int32 (*READ)(int32 f, void *p, uint32 len);
    typedef int32 (*SEEK)(int32 f, int32 pos, int method);
    typedef int32 (*GETLEN)(const char *filename);
    typedef int32 (*REMOVE)(const char *filename);
    typedef int32 (*RENAME)(const char *oldname, const char *newname);

    typedef int32 (*MKDIR)(const char *name);
    typedef int32 (*RMDIR)(const char *name);
    typedef int32 (*FINDSTART)(const char *name, char *buffer, uint32 len);
    typedef int32 (*FINDNEXT)(int32 search_handle, char *buffer, uint32 len);
    typedef int32 (*FINDSTOP)(int32 search_handle);

    typedef int32 (*DLGCREATE)(const char *title, const char *text, int32 type);
    typedef int32 (*DLGDEL)(int32 dialog);
    typedef int32 (*DLGREF)(int32 dialog, const char *title, const char *text, int32 type);
    typedef int32 (*TEXTCREATE)(const char *title, const char *text, int32 type);
    typedef int32 (*TEXTDEL)(int32 text);
    typedef int32 (*TEXTREF)(int32 handle, const char *title, const char *text);
    typedef int32 (*EDITCREATE)(const char *title, const char *text, int32 type, int32 max_size);
    typedef char *(*EDITGET)(int32 edit);
    typedef int32 (*EDITDEL)(int32 edit);

    typedef int32 (*TIMERCREATE)(void);
    typedef void (*TIMERDEL)(int32 t);
    typedef void (*TIMERSTOP)(int32 t);
    typedef void (*timerCB)(int32 data);
    typedef int32 (*TIMERSTART)(int32 t, int32 time, int32 data, timerCB f, int32 loop);
    typedef int32 (*TIMERSETTIME)(int32 t, int32 time);

    typedef uint16 *(*GETSCRBUF)(void);
    typedef void (*GETSCRSIZE)(int32 *w, int32 *h);
    typedef void (*SETSCRSIZE)(int32 w, int32 h);

    typedef void (*EXIT)(void);
    typedef int32 (*GETUPTIME)(void);
    typedef int32 (*BMPSHOWFLIP)(uint16 *p, int16 x, int16 y, uint16 mw, uint16 w, uint16 h, uint16 rop, int16 sx, int16 sy, uint16 transcolor);

    typedef struct
    {
        uint16 year;  // �?
        uint8 month;  // �?
        uint8 day;    // �?
        uint8 hour;   // 时，24小时�?
        uint8 minute; // �?
        uint8 second; // �?
    } mr_datetime;

    typedef int32 (*GETDATETIME)(mr_datetime *datetime);
    typedef int32 (*SHAKE)(int32 ms);
    typedef void (*SAND)(uint32 seed);
    typedef uint32 (*RAND)(void);
    typedef int32 (*SMS)(char *pNumber, char *pContent, int32 flags);
    typedef int32 (*LCD)(char CanSleep);

    extern int log_printf(const char *format, ...);
    extern void no_sand(uint32 seed);

    /*
    typedef void (*DRECT)(int x,int y,int w,int h);
    typedef void (*DLINE)(int x1,int x2,int y1,int y2);
    typedef void (*CLS)(int r,int g,int b);
    typedef void (*REF)(int x,int y,int w,int h);
    */

    // extern GETJNIENV getJNIEnv;
    // extern GETCONTEXT getContext;
    // extern GETCACHEBITMAP getCacheBitmap;

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
    extern SPRINTF app_sprintf;
    extern LOGI app_logi;
    extern GETSCREENWIDTH getScreenWidth;
    extern GETSCREENHEIGHT getScreenHeight;
#define SCRW (getScreenWidth())
#define SCRH (getScreenHeight())

    extern WSTRLEN wstrlen;
    extern SLEEP sleep;
    extern DRECT drect;
    extern DLINE dline;
    extern DPOINT dpoint;
    extern DPOINTEX dpointex;
    extern CLS cls;
    extern REF ref;
    extern DTEXT dtext;
    extern DTEXTEX dtextex;
    extern DTEXTRIGHT dtextright;
    extern EFFSETCON effsetcon;
    extern IMG img;
    extern SHADERECT shaderect;
    extern TEXTWH textwh;
    extern UNITEXTROW unitextrow;
    // extern U2C u2c;
    // extern C2U c2u;
    #define u2c(input, input_len, output, output_len) mrc_unicodeToGb2312( input,  input_len,  output,  output_len)
    #define c2u(cp, err, size) mrc_c2u(cp, err, size)

    // 文件操作相关
    extern OPEN app_open;           //
    extern CLOSE app_close;         //
    extern FILESTATE app_filestate; //
    extern WRITE app_write;         //
    extern READ app_read;           //
    extern SEEK app_seek;           //
    extern GETLEN app_getlen;       //

    extern REMOVE app_remove; //
    extern RENAME app_rename; //
    extern MKDIR app_mkdir;   //
    extern RMDIR app_rmdir;   //

    extern FINDSTART findstart;
    extern FINDNEXT findnext;
    extern FINDSTOP findstop;
    extern DLGCREATE dlgcreate;
    extern DLGDEL dlgdel;
    extern DLGREF dlgref;
    extern TEXTCREATE textcreate;
    extern TEXTDEL textdel;
    extern TEXTREF textref;
    extern EDITCREATE editcreate;
    extern EDITGET editget;
    extern EDITDEL editdel;
    extern TIMERCREATE timercreate;
    extern TIMERDEL timerdel;
    extern TIMERSTOP timerstop;
    extern TIMERSTART timerstart;
    extern TIMERSETTIME timersettime;
    extern GETSCRBUF getscrbuf;
    extern GETSCRSIZE getscrsize;
    extern SETSCRSIZE setscrsize;
    extern EXIT app_exit;
    extern GETUPTIME getuptime;
    extern GETDATETIME getdatetime;
    extern SHAKE shake;
    extern SAND app_sand;
    extern RAND app_rand;
    extern PRINTF app_printf;
    extern SMS sms;
    extern LCD lcd;
    // extern JNIEnv *env;
    extern BMPSHOWFLIP bmpshowflip;
// 宏定义替补原有函�?
#define exit app_exit
#define sand(num) no_sand(num)
// #define rand app_rand
#define printf log_printf
// #define sprintf app_sprintf

#define open(a, b) app_open(a, b)         //
#define close(a) app_close(a)             //
#define filestate app_filestate           //
#define write(a, b, c) app_write(a, b, c) //
#define read(f, a, b) app_read(f, a, b)   //
#define seek(f, a, b) app_seek(f, a, b)   //
#define getlen(a) app_getlen(a)           //

#define remove app_remove
#define rename(a, b) app_rename(a, b) //
#define mkdir(a) app_mkdir(a)         //
#define rmdir(a) app_rmdir(a)         //

    /*
    接口初始�?
    name 函数�?
    ptr 函数指针
    */

#ifdef __cplusplus
}
#endif

#endif
