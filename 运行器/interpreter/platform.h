/* all platform-specific includes and defines go in this file */
#ifndef PLATFORM_H
#define PLATFORM_H
#include "base.h"
//#ifdef IOS
#include <assert.h>
//#endif
//xlpicoc
extern intptr debugfile;
extern int32 FuncRet;
/* configurable options */
/* select your host type (or do it in the Makefile):
 * #define  UNIX_HOST
 * #define  FLYINGFOX_HOST
 * #define  SURVEYOR_HOST
 * #define  SRV1_UNIX_HOST
 * #define  UMON_HOST
 * #define  WIN32  (predefined on MSVC)
 */

#define LARGE_INT_POWER_OF_TEN 1000000000   /* the largest power of ten which fits in an int on this architecture */
#if defined(__hppa__) || defined(__sparc__)
#define ALIGN_TYPE double                   /* the default data type to use for alignment */
#else
#define ALIGN_TYPE void *                   /* the default data type to use for alignment */
#endif

#define GLOBAL_TABLE_SIZE 150                // 全局变量表 
#define STRING_TABLE_SIZE 150                // 共享字符串表的大小 
#define STRING_LITERAL_TABLE_SIZE 150        // 字符串文字表的大小 
#define RESERVED_WORD_TABLE_SIZE 97         /* reserved word table size */
#define PARAMETER_MAX 16                    // 函数参数的最大数量 
#define LINEBUFFER_MAX 256                  // 行的最大字符数 
#define LOCAL_TABLE_SIZE 40                 // 局部变量表的大小（可扩展） 
#define STRUCT_TABLE_SIZE 40                // 结构/联合成员表的大小（可扩展）

// #define GLOBAL_TABLE_SIZE 97                /* global variable table */
// #define STRING_TABLE_SIZE 97                /* shared string table size */
// #define STRING_LITERAL_TABLE_SIZE 97        /* string literal table size */
// #define RESERVED_WORD_TABLE_SIZE 97         /* reserved word table size */
// #define PARAMETER_MAX 16                    /* maximum number of parameters to a function */
// #define LINEBUFFER_MAX 256                  /* maximum number of characters on a line */
// #define LOCAL_TABLE_SIZE 11                 /* size of local variable table (can expand) */
// #define STRUCT_TABLE_SIZE 11                /* size of struct/union member table (can expand) */

#define INTERACTIVE_PROMPT_START "starting picoc " PICOC_VERSION "\n"
#define INTERACTIVE_PROMPT_STATEMENT "picoc> "
#define INTERACTIVE_PROMPT_LINE "     > "
#define HEAP_SIZE (1024*1024)  

/* host platform includes */
#ifdef UNIX_HOST
# define USE_MALLOC_STACK                   /* stack is allocated using malloc() */
# define USE_MALLOC_HEAP                    /* heap is allocated using malloc() */
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <assert.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdarg.h>
# include <setjmp.h>
# ifndef NO_FP
#  include <math.h>
#  define PICOC_MATH_LIBRARY
#  define USE_READLINE
#  undef BIG_ENDIAN
#  if defined(__powerpc__) || defined(__hppa__) || defined(__sparc__)
#   define BIG_ENDIAN
#  endif
# endif

extern jmp_buf ExitBuf;

#else
# ifdef WIN32
#  define USE_MALLOC_STACK                   /* stack is allocated using malloc() */
#  define USE_MALLOC_HEAP                    /* heap is allocated using malloc() */
#  include <stdio.h>
#  include <stdlib.h>
#  include <ctype.h>
#  include <string.h>
#  include <assert.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <stdarg.h>
#  include <setjmp.h>
#  include <math.h>
#  define PICOC_MATH_LIBRARY
#  undef BIG_ENDIAN

extern jmp_buf ExitBuf;

# else
#  ifdef FLYINGFOX_HOST
#   define HEAP_SIZE (16*1024)               /* space for the heap and the stack */
#   define NO_HASH_INCLUDE
#   include <stdlib.h>
#   include <ctype.h>
#   include <string.h>
#   include <sys/types.h>
#   include <stdarg.h>
#   include <setjmp.h>
#   include <math.h>
#   define assert(x)
#   define BUILTIN_MINI_STDLIB
#   undef BIG_ENDIAN

#  else
#   ifdef SURVEYOR_HOST
#    define HEAP_SIZE C_HEAPSIZE
#    define NO_FP
#    define NO_CTYPE
#    define NO_HASH_INCLUDE
#    define NO_MODULUS
#    include <cdefBF537.h>
#    include "../string.h"
#    include "../print.h"
#    include "../srv.h"
#    include "../setjmp.h"
#    include "../stdarg.h"
#    include "../colors.h"
#    include "../neural.h"
#    include "../gps.h"
#    include "../i2c.h"
#    include "../jpeg.h"
#    include "../malloc.h"
#    include "../xmodem.h"
#    define assert(x)
#    undef BIG_ENDIAN
#    define NO_CALLOC
#    define NO_REALLOC
#    define BROKEN_FLOAT_CASTS
#    define BUILTIN_MINI_STDLIB
#   else
#    ifdef UMON_HOST
#     define HEAP_SIZE (128*1024)               /* space for the heap and the stack */
#     define NO_FP
#     define BUILTIN_MINI_STDLIB
#     include <stdlib.h>
#     include <string.h>
#     include <ctype.h>
#     include <sys/types.h>
#     include <stdarg.h>
#     include <math.h>
#     include "monlib.h"
#     define assert(x)
#     define malloc mon_malloc
#     define calloc(a,b) mon_malloc(a*b)
#     define realloc mon_realloc
#     define free mon_free
#    endif
#   endif
#  endif

extern int ExitBuf[];

# endif
#endif

#endif /* PLATFORM_H */
