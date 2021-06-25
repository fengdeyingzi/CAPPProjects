#ifndef __CINIFILE_H__
#define __CINIFILE_H__

//*************************  begin of -- macro definitions  ********************
#define M_MAX_BUFFER_SIZE           6144
#define M_MAX_VALUE_BUFFER_SIZE     256
#define M_MAX_INTVAL_BUFFER_SIZE    32
#define M_MAX_SECTION_SIZE          32
//*************************  **end of -- macro definitions  ********************

//*************************  begin of -- type definitions  *********************
typedef struct
{
    char *p_filename;
    long i_filesize;

    char *sz_filebuffer;
    int  b_bufferchanged;                      // if TRUE, save file when close

    char sz_lastsection[M_MAX_SECTION_SIZE];   // previous section name
    int  b_sectionfound;
    long i_sc_startpos;                        // start/end position of the
    long i_sc_endpos;                          // following lines of section

    long i_value_startpos;                     // start/end position of key
    long i_value_endpos;                       // value
} IniFileData_TS;
//*************************  **end of -- type definitions  *********************

int IniOpenFile(const char *psz_file);
int IniCloseFile(void);

int IniGetString(const char *psz_section, const char *psz_key, char *psz_value);
int IniSetString(const char *psz_section, const char *psz_key, const char *psz_value);

int IniGetInteger(const char *psz_section, const char *psz_key, int i_default);
int IniSetInteger(const char *psz_section, const char *psz_key, const int i_value);

int IniGetBool(const char *psz_section, const char *psz_key, int b_default);
int IniSetBool(const char *psz_section, const char *psz_key, const int b_value);

#ifdef SUPPORT_REAL_VALUE
double IniGetDouble(const char *psz_section, const char *psz_key, double i_default);
int IniSetDouble(const char *psz_section, const char *psz_key, const double i_value);
#endif

int IniClearContent(void);

#endif // __CINIFILE_H__
