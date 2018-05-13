#ifndef MYCHARTINPUT_H
#define MYCHARTINPUT_H

#include <QFrame>
#include "mylistselect.h"
#include <QListWidgetItem>
#include "cpp_core/geodata.h"
#include <QStringList>
#include "hwqt/qhwdatechooser.h"
#include "hwqt/qhwtimechooser.h"
#include "hwqt/qhwlatlongchooser.h"


// For QListWidgetItems in countryList:
#define ROLE_COUNTRY_SHORT_CODE (Qt::UserRole + 0)
#define ROLE_PLACE_NAME (Qt::UserRole + 1)
#define ROLE_PLACE_LATITUDE (Qt::UserRole + 2)
#define ROLE_PLACE_LONGITUDE (Qt::UserRole + 3)

class MyChartInput : public QFrame
{
    Q_OBJECT

public:
    explicit MyChartInput(QWidget *parent = 0);
    ~MyChartInput();

    static QString formatLatitudeLongitude(int latCents, int longCents);
signals:
    void cancelled();
    void chartDataChanged(
            QString countryCode,
            QString contry,
            QString placeName,
            int latitudeCents,
            int longitudeCents,
            QString timeZone,
            int year,
            int month,
            int day,
            int hour,
            int minute);
private slots:
    void doneInputting();
    void cancel();
    void editFieldSelected(QListWidgetItem* item);
    void inputCountryChanged(QListWidgetItem* countryItem);
    void inputPlaceChanged(QListWidgetItem* placeItem);
    void inputDateChanged(int year, int month, int day);
    void inputTimeChanged(int hour, int minute);
    void inputTimezoneChanged(QString place);
    void inputLatitudeLongtudeChanged(int latitude, int longitude);

    void subInputCancelled();

protected:
    virtual void resizeEvent ( QResizeEvent * event );
    void setVisibleWidget(QWidget* w);
    void loadCountries();
    void loadPlacesByCountry(QString countryCode);
    void loadTimeszones();
    QList<GeoCountryInfo>* getCountryInfo();
    QList<GeoPlaceInfo>* getPlaceInfo(QString countryCode);

    void activateCountrySelect();
    void activatePlaceSelect();
    void activateTimezoneSelect();
    void activateDateSelect();
    void activateTimeSelect();
    void activateLatitudeLongitudeSelect();

    virtual void focusInEvent ( QFocusEvent * event );

private:
    QAction *actionDone;
    QAction *actionCancel;

    MyListSelect *inputFieldSelect;
    // Sub selects:
    MyListSelect *countrySelect;
    MyListSelect *placeSelect;
    //MyListSelect *dateSelect;
    //MyListSelect *timeSelect
    MyListSelect *timezoneSelect;
    QHWDateChooser *dateSelect;
    QHWTimeChooser *timeSelect;
    QHWLatLongChooser* latLongSelect;

    QListWidgetItem *itemCountry;
    QListWidgetItem *itemPlace;
    QListWidgetItem *itemDate;
    QListWidgetItem *itemTime;
    QListWidgetItem *itemTimezone;

    QStringList* suggestedTimeZones;
    QStringList* zoneList;
    QList<GeoCountryInfo>* _countryInfo; //= GeoData::loadCountryInfo();
    QString _currentCountryCode;
    QString _currentCountryName;
    QString _placesLoadedForCountryCode;
    QString _currentPlaceName;
    QString _currentTimeZone;

    int _currentLatitudeCents;
    int _currentLongitudeCents;
    int _year;
    int _month;
    int _day;
    int _hour;
    int _minute;
    QList<GeoPlaceInfo>* _placeInfo; //gpi = GeoData::loadPlaceInfoForCountryCode("NO");


};

#endif // MYCHARTINPUT_H
