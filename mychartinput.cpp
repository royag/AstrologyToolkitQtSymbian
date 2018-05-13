#include "mychartinput.h"

#include "cpp_core/timezoneinfo.h"
#include <QMessageBox>

#define NO_GEO_LOCATION -1000000

MyChartInput::MyChartInput(QWidget *parent) :
    QFrame(parent),
    _countryInfo(0),
    _currentCountryCode("_NONE_"),
    _currentCountryName("Not selected"),
    _placeInfo(0),
    _placesLoadedForCountryCode("_NONE_"),
    _currentPlaceName(""),
    _currentLatitudeCents(NO_GEO_LOCATION),
    _currentLongitudeCents(NO_GEO_LOCATION),
    suggestedTimeZones(new QStringList()),
    _year(2000),
    _month(1),
    _day(1),
    _hour(0),
    _minute(0),

    zoneList(new QStringList())
{
    //connect(ui->inputComplete, SIGNAL(clicked()), this, SLOT(doneInputting()));

    inputFieldSelect = new MyListSelect("Done", this);
    inputFieldSelect->setFontSize(10);
    inputFieldSelect->setHeaderText(tr("Edit Chart Data"));
    connect(inputFieldSelect, SIGNAL(itemSelected(QListWidgetItem*)), this, SLOT(editFieldSelected(QListWidgetItem*)));
    inputFieldSelect->setActivateByPositiveSoftkey(false);
    connect(inputFieldSelect, SIGNAL(selectActionTriggered()), this, SLOT(doneInputting()));

    actionCancel = new QAction("Cancel", inputFieldSelect);
    actionCancel->setSoftKeyRole(QAction::NegativeSoftKey);
    inputFieldSelect->addAction(actionCancel);
    connect(actionCancel, SIGNAL(triggered()), this, SLOT(cancel()));
    //setVisibleWidget(inputFieldSelect);

    itemCountry = new QListWidgetItem("Select Country", inputFieldSelect->getListWidget());
    itemPlace = new QListWidgetItem("Select Place", inputFieldSelect->getListWidget());
    itemPlace->setHidden(true);
    itemDate = new QListWidgetItem("Select Date", inputFieldSelect->getListWidget());
    itemTime = new QListWidgetItem("Select Time", inputFieldSelect->getListWidget());
    itemTimezone = new QListWidgetItem("Select Timezone", inputFieldSelect->getListWidget());


    //inputFieldSelect->getListWidget()->addItem();

    countrySelect = new MyListSelect("Select", this);
    countrySelect->setHeaderText(tr("Choose Country"));
    connect(countrySelect, SIGNAL(itemSelected(QListWidgetItem*)), this, SLOT(inputCountryChanged(QListWidgetItem*)));
    connect(countrySelect, SIGNAL(selectCancelled()), this, SLOT(subInputCancelled()));
    countrySelect->hide();

    placeSelect = new MyListSelect("Select", this);
    placeSelect->setHeaderText(tr("Choose place"));
    connect(placeSelect, SIGNAL(itemSelected(QListWidgetItem*)), this, SLOT(inputPlaceChanged(QListWidgetItem*)));
    connect(placeSelect, SIGNAL(selectCancelled()), this, SLOT(subInputCancelled()));
    placeSelect->hide();

    timezoneSelect = new MyListSelect("Select", this);
    timezoneSelect->setHeaderText(tr("Choose timezone"));
    connect(timezoneSelect, SIGNAL(itemSelected(QString)), this, SLOT(inputTimezoneChanged(QString)));
    connect(timezoneSelect, SIGNAL(selectCancelled()), this, SLOT(subInputCancelled()));
    timezoneSelect->hide();

    dateSelect = new QHWDateChooser(this);
    connect(dateSelect, SIGNAL(dateSelected(int,int,int)), this, SLOT(inputDateChanged(int,int,int)));
    connect(dateSelect, SIGNAL(cancelled()), this, SLOT(subInputCancelled()));
    dateSelect->hide();

    timeSelect = new QHWTimeChooser(this);
    connect(timeSelect, SIGNAL(timeSelected(int,int)), this, SLOT(inputTimeChanged(int,int)));
    connect(timeSelect, SIGNAL(cancelled()), this, SLOT(subInputCancelled()));
    timeSelect->hide();

    latLongSelect = new QHWLatLongChooser(this);
    connect(latLongSelect, SIGNAL(latLongSelected(int,int)), this, SLOT(inputLatitudeLongtudeChanged(int,int)));
    connect(latLongSelect, SIGNAL(cancelled()), this, SLOT(subInputCancelled()));
    latLongSelect->hide();
}

