/*
 * �ַ�����������
 * ��Ȩ���� (C) 2011-2012 eleqian
 * [6/7/2012]
 */

#include <base.h>
//#include <mrc_exb.h>
#include "xl_base.h"
//#include "String.h"
/*
//ת��Unicode�ַ���Ϊ��ֵ
int32 watoi(char *uniStr)
{
    int32 sLen, i, rValue;
    char *asciiStr;

    sLen = wstrlen(uniStr) / 2;
    if (0 == sLen)
        return 0;

    asciiStr = (char*)malloc(sLen + 1);

    for (i = 0; i < sLen; i++)
    {
        asciiStr[i] = uniStr[i * 2 + 1];
    }

    asciiStr[sLen] = '\0';
    rValue = atoi(asciiStr);
    free(asciiStr);

    return rValue;
}

//ת����ֵΪUnicode�ַ���
*/char *witoa(int32 value)
{
    char inValue[13] = {0};
    char *outStr;
    int32 sLen, i;

    sprintf(inValue, "%d", value);
    sLen = strlen(inValue);
    outStr = (char*)malloc(sLen * 2 + 2);
    memset(outStr, 0, sLen * 2 + 2);

    for (i = 0; i < sLen; i++)
    {
        outStr[i * 2 + 1] = inValue[i];
    }

    return outStr;
}

/*---------------------------------------------------------------------------*/

//���ַ���ת��Ϊ��д
char *strupr(char *str)
{
    char *p;

    for (p = str; '\0' != *p; p++)
    {
        if (*p >= 'a' && *p <= 'z')  // Сд��ĸ
        {
            *p -= 32;
        }
    }

    return str;
}

//���ַ���ת��Ϊ��д
char *strlwr(char *str)
{
    char *p;

    for (p = str; '\0' != *p; p++)
    {
        if (*p >= 'A' && *p <= 'Z')  // ��д��ĸ
        {
            *p += 32;
        }
    }

    return str;
}

// ���ַ���ĩβ�����ַ�
/*
char *strrchr(char * str, int ch)
{

    char *p = (char *)str;

    while (*p) 
        p++;

    while (p-- != str && *p != (char)ch)
        ;

    if (*p == (char)ch)
        return p;

    return NULL;
}
*/
//�����ִ�Сд�Ƚ��ַ���
int stricmp(char *str1, char *str2)
{
    uint8 *dst = (unsigned char*)str1;
    uint8 *src = (unsigned char*)str2;
    uint8 f, l;
    
    do {
        if (((f = *(dst++)) >= 'A') && (f <= 'Z'))
            f -= ('A' - 'a');
        
        if (((l = *(src++)) >= 'A') && (l <= 'Z'))
            l -= ('A' - 'a');
    } while (f && (f == l));
    
    return (f - l);
}

// �����ִ�Сд�Ƚ��ַ���ǰn���ַ�
int strnicmp(char *dst, char *src, int32 count)
{
    int ch1, ch2;

    do {
        if (((ch1 = (unsigned char)(*(dst++))) >= 'A') &&(ch1 <= 'Z'))
            ch1 += 0x20;

        if (((ch2 = (unsigned char)(*(src++))) >= 'A') &&(ch2 <= 'Z'))
            ch2 += 0x20;

    } while (--count && ch1 && (ch1 == ch2));

    return (ch1 - ch2);
}

//�����ַ���
char *strdup(char *pcStr)
{
    char *pcTmp = NULL;
    int32 slen = 0;

    if (NULL == pcStr)
        return NULL;

    slen = strlen(pcStr) + 1;
    pcTmp = (char*)malloc(slen);
    if(NULL != pcTmp)
        memcpy(pcTmp, pcStr, slen);

    return pcTmp;
}

// ת��gb�ַ���Ϊunicode����free
char *strc2u(char *gbstr)
{
    int32 slen;
    char *uniStr;

    if (NULL == gbstr)
        return NULL;

    slen = strlen(gbstr);
    slen = slen * 2 + 2;
    uniStr = (char *)malloc(slen);
    if(NULL == uniStr)
        return NULL;
    GBToUni(gbstr, uniStr, slen);

    return uniStr;
}

