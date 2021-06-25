/*
 * INI文件读写代码
 * 原作者信息丢失，sorry
 * eleqian 修改
 * [5/26/2012]
 */

#include "mrc_base.h"
#include "src/base.h"
#include "FileIO.h"
#include "IniFile.h"

IniFileData_TS f_inifile;

#define DBGPRINT(...)

#define strnicmp(d,s,n) my_strnicmp(d,s,n)
#define strtol(s,e,b)   my_strtol(s,e,b)

#define LONG_MAX    2147483647L  /*0x7FFFFFFF*/
#define LONG_MIN    (-2147483647L-1L) /*-0x80000000*/

#define isalpha(a)  ((unsigned int)(((a) | 0x20) - 'a') < 26u)
#define isupper(a)  ((unsigned int)((a) - 'A') < 26u)
#define isdigit(a)  ((unsigned int)((a) - '0') < 10u)
#define isspace(a)  ((unsigned int)((a) - 9) < 5u || (a) == ' ')
//#define isspace(a)  ((a) == ' ' || (a) == '\t' || (a) == '\n' || (a) == '\v' || (a) == '\f' || (a) == '\r')

int IniSearchSection(const char *psz_section);
int IniSearchContentStart(const long i_startpos);
int IniSearchContentEnd(const long i_startpos);

#ifdef SUPPORT_REAL_VALUE
#define atof(s)         my_atof(s)

// 转换字符串为浮点型
static double my_atof(char *s)
{
    int i;
    int sign;
    int expn;
    double val;
    double power;

    sign = 1;
    power = 1.0;
    expn = 0;

    for (i = 0; isspace(s[i]); i++)
        ;

    if (s[i] == '-')
        sign =  - 1;

    if (s[i] == '+' || s[i] == '-')
        ++i;

    for (val = 0.0; isdigit(s[i]); i++)
        val = val * 10.0 + (s[i] - '0');

    if (s[i] == '.')
        ++i;

    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = val * 10.0 + (s[i] - '0');
        power = power * 10.0;
    }

    val = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E')
    {
        sign = (s[++i] == '-') ?  - 1: 1;
        if (s[i] == '+' || s[i] == '-')
            ++i;

        for (expn = 0; isdigit(s[i]); i++)
            expn = expn * 10+(s[i] - '0');

        if (sign == 1)
            while (expn-- > 0)
                val = val * 10.0;
            else
                while (expn-- > 0)
                    val = val / 10.0;
    }

    return val;
}

#endif

// 转换字符串为整数
static long my_strtol(const char *nptr, char **endptr, int base)
{
    const char *p = nptr;
    unsigned long ret, Overflow;
    int sign = 0, flag, LimitRemainder;
    int ch;

    /*
    跳过前面多余的空格，并判断正负符号。
    如果base是0，允许以0x开头的十六进制数，
    以0开头的8进制数。
    如果base是16，则同时也允许以0x开头。
     */
    do {
        ch =  *p++;
    } while (isspace(ch));

    if (ch == '-') {
        sign = 1;
        ch =  *p++;
    } else if (ch == '+')
        ch =  *p++;

    if ((base == 0 || base == 16) && ch == '0' && (*p == 'x' ||  *p == 'X'))
    {
        ch = p[1];
        p += 2;
        base = 16;
    }

    if (base == 0)
        base = ch == '0' ? 8 : 10;

    Overflow = sign ? (unsigned long) - (LONG_MIN + LONG_MAX) + LONG_MAX: LONG_MAX;
    LimitRemainder = Overflow % (unsigned long)base;
    Overflow /= (unsigned long)base;

    for (ret = 0, flag = 0;; ch =  *p++)
    {
        /*把当前字符转换为相应运算中需要的值。*/
        if (isdigit(ch))
            ch -= '0';
        else if (isalpha(ch))
            ch -= isupper(ch) ? 'A' - 10: 'a' - 10;
        else
            break;

        if (ch >= base)
            break;

        /*如果产生溢出，则置标志位，以后不再做计算。*/
        if (flag < 0 || ret > Overflow || (ret == Overflow && ch > LimitRemainder))
            flag =  - 1;
        else
        {
            flag = 1;
            ret *= base;
            ret += ch;
        }
    }

    /*
    如字符串不为空，则*endptr等于指向nptr结束
    符的指针值；否则*endptr等于nptr的首地址。
     */
    if (endptr != 0)
        *endptr = (char*)(flag ? (p - 1): nptr);

    /*
    如果溢出，则返回相应的Overflow的峰值。
    没有溢出，如是符号位为负，则转换为负数。
     */
    if (flag < 0)
        return sign ? LONG_MIN : LONG_MAX;
    else if (sign)
        return  - (signed)ret;
    else
        return ret;
}

