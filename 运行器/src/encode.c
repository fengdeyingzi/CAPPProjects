#include "encode.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include "tables.h"
#include <string.h>


///////////////////////
//编码转换，从GB2312转成unicode
 unsigned char *GBCodeToUnicode(const unsigned char *gbCode)
{
	unsigned char *p_map = 0;
	int i;

	if ((*(gbCode + 1) >= 0xa1) && (*(gbCode + 1) <= 0xfe))
	{
		if ((*gbCode >= 0xa1) && (*gbCode <= 0xa9))
		{
			i = ((*gbCode - 0xa1) * 94 + (*(gbCode + 1) - 0xa1))*2;
			p_map = (unsigned char*)&gb2uTable[i];
		}else if ((*gbCode >= 0xb0) && (*gbCode <= 0xf7))
		{
			i= ((*gbCode - 0xb0+9) *94 + (*(gbCode + 1) - 0xa1))*2;
			p_map = (unsigned char*)&gb2uTable[i];
		} 
	} 

	return p_map;
}

// 查找一个unicode字符对应的gb编码
static uint16 Unicode2GB(uint16 ucs)
{
	int First = 0;
	int Last = 717 - 1;
	int Mid;

	if (ucs >= 0x4E00 && ucs <= 0x9FA5) {
		return tab_ucs2gb[ucs - 0x4E00];
	} else {
		while (Last >= First) {
			Mid = (First + Last) >> 1;

			if (ucs < tab_symucs2gb[Mid].ucs) {
				Last = Mid - 1;
			} else if (ucs > tab_symucs2gb[Mid].ucs) {
				First = Mid + 1;
			} else if (ucs == tab_symucs2gb[Mid].ucs) {
				return tab_symucs2gb[Mid].gb;
			}
		}
	}

	return 0xffff;
}

//指定转码的长度
int gbToUCS2len(const unsigned char *gbCode, unsigned char *unicode,int len)
{
	int i=0, j=0;

	if(!gbCode || !gbCode[0] || !unicode) 
		return -1;

	while(gbCode[i])
	{
		if (gbCode[i] < 0x80)
		{
			unicode[j+1] = 0;
			unicode[j] = gbCode[i];
			i += 1;
		}else
		{
			const unsigned char *pReturn = GBCodeToUnicode(&gbCode[i]);

			if(pReturn )//&& (0 != *(pReturn))
			{
				unicode[j+1] = *(pReturn+1);
				unicode[j] = *pReturn;
			}else
			{//全角空格
				unicode[j+1] = 0x30;
				unicode[j] = 0x00;
			}

			i+=2;
		}

		j += 2;
		if(j>=len)break;
	}
unicode[j]=0;
unicode[j+1]=0;
	return j;
}


//GB2312 -> UCS2LE
int gbToUCS2(unsigned char *gbCode, unsigned char *unicode)
{
	int i=0, j=0;

	if(!gbCode || !gbCode[0] || !unicode) 
		return -1;

	while(gbCode[i])
	{
		if (gbCode[i] < 0x80)
		{
			unicode[j+1] = 0;
			unicode[j] = gbCode[i];
			i += 1;
		}else
		{
			const unsigned char *pReturn = GBCodeToUnicode(&gbCode[i]);

			if(pReturn )//&& (0 != *(pReturn))
			{
				unicode[j+1] = *(pReturn+1);
				unicode[j] = *pReturn;
			}else
			{//全角空格
				unicode[j+1] = 0x30;
				unicode[j] = 0x00;
			}

			i+=2;
		}

		j += 2;
	}
unicode[j]=0;
unicode[j+1]=0;
	return j;
}

char *UCS2ByteRev(char * str)
{
	char temp;
	int i=0;

	while(str[i] || str[i+1]){
		temp = str[i];
		str[i] = str[i+1];
		str[i+1] = temp;
		i += 2;
	}

	return str;
}


// 转换unicode小端字符串为gb
int UCS2ToGBString(const uint16 *uniStr, uint8 *gbBuf, int gbMaxLen)
{
	uint16 Gb;
	uint8 *gb = gbBuf;

	while (*uniStr && gbMaxLen > 0) {
		if ((*uniStr <= 0x7f)) {
			*gb++ = (uint8)(*uniStr & 0x00ff);
			gbMaxLen--;
		} else {
			Gb = Unicode2GB(*uniStr);
			*gb++ = (uint8)(Gb >> 8);
			*gb++ = (uint8)(Gb & 0x00ff);
			gbMaxLen -= 2;
		}
		uniStr++;
	}
	*gb = '\0';

	return gb - gbBuf;
}