// ת��unicode�ַ���Ϊgb����free
char *stru2c(char *unistr)
{
    int32 slen;
    char *gbStr;

    if (NULL == unistr)
        return NULL;

    slen = wstrlen(unistr);
    slen = slen + 1;
    gbStr = (char *)malloc(slen);
    if(NULL == gbStr)
        return NULL;
    UniToGB(unistr, gbStr, slen);

    return gbStr;
}

/*---------------------------------------------------------------------------*/

// unicode�ַ�������
/*
int wstrlen(char *str)
{
    int i = 0;

    while (str[i] || str[i + 1]) 
        i += 2;

    return i;
}
*/
// unicode�ַ����Ƚ�
int wstrcmp(char *str1, char *str2)
{
    while ((str1[0] || str1[1]) && str1[0] == str2[0] && str1[1] == str2[1])
    {
        str1 += 2; 
        str2 += 2;
    }

    return str1[0] == str2[0] ? str1[1] - str2[1] : str1[0] - str2[0];
}

// unicode�ַ�������
char *wstrcpy(char *dst, char *src)
{
    int i = 0;

    while (src[i] || src[i + 1]) 
    {
        dst[i] = src[i];
        dst[i+1] = src[i + 1];
        i += 2;
    }

    dst[i] = dst[i + 1] = '\0';

    return dst;
}

// unicode�ַ�������ָ������
char *wstrncpy(char *dst, char *src, int32 size)
{
    int i = 0;

    size -= 2;

    while (src[i] || src[i + 1]) 
    {
        if (i >= size) break;

        dst[i] = src[i];
        dst[i + 1] = src[i + 1];
        i += 2;
    }

    dst[i] = dst[i + 1] = '\0';

    return dst;
}

// unicode�ַ�������
char *wstrcat(char *dst, char *src)
{
    int len = wstrlen(dst);
    return wstrcpy(dst + len, src);
}

// unicode�ַ�������
char *wstrdup(char *str)
{
    int len = 0;
    char *pDest = NULL;

    if (NULL == str)
        return NULL;

    len = wstrlen(str) + 2;
    pDest = (char*)malloc(len);
    if(NULL != pDest)
        memcpy(pDest, str, len);

    return pDest;
}

/*---------------------------------------------------------------------------*/

//UTF8ת��ΪUnicode
//������UTF8�ַ�����Unicode����������������С
//���أ�������ʹ�ô�С
int UTF8ToUni(char *utf8str, char *unistr, int32 size)
{
    int32 i = 0, u = 0;
    uint8 *utf8, *unicode;

    utf8 = (unsigned char*)utf8str;
    unicode = (unsigned char*)unistr;

    while (utf8[i] && u < size - 2)
    {
        if((utf8[i] & 0x80) == 0)
        {
            // one byte 0...
            unicode[u] = 0;
            unicode[u + 1] = utf8[i++];
        }else if((utf8[i] & 0x20) == 0){
            // two bytes 110... 10...
            unicode[u] = (unsigned char)((utf8[i] & 0x1f) >> 2);
            unicode[u + 1] = (unsigned char)((utf8[i] << 6) & 0xff) | (utf8[i + 1] & 0x3f);
            i += 2;
        }else{
            // three bytes 1110... 10... 10...
            unicode[u] = (unsigned char)((utf8[i] << 4) & 0xff) | ((utf8[i + 1] & 0x3f) >> 2);
            unicode[u + 1] = (unsigned char)((utf8[i + 1] << 6) & 0xff) | (utf8[i + 2] & 0x3f);
            i += 3;
        }

        u += 2;
    }

    unicode[u] = '\0';
    unicode[u + 1] = '\0';

    return u;
}