void MyChartInput::cancel() {
    emit cancelled();
}

QList<GeoCountryInfo>* MyChartInput::getCountryInfo() {
    if (_countryInfo == 0) {
        _countryInfo = GeoData::loadCountryInfo();
    }
    return _countryInfo;
}



QList<GeoPlaceInfo>* MyChartInput::getPlaceInfo(QString countryCode) {
    if (_placeInfo != 0) {
        if (_placesLoadedForCountryCode.compare(countryCode) == 0) {
            return _placeInfo;
        } else {
            GeoData::free(_placeInfo);
        }
    }
    _placesLoadedForCountryCode = countryCode;
    _placeInfo = GeoData::loadPlaceInfoForCountryCode(countryCode);
    return _placeInfo;
}

void MyChartInput::loadCountries(){
    //QList<GeoCountryInfo>* gci = GeoData::loadCountryInfo();
    //QList<GeoPlaceInfo>* gpi = GeoData::loadPlaceInfoForCountryCode("NO");
    QList<GeoCountryInfo>* ci = getCountryInfo();
    QListWidget *list = countrySelect->getListWidget();
    list->clear();
    QListIterator<GeoCountryInfo> it(*ci);
    QListWidgetItem* item;

    item = new QListWidgetItem("[CUSTOM PLACE]", list);
    item->setData(ROLE_COUNTRY_SHORT_CODE, QVariant(QString("CUSTOM")));

    GeoCountryInfo country;
    while (it.hasNext()) {
        country = it.next();
        item = new QListWidgetItem(*(country.countryName), list);
        item->setData(ROLE_COUNTRY_SHORT_CODE, QVariant(*(country.countryCode)));
    }
}

void MyChartInput::loadPlacesByCountry(QString countryCode) {
    QList<GeoPlaceInfo>* pInfo = getPlaceInfo(countryCode);
    QListWidget *list = placeSelect->getListWidget();
    list->clear();
    QListIterator<GeoPlaceInfo> it(*pInfo);
    QListWidgetItem* item;
    GeoPlaceInfo place;
    while (it.hasNext()) {
        place = it.next();
        item = new QListWidgetItem(*(place.placeName), list);

        /*item->setData(ROLE_PLACE_NAME, QVariant(*(place.placeName)));
        item->setData(ROLE_PLACE_LATITUDE, QVariant(place.latitudeCents));
        item->setData(ROLE_PLACE_LONGITUDE, QVariant(place.longitudeCents));*/
    }
}

void MyChartInput::loadTimeszones() {
    zoneList->clear();
    if (suggestedTimeZones->count() > 1) {
        zoneList->append(*suggestedTimeZones);
    }
    TimeZoneInfo::readZones(*zoneList);
    QListWidget *list = timezoneSelect->getListWidget();
    list->clear();
    list->addItems(*zoneList);
    /*if(_currentTimeZone.length() > 0) {
        QListIterator<QListWidgetItem> it(list->->items());

        QListWidgetItem* item;
        while (it.hasNext()) {
            item = it.next();
            if (item->text().compare(_currentTimeZone) == 0) {
                list->setCurrentItem(item);
                break;
            }
        }
    }*/
}

void MyChartInput::setVisibleWidget(QWidget* w) {
    (inputFieldSelect == w ? inputFieldSelect->show() : inputFieldSelect->hide());
    (countrySelect == w ? countrySelect->show() : countrySelect->hide());
    (placeSelect == w ? placeSelect->show() : placeSelect->hide());
    (timezoneSelect == w ? timezoneSelect->show() : timezoneSelect->hide());
    (dateSelect == w ? dateSelect->show() : dateSelect->hide());
    (timeSelect == w ? timeSelect->show() : timeSelect->hide());
    (latLongSelect == w ? latLongSelect->show() : latLongSelect->hide());
    /*inputFieldSelect->update();
    countrySelect->update();
    placeSelect->update();
    timezoneSelect->update();
    dateSelect->update();*/
    w->update();
    w->setFocus();
}

