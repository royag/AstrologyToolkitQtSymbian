#ifndef GEODATA_H
#define GEODATA_H

//#include "hwxfilereader.h"

#include <QString>
//#include <QDataStream>
#include <QList>

struct GeoCountryInfo {
    QString* countryCode;
    QString* countryName;
};

struct GeoPlaceInfo {
    QString* placeName;
    int latitudeCents;
    int longitudeCents;
};

class GeoData
{
public:
    GeoData();
    //void test();
    static QList<GeoCountryInfo>* loadCountryInfo();
    static QList<GeoPlaceInfo>* loadPlaceInfoForCountryCode(QString code);
    static QString readStringOfSize(QDataStream* stream, int size);
    static void free(QList<GeoCountryInfo>* &countryInfo);
    static void free(QList<GeoPlaceInfo>* &placeInfo);
    static QString coordinatesToString(int latitudeCents, int longitudeCents);
private:

    static void load(bool loadCountries, QList<GeoCountryInfo>* countryTarget, bool loadPlaces = false, QList<GeoPlaceInfo>* placeTarget = 0, QString wantedCountryCode = "tst");
};

#endif // GEODATA_H


