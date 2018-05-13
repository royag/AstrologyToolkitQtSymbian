#include "geodata.h"

#include "qfile.h"
#include "qiodevice.h"
#include "qdatastream.h"

#include <QList>
#include <QString>
#include <QMutableListIterator>

GeoData::GeoData()
{
}

QString GeoData::coordinatesToString(int latitudeCents, int longitudeCents) {
    QString latS = "N";
    if (latitudeCents < 0) {
        latS = "S";
        latitudeCents = -latitudeCents;
    }
    QString longS = "E";
    if (longitudeCents < 0) {
        longS = "W";
        longitudeCents = -longitudeCents;
    }

    int latFull = latitudeCents / 100.0;
    int longFull = longitudeCents / 100.0;
    int latCent = latitudeCents - (100 * latFull);
    int longCent = longitudeCents - (100 * longFull);

    return QString::number(latFull) + latS + (latCent < 10 ? "0" : "") + QString::number(latCent) +
            " " +
            QString::number(longFull) + longS + (longCent < 10 ? "0" : "") + QString::number(longCent);
}

void GeoData::free(QList<GeoCountryInfo>* &countryInfo) {
    QMutableListIterator<GeoCountryInfo> it(*countryInfo);
    GeoCountryInfo rec;
    while (it.hasNext()) {
        rec = it.next();
        it.remove();
        delete rec.countryCode;
        delete rec.countryName;
    }
    delete countryInfo;
    countryInfo = 0;
}

void GeoData::free(QList<GeoPlaceInfo>* &placeInfo) {
    QMutableListIterator<GeoPlaceInfo> it(*placeInfo);
    GeoPlaceInfo rec;
    while (it.hasNext()) {
        rec = it.next();
        it.remove();
        delete rec.placeName;
    }
    delete placeInfo;
    placeInfo = 0;
}

QString GeoData::readStringOfSize(QDataStream* in, int size) {
    quint8 tmp[1000];
    int i = 0;
    for (; i < size; i++) {
        *in >> tmp[i];
    }
    tmp[i] = 0;
    return QString((char*)&tmp);
}

QList<GeoCountryInfo>* GeoData::loadCountryInfo() {
    QList<GeoCountryInfo>* ret = new QList<GeoCountryInfo>();
    load(true, ret);
    return ret;
}

QList<GeoPlaceInfo>* GeoData::loadPlaceInfoForCountryCode(QString code) {
    QList<GeoPlaceInfo>* ret = new QList<GeoPlaceInfo>();
    load(false, 0, true, ret, code);
    return ret;
}

void GeoData::load(bool loadCountries, QList<GeoCountryInfo>* countryTarget, bool loadPlaces, QList<GeoPlaceInfo>* placeTarget, QString wantedCountryCode) {

    QFile f(":/astrodata/geodata/geodata.dat"); //":/data/Oslo");
    bool ok = f.open(QIODevice::ReadOnly);

    QDataStream in(&f);
    in.setByteOrder(QDataStream::LittleEndian);

    quint8 countryCodeSize;
    QString countryCode;
    quint8 countryNameSize;
    QString countryName;
    quint16 countryDataSize;

    quint8 placeNameSize;
    QString placeName;
    qint16 latitude;
    qint16 longitude;

    while (!in.atEnd()) {
        in >> countryCodeSize;
        countryCode = readStringOfSize(&in, countryCodeSize);
        in >> countryNameSize;
        countryName = readStringOfSize(&in, countryNameSize);
        in >> countryDataSize;

        if (loadCountries) {
            GeoCountryInfo gci;
            gci.countryCode = new QString(countryCode);
            gci.countryName = new QString(countryName);
            countryTarget->append(gci);
        }


        if (loadPlaces && (0 == wantedCountryCode.compare(QStringRef(&countryCode), Qt::CaseInsensitive))) {
            int bytesRead = 0;
            while (bytesRead < countryDataSize) {
                in >> placeNameSize;
                placeName = readStringOfSize(&in, placeNameSize);
                in >> latitude;
                in >> longitude;

                bytesRead += 1 + placeNameSize + 2 + 2;

                GeoPlaceInfo gpi;
                gpi.placeName = new QString(placeName);
                gpi.latitudeCents = latitude;
                gpi.longitudeCents = longitude;
                placeTarget->append(gpi);
            }
            if (!loadCountries) {
                break; // while
            }
        } else {
            in.skipRawData(countryDataSize);
        }

    }



    f.close();
}

/*

def self.createCountryRec(name,code)
  d = GeodataReader.load_geo_data(code, "geodata3s")
  res = ""
  i = 0
  d.each do |rec|
    #puts rec
        i += 1+ rec.place_name.size() + 6
        res += [rec.place_name.size(), rec.place_name, (rec.latitude*100), (rec.longitude*100)].pack("CA#{rec.place_name.size()}SS");
  end
  if (i != res.size())
        #throw Exception("ugh");
        puts "ERROR"
  end
  pt = "CA#{code.size()}CA#{name.size()}S"
  #puts pt
  rec_header = [code.size(), code, name.size(), name, res.size()].pack(pt);
  rec_header + res
end
end

all = ""

AllCountryCodes.each do |cc|
  puts cc
  all += GeodataReader.createCountryRec(cc[0],cc[1])
end

 */