// 转换utf8字符串为unicode小端
int UTF8ToUCS2String(const uint8 *utf8Str, uint16 *ucs2Buf, int ucs2MaxLen)
{
	uint16 *ucs2;
	uint8 v_Byte;

	ucs2 = ucs2Buf;

	if (ucs2 && utf8Str) {
		while ((v_Byte = *utf8Str) && (ucs2MaxLen-- > 0)) {
			if ((v_Byte & 0x80) == 0) {
				/* 1 Byte */
				*ucs2++ = v_Byte;
				utf8Str++;
			} else if ((v_Byte & 0xe0) == 0xc0) {
				/* 2 Bytes */
				*ucs2++ = ((v_Byte & 0x1f) << 6) | ((*(utf8Str + 1) & 0x3f));
				utf8Str += 2;
			} else if ((v_Byte & 0xf0) == 0xe0) {
				/* 3 Bytes */
				*ucs2++ = ((v_Byte & 0x0f) << 12)
						| ((*(utf8Str + 1) & 0x3f) << 6)
						| ((*(utf8Str + 2) & 0x3f));
				utf8Str += 3;
			} else {
				break;
			}
		}
		
		*ucs2 = 0;
	}

	return ucs2 - ucs2Buf;
}

// 转换utf8字符串为gb
int UTF8ToGBString(const uint8 *utf8Str, uint8 *gbBuf, int gbMaxLen)
{
	uint16 Ucs2, Gb;
	uint8 v_Byte;
	uint8 *gb;

	gb = gbBuf;

	if (gb && utf8Str) {
		while ((v_Byte = *utf8Str) && (gbMaxLen > 0)) {
			if ((v_Byte & 0x80) == 0) {
				/* 1 Byte */
				*gb++ = v_Byte;
				utf8Str++;
				gbMaxLen--;
			} else if ((v_Byte & 0xe0) == 0xc0) {
				/* 2 Bytes */
				Ucs2 = ((v_Byte & 0x1f) << 6) | ((*(utf8Str + 1) & 0x3f));
				Gb = Unicode2GB(Ucs2);
				*gb++ = (uint8)(Gb >> 8);
				*gb++ = (uint8)(Gb & 0x00ff);
				utf8Str += 2;
				gbMaxLen -= 2;
			} else if ((v_Byte & 0xf0) == 0xe0) {
				/* 3 Bytes */
				Ucs2 = ((v_Byte & 0x0f) << 12)
						| ((utf8Str[1] & 0x3f) << 6)
						| ((utf8Str[2] & 0x3f));
				Gb = Unicode2GB(Ucs2);
				*gb++ = (uint8)(Gb >> 8);
				*gb++ = (uint8)(Gb & 0x00ff);
				utf8Str += 3;
				gbMaxLen -= 2;
			} else {
				break;
			}
		}

		*gb = 0;
	}

	return gb - gbBuf;
}

// 转换gb字符串为utf8
int GBToUTF8String(const uint8 *gbStr, uint8 *utf8Buf, int utf8MaxLen)
{
    uint8 unicode[2];
    uint8 *utf8;
    const uint8 *ucs2;

    utf8 = utf8Buf;

    while (*gbStr && utf8MaxLen > 0)
    {
        if (*gbStr < 128) {
            // 0 - 7 bits
            *utf8++ = *gbStr;
            gbStr++;
        } else {
        	ucs2 = GBCodeToUnicode((uint8*)gbStr);
        	gbStr += 2;

            if (NULL != ucs2) {
                unicode[0] = ucs2[1];
                unicode[1] = ucs2[0];
            } else {
                // 全角空格
                /*unicode[0] = 0x30;
                unicode[1] = 0x00;*/
                // □
                unicode[0] = 0x25;
                unicode[1] = 0xa1;
            }

        	if((unicode[0] & 0xf8) == 0) {
				// 8 - 11 bits
				*utf8++ = 0xc0 | ((unicode[0] << 2) & 0xff) | (unicode[1] >> 6);
				*utf8++ = 0x80 | (unicode[1] & 0x3f);
			} else {
				// 12 - 16 bits
				*utf8++ = 0xe0 | (unicode[0] >> 4);
				*utf8++ = 0x80 | ((unicode[0] << 2) & 0x3f) | (unicode[1] >> 6);
				*utf8++ = 0x80 | (unicode[1] & 0x3f);
			}
        }
    }

    *utf8 = 0;

    return utf8 - utf8Buf;
}

