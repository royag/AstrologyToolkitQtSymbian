#include "hwxfilereader.h"

#include "stdio.h"
//#include ""

//#ifdef QT_VERSION
/*************************************
** QT - BEGIN
*************************************/
/*
#include "qfile.h"
#include "qiodevice.h"
#include "qdatastream.h"
#include "qstring.h"

class HWXQTFileReader {
private:
    QFile* qfile;
    QDataStream* in;
    bool fileOpened;
    QDataStream::ByteOrder currentByteOrder;
public:
    HWXQTFileReader(char* name, int bitOrder) {
        FILE *fp;
        fseek()
        QString qname = QString(name);
        qfile = new QFile(qname); //("tralalal"); //qname); //":/data/Oslo");
        fileOpened = qfile->open(QIODevice::ReadOnly);
        if (fileOpened) {

            in = new QDataStream(qfile);

            if (bitOrder == HWX_BIG_ENDIAN) {
                currentByteOrder = QDataStream::LittleEndian;
            } else {
                currentByteOrder = QDataStream::BigEndian;
            }
            in->setByteOrder(currentByteOrder);
        }
    }
    void close() {
        qfile->close();
    }
    bool isOpen() {
        return fileOpened;
    }
    int readUInt8() {
        quint8 n;
        *in >> n;
        return n;
    }
    int readUInt16() {
        quint16 n;
        *in >> n;
        return n;
    }
    int readUInt32() {
        quint32 n;
        *in >> n;
        return n;
    }
    void readStringOfLength(char* dest, int len) {
        in->readRawData(dest, len);
        dest[len] = 0;
    }
    void skipBytes(int len) {
        in->skipRawData(len);
    }
    bool eof() {
        return in->atEnd();
    }
    void switchBitOrder(int bitOrder) {
        if (bitOrder == HWX_BIG_ENDIAN) {
            currentByteOrder = QDataStream::LittleEndian;
        } else {
            currentByteOrder = QDataStream::BigEndian;
        }
        in->setByteOrder(currentByteOrder);
    }

    ~HWXQTFileReader() {
        delete in;
        delete qfile;
    }
    static inline HWXQTFileReader* ofFile(HWXFILE &f) {
        return static_cast<HWXQTFileReader*>(f.filePointer);
    }

};



HWXFILE hwxOpenForRead(char* name, int bitOrder) {
   HWXQTFileReader* fr = new HWXQTFileReader(name, bitOrder);
   struct HWXFILE f;
   f.filePointer = fr;
   return f;
}

void hwxClose(HWXFILE f){
    HWXQTFileReader* fr = HWXQTFileReader::ofFile(f);
    fr->close();
    delete fr;
}

bool hwxIsOpen(HWXFILE f){
    return HWXQTFileReader::ofFile(f)->isOpen();
}


int hwxReadUInt8(HWXFILE f){
    return HWXQTFileReader::ofFile(f)->readUInt8();
}

int hwxReadUInt16(HWXFILE f){
    return HWXQTFileReader::ofFile(f)->readUInt16();
}

int hwxReadUInt32(HWXFILE f){
    return HWXQTFileReader::ofFile(f)->readUInt32();
}


void hwxReadStringOfLength(HWXFILE f, char* dest, int len){
    HWXQTFileReader::ofFile(f)->readStringOfLength(dest, len);
}

void hwxSkipBytes(HWXFILE f, int num){
    HWXQTFileReader::ofFile(f)->skipBytes(num);
}

bool hwxEOF(HWXFILE f) {
    return HWXQTFileReader::ofFile(f)->eof();
}

void hwxSwitchBitOrder(HWXFILE f, int bitOrder) {
    HWXQTFileReader::ofFile(f)->switchBitOrder(bitOrder);
}
*/

/*************************************
** QT - END
*************************************/
//S#endif



HWXFILE hwxOpenForRead(char* name, int bitOrder) {
   //HWXQTFileReader* fr = new HWXQTFileReader(name, bitOrder);
   FILE* fptr = fopen(name,"r");
   struct HWXFILE f;
   f.filePointer = fptr;
   f.bitOrder = bitOrder;
   return f;
}

void hwxClose(HWXFILE f){
    /*HWXQTFileReader* fr = HWXQTFileReader::ofFile(f);
    fr->close();
    delete fr;*/
    fclose(f.filePointer);
    f.filePointer = NULL;
}

int hwxIsOpen(HWXFILE f){
    return f.filePointer != NULL;
    //return HWXQTFileReader::ofFile(f)->isOpen();
}


HWX_UINT8 hwxReadUInt8(HWXFILE f){
    //return HWXQTFileReader::ofFile(f)->readUInt8();
    HWX_UINT8 n = 0;
    fread(&n, 1, 1, f.filePointer);
    return n;
}

HWX_UINT16 hwxReadUInt16(HWXFILE f){
    HWX_UINT16 n = 0;
    fread(&n, 2, 1, f.filePointer);
    return n;
    //return HWXQTFileReader::ofFile(f)->readUInt16();
}

HWX_UINT32 hwxReadUInt32(HWXFILE f){
    //return HWXQTFileReader::ofFile(f)->readUInt32();
    HWX_UINT32 n = 0;
    fread(&n, 4, 1, f.filePointer);
    return n;
}


void hwxReadStringOfLength(HWXFILE f, char* dest, int len){
    //HWXQTFileReader::ofFile(f)->readStringOfLength(dest, len);
    fread(dest, len, 1, f.filePointer);
    dest[len] = 0;
}

void hwxSkipBytes(HWXFILE f, int num){
    //int pos = ftell(f.filePointer);
    fseek(f.filePointer, ftell(f.filePointer), num);
    //HWXQTFileReader::ofFile(f)->skipBytes(num);
}

int hwxEOF(HWXFILE f) {
    return (feof(f.filePointer) != 0);
    //return HWXQTFileReader::ofFile(f)->eof();
}

void hwxSwitchBitOrder(HWXFILE f, int bitOrder) {
    //HWXQTFileReader::ofFile(f)->switchBitOrder(bitOrder);
    f.bitOrder = bitOrder;
}
