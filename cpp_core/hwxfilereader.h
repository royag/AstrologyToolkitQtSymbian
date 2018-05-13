#ifndef HWXFILEREADER_H
#define HWXFILEREADER_H

#define HWX_UNKNOWN -1
#define HWX_BIG_ENDIAN 0
#define HWX_LITTLE_ENDIAN 1

#include "stdio.h"
#include "stdint.h"

//typedef signed char HWX_INT8;         /* 8 bit signed */
//typedef unsigned char HWX_UINT8;      /* 8 bit unsigned */
//typedef short HWX_INT16;              /* 16 bit signed */
//typedef unsigned short HWX_UINT16;    /* 16 bit unsigned */
//typedef int HWX_INT32;                /* 32 bit signed */
//typedef unsigned int HWX_UINT32;      /* 32 bit unsigned */
#define HWX_UINT8 uint8_t
#define HWX_UINT16 uint16_t
#define HWX_UINT32 uint32_t

struct HWXFILE {
    FILE* filePointer;
    int byteOrder;
    int nativeByteOrder;
};

HWXFILE hwxOpenForRead(char* name, int byteOrder);
void hwxClose(HWXFILE f);
int hwxIsOpen(HWXFILE f);

HWX_UINT8 hwxReadUInt8(HWXFILE f);
HWX_UINT16 hwxReadUInt16(HWXFILE f);
HWX_UINT32 hwxReadUInt32(HWXFILE f);

void hwxReadStringOfLength(HWXFILE f, char* dest, int len);
void hwxSkipBytes(HWXFILE f, int num);
void hwxSwitchByteOrder(HWXFILE f, int byteOrder);

int hwxEOF(HWXFILE f);

#endif // HWXFILEREADER_H
