#include "timezoneinfo.h"

#include <QString>

#include "qfile.h"
#include "qiodevice.h"
#include "qdatastream.h"

#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QByteArray>

#include "geodata.h"

#include "stdlib.h"



TZType::TZType() {

}

TZType::TZType(QString name, int offset, bool dst) {
    this->name = new QString(name);
    this->offset = offset;
    this->dst = dst;
}



TimeZoneInfo::TimeZoneInfo(QString zoneName)
{

    this->tztypes = new QList<TZType*>();
    this->loadZoneFromAll(zoneName);
    //this->loadFile(filename);
}

// TODO: Write unit-test thouroguhly checking this one:
long TimeZoneInfo::toSecsSinceEpoch(int year, int month, int day, int h, int m) {
    QDate d = QDate(year,month,day);
    QDateTime dt = QDateTime(d, QTime(h,m),Qt::UTC);
    //(60 x 60 x 24 x 365 x 3) + (60 x 60 x 24 x 366) = 126230400
    long simpleFourYears = 126230400; // summer time no problem =?

    if (year < 1970) {
        int toAdd = 0;
        while (year + toAdd < 1970) {
            toAdd += 4;
        }
        QDateTime d4 = dt.addYears(toAdd);
        //quint32 t = dt.toTime_t();
        long t4 = d4.toTime_t();
        return t4 - (toAdd / 4) * simpleFourYears;
    }
    return dt.toTime_t();
}

SimpleTime TimeZoneInfo::toUTC(int year, int month, int day, int h, int m) {
    QDate d = QDate(year,month,day);
    QDateTime dt = QDateTime(d, QTime(h,m),Qt::UTC);
    // (QT 4.7 only) long s = dt.toMSecsSinceEpoch() / 1000;
    long s = TimeZoneInfo::toSecsSinceEpoch(year,month,day,h,m);

    TZType* t = getTZ(s);
    int secondsOffset = t->offset;
    dt = dt.addSecs(-secondsOffset);
    QDate d2 = dt.date();
    QTime t2 = dt.time();
    SimpleTime ret;
    ret.year = d2.year();
    ret.month = d2.month();
    ret.day = d2.day();
    ret.hour = t2.hour();
    ret.minute = t2.minute();
    return ret;
}

void TimeZoneInfo::loadFile(QString filename) {
    QFile f(filename); //":/data/Oslo");
    bool ok = f.open(QIODevice::ReadOnly);
    QDataStream in(&f);

    loadFile(&in);
    f.close();
}