// 不区分大小写比较字符串前n个字符
static int32 my_strnicmp(const char *dst, const char *src, int32 count)
{
    int ch1, ch2;

    do {
        if (((ch1 = (unsigned char)(*(dst++))) >= 'A') && (ch1 <= 'Z'))
            ch1 += 0x20;

        if (((ch2 = (unsigned char)(*(src++))) >= 'A') && (ch2 <= 'Z'))
            ch2 += 0x20;

    } while (--count && ch1 && (ch1 == ch2));

    return (ch1 - ch2);
}

/*******************************************************************************
 *   desc: open ini file
 *------------------------------------------------------------------------------
 *  param: char *psz_file       -- file to open
 *------------------------------------------------------------------------------
 * return:  0   -- file succefully opened
 *         -1   -- fail to open ini file
 *         -2   -- fail to read file to buffer
 *******************************************************************************/
int IniOpenFile(const char *psz_file)
{
    int32 fd;
    int32 fsize;

    IniCloseFile();

    memset(&f_inifile, 0, sizeof(IniFileData_TS));
    f_inifile.sz_filebuffer = (char *)malloc(M_MAX_BUFFER_SIZE);
    if (NULL == f_inifile.sz_filebuffer)
        return -2;

    memset(f_inifile.sz_filebuffer, 0, M_MAX_BUFFER_SIZE);
    fsize = app_getlen(psz_file);
    f_inifile.i_filesize = fsize; // save file size
    f_inifile.p_filename = (char*)psz_file;

    // open file
    fd = app_open(psz_file, MR_FILE_RDONLY);
    if (fd == 0)
        return  -1;

    // read file to buffer
    if (app_read(fd, f_inifile.sz_filebuffer, fsize) != fsize)
    {
        if (fd != 0)
            app_close(fd);
        return  -2;
    }

    app_close(fd);

    // 替换\r为\n
    if (fsize > 0)
    {
        char *p = f_inifile.sz_filebuffer;

        while (*p)
        {
            if (*p == '\r')
                *p = '\n';
            p++;
        }
    }

    return 0;
}

/*******************************************************************************
 *   desc: close ini file
 *------------------------------------------------------------------------------
 *  param: none
 *------------------------------------------------------------------------------
 * return:  0   -- file succefully closed
 *         -1   -- fail to close the opened file
 *******************************************************************************/