void MyChartInput::subInputCancelled() {
    setVisibleWidget(inputFieldSelect);
    //inputFieldSelect->
}

void MyChartInput::activateCountrySelect() {
    if (countrySelect->getListWidget()->count() < 1) {
        loadCountries();
    }
    setVisibleWidget(countrySelect);
}

void MyChartInput::activatePlaceSelect() {
    if (_placesLoadedForCountryCode.compare(_currentCountryCode) != 0) {
        // New country:
        loadPlacesByCountry(_currentCountryCode);
    }
    setVisibleWidget(placeSelect);
}

void MyChartInput::activateTimezoneSelect() {
    loadTimeszones();
    setVisibleWidget(timezoneSelect);
}

void MyChartInput::activateDateSelect() {
    setVisibleWidget(dateSelect);
}

void MyChartInput::activateTimeSelect() {
    setVisibleWidget(timeSelect);
}

void MyChartInput::activateLatitudeLongitudeSelect() {
    setVisibleWidget(latLongSelect);
}

void MyChartInput::editFieldSelected(QListWidgetItem* item) {
    //long ii = (long)item;
    //long ic = (long)itemCountry;
    if (item == itemCountry) {
        activateCountrySelect();
    } else if (item == itemPlace) {
        if (_currentCountryCode.compare("CUSTOM") == 0) {
            activateLatitudeLongitudeSelect();
        } else {
            activatePlaceSelect();
        }
    } else if (item == itemTimezone) {
        activateTimezoneSelect();
    } else if (item == itemDate) {
        activateDateSelect();
    } else if (item == itemTime) {
        activateTimeSelect();
    }
    this->update();
}

void MyChartInput::inputCountryChanged(QListWidgetItem* countryItem) {
    if (countryItem != 0) {
        _currentCountryCode = countryItem->data(ROLE_COUNTRY_SHORT_CODE).toString();
        _currentCountryName = countryItem->text();
        itemCountry->setText(tr("Country: ") + _currentCountryName);

        suggestedTimeZones->clear();
        TimeZoneInfo::addDefaultZonesForCountry(_currentCountryCode, *suggestedTimeZones);
        if (suggestedTimeZones->count() == 1) {
            _currentTimeZone = suggestedTimeZones->first();
            itemTimezone->setText(_currentTimeZone);
        } else {
            _currentTimeZone = "";
            itemTimezone->setText("Select timezone");
        }

        if (_currentCountryCode.compare(_placesLoadedForCountryCode) != 0) {
            // country other than last
            itemPlace->setText("Select Place");
            _currentPlaceName = tr("");
            _currentLatitudeCents = NO_GEO_LOCATION;
            _currentLongitudeCents = NO_GEO_LOCATION;
        }
        itemPlace->setHidden(false);

    }
    setVisibleWidget(inputFieldSelect);
}

QString MyChartInput::formatLatitudeLongitude(int totalLatCents, int totalLongCents) {
    QString sLat = "N";
    if (totalLatCents < 0) {
        sLat = "S";
        totalLatCents = -totalLatCents;
    }
    QString sLong = "E";
    if  (totalLongCents < 0) {
        sLong = "W";
        totalLongCents = -totalLongCents;
    }
    int latWhole = totalLatCents / 100;
    int longWhole = totalLongCents / 100;
    int latCents = totalLatCents - (latWhole * 100);
    int longCents = totalLongCents - (longWhole * 100);
    QString ret =
            QString::number(latWhole).rightJustified(2, QChar::fromAscii('0')) +
            sLat +
            QString::number(latCents).rightJustified(2, QChar::fromAscii('0')) +
            " " +
            QString::number(longWhole).rightJustified(2, QChar::fromAscii('0')) +
            sLong +
            QString::number(longCents).rightJustified(2, QChar::fromAscii('0'));
    return ret;
}