void TimeZoneInfo::loadFile(QDataStream* in) {
        QDataStream::ByteOrder origByteOrder = in->byteOrder();
        in->setByteOrder(QDataStream::BigEndian);
        in->skipRawData(28);
        int leapcnt;


        int charcnt;
        *in >> leapcnt;
        *in >> timecnt;
        *in >> typecnt;

        *in >> charcnt;

        //qint32* transTimes;	// transition times
        //qint8* transTypes;	// timezone description for each transition

        transTimes = (qint32*)malloc(sizeof(qint32) * timecnt);
        for (int i = 0; i < timecnt; i++) {
            *in >> transTimes[i];
        }



        transTypes = (qint8*)malloc(sizeof(qint8) * timecnt);
        for (int i = 0; i < timecnt; i++) {
            *in >> transTypes[i];
        }

        qint32* offset  = new qint32[typecnt];
        qint8* dst = new qint8[typecnt];
        qint8* idx = new qint8[typecnt];

        qint32 tmp32;
        qint8 tmp8;
        for (int i = 0; i < typecnt; i++) {

            *in >> offset[i];
            *in >> dst[i];
            *in >> idx[i];

            tmp32 = offset[i];
            tmp8 = dst[i];
            tmp8 = idx[i];
        }
        qint8* str = new qint8[charcnt];
        for (int i = 0; i < charcnt; i++) {
            *in >> str[i];
        }

        //tz = new TZType[typecnt];
        for (int i = 0; i < typecnt; ++i) {
            // find string
            int pos = idx[i];
            int end = pos;
            while (str[end] != 0) ++end;
            //QString tmp = QString(str[pos], end-pos);
            char ctmp[100];
            memcpy(&ctmp, &str[pos], end-pos);
            ctmp[end-pos] = 0;

            tztypes->append(new TZType(QString((char*)&ctmp),offset[i],dst[i] != 0));
        }

        qint32* leapSecs = new int[leapcnt * 2];
        for (int i = 0; leapcnt > 0; --leapcnt) {
            *in >> leapSecs[i++];
            *in >> leapSecs[i++];
        }

        //f.close();
        in->setByteOrder(origByteOrder);

        // Set default timezone (normaltz).
        // First, set default to first non-DST rule.
        int n = 0;
        while (tztypes->at(n)->dst && n < tztypes->length())
            ++n;
        normalTZ = tztypes->at(n);

        // When setting "normaltz" (the default timezone) in the constructor,
        // we originally took the first non-DST rule for the current TZ.
        // But this produces nonsensical results for areas where historical
        // non-integer time zones were used, e.g. if GMT-2:33 was used until 1918.

        // This loop, based on a suggestion by Ophir Bleibergh, tries to find a
        // non-DST rule close to the current time. This is somewhat of a hack, but
        // much better than the previous behavior in this case.

        // Tricky: we need to get either the next or previous non-dst TZ
        // We shall take the future non-dst value, by trying to add 3 months at a
        // time to the current date and searching.
        // (QT 4.7 only) qint64 ts = QDateTime::currentMSecsSinceEpoch() / 1000;
        qint64 ts = QDateTime::currentDateTime().toTime_t();
        //final long ts = System.currentTimeMillis() / 1000;
        for (int i = 0; i < 9; i++) {
          TZType* currTz = getTZ(ts + secsPerThreeMonths*i);
          if (!currTz->dst) {
            normalTZ = currTz;
            break;
          }
        }

        delete offset;
        delete idx;
        delete dst;
        delete str;
        // delete leapSecs;
}

TZType* TimeZoneInfo::getTZ(long clock) {
    // FIXME: use binary search
    if (timecnt > 0 && clock >= transTimes[0]) {
        int i = 1;
        for (;i < timecnt; ++i) {
            if (clock < transTimes[i]) {
                break;
            }
        }
        return tztypes->at(transTypes[i - 1]);
    }
    return normalTZ;
}



QStringList* TimeZoneInfo::readZones() {
    QStringList * list = new QStringList();
    readZones(*list);
    return list;
}

int TimeZoneInfo::readZones(QStringList &zones) {
    QFile f(TZ_ALL_FILENAME);
    bool ok = f.open(QIODevice::ReadOnly);

    QDataStream in(&f);
    in.setByteOrder(QDataStream::LittleEndian);

    quint16 nameLength;
    QString name;
    quint16 dataLength;
    int i = 0;
    while (!in.atEnd()) {
        in >> nameLength;
        name = GeoData::readStringOfSize(&in, nameLength);
        in >> dataLength;
        in.skipRawData(dataLength);
        zones.append(name);
        i++;
    }

    f.close();
    return i;
}

void TimeZoneInfo::loadZoneFromAll(QString zoneName) {
    QFile f(TZ_ALL_FILENAME);
    bool ok = f.open(QIODevice::ReadOnly);

    QDataStream in(&f);
    in.setByteOrder(QDataStream::LittleEndian);

    quint16 nameLength;
    QString name;
    quint16 dataLength;
    while (!in.atEnd()) {
        in >> nameLength;
        name = GeoData::readStringOfSize(&in, nameLength);
        in >> dataLength;
        if (0 == name.compare(QStringRef(&zoneName), Qt::CaseInsensitive)) {
            loadFile(&in);
            break;
        } else {
            in.skipRawData(dataLength);
        }
    }
    f.close();
}

int TimeZoneInfo::addDefaultZonesForCountry(QString countryCode, QStringList &list) {
    return TimeZoneDefaults::addDefaultZonesForCountry(countryCode, list);
}