int IniCloseFile(void)
{
    int32 ret = MR_SUCCESS;

    // file not opened
    if (f_inifile.p_filename == NULL)
        return FALSE;

    // save file if buffer changed
    if (f_inifile.b_bufferchanged)
    {
        int32 fd;
        char *p = f_inifile.sz_filebuffer;

        // 替换\n\n为\r\n
        while (*p && *(p + 1))
        {
            if (*p == '\n' && *(p + 1) == '\n')
                *p++ = '\r';
            p++;
        }

        DBGPRINT(("\nCloseFile -- wrtie file, file size = %d\n", f_inifile.i_filesize));

        app_remove(f_inifile.p_filename);
        fd = mrc_open(f_inifile.p_filename, MR_FILE_RDWR | MR_FILE_CREATE);
        app_write(fd, f_inifile.sz_filebuffer, f_inifile.i_filesize);
        ret = app_close(fd);
        f_inifile.b_bufferchanged = FALSE;
    }

    if (NULL != f_inifile.sz_filebuffer)
    {
        free(f_inifile.sz_filebuffer);
        f_inifile.sz_filebuffer = NULL;
    }

    f_inifile.p_filename = NULL;

    // close file
    if (ret == MR_SUCCESS) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// 清除内容
int IniClearContent(void)
{
    // file not opened
    if (f_inifile.p_filename == NULL)
        return FALSE;

    memset(f_inifile.sz_filebuffer, 0, M_MAX_BUFFER_SIZE);
    f_inifile.i_filesize = 0;

    return TRUE;
}

/*******************************************************************************
 *   desc: get a string value by key
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *         const char * psz_key         -- key name
 *         char *       psz_value       -- key value
 *------------------------------------------------------------------------------
 * return: TRUE   -- key value found
 *         FALSE  -- key value not found
 *******************************************************************************/
int IniGetString(const char *psz_section, const char *psz_key, char *psz_value)
{
    long i = 0;
    long j = 0;
    int b_skip = FALSE;
    int i_key_len;

    // file not opened
    if (f_inifile.p_filename == NULL)
        return FALSE;

    // key name can't be null
    if (NULL == psz_key)
        return FALSE;

    i_key_len = strlen(psz_key);
    if (0 == i_key_len)
        return FALSE;

    // return if section not found
    if (IniSearchSection(psz_section) == FALSE)
        return FALSE;

    DBGPRINT(("\nGetString -- to get value of %s\n", psz_key));
    i = f_inifile.i_sc_startpos;
    while (i < f_inifile.i_sc_endpos)
    {
        // skip space, tab and \n
        while (i < f_inifile.i_filesize && isspace(f_inifile.sz_filebuffer[i]))
            i++;
        if (i >= f_inifile.i_sc_endpos)
            return FALSE;

        b_skip = FALSE;
        switch (f_inifile.sz_filebuffer[i])
        {
            case '#':
                // a comment line
                b_skip = TRUE;
                break;
#if 0
            case '[':
                // next section begin mark -- [
                // we can't continue if we run into next '[' of next section
                return FALSE;
#endif
            default:
                if (strnicmp(f_inifile.sz_filebuffer + i, psz_key, i_key_len) == 0)
                {
                    //======================================================================
                    // key matched, try to find value
                    //======================================================================
                    i += i_key_len;

                    // 1. skip space and tab
                    while (i < f_inifile.i_sc_endpos && (f_inifile.sz_filebuffer[i] == ' ' ||
                        f_inifile.sz_filebuffer[i] == '\t'))
                        i++;
                    if (i >= f_inifile.i_sc_endpos)
                        return FALSE;

                    // 2. try to find '='
                    if (f_inifile.sz_filebuffer[i] == '=')
                    {
                        //====================================================================
                        // '=' found, get kay value
                        //====================================================================
                        i++;
                        // skip space and tab
                        while (i < f_inifile.i_sc_endpos && (f_inifile.sz_filebuffer[i] == ' ' ||
                            f_inifile.sz_filebuffer[i] == '\t'))
                            i++;
                        if (i >= f_inifile.i_sc_endpos)
                            return TRUE;

                        if (f_inifile.sz_filebuffer[i] == '\n')  // add by eleqian 2012-5-19
                        {
                            psz_value[0] = '\0';
                            f_inifile.i_value_startpos = i;
                            f_inifile.i_value_endpos = i - 1;
                        }
                        else
                        {
                            // search the end of the key value
                            j = i;
                            while (j < f_inifile.i_sc_endpos && f_inifile.sz_filebuffer[j] != '\n')
                                j++;
                            j--;
                            while (f_inifile.sz_filebuffer[j] == ' ' || f_inifile.sz_filebuffer[j] == '\t')
                                j--;

                            // copy the key value
                            strncpy(psz_value, f_inifile.sz_filebuffer + i, j - i + 1);
                            *(psz_value + j - i + 1) = '\0';

                            f_inifile.i_value_startpos = i;
                            f_inifile.i_value_endpos = j;
                        }

                        DBGPRINT(("GetString -- value of %s is: %s\n", psz_key, psz_value));

                        return TRUE;
                    }
                    else
                    {
                        //====================================================================
                        // no matching '=', ignore the line
                        //====================================================================
                        b_skip = TRUE;
                    }
                }
                else
                {
                    //======================================================================
                    // key not matched, ignore the line and forward
                    //======================================================================
                    b_skip = TRUE;
                }
                break;
        }

        if (b_skip)
        {
            // ignore the line and forward
            while (i < f_inifile.i_filesize && f_inifile.sz_filebuffer[i] != '\n')
                i++;
            if (i >= f_inifile.i_filesize)
                return FALSE;
            i++; // Jump to the next line
        }
    }

    return FALSE;
}

/*******************************************************************************
 *   desc: set a string value by key
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *         const char * psz_key         -- key name
 *         const char * psz_value       -- key value
 *------------------------------------------------------------------------------
 * return: TRUE   -- key value writen to buffer
 *******************************************************************************/
int IniSetString(const char *psz_section, const char *psz_key, const char *psz_value)
{
    char sz_value[M_MAX_VALUE_BUFFER_SIZE];
    int i_oldvaluelen = 0; // lenght of old value
    int i_newvaluelen = 0; // lenght of new value
    long i = 0;
    long i_temp = 0;

    // file not opened
    if (f_inifile.p_filename == NULL)
        return FALSE;

    //DBGPRINT(( "\nSetString -- to search section: %s\n", psz_section ));
    if (IniSearchSection(psz_section) == FALSE)
    {
        //==========================================================================
        // section not found, we append the section and key value
        // at the end of buffer
        //==========================================================================
        memset(sz_value, 0, sizeof(sz_value));
        // 两个\n会在保存时替换为\r\n
        sprintf(sz_value, "\n\n[%s]\n\n%s = %s\n\n", psz_section, psz_key, psz_value);
        i_temp = strlen(sz_value);
        strncpy(f_inifile.sz_filebuffer + f_inifile.i_filesize, sz_value, strlen(sz_value));
        f_inifile.i_filesize += i_temp;
        f_inifile.b_bufferchanged = TRUE;
        return TRUE;
    }

    if (IniGetString(psz_section, psz_key, sz_value))
    {
        //==========================================================================
        // section and key found, replace value
        //==========================================================================
        i_oldvaluelen = f_inifile.i_value_endpos - f_inifile.i_value_startpos + 1;
        i_newvaluelen = strlen(psz_value);

        //if (i_oldvaluelen < 0)  // add by eleqian
        //    i_oldvaluelen = 0;

        //DBGPRINT(( "SetString -- before update, file size = %d\n", i_filesize ));
        if (i_newvaluelen > i_oldvaluelen)
        {
            // new value is longer than old value ************************************
            // 1. get more space by moving content backward
            i_temp = i_newvaluelen - i_oldvaluelen;
            for (i = f_inifile.i_filesize - 1; i >= f_inifile.i_value_endpos; i--)
            {
                f_inifile.sz_filebuffer[i + i_temp] = f_inifile.sz_filebuffer[i];
            }
            f_inifile.i_filesize += i_temp;
            f_inifile.sz_filebuffer[f_inifile.i_filesize + 1] = '\0';
        }
        else if (i_newvaluelen < i_oldvaluelen)
        {
            // new value is shorter than old value ***********************************
#if 1
            // 1. cut some space by moving content forward
            i_temp = i_oldvaluelen - i_newvaluelen;
            for (i = f_inifile.i_value_endpos + 1; i < f_inifile.i_filesize; i++)
            {
                f_inifile.sz_filebuffer[i - i_temp] = f_inifile.sz_filebuffer[i];
            }
            f_inifile.i_filesize -= i_temp;
            memset(f_inifile.sz_filebuffer + f_inifile.i_filesize, 0, i_temp);
#else
            // 1. replace the following chars with spaces
            i_temp = i_oldvaluelen - i_newvaluelen;
            for (i = 0; i < i_temp; i++)
            {
                f_inifile.sz_filebuffer[f_inifile.i_value_endpos - i] = ' ';
            }
#endif
        }
        else
        {
            // same length ***********************************************************
            // 1. nothing need to do.
        }

        // 2. write new value to buffer
        strncpy(f_inifile.sz_filebuffer + f_inifile.i_value_startpos, psz_value, i_newvaluelen);
        //DBGPRINT(( "SetString -- after  update, file size = %d\n", f_inifile.i_filesize ));
        f_inifile.b_bufferchanged = TRUE;
    }
    else
    {
        //==========================================================================
        // key not found, we add key value by inserting a new line
        //==========================================================================
        // 1. make new line
        memset(sz_value, 0, sizeof(sz_value));
        // 两个\n会在保存时替换为\r\n
        sprintf(sz_value, "\n\n%s = %s", psz_key, psz_value);
        i_temp = strlen(sz_value);

        // 2. move buffer for new line
        for (i = f_inifile.i_filesize; i >= f_inifile.i_sc_endpos; i--)
        {
            f_inifile.sz_filebuffer[i + i_temp] = f_inifile.sz_filebuffer[i];
        }

        // 3. copy new line to buffer
        strncpy(f_inifile.sz_filebuffer + f_inifile.i_sc_endpos, sz_value, i_temp);
        f_inifile.i_filesize += i_temp;
        f_inifile.b_bufferchanged = TRUE;
    }

    // search end position of content again
    IniSearchContentEnd(f_inifile.i_sc_startpos);

    return TRUE;
}

/*******************************************************************************
 *   desc: get a interger value by key
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *         const char * psz_key         -- key name
 *         int          i_default       -- default value
 *------------------------------------------------------------------------------
 * return: key value or default value
 *******************************************************************************/
int IniGetInteger(const char *psz_section, const char *psz_key, int i_default)
{
    char sz_buffer[M_MAX_INTVAL_BUFFER_SIZE];

    // file not opened
    if (f_inifile.p_filename == NULL)
        return i_default;

    if (IniGetString(psz_section, psz_key, sz_buffer))
    {
        DBGPRINT(("GetInteger -- key value is: %s\n", sz_buffer));
        //if( strlen(sz_buffer) > 2 )
        //{
        //    // maybe a hex value
        //    if( sz_buffer[0] == '0'  && ( sz_buffer[1]=='x' || sz_buffer[1]=='X' ) ) {
        //        return (int)(strtol(sz_buffer, (char **)NULL, 16));
        //    }
        //}
        //return  atoi(sz_buffer);

        // modified  by eleqian 2012-5-24
        return (int)(strtol(sz_buffer, (char **)NULL, 0));
    }

    return i_default;
}

/*******************************************************************************
 *   desc: set a interger value
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *         const char * psz_key         -- key name
 *         const int    i_value         -- key value
 *------------------------------------------------------------------------------
 * return: TRUE
 *******************************************************************************/
int IniSetInteger(const char *psz_section, const char *psz_key, const int i_value)
{
    char sz_buffer[M_MAX_INTVAL_BUFFER_SIZE];

    // file not opened
    if (f_inifile.p_filename == NULL)
        return FALSE;

    DBGPRINT(("SetInteger -- key value is: %d\n", i_value));
    memset(sz_buffer, 0, sizeof(sz_buffer));
    sprintf(sz_buffer, "%d", i_value);
    DBGPRINT(("SetInteger -- value buffer is: %s\n", sz_buffer));
    IniSetString(psz_section, psz_key, sz_buffer);

    return TRUE;
}

/*******************************************************************************
 *   desc: get a bool value by key
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *         const char * psz_key         -- key name
 *         bool         b_default       -- default value
 *------------------------------------------------------------------------------
 * return: key value or default value
 *******************************************************************************/
int IniGetBool(const char *psz_section, const char *psz_key, int b_default)
{
    char sz_buffer[M_MAX_INTVAL_BUFFER_SIZE];

    // file not opened
    if (f_inifile.p_filename == NULL)
        return b_default;

    if (IniGetString(psz_section, psz_key, sz_buffer))
    {
        DBGPRINT(("GetBool -- key value is: %s\n", sz_buffer));
        if (strnicmp(sz_buffer, "y", 1) == 0 || strnicmp(sz_buffer, "yes", 3) == 0 || strnicmp(sz_buffer,
            "true", 4) == 0)
            return TRUE;
        if (strnicmp(sz_buffer, "n", 1) == 0 || strnicmp(sz_buffer, "no", 3) == 0 || strnicmp(sz_buffer,
            "false", 4) == 0)
            return FALSE;
    }

    return b_default;
}

/*******************************************************************************
 *   desc: set a bool value
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *         const char * psz_key         -- key name
 *         const bool   b_value         -- key value
 *------------------------------------------------------------------------------
 * return: TRUE
 *******************************************************************************/
int IniSetBool(const char *psz_section, const char *psz_key, const int b_value)
{
    char sz_buffer[M_MAX_INTVAL_BUFFER_SIZE];

    // file not opened
    if (f_inifile.p_filename == NULL)
        return FALSE;

    memset(sz_buffer, 0, sizeof(sz_buffer));
    if (b_value)
        sprintf(sz_buffer, "%s", "true");
    else
        sprintf(sz_buffer, "%s", "false");
    IniSetString(psz_section, psz_key, sz_buffer);

    return TRUE;
}

#ifdef SUPPORT_REAL_VALUE
/*******************************************************************************
 *   desc: get a double value by key
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *         const char * psz_key         -- key name
 *         double       i_default       -- default value
 *------------------------------------------------------------------------------
 * return: key value or default value
 *******************************************************************************/
double IniGetDouble(const char *psz_section, const char *psz_key, double i_default)
{
    char sz_buffer[M_MAX_INTVAL_BUFFER_SIZE];

    //memset( sz_buffer, 0, sizeof(sz_buffer) );
    if (IniGetString(psz_section, psz_key, sz_buffer))
    {
        return atof(sz_buffer);
    }

    return i_default;
}

/*******************************************************************************
 *   desc: set a double value
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *         const char * psz_key         -- key name
 *         const double i_value         -- key value
 *------------------------------------------------------------------------------
 * return: TRUE
 *******************************************************************************/
int IniSetDouble(const char *psz_section, const char *psz_key, const double i_value)
{
    char sz_buffer[M_MAX_INTVAL_BUFFER_SIZE];

    memset(sz_buffer, 0, sizeof(sz_buffer));
    sprintf(sz_buffer, "%g", i_value);
    IniSetString(psz_section, psz_key, sz_buffer);

    return TRUE;
}

#endif

/*******************************************************************************
 *   desc: search a section
 *------------------------------------------------------------------------------
 *  param: const char * psz_section     -- section name
 *------------------------------------------------------------------------------
 * return: TRUE   -- section found
 *         FALSE  -- section not found
 *******************************************************************************/
int IniSearchSection(const char *psz_section)
{
    long i = 0;
    int b_skip = FALSE;

    f_inifile.b_sectionfound = FALSE;

    // file error
    if (f_inifile.p_filename == NULL)
        return FALSE;

    // section name can't be null
    if (NULL == psz_section || strlen(psz_section) == 0)
        return FALSE;

    // same section name to the previous one
    if (strnicmp(f_inifile.sz_lastsection, psz_section, strlen(psz_section)) == 0)
    {
        f_inifile.b_sectionfound = TRUE;
        return TRUE;
    }

    while (i < f_inifile.i_filesize)
    {
        // skip space, tab and \n
        while (i < f_inifile.i_filesize && isspace(f_inifile.sz_filebuffer[i]))
            i++;
        if (i >= f_inifile.i_filesize)
            return FALSE;

        b_skip = FALSE;
        switch (f_inifile.sz_filebuffer[i])
        {
            case '#':
                // comment
                b_skip = TRUE;
                break;

            case '[':
                // section begin mark -- [
                i++;
                while (i < f_inifile.i_filesize && (f_inifile.sz_filebuffer[i] == ' ' ||
                    f_inifile.sz_filebuffer[i] == '\t'))
                    i++;
                if (i >= f_inifile.i_filesize)
                    return FALSE;

                if (strnicmp(f_inifile.sz_filebuffer + i, psz_section, strlen(psz_section)) == 0)
                {
                    // found section name, we try to seek ']'
                    i += strlen(psz_section);
                    while (i < f_inifile.i_filesize && (f_inifile.sz_filebuffer[i] == ' ' ||
                        f_inifile.sz_filebuffer[i] == '\t'))
                        i++;
                    if (i >= f_inifile.i_filesize)
                        return FALSE;

                    if (f_inifile.sz_filebuffer[i] == ']')
                    {
                        // ']' found, so we:

                        // 1. save section name to sz_lastsection
                        memset(f_inifile.sz_lastsection, 0, sizeof(f_inifile.sz_lastsection));
                        sprintf(f_inifile.sz_lastsection, "%s", psz_section);

                        // 2. get start and end position of section content
                        i++;
                        IniSearchContentStart(i);
                        IniSearchContentEnd(f_inifile.i_sc_startpos);
                        DBGPRINT(("\nSearchSection -- section content start at %d, end at %d\n",
                            f_inifile.i_sc_startpos, f_inifile.i_sc_endpos));
                        f_inifile.b_sectionfound = TRUE;
                        return TRUE;
                    }
                    else
                    {
                        // no matching ']'
                        b_skip = TRUE;
                    }
                }
                else
                {
                    // section name not match
                    b_skip = TRUE;
                }
                break;

            default:
                // other
                b_skip = TRUE;
                break;
        }

        if (b_skip)
        {
            // ignore the line and forward
            while (i < f_inifile.i_filesize && f_inifile.sz_filebuffer[i] != '\n')
                i++;
            if (i >= f_inifile.i_filesize)
                return FALSE;
            i++; // Jump to the next line
        }
    }

    return FALSE;
}

/*******************************************************************************
 *   desc: search start position of section content
 *------------------------------------------------------------------------------
 *  param: const long i_position  -- next position to ']'<section name end mark>
 *------------------------------------------------------------------------------
 * return: TRUE     -- found
 *******************************************************************************/
int IniSearchContentStart(const long i_position)
{
    long i = 0;
    long i_temp = 0;

    i = i_position;

    // we ignore the rest of sectio name line
    while (i < f_inifile.i_filesize && f_inifile.sz_filebuffer[i] != '\n')
        i++;
    if (f_inifile.sz_filebuffer[i] == '\n')
        i++;

    // if reach end of file, we append some \n
    if (i >= f_inifile.i_filesize)
    {
        for (i_temp = 0; i_temp < 2; i_temp++)
        {
            f_inifile.sz_filebuffer[i + i_temp] = '\n';
        }
        f_inifile.i_sc_startpos = i + 1;
        f_inifile.i_filesize += 2;
        f_inifile.b_bufferchanged = TRUE;
        return TRUE;
    }

    // not reach end of file
    f_inifile.i_sc_startpos = i;

    // if it's '['(which means no enough \n between setciotns), we insert some \n
    if (f_inifile.sz_filebuffer[i] == '[')
    {
        for (i_temp = f_inifile.i_filesize; i_temp >= f_inifile.i_sc_startpos; i_temp--)
        {
            f_inifile.sz_filebuffer[i_temp + 2] = f_inifile.sz_filebuffer[i_temp];
        }
        for (i_temp = 0; i_temp < 2; i_temp++)
        {
            f_inifile.sz_filebuffer[f_inifile.i_sc_startpos + i_temp] = '\n';
        }
        f_inifile.b_bufferchanged = TRUE;
        f_inifile.i_filesize += 2;
    }

    return TRUE;
}

/*******************************************************************************
 *   desc: search end position of section content
 *------------------------------------------------------------------------------
 *  param: const long i_startpos      -- start position of section content
 *------------------------------------------------------------------------------
 * return: TRUE   -- found
 ******************************************************************************/
int IniSearchContentEnd(const long i_startpos)
{
    long i = 0;
    long i_temp = 0;

    i = i_startpos;

    // try to serach position of next '['
    while (i < f_inifile.i_filesize)
    {
        // skip space, tab and \n
        while (i < f_inifile.i_filesize && isspace(f_inifile.sz_filebuffer[i]))
            i++;

        //==========================================================================
        // 1. found '[', we try to find a position before '['
        //==========================================================================
        if (f_inifile.sz_filebuffer[i] == '[')
        {
            //DBGPRINT(( "SearchContentEnd -- position of next [ = %ld\n", i ));
            // skip \n backward
            i_temp = i;
            while (i > i_startpos + 1 && f_inifile.sz_filebuffer[i - 1] == '\n')
                i--;
            f_inifile.i_sc_endpos = i;

            // if no enough \n between sections, we insert some \n
            if (f_inifile.i_sc_endpos == i_temp)
            {
                for (i = f_inifile.i_filesize; i >= i_temp; i--)
                {
                    f_inifile.sz_filebuffer[i + 2] = f_inifile.sz_filebuffer[i];
                }
                for (i = 0; i < 2; i++)
                {
                    f_inifile.sz_filebuffer[i_temp + i] = '\n';
                }
                f_inifile.i_filesize += 2;
                f_inifile.b_bufferchanged = TRUE;
            }
            return TRUE;
        }
        else
        {
            // ignore the line and forward
            while (i < f_inifile.i_filesize && f_inifile.sz_filebuffer[i] != '\n')
                i++;
            if (f_inifile.sz_filebuffer[i] == '\n')
                i++;
        }

        //==========================================================================
        // 2. if reach end of file
        //==========================================================================
        if (i == f_inifile.i_filesize)
        {
            // skip \n backward
            while (i > i_startpos + 1 && f_inifile.sz_filebuffer[i - 1] == '\n')
                i--;
            f_inifile.i_sc_endpos = i;

            // we append some \n if not enough
            if (i >= f_inifile.i_filesize - 1)
            {
                i = f_inifile.i_filesize;
                for (i_temp = 0; i_temp < 2; i_temp++)
                {
                    f_inifile.sz_filebuffer[i_temp + i] = '\n';
                }
                f_inifile.i_filesize += 2;
                f_inifile.b_bufferchanged = TRUE;
            }
            return TRUE;
        }
    }

    return TRUE;
}