//Unicodeת��ΪUTF8
//������Unicode�ַ�����UTF8����������������С
//���أ�������ʹ�ô�С
int UniToUTF8(char *unistr, char *utf8str, int32 size)
{
    int32 u = 0, i = 0;
    uint8 *unicode, *utf8;

    unicode = (unsigned char *)unistr;
    utf8 = (unsigned char *)utf8str;

    while ((unicode[u] || unicode[u + 1]) && i < size - 1)
    {
        if (unicode[u] == 0 && unicode[u + 1] < 128) {
            // 0 - 7 bits
            utf8[i++] = unicode[u + 1];
        } else if((unicode[u] & 0xf8) == 0) {
            // 8 - 11 bits
            utf8[i++] = 0xc0 | ((unicode[u] << 2) & 0xff) | (unicode[u + 1] >> 6);
            utf8[i++] = 0x80 | (unicode[u + 1] & 0x3f);
        } else {
            // 12 - 16 bits
            utf8[i++] = 0xe0 | (unicode[u] >> 4);
            utf8[i++] = 0x80 | ((unicode[u] << 2) & 0x3f) | (unicode[u + 1] >> 6);
            utf8[i++] = 0x80 | (unicode[u + 1] & 0x3f);
        }

        u += 2;
    }

    utf8[i] = '\0';

    return i;
}

// ת��ascii�ַ���Ϊunicode�ַ���
int Asc2Uni(char *input, char *output, int32 outlen)
{
    int32 i;

    if (NULL == input || NULL == output)
        return -1;

    for (i = 0; input[i] != '\0' && outlen >= 4; i++)
    {
        output[i * 2] = '\0';
        output[i * 2 + 1] = input[i];
        outlen -= 2;
    }

    output[i * 2] = '\0';
    output[i * 2 + 1] = '\0';

    return (i * 2);
}

// ת��unicode�ַ���Ϊascii�ַ���
int Uni2Asc(char *input, char *output,int32 outlen)
{
    int32 i;

    if (NULL == input || NULL == output)
        return -1;

    for (i = 0; input[i * 2 + 1] != '\0' && outlen >= 2; i++)
    {
        output[i] = input[i * 2 + 1];
        outlen--;
    }

    output[i] = '\0';

    return (i);
}

// ת��UnicodeΪGB2312
// ������Unicode�ַ�����GB2312����������������С
// ���أ�gb����С
int UniToGB(char *uniStr, char *gbBuf, int32 bufSize)
{
    char *gbStr;
    int32 ret;
    int32 gbSize;
    int32 uniSize;
    int32 outSize = 0;

    gbStr = (char*)malloc(bufSize);//�������
    if (NULL != gbStr)
    {
        gbSize = bufSize;
        uniSize = wstrlen(uniStr);

        ret = mrc_unicodeToGb2312((unsigned char*)uniStr, uniSize, &gbStr, &gbSize);
        if (MR_SUCCESS == ret)
        {
            gbSize = strlen(gbStr);
            outSize = (gbSize > bufSize - 1) ? (bufSize - 1) : gbSize;
            memcpy(gbBuf, gbStr, outSize);
        }
        free(gbStr);
    }

    gbBuf[outSize] = '\0';

    return outSize;
}

// �������ʹ��ϵͳ����ת��
// ò��ϵͳ������bug������Ŀǰʹ�ô���ʵ��ת��
//#define USE_SYS_GBCONV  

#ifdef USE_SYS_GBCONV

// ת��GB2312ΪUnicode
// ������GB2312�ַ�����Unicode����������������С
// ���أ�unicode����С
int GBToUni(char *gbStr, char *uniBuf, int32 bufSize)
{
    char *uniStr = NULL;
    int32 uniSize = 0;
    int32 outSize = 0;

    uniStr = (char*)mrc_c2uVM((char*)gbStr, NULL, &uniSize);
    if (NULL != uniStr)
    {
        outSize = (uniSize > bufSize - 2) ? (bufSize - 2) : uniSize;
        memcpy(uniBuf, uniStr, outSize);
        mrc_c2uVMfree(uniStr, uniSize);
    }
    uniBuf[outSize] = '\0';
    uniBuf[outSize + 1] = '\0';

    return outSize - 2;
}

#else  /* !USE_SYS_GBCONV */

static uint8 *gb2uTable;  // ����ת����
static int32 gb2uCount;   // �������

// ��ʼ��gbתunicode���
static int32 GBCodeTableInit(void)
{
    char *fbuf;
    int32 fsize;
    int32 ret = -1;

    fbuf = mrc_readFileFromMrp("gb.bin", &fsize, 0);
    if (NULL != fbuf)
    {
        gb2uTable = malloc(fsize);
        if (NULL != gb2uTable)
        {
            memcpy(gb2uTable, fbuf, fsize);
            gb2uCount = fsize;
            ret = 0;
        }
        mrc_freeFileData(fbuf, fsize);
    }

    return ret;
}

// ����ת������GB2312ת��unicode
static unsigned char *GBCodeToUnicode(uint8 *gbCode)
{
    uint8 *p_map = NULL;
    uint32 i;

    if ((*(gbCode + 1) >= 0xa1) && (*(gbCode + 1) <= 0xfe))
    {
        if ((*gbCode >= 0xa1) && (*gbCode <= 0xa9))
        {
            i= ((*gbCode - 0xa1) * 94 + (*(gbCode + 1) - 0xa1)) * 2;
            p_map = &gb2uTable[i];
        }
        else if ((*gbCode >= 0xb0) && (*gbCode <= 0xf7))
        {
            i = ((*gbCode - 0xb0 + 9) * 94 + (*(gbCode + 1) - 0xa1)) * 2;
            p_map = &gb2uTable[i];
        } 
    } 

    return p_map;
}

/*
 * ˵��
 * ������ gbCode����ת����gb�ַ���
 *   gbLen��gb�ַ����ֽڳ���
 *     unicode������ת�����unicode�����������ڴ��Լ����룩
 * ���أ� �ɹ���ת����unicode����
 *    ʧ�ܣ�-1
 */
int GBToUni(char *gbStr, char *uniBuf, int32 bufSize)
{
    uint8 *gbCode = (unsigned char *)gbStr;
    uint8 *unicode = (unsigned char *)uniBuf;
    uint8 *pReturn = NULL;
    int32 i = 0, j = 0;

    if(!gbCode || !unicode || bufSize <= 0) 
        return -1;

    // ��ʼ��gbתunicode���
    if (NULL == gb2uTable)
    {
        int32 ret;

        ret = GBCodeTableInit();
        if (0 != ret || NULL == gb2uTable)
        {
            return -1;
        }
    }

    // ѭ��ת�������ַ�
    while ('\0' != gbCode[i] && j < bufSize - 2)
    {
        if (gbCode[i] < 0x80)
        {
            unicode[j] = 0;
            unicode[j + 1] = gbCode[i];
            i++;
        }
        else
        {
            pReturn = GBCodeToUnicode(&gbCode[i]);

            if (NULL != pReturn)
            {
                unicode[j] = *(pReturn + 1);
                unicode[j + 1] = *pReturn;
                i++;

                // �����жϷ�ֹԽ��'\0'������
                if ('\0' != gbCode[i])
                    i++;
            }
            else
            {
                // ȫ�ǿո�
                /*unicode[j] = 0x30;
                unicode[j + 1] = 0x00;*/
                // ��
                unicode[j] = 0x25;
                unicode[j + 1] = 0xa1;
                i++;
            }
        }

        j += 2;
    }

    unicode[j] = '\0';
    unicode[j + 1] = '\0';

    return j;
}

#endif  /* !USE_SYS_GBCONV */

/*---------------------------------------------------------------------------*/

// ����BMH���ַ���
int BMH_BuildTable(uint32 *shift, uint32 shift_size, void *in_pattern, uint32 pattern_size)
{
    uint32 byte_nbr;
    uint8 *pattern = (unsigned char*)in_pattern;

    if (pattern == NULL || shift == NULL)
        return (-1);

    for (byte_nbr = 0; byte_nbr < shift_size; byte_nbr++)
        shift[byte_nbr] = pattern_size + 1;

    for (byte_nbr = 0; byte_nbr < pattern_size; byte_nbr++)
        shift[pattern[byte_nbr]] = pattern_size - byte_nbr;

    return 0;
}

