#include "hwxfilereader.h"
#include "stdio.h"

#define  EBIG(x)     x & (0x1 << 0)
#define  ELITTLE(x)  x & (0x1 << 1)

#define SETBIG(x)    x |= (0x1 << 0)
#define SETLITTLE(x) x |= (0x1 << 1)

static unsigned char get_endian (void)
{
   static unsigned char ret = 0;
   static unsigned int ivar = 0xdeadbeef;
   static unsigned char *cvar = (unsigned char *)&ivar;
   static unsigned char avar[sizeof ivar];
   size_t i=0;

   if (ret) return ret;

   while (i<sizeof ivar) {
      avar[i++] = *cvar++;
   }
   if ((avar[0]==0xde && avar[1]==0xad) || (avar[0]==0xbe && avar[1]==0xef)) {
      SETBIG (ret);
   }
   if ((avar[0]==0xad && avar[1]==0xde) || (avar[0]==0xef && avar[1]==0xbe)) {
      SETLITTLE (ret);
   }

   return ret;
}

#define HWX_ENDIAN_SWAP_U16(num)  ((num>>8) | (num<<8))
#define HWX_ENDIAN_SWAP_U32(num)  (((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000))

/*
((num>>24)&0xff) | // move byte 3 to byte 0
                    ((num<<8)&0xff0000) | // move byte 1 to byte 2
                    ((num>>8)&0xff00) | // move byte 2 to byte 1
                    ((num<<24)&0xff000000) // byte 0 to byte 3
                    */

static int HWX_ENDIANNESS = HWX_UNKNOWN;

static int hwx_setEndianess() {
    unsigned char result = get_endian ();
    if (EBIG(result)) {
        HWX_ENDIANNESS = HWX_BIG_ENDIAN;
    } else {
        HWX_ENDIANNESS = HWX_LITTLE_ENDIAN;
    }
}

static int hwx_getEndian() {
    if (HWX_ENDIANNESS == HWX_UNKNOWN) {
        hwx_setEndianess();
    }
    return HWX_ENDIANNESS;
}


HWXFILE hwxOpenForRead(char* name, int byteOrder) {
   FILE* fptr = fopen(name,"r");
   struct HWXFILE f;
   f.filePointer = fptr;
   f.byteOrder = byteOrder;
   f.nativeByteOrder = hwx_getEndian();
   return f;
}

void hwxClose(HWXFILE f){
    fclose(f.filePointer);
    f.filePointer = NULL;
}

int hwxIsOpen(HWXFILE f){
    return f.filePointer != NULL;
}


HWX_UINT8 hwxReadUInt8(HWXFILE f){
    HWX_UINT8 n = 0;
    fread(&n, 1, 1, f.filePointer);
    return n;
}

HWX_UINT16 hwxReadUInt16(HWXFILE f){
    HWX_UINT16 n = 0;
    fread(&n, 2, 1, f.filePointer);
    if (f.nativeByteOrder != f.byteOrder) {
        n = HWX_ENDIAN_SWAP_U16(n);
    }
    return n;
}

HWX_UINT32 hwxReadUInt32(HWXFILE f){
    HWX_UINT32 n = 0;
    fread(&n, 4, 1, f.filePointer);
    if (f.nativeByteOrder != f.byteOrder) {
        n = HWX_ENDIAN_SWAP_U32(n);
    }
    return n;
}


void hwxReadStringOfLength(HWXFILE f, char* dest, int len){
    fread(dest, len, 1, f.filePointer);
    dest[len] = 0;
}

void hwxSkipBytes(HWXFILE f, int num){
    fseek(f.filePointer, ftell(f.filePointer), num);
}

int hwxEOF(HWXFILE f) {
    return (feof(f.filePointer) != 0);
}

void hwxSwitchByteOrder(HWXFILE f, int byteOrder) {
    f.byteOrder = byteOrder;
}