void MyChartInput::inputPlaceChanged(QListWidgetItem* placeItem){
    if (placeItem != 0) {
        QList<GeoPlaceInfo>* pInfo = getPlaceInfo(_currentCountryCode);
        QListIterator<GeoPlaceInfo> it(*pInfo);
        GeoPlaceInfo place;
        while (it.hasNext()) {
            place = it.next();
            if (place.placeName->compare(placeItem->text()) == 0) {
                _currentPlaceName = *(place.placeName);
                _currentLatitudeCents = place.latitudeCents;
                _currentLongitudeCents = place.longitudeCents;
                itemPlace->setText(_currentPlaceName +
                                   tr(" (") +
                                   formatLatitudeLongitude(_currentLatitudeCents, _currentLongitudeCents) +
                                   tr(")") );
                break;
            }
        }
    }
    setVisibleWidget(inputFieldSelect);
}

void MyChartInput::inputDateChanged(int year, int month, int day){
    _year = year;
    _month = month;
    _day = day;
    itemDate->setText(QString::number(_year) + "-" +
                      QString::number(_month) + "-" +
                      QString::number(_day));
    setVisibleWidget(inputFieldSelect);
}
void MyChartInput::inputTimeChanged(int hour, int minute){
    _hour = hour;
    _minute = minute;
    itemTime->setText(QString::number(hour).rightJustified(2, '0') +
                      ":" +
                      QString::number(minute).rightJustified(2, '0'));
    setVisibleWidget(inputFieldSelect);
}

void MyChartInput::inputTimezoneChanged(QString timeZone){
    _currentTimeZone = timeZone;
    itemTimezone->setText(_currentTimeZone);
    setVisibleWidget(inputFieldSelect);
}
void MyChartInput::inputLatitudeLongtudeChanged(int latitude, int longitude) {
    _currentPlaceName = "Custom";
    _currentLatitudeCents = latitude;
    _currentLongitudeCents = longitude;
    itemPlace->setText(_currentPlaceName +
                       tr(" (") +
                       formatLatitudeLongitude(_currentLatitudeCents, _currentLongitudeCents) +
                       tr(")") );
    setVisibleWidget(inputFieldSelect);
}

void MyChartInput::resizeEvent ( QResizeEvent * event )  {
    QFrame::resizeEvent(event);
    inputFieldSelect->setGeometry(geometry());
    inputFieldSelect->update();
    countrySelect->setGeometry(geometry());
    countrySelect->update();
    placeSelect->setGeometry(geometry());
    placeSelect->update();
    dateSelect->setGeometry(geometry());
    dateSelect->update();
    timeSelect->setGeometry(geometry());
    timeSelect->update();
    latLongSelect->setGeometry(geometry());
    latLongSelect->update();

    timezoneSelect->setGeometry(geometry());
    timezoneSelect->update();
    this->update();
}

void MyChartInput::focusInEvent ( QFocusEvent * event ) {
    QFrame::focusInEvent(event);
    if (event->reason() == Qt::OtherFocusReason) {
        inputFieldSelect->setFocus(event->reason());
    }
}

void MyChartInput::doneInputting() {


    if (_currentCountryCode.compare("_NONE_") == 0 ||
        _currentPlaceName.compare("") == 0 ||
        _currentTimeZone.compare("") == 0) {
        QMessageBox::critical(0,"Incomplete data", "You must specify place and timezone");
    } else {
        emit chartDataChanged(
                    _currentCountryCode,
                    _currentCountryName,
                    _currentPlaceName,
                    _currentLatitudeCents,
                    _currentLongitudeCents,
                    _currentTimeZone,
                    _year,
                    _month,
                    _day,
                    _hour,
                    _minute);
    }
}

MyChartInput::~MyChartInput()
{
     if (_countryInfo != 0) {
        GeoData::free(_countryInfo);
    }
    if (_placeInfo != 0) {
        GeoData::free(_placeInfo);
    }
    if (zoneList != 0) {
        delete zoneList;
    }
}