// ����BMHƥ��
void *BMH_Ex(uint32 *shift, void *in_block, uint32 block_size, void *in_pattern, uint32 pattern_size)
{
    uint32 byte_nbr, match_size, limit;
    uint8 *match_ptr = NULL;
    uint8 *block = (unsigned char *)in_block;
    uint8 *pattern = (unsigned char *)in_pattern;

    if (block == NULL || pattern == NULL || shift == NULL)
        return NULL;

    // ���ҵĴ���Ӧ��С�� ���ݳ���
    if (block_size < pattern_size)
        return NULL;

    if (pattern_size == 0)  // �մ�ƥ���һ��
        return (void *)block;

    // ��ʼ�������ݿ飬ÿ��ǰ����λ���е�����
    limit = block_size - pattern_size + 1;
    for (byte_nbr = 0; byte_nbr < limit; byte_nbr += shift[block[byte_nbr + pattern_size]]) 
    {
        if (block[byte_nbr] == *pattern)
        {
            // �����һ���ֽ�ƥ�䣬��ô����ƥ��ʣ�µ�
            match_ptr = block + byte_nbr + 1;
            match_size = 1;

            do {
                if (match_size == pattern_size)
                    return (void *)(block + byte_nbr);
            } while (*match_ptr++ == pattern[match_size++]);
        }
    }

    return NULL;
}

// BMH�ַ���ƥ���㷨
// ���������ݣ����ݴ�С��ƥ�䴮��ƥ�䴮��С
// ���أ�ƥ��λ��ָ�룬ʧ�ܷ���NULL
void *BMH(void *in_block, uint32 block_size, void *in_pattern, uint32 pattern_size)
{
    int32 ret;
    uint32 *bad_char_skip;
    void *match;

    if (NULL == in_block || NULL == in_pattern)
        return NULL;

    bad_char_skip = malloc(256 * sizeof(int));
    if (NULL == bad_char_skip)
        return NULL;

    ret = BMH_BuildTable(bad_char_skip, 256, in_pattern, pattern_size);
    match = BMH_Ex(bad_char_skip, in_block, block_size, in_pattern, pattern_size);
    free(bad_char_skip);

    return match;
}

///---------------------------------------------------------------------------
/*
// ��ʼ��
int String_Init(void)
{
#ifndef USE_SYS_GBCONV
    if (NULL == gb2uTable)
    {
       return GBCodeTableInit();
    }
#endif

    return 0;
}

// �ͷ���Դ
int String_End(void)
{
#ifndef USE_SYS_GBCONV
    if (NULL != gb2uTable)
    {
        free(gb2uTable);
        gb2uTable = NULL;
    }
#endif

    return 0;
}
*/
//struct CHARBUF{
//    void *orginBuf;
//    int32 orginLen;
//    void *freeBuf;
//    int8 isOrgin;
//    int8 isFree;    
//}charbuf;
//
//int All_init(void)
//{
//    mrc_memset(&charbuf,0,sizeof(struct CHARBUF));
//    return 0;
//}
//
//int All_free(void)
//{
//    if (charbuf.isOrgin==TRUE)
//        mrc_freeOrigin(charbuf.orginBuf,charbuf.orginLen);
//    if (charbuf.isFree==TRUE)
//        mrc_free(charbuf.freeBuf);
//    mrc_memset(&charbuf,0,sizeof(struct CHARBUF));
//    return 0;
//}
//
//PSTR UniToGB(PCWSTR unicode)
//{
//    int32 inLen,outLen;
//
//    outLen=514;
//    if (charbuf.isFree==FALSE)
//    {
//        charbuf.freeBuf = mrc_malloc(outLen);
//        charbuf.isFree=TRUE;
//    }
//
//    inLen = mrc_wstrlen((char*)unicode);
//    mrc_unicodeToGb2312((uint8 *)unicode, inLen, (uint8**)&charbuf.freeBuf, &outLen);
//    return charbuf.freeBuf;
//}
//
//PWSTR GBToUni(char* str)
//{
//    if(charbuf.isOrgin==TRUE)
//    {
//        mrc_freeOrigin(charbuf.orginBuf,charbuf.orginLen);
//    }
//    else
//    {
//        charbuf.isOrgin=TRUE;
//    }
//    charbuf.orginBuf = mrc_c2uVM(str, NULL, &charbuf.orginLen); 
//    return (PWSTR)charbuf.orginBuf;
//}
