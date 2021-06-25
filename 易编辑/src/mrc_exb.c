
#include "mrc_exb.h"

uint32 readBigEndianUint32(uint8 *p)
{

    return (((uint32)*p)<<24) | (((uint32)*(p+1))<<16) | (((uint32)*(p+2))<<8) | ((uint32)*(p+3));
}
uint16 readBigEndianUint16(uint8 *p)
{
    return (((uint16)*(p))<<8) | ((uint16)*(p+1));
}
int32 mrc_writeBigEndianU32(uint32 data,uint8 *p)
{
    *(p)= (uint8)(data>>24 & 0xff);
    *(p+1)=(uint8)(data>>16 & 0xff);
    *(p+2)=(uint8)(data>>8 & 0xff);
    *(p+3)=(uint8)(data & 0xff);
    return 0;
}
int32 mrc_writeBigEndianU16(uint16 data,uint8 *p)
{
    *(p)= (uint8)(data>>8 & 0xff);
    *(p+1)=(uint8)(data & 0xff);

    return 0;
}


uint16 readLittleEndianUint16(uint8 *p)
{

    return (((uint16)*p)) | (((uint16)*(p+1))<<8);
}

uint32 readLittleEndianUint32(uint8 *p)
{
    return (((uint32)*p)) | (((uint32)*(p+1))<<8) | (((uint32)*(p+2))<<16) | (((uint32)*(p+3))<<24);
    return 0;
}



