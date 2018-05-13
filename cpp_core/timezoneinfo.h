#ifndef TIMEZONEINFO_H
#define TIMEZONEINFO_H

#include <QString>
#include <QList>
#include <QStringList>

#include "timezonedefaults.h"

#define TZ_ALL_FILENAME ":/astrodata/tz/tzall.dat"

class TZType {
public:
    TZType();
    TZType(QString name, int offset, bool dst);
    QString* name;
    int offset;
    bool dst;


    ~TZType()  {
        delete name;
    }
};

struct SimpleTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

class TimeZoneInfo
{
public:
    TimeZoneInfo(QString zoneName);
    TZType* getTZ(long clock);
    ~TimeZoneInfo() {
        for (int i = 0; i < tztypes->length(); i++) {
            delete tztypes->at(i);
        }
        delete tztypes;
        delete transTimes;
        delete transTypes;
    }
    static long toSecsSinceEpoch(int year, int month, int day, int h, int m);
    SimpleTime toUTC(int year, int month, int day, int h, int m);
    static QStringList* readZones();
    static int readZones(QStringList &);

    static int addDefaultZonesForCountry(QString countryCode, QStringList &list);

private:
    void loadFile(QString filename);
    void loadFile(QDataStream* in);
    void loadZoneFromAll(QString zoneName);
    QList<TZType*> *tztypes;
    TZType* normalTZ;

    qint32* transTimes;	// transition times
    qint8* transTypes;	// timezone description for each transition
    static const long secsPerThreeMonths = 60*60*24*30*3;
    int timecnt;
    int typecnt;

};

#endif // TIMEZONEINFO_H
