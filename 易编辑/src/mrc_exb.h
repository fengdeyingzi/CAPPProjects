#ifndef __MRC_EXB_H__
#define __MRC_EXB_H__
#include "base.h"
uint32 readBigEndianUint32(uint8 *p);

uint16 readBigEndianUint16(uint8 *p);

int32 mrc_writeBigEndianU32(uint32 data,uint8 *p);

int32 mrc_writeBigEndianU16(uint16 data,uint8 *p);



uint16 readLittleEndianUint16(uint8 *p);


uint32 readLittleEndianUint32(uint8 *p);

#endif