//将Unicode小端转为UTF8
int UCS2ToUTF8(const uint8 *unicode, uint8 *utf8, int size)
{
	int u = 0, i = 0;

	//memset(utf8, 0, size);
	while((unicode[u] || unicode[u+1]) && i < size-1)
	{
		if(unicode[u] == 0 && unicode[u+1] < 128)
		{
			// 0 - 7 bits
			utf8[i++] = unicode[u+1];
		}else if((unicode[u] & 0xf8) == 0){
			// 8 - 11 bits
			utf8[i++] = 0xc0 | (unicode[u] << 2) | (unicode[u+1] >> 6);
			utf8[i++] = 0x80 | (unicode[u+1] & 0x3f);
		}else{
			// 12 - 16 bits
			utf8[i++] = 0xe0 | (unicode[u] >> 4);
			utf8[i++] = 0x80 | ((unicode[u] & 0x0f) << 2) | (unicode[u+1] >> 6);
			utf8[i++] = 0x80 | (unicode[u+1] & 0x3f);
		}

		u+=2;
	}
	utf8[i] = 0;

	return i;
}

int UCS2_strlen(const char * txt)
{
	int i=0;

	while(txt[i] || txt[i+1]) i += 2;

	return i;
}

//gb编码转unicode，
uint16 *mrc_c2u(char *cp, int32 *err, int32 *size)
{
    uint8 *ucp = (uint8 *)cp;
    const uint8 *pReturn;
    uint16 *uniBuf;
    int32 uniSize;
    uint32 chCount;
    uint32 i;

   // LOGI("mr_c2u(%#p,%#p,%#p)", cp, err, size);

    if (NULL != err)
        *err = -1;

    chCount = 0;
    for (i = 0; 0 != ucp[i]; i++)
    {
        if (ucp[i] >= 0xa1 && ucp[i] <= 0xfe && 0 != ucp[i + 1])
            i++;
        chCount++;
    }

    uniSize = 2 * chCount + 2;
    if (NULL != size)
        *size = uniSize;
    //if(uniSize<100)uniSize=100;
    uniBuf = malloc(uniSize);
		//memset(uniBuf,0,uniSize);
		//log_i("c2u申请内存",uniSize);
    if (NULL != uniBuf)
    {
        chCount = 0;
        i = 0;
        while (0 != ucp[i])
        {
            if (ucp[i] < 0x80)
            {
                uniBuf[chCount++] = ucp[i] << 8;
                i++;
            }
            else
            {
                pReturn = GBCodeToUnicode(ucp + i);
                if (NULL != pReturn)
                {
                    uniBuf[chCount++] = (pReturn[0] << 8) + pReturn[1];
                }
                else
                {
                    if (NULL != err)
                    {
										//  log_c("c2u","err!=null");
                        *err = i;
                        free(uniBuf);//, uniSize);
                        uniBuf = NULL;
                        goto end;
                    }
                    else
                    {
                        uniBuf[chCount++] = 0x3000;
                    }
                }
                i += 2;
            }
        }

        uniBuf[chCount] = 0;
			//	uniBuf[chCount+1] = 0;
    }

end:
    //LOGI("mr_c2u:%#p", uniBuf);

    return uniBuf;
}

int32 mrc_unicodeToGb2312(uint8* input, int32 input_len, uint8** output, int32* output_len)
{
 	if(!input || input_len == 0){
				// LOGE("mr_platEx(1207) input err");
				return MR_FAILED;
			}

			if(!*output){
				// LOGE("mr_platEx(1207) ouput err");
				return MR_FAILED;
			}

			//input is bigend
			
				int len = UCS2_strlen((const char *) input);
				char *buf = malloc(len + 2);

				int gbBufLen = len + 1;
				char *gbBuf = malloc(gbBufLen);

				memcpy(buf, input, len+2);
				UCS2ByteRev(buf);
				UCS2ToGBString((uint16*)buf, (uint8 *) gbBuf, gbBufLen);

				strcpy((char *) *output, gbBuf);
				/**
				 * output_len 返回的GB字符串缓冲的长度。
				 *
				 * output   	转换成功以后的bg2312编码字符串存放缓冲区指针，缓冲区的内存由应用调用者提供并管理、释放。
				 * output_len   output缓冲区的长度，单位字节数
				 *
				 * 2013-3-25 16:29:21 2013-3-25 16:51:44
				 */
				if(output_len)
					*output_len = strlen(gbBuf);
				
				free(buf);
			
 
// return mrc_u2c(input,input_len, output, output_len);
 return 0;
}





/*
char *stringToGb(jstring str)
{
  jboolean iscopy=TRUE; 
  jchar *untext = (*jniEnv)->GetStringChars(jniEnv, str, &iscopy); 
	char *gbBuf;
	int gbMaxLen=40*1024;
	int len;
	gbBuf=malloc(gbMaxLen);
	memset(gbBuf,0,gbMaxLen);
  len=UCS2ToGBString(untext, gbBuf, gbMaxLen);
//	(*jniEnv)->RealeaseStringChars(jniEnv,untext);
	//把结尾设0
	*(gbBuf+len)=0;
	return gbBuf;
}
*/







//un小端转string



