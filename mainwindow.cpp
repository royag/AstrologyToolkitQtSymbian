#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qfile.h"
#include "qiodevice.h"
#include "qdatastream.h"

#include "time.h"

#include "cpp_core/astrodefs.h"
#include "cpp_core/house_calc.h"

#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>


#include <QTime>
#include <QDateTime>
#include <QDate>
#include <QList>
#include <QPixmap>

#include "cpp_core/timezoneinfo.h"
#include "cpp_core/geodata.h"

//#include "chartdraw.h"
#include "math.h"

#include <QApplication>
#include <QMenuBar>
#include "hwqt/hwqwertyinput.h"

#include <QListWidget>
#include <QListWidgetItem>
#include "cpp_core/geodata.h"
//#include "hwqt/hwcomboinput.h"
#include <QRect>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QInputDialog>

#include <QGeoPositionInfoSource>
#include <QDir>
#include "cpp_core/house_calc.h"

#include <mychartopendialog.h>
#include <QProgressDialog>

QTM_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    chartInput(0),
    chartOpener(0),
    vipChartOpener(0),
    ui(new Ui::MainWindow),
    geoInfoSource(0),
    lastChartName(QString::null),
    lastCompareChartName(QString::null)
{
    ui->setupUi(this);

    ui->labelChartInfo1->setVisible(false);
    ui->labelChartInfo2->setVisible(false);

    chartView = new QHWAstroChartView(ui->tabChart); //centralWidget);
    ui->chartTabLayout->insertWidget(0, chartView);

    setupAnimationButtons();
    setAnimateToolVisible(false);

    m_countryInfo = GeoData::loadCountryInfo();

    QMenu* chartMenu = menuBar()->addMenu(tr("Chart"));
    actionNewChart = new QAction(tr("New chart..."), this);
    connect(actionNewChart, SIGNAL(triggered()), this, SLOT(inputNewChartData()));
    chartMenu->addAction(actionNewChart);

    actionOpenChart = new QAction(tr("Open chart..."), this);
    connect(actionOpenChart, SIGNAL(triggered()), this, SLOT(openChart()));
    chartMenu->addAction(actionOpenChart);

    actionSaveChart = new QAction(tr("Save as"), this);
    connect(actionSaveChart, SIGNAL(triggered()), this, SLOT(saveChart()));
    chartMenu->addAction(actionSaveChart);



    actionChartVIP = new QAction(tr("VIP charts"), this);
    connect(actionChartVIP, SIGNAL(triggered()), this, SLOT(openVIPChart()));
    chartMenu->addAction(actionChartVIP);

    actionChartNow = new QAction(tr("Chart for Now"), this);
    connect(actionChartNow, SIGNAL(triggered()), this, SLOT(chartHereAndNow()));
    chartMenu->addAction(actionChartNow);

    ////////////

    QMenu* compareChartMenu = menuBar()->addMenu(tr("Compare to"));

    actionOpenCompareChart = new QAction(tr("saved chart"), this);
    connect(actionOpenCompareChart, SIGNAL(triggered()), this, SLOT(openCompareChart()));
    compareChartMenu->addAction(actionOpenCompareChart);

    QAction* actionOpenVIPCompareChart = new QAction(tr("VIP chart"), this);
    connect(actionOpenVIPCompareChart, SIGNAL(triggered()), this, SLOT(openVIPCompareChart()));
    compareChartMenu->addAction(actionOpenVIPCompareChart);


    actionTransits = new QAction(tr("Show/Hide Transits"), this);
    connect(actionTransits, SIGNAL(triggered()), this, SLOT(showTransits()));
    menuBar()->addAction(actionTransits);

    //////// HOUSES:
    QMenu* houseMenu = menuBar()->addMenu(tr("House System"));

    actionHousesPlacidus = new QAction(tr("Placidus"), this);
    connect(actionHousesPlacidus, SIGNAL(triggered()), this, SLOT(setHousesPlacidus()));
    houseMenu->addAction(actionHousesPlacidus);

    actionHousesKoch = new QAction(tr("Koch"), this);
    connect(actionHousesKoch, SIGNAL(triggered()), this, SLOT(setHousesKoch()));
    houseMenu->addAction(actionHousesKoch);

    actionHousesNULL = new QAction(tr("NULL"), this);
    connect(actionHousesNULL, SIGNAL(triggered()), this, SLOT(setHousesNULL()));
    houseMenu->addAction(actionHousesNULL);

    actionHousesEqualASC = new QAction(tr("Equal"), this);
    connect(actionHousesEqualASC, SIGNAL(triggered()), this, SLOT(setHousesEqualASC()));
    houseMenu->addAction(actionHousesEqualASC);

    actionHousesWholeVedic = new QAction(tr("Whole/Vedic"), this);
    connect(actionHousesWholeVedic, SIGNAL(triggered()), this, SLOT(setHousesWholeVedic()));
    houseMenu->addAction(actionHousesWholeVedic);

    actionHousesPorphyry = new QAction(tr("Porphyry"), this);
    connect(actionHousesPorphyry, SIGNAL(triggered()), this, SLOT(setHousesPorphyry()));
    houseMenu->addAction(actionHousesPorphyry);
    //////////

    actionAnimateOnOff = new QAction(tr("Animate on/off"), this);
    connect(actionAnimateOnOff, SIGNAL(triggered()), this, SLOT(animateOnOff()));
    menuBar()->addAction(actionAnimateOnOff);

    QAction* actionAbout = new QAction(tr("About"), this);
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(aboutApp()));
    menuBar()->addAction(actionAbout);


     update();
     //show();
     int w = this->width();
     QRect r = geometry();
     chartInput = new MyChartInput(this);
     chartInput->setObjectName("chartInput");
     chartInput->hide();
     chartInput->setGeometry(0,0,r.width(),r.height());

     connect(chartInput, SIGNAL(cancelled()), this, SLOT(inputDataCancelled()));
     connect(chartInput, SIGNAL(chartDataChanged(QString,QString,QString,int,int,QString,int,int,int,int,int)),
             this, SLOT(chartDataChanged(QString,QString,QString,int,int,QString,int,int,int,int,int)));

     /* TODO ? Can we remove this ?:
QAction *inpDone = new QAction(tr("DONE NOW"), chartInput);
      inpDone->setSoftKeyRole(QAction::PositiveSoftKey);
      chartInput->addAction(inpDone);
      connect(inpDone, SIGNAL(triggered()), this, SLOT(newChartDataInputted()));
*/
     chartOpener = new MyChartOpenWindow(this, QApplication::applicationDirPath());
     chartOpener->setObjectName("chartOpener");
     chartOpener->hide();
     chartOpener->setGeometry(0,0,r.width(),r.height());
     connect(chartOpener, SIGNAL(selectedFile(QString)), this, SLOT(chartFileSelected(QString)));
     connect(chartOpener, SIGNAL(cancelled()), this, SLOT(chartOpenCancelled()));

     chartCompareOpener = new MyChartOpenWindow(this, QApplication::applicationDirPath());
     chartCompareOpener->setObjectName("chartOpener");
     chartCompareOpener->setHeaderText("Compare to");
     chartCompareOpener->hide();
     chartCompareOpener->setGeometry(0,0,r.width(),r.height());
     connect(chartCompareOpener, SIGNAL(selectedFile(QString)), this, SLOT(chartCompareFileSelected(QString)));
     connect(chartCompareOpener, SIGNAL(cancelled()), this, SLOT(chartCompareFileCancelled()));


     QString appDirPath = QApplication::applicationDirPath();
     QString vipDirPath = appDirPath + "/vip";
     QDir vipDir(vipDirPath);
     bool vipOk = true;
     if (!vipDir.exists()) {
         QDir appDir(appDirPath);
         if (!appDir.mkdir("vip")) {
             vipOk = false;
         }
     }

     vipChartOpener = new MyChartOpenWindow(this, vipDirPath,
                                            true,
                                            QString("http://www.leapinglight.com/astro/vip"));
     vipChartOpener->setObjectName("vipChartOpener");
     vipChartOpener->setHeaderText("Open VIP chart");
     vipChartOpener->hide();
     vipChartOpener->setGeometry(0,0,r.width(),r.height());
     connect(vipChartOpener, SIGNAL(selectedFile(QString)), this, SLOT(vipChartFileSelected(QString)));
     connect(vipChartOpener, SIGNAL(cancelled()), this, SLOT(vipChartOpenCancelled()));


     vipChartCompareOpener = new MyChartOpenWindow(this, vipDirPath,
                                            true,
                                            QString("http://www.leapinglight.com/astro/vip"));
     vipChartCompareOpener->setObjectName("vipChartOpener");
     vipChartCompareOpener->setHeaderText("Compare to VIP");
     vipChartCompareOpener->hide();
     vipChartCompareOpener->setGeometry(0,0,r.width(),r.height());
     connect(vipChartCompareOpener, SIGNAL(selectedFile(QString)), this, SLOT(vipChartCompareFileSelected(QString)));
     connect(vipChartCompareOpener, SIGNAL(cancelled()), this, SLOT(vipChartCompareFileCancelled()));


     searchResultChartOpener = new MyChartOpenWindow(this, QString::null, false);
     searchResultChartOpener->setObjectName("searchResultChartOpener");
     searchResultChartOpener->hide();
     searchResultChartOpener->setGeometry(0,0,r.width(),r.height());

     connect(searchResultChartOpener, SIGNAL(selectedFile(QString)), this, SLOT(searchResultChartFileSelected(QString)));
     connect(searchResultChartOpener, SIGNAL(cancelled()), this, SLOT(searchResultChartOpenCancelled()));

      aspectTableFrame = new InfoFrame(ui->tabAspects);
      ui->aspectFrameLayout->addWidget(aspectTableFrame);
      aspectTableFrame->setEscapable(false);
      aspectTableFrame->setObjectName("aspectInfoFrame");
      aspectTableFrame->setLabelName("aspectInfoFrameLabel");
      connect(chartView, SIGNAL(aspectTableChanged(QString)), this, SLOT(aspectTableUpdated(QString)));

      connect(chartView->infoFrame, SIGNAL(wantSearchForPlacement(int,int,int,int,int)),
              this, SLOT(searchForPlacement(int,int,int,int,int)));

    setWindowTitle(tr("Astrology Toolkit"));

    //populateGraphics();
    //chartHereAndNow();

    int thisYear = QDateTime::currentDateTime().toUTC().date().year();
    preloadedYear = (EPHEM_YEAR*)malloc(sizeof(EPHEM_YEAR));
    ephem_readYear(thisYear, preloadedYear);

    chartNowWithoutGPS();

    mainLayoutVertical = new QVBoxLayout(centralWidget());
    mainLayoutHorizontal = new QHBoxLayout(centralWidget());

    QAction* actionExit = new QAction(tr("Exit"), this);
    actionExit->setSoftKeyRole(QAction::NegativeSoftKey);
    addAction(actionExit);

    connect(actionExit, SIGNAL(triggered()),
            this, SLOT(exitApp()));

    //setLayoutVertical(true);
}

void MainWindow::setLayoutVertical(bool vertical) {
    mainLayoutVertical->removeWidget(ui->tabWidget);
    mainLayoutVertical->removeWidget(ui->infoFrame);
    mainLayoutHorizontal->removeWidget(ui->tabWidget);
    mainLayoutHorizontal->removeWidget(ui->infoFrame);
    if (vertical) {
        mainLayoutVertical->addWidget(ui->infoFrame);
        mainLayoutVertical->addWidget(ui->tabWidget);
        mainLayoutVertical->setGeometry(geometry());
    } else {
        mainLayoutHorizontal->addWidget(ui->infoFrame);
        mainLayoutHorizontal->addWidget(ui->tabWidget);
        mainLayoutHorizontal->setGeometry(geometry());
    }
}

void MainWindow::preloadIfNotYearIs(int year) {
    if (preloadedYear->days[0].year != year) {
        qDebug("Loading year %i", year);
        ephem_readYear(year, preloadedYear);
        qDebug("DONE Loading year %i", year);
    } else {
        qDebug("Reusing year %i", year);
    }
}


QString MainWindow::shortenLeft(QString s, int len) {
    QString ret = s;
    if (ret.size() > len) {
        ret.remove(0,ret.size()-(len-2));
        ret = ".." + ret;
    }
    return ret;
}

QString MainWindow::shortenRight(QString s, int len) {
    QString ret = s;
    if (ret.size() > len) {
        ret.truncate(len-2);
        ret = ret + "..";
    }
    return ret;
}


QString MainWindow::shortenZone(QString tzone) {
    return shortenLeft(tzone, 13);
}

/*void MainWindow::showPlanetInfo(int planet) {
    ui->labelPlace->setText(tr("planet=") + QString::number(planet));
}

void MainWindow::showComparisonPlanetInfo(int planet) {
    ui->labelPlace->setText(tr("compPlanet=") + QString::number(planet));
}

void MainWindow::showAspectInfo(int planet1, int planet2) {
    ui->labelPlace->setText(tr("aspect=") + QString::number(planet1) + tr("vs") + QString::number(planet2));
}*/

void MainWindow::setHousesNULL(){
    chartView->changeHouseSystem(HOUSES_NULL);
    ui->labelHouse->setText(chartView->currentHouseSystemName() + " houses");
}

void MainWindow::setHousesEqualASC() {
    chartView->changeHouseSystem(HOUSES_EQUAL_ASC);
    ui->labelHouse->setText(chartView->currentHouseSystemName() + " houses");
}

void MainWindow::setHousesWholeVedic() {
    chartView->changeHouseSystem(HOUSES_WHOLE_VEDIC);
    ui->labelHouse->setText(chartView->currentHouseSystemName() + " houses");
}

void MainWindow::setHousesPorphyry() {
    chartView->changeHouseSystem(HOUSES_PORPHYRY);
    ui->labelHouse->setText(chartView->currentHouseSystemName() + " houses");
}

void MainWindow::setHousesPlacidus() {
    chartView->changeHouseSystem(HOUSES_PLACIDUS);
    ui->labelHouse->setText(chartView->currentHouseSystemName() + " houses");
}

void MainWindow::setHousesKoch() {
    chartView->changeHouseSystem(HOUSES_KOCH);
    ui->labelHouse->setText(chartView->currentHouseSystemName() + " houses");
}

void MainWindow::setAnimateToolVisible(bool isIt) {
    //ui->labelAnimateInfo->setVisible(isIt);
    ui->btnAnimateBackLarge->setVisible(isIt);
    ui->btnAnimateBackStep->setVisible(isIt);
    ui->btnAnimateForwardLarge->setVisible(isIt);
    ui->btnAnimateForwardStep->setVisible(isIt);
    ui->labelChartInfo2->setVisible(!isIt);
}

void MainWindow::animateOnOff() {
    if (ui->btnAnimateBackLarge->isVisible()) {
        setAnimateToolVisible(false);
    } else {
        setAnimateToolVisible(true);
    }
}


void MainWindow::animateBackLarge() {
    if (chartView->isComparisonChart()) {
        adjustCompareChart(0,0,-1,0,0);
    } else {
        adjustChart(0,0,-1,0,0);
    }
}

void MainWindow::animateBackStep() {
    if (chartView->isComparisonChart()) {
        adjustCompareChart(0,0,0,-1,0);
    } else {
        adjustChart(0,0,0,-1,0);
    }
}

void MainWindow::animateForwardLarge() {
    if (chartView->isComparisonChart()) {
        adjustCompareChart(0,0,1,0,0);
    } else {
        adjustChart(0,0,1,0,0);
    }
}

void MainWindow::animateForwardStep() {
    if (chartView->isComparisonChart()) {
        adjustCompareChart(0,0,0,1,0);
    } else {
        adjustChart(0,0,0,1,0);
    }
}

QString MainWindow::filterFileName(const QString & fn) {
    QString ret = "";
    QChar c;
    for (int i = 0; i < fn.length(); i++) {
        c = fn.at(i);
        if ((c >= QChar('a') && c <= QChar('z')) ||
            (c >= QChar('A') && c <= QChar('Z')) ||
            (c >= QChar('0') && c <= QChar('9'))
            ) {
                ret.append(c);
            } else {
                ret.append("_");
            }
    }
    return ret;
}


void MainWindow::saveChart() {

    QString chartData =
        currentChartData.countryCode + tr("\n") +
        currentChartData.country + tr("\n") +
        currentChartData.placeName + tr("\n") +
        QString::number(currentChartData.latitudeCents) + tr("\n") +
        QString::number(currentChartData.longitudeCents) + tr("\n") +
        currentChartData.timeZone + tr("\n") +
        QString::number(currentChartData.year) + tr("\n") +
        QString::number(currentChartData.month) + tr("\n") +
        QString::number(currentChartData.day) + tr("\n") +
        QString::number(currentChartData.hour) + tr("\n") +
        QString::number(currentChartData.minute) + tr("\n");


    QString defaultName =
        QString::number(currentChartData.year) +
        QString::number(currentChartData.month).rightJustified(2,'0') +
        QString::number(currentChartData.day).rightJustified(2,'0') +
        '_' + QString::number(currentChartData.hour).rightJustified(2,'0') +
        QString::number(currentChartData.minute).rightJustified(2,'0') +
        '_' + currentChartData.countryCode;

    bool ok = false;
    QString fileFirstName = QInputDialog::getText(this, tr("Save as"),
                                              tr("File name:"), QLineEdit::Normal,
                                              defaultName, &ok);
    if (ok && !fileFirstName.isEmpty()) {
        fileFirstName = filterFileName(fileFirstName);
        QString chartFileName =
                QApplication::applicationDirPath() + "/" +
                fileFirstName +
                ".chr";
        QFile file(chartFileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Could not save file");
            return;
        }
        QTextStream out(&file);
        out << chartData;
        // optional, as QFile destructor will already do it:
        file.close();
    }
}

void MainWindow::showChartOpener(MyChartOpenWindow* opener) {
    ui->centralWidget->hide();

    opener->reloadDir();
    opener->show();
    opener->update();
    opener->repaint();
    opener->setFocus();
}

void MainWindow::openChart() {
    showChartOpener(chartOpener);
}

void MainWindow::openCompareChart() {
    showChartOpener(chartCompareOpener);
}

void MainWindow::openVIPChart() {
    showChartOpener(vipChartOpener);
}

void MainWindow::openVIPCompareChart() {
    showChartOpener(vipChartCompareOpener);
}


void MainWindow::searchForPlanetInHouse(int planet, int house) {
    searchForPlacement(planet, -1, house, -1, -1);
}

void MainWindow::searchForPlanetInSign(int planet, int sign) {
    searchForPlacement(planet, sign, -1, -1, -1);
}

void MainWindow::searchForAspect(int planet, int planet2, int aspect) {
    searchForPlacement(planet, -1, -1, aspect, planet2);
}

planet_positions MainWindow::calcPositionsForChart(QString chartFile) {
    QFile file(chartFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    //QString s = in.readAll();
    //QStringList chartData = s.split('\n');

    in.readLine(200);
    in.readLine(200);
    in.readLine(200);
    int latitude = in.readLine(200).toInt();
    int longitude = in.readLine(200).toInt();
    QString timeZone = in.readLine(200);
    int year = in.readLine(200).toInt();
    int month = in.readLine(200).toInt();
    int day = in.readLine(200).toInt();
    int hour = in.readLine(200).toInt();
    int minute = in.readLine(200).toInt();
    file.close();

    /*int latitude = chartData.at(3).toInt();
    int longitude = chartData.at(4).toInt();
    QString timeZone = chartData.at(5);
    int year = chartData.at(6).toInt();
    int month = chartData.at(7).toInt();
    int day = chartData.at(8).toInt();
    int hour = chartData.at(9).toInt();
    int minute = chartData.at(10).toInt();*/
    return calcPlanetPositionsFor(latitude, longitude, timeZone,
                               year,month,day,hour,minute,true);
}

void MainWindow::searchForPlacement(int planet, int sign, int house, int aspect, int planet2) {
    QString appDirPath = QApplication::applicationDirPath();
    QString vipDirPath = appDirPath + "/vip";
    QDir mydir(appDirPath);
    QStringList e = mydir.entryList(QStringList("*.chr"));
    QDir mydirVip(vipDirPath);
    QStringList eVip = mydirVip.entryList(QStringList("*.chr"));

    QStringListIterator it(e);
    QStringListIterator itVip(eVip);
    planet_positions pp;

    float houses[12];
    int houseSystem = HOUSES_PORPHYRY;

    int numFiles = e.size() + eVip.size();
    int i = 0;

    QProgressDialog progress("Searching...", "Abort", 0, numFiles, this);
    progress.setWindowModality(Qt::WindowModal);

    QStringList matches;
    QString chrName;
    while (it.hasNext() || itVip.hasNext()) {
        progress.setValue(i); i++;
        if (progress.wasCanceled()) {
            break;
        }
        bool vip = !it.hasNext();
        if (vip) {
            chrName = "vip/" + itVip.next();
        } else {
            chrName = it.next();
        }
        pp = calcPositionsForChart(QApplication::applicationDirPath() + "/" + chrName);
        bool ok = true;
        if (ok && sign > -1) {
            if (sign != ephem_signForPosition(ephem_positionOfPlanet(pp, planet))) ok = false;
        }
        if (ok && house > -1) {
            calcHouses((float*)&houses, pp, houseSystem);
            if (house != houses_houseOfPosition(ephem_positionOfPlanet(pp,planet), (float*)&houses)) ok = false;
        }
        if (ok && aspect > -1 && planet2 > -1) {
            if (aspect != getAspect(ephem_positionOfPlanet(pp,planet), ephem_positionOfPlanet(pp,planet2)))
                ok = false;
        }
        if (ok) {
            matches.append(chrName);
        }
    }
    //progress.
    if (matches.size() < 1) {
        QMessageBox::information(this, "Search result", "No matches");
    } else {

        QString desc = "";
        if (aspect > -1) {
            desc += QString(PLANET_FULL_NAMES[planet]) + " " +
                    QString(ephem_nameOfAspect(aspect)) + " " +
                    QString(PLANET_FULL_NAMES[planet2]) + " ";
        }
        if (house > -1) {
            desc +=
                 QString(PLANET_FULL_NAMES[planet]) + " in " +
                 QString(HOUSE_NAMES[house]) + " house ";
        }
        if (sign > -1) {
            desc +=
                 QString(PLANET_FULL_NAMES[planet]) + " in " +
                 QString(SIGN_NAMES[sign]) + " ";
        }

        ui->centralWidget->hide();
        searchResultChartOpener->setHeaderText("Charts w/" + desc + ":");
        searchResultChartOpener->setFilenames(matches);
        searchResultChartOpener->show();
        searchResultChartOpener->update();
        searchResultChartOpener->repaint();
        searchResultChartOpener->setFocus();
    }
}


void MainWindow::chartFileSelected(QString fn) {
    chartOpenCancelled();
    if (!fn.isNull()) {
        MainWindow::loadChartFile(fn);
    }
}

void MainWindow::vipChartFileSelected(QString fn) {
    vipChartOpenCancelled();
    if (!fn.isNull()) {
        MainWindow::loadChartFile(fn);
    }
}

void MainWindow::chartCompareFileSelected(QString fn) {
    chartCompareFileCancelled();
    if (!fn.isNull()) {
        MainWindow::loadCompareChartFile(fn);
    }
}

void MainWindow::vipChartCompareFileSelected(QString fn) {
    vipChartCompareFileCancelled();
    if (!fn.isNull()) {
        MainWindow::loadCompareChartFile(fn);
    }
}

void MainWindow::searchResultChartFileSelected(QString fn) {
    searchResultChartOpenCancelled();
    if (!fn.isNull()) {
        MainWindow::loadChartFile(QApplication::applicationDirPath() + "/" + fn);
    }
}


void MainWindow::loadChartFile(QString fn) {
    if (!fn.isNull()) {
        QFile file(fn);
        QString chrName = QFileInfo(file).fileName();
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        QString s = in.readAll();
        file.close();
        QStringList chartData = s.split('\n');
        setAnimateToolVisible(false);
        chartDataChanged(
                chartData.at(0),
                chartData.at(1),
                chartData.at(2),
                chartData.at(3).toInt(),
                chartData.at(4).toInt(),
                chartData.at(5),
                chartData.at(6).toInt(),
                chartData.at(7).toInt(),
                chartData.at(8).toInt(),
                chartData.at(9).toInt(),
                chartData.at(10).toInt(),
                chrName
                );
    }
}


void MainWindow::loadCompareChartFile(QString fn) {
    if (!fn.isNull()) {
        QFile file(fn);
        QString chrName = QFileInfo(file).fileName();
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);

        QString s = in.readAll();

        file.close();

        QStringList chartData = s.split('\n');


        setAnimateToolVisible(false);
        chartCompareDataChanged(
                chartData.at(0),
                chartData.at(1),
                chartData.at(2),
                chartData.at(3).toInt(),
                chartData.at(4).toInt(),
                chartData.at(5),
                chartData.at(6).toInt(),
                chartData.at(7).toInt(),
                chartData.at(8).toInt(),
                chartData.at(9).toInt(),
                chartData.at(10).toInt(),
                false,
                chrName
                );
    }
}


void MainWindow::positionUpdated(QGeoPositionInfo posInfo) {
    int latitudeCents = posInfo.coordinate().latitude() * 100;
    int longitudeCents = posInfo.coordinate().longitude() * 100;
    geoInfoSource->stopUpdates();
    QDateTime ut = QDateTime::currentDateTime().toLocalTime(); //.toUTC();
    chartDataChanged(
            "Here", //QString countryCode,
            "Here", //QString country,
            "Here and now", //QString placeName,
            latitudeCents,
            longitudeCents,
            QString("DeviceLocal"), //QString timeZone,
            ut.date().year(),
            ut.date().month(),
            ut.date().day(),
            ut.time().hour(),
            ut.time().minute());
    setAnimateToolVisible(true);
}

void MainWindow::chartNowWithoutGPS() {
    QGeoPositionInfo posInfo;
    if (geoInfoSource == 0) {
        geoInfoSource = QGeoPositionInfoSource::createDefaultSource(this);
        if (geoInfoSource) {
            geoInfoSource->setUpdateInterval(1000); // time in milliseconds
            geoInfoSource->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
            connect(geoInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
            connect(geoInfoSource, SIGNAL(updateTimeout()), this, SLOT(positionUpdateTimedOut()));
        }
    }
    if (geoInfoSource) {
        posInfo = geoInfoSource->lastKnownPosition();
    }

    int latitudeCents = 5128;
    int longitudeCents = 0;
    QString countryCode = "UK";
    QString country = "United Kingdom";
    QString placeName = "Greenwich";

    if ((!posInfo.isValid()) ||
        (!posInfo.coordinate().isValid() ||
         (posInfo.coordinate().latitude() == 0 && posInfo.coordinate().longitude() == 0))) {
    } else {
        countryCode = "Here";
        country = "Here";
        placeName = "Last known position";
        latitudeCents = posInfo.coordinate().latitude() * 100;
        longitudeCents = posInfo.coordinate().longitude() * 100;
    }

    QDateTime ut = QDateTime::currentDateTime().toLocalTime(); //.toUTC();
    chartDataChanged(
            countryCode,
            country,
            placeName,
            latitudeCents,
            longitudeCents,
            QString("DeviceLocal"), //QString timeZone,
            ut.date().year(),
            ut.date().month(),
            ut.date().day(),
            ut.time().hour(),
            ut.time().minute());
    setAnimateToolVisible(true);
}


void MainWindow::showTransits() {
    if (!chartView->isShowingTransits()) {
        QDateTime ut = QDateTime::currentDateTime().toLocalTime();
        chartCompareDataChanged(
                "NOW", //QString countryCode,
                "HERE", //QString country,
                "Here and now", //QString placeName,
                currentChartData.latitudeCents,
                currentChartData.longitudeCents,
                tr("DeviceLocal"), //QString timeZone,
                ut.date().year(),
                ut.date().month(),
                ut.date().day(),
                ut.time().hour(),
                ut.time().minute(),
                true);
        setAnimateToolVisible(true);
    } else {
        chartView->removeComparisonPositions();
        setAnimateToolVisible(false);
        if (lastChartName.isNull()) {
            ui->labelChartInfo1->setVisible(false);
        } else {
            ui->labelChartInfo1->setVisible(true);
            ui->labelChartInfo1->setText("Chart: " + shortenRight(lastChartName,20));
        }
    }
}

void MainWindow::positionUpdateTimedOut() {
    //qDebug("positioning timed out");
    chartNowWithoutGPS();
}

void MainWindow::chartHereAndNow() {
    int updateTimeoutMs = 20000;
    if (geoInfoSource == 0) {
        geoInfoSource = QGeoPositionInfoSource::createDefaultSource(this);
        if (geoInfoSource) {
            geoInfoSource->setUpdateInterval(1000); // time in milliseconds
            geoInfoSource->setPreferredPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
            connect(geoInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
            connect(geoInfoSource, SIGNAL(updateTimeout()), this, SLOT(positionUpdateTimedOut()));
        }
    }
    if (geoInfoSource) {
        geoInfoSource->startUpdates();
        geoInfoSource->requestUpdate(updateTimeoutMs);
    } else {
        chartNowWithoutGPS();
    }
}

void MainWindow::resizeEvent(QResizeEvent *e) {
    //e->size()
    QRect r = geometry();
    if (chartInput != 0) {
        chartInput->setGeometry(0,0,r.width(),r.height());
    }
    if (chartOpener != 0) {
        chartOpener->setGeometry(0,0,r.width(),r.height());
    }
    if (vipChartOpener != 0) {
        vipChartOpener->setGeometry(0,0,r.width(),r.height());
    }
    if (chartCompareOpener != 0) {
        chartCompareOpener->setGeometry(0,0,r.width(),r.height());
    }
    if (vipChartCompareOpener != 0) {
        vipChartCompareOpener->setGeometry(0,0,r.width(),r.height());
    }
    if (searchResultChartOpener != 0) {
        searchResultChartOpener->setGeometry(0,0,r.width(),r.height());
    }
    setLayoutVertical(r.height() > r.width());

}

/*void MainWindow::populateGraphics() {
    planet_positions pp = ephem_calculateRecForGmt(1978, 4, 12, 18, 20, 0); // ,&(this->ephemYear));
    //planet_positions pp = ephem_calculateRecForGmt(2010, 12, 31, 18, 20, 0); // ,&(this->ephemYear));
    calcAscAndMc(&pp, 59.44, 10.15);

    chartView->setPositions(pp);
}*/

QString posToString(float pos) {
    char signName[10];
    ephem_positionToChar6(pos, (char*)&signName);
    return QString((char*)&signName);
}

QString toString(planet_positions rec) {
    QString ret = "";
    ret += ",weekday=" + QString::number(rec.weekday);
    //ret += ",year=" + QString::number(rec.year);
    ret += ",sun=" + posToString(rec.sun);
    ret += ",moon=" + posToString(rec.moon);
    ret += ",mercury=" + posToString(rec.mercury);
    ret += ",venus=" + posToString(rec.venus);
    ret += ",mars=" + posToString(rec.mars);
    ret += ",jupiter=" + posToString(rec.jupiter);
    ret += ",saturn=" + posToString(rec.saturn);
    ret += ",uranus=" + posToString(rec.uranus);
    ret += ",neptune=" + posToString(rec.neptune);
    ret += ",pluto=" + posToString(rec.pluto);
    ret += ",node=" + posToString(rec.node);
    ret += ",ASC=" + posToString(rec.ascendant);
    ret += ",MC=" + posToString(rec.mediumCoeli);
    return ret;
}

/*void MainWindow::testZone() {

    //TimeZoneInfo* tz = new TimeZoneInfo(":/data/Oslo");
    TimeZoneInfo* tz = new TimeZoneInfo(":/data/New_York"); //Hong_Kong");
    SimpleTime time = tz->toUTC(1978,4,12,19,20);

    int a = 2;

    delete tz;
}*/

void MainWindow::inputDataCancelled() {
    /*chartInput->hide();
    ui->centralWidget->show();
    ui->centralWidget->update();
    ui->centralWidget->setFocus();*/
    hideDialogWindow(chartInput);
}

void MainWindow::hideDialogWindow(QWidget* window) {
    window->hide();
    ui->centralWidget->show();
    ui->centralWidget->update();
    ui->centralWidget->setFocus();
}

void MainWindow::chartOpenCancelled(){
    hideDialogWindow(chartOpener);
    /*chartOpener->hide();
    ui->centralWidget->show();
    ui->centralWidget->update();
    ui->centralWidget->setFocus();*/
}
void MainWindow::vipChartOpenCancelled(){
    hideDialogWindow(vipChartOpener);
    /*vipChartOpener->hide();
    ui->centralWidget->show();
    ui->centralWidget->update();
    ui->centralWidget->setFocus();*/
}

void MainWindow::searchResultChartOpenCancelled(){
    hideDialogWindow(searchResultChartOpener);
    /*searchResultChartOpener->hide();
    ui->centralWidget->show();
    ui->centralWidget->update();
    ui->centralWidget->setFocus();*/
}

void MainWindow::chartCompareFileCancelled() {
    hideDialogWindow(chartCompareOpener);
}
void MainWindow::vipChartCompareFileCancelled() {
    hideDialogWindow(vipChartCompareOpener);
}


SimpleTime MainWindow::makeUTC(QString timeZone,int year,int month,int day,int hour,int minute) {
    SimpleTime utc;
    if (timeZone.compare("DeviceLocal") == 0) {
        QDate d = QDate(year,month,day);
        QDateTime dt = QDateTime(d, QTime(hour,minute),Qt::LocalTime);
        QDateTime dtUTC = dt.toUTC();
        utc.year = dtUTC.date().year();
        utc.month = dtUTC.date().month();
        utc.day = dtUTC.date().day();
        utc.hour = dtUTC.time().hour();
        utc.minute = dtUTC.time().minute();
    } else {
        TimeZoneInfo* tz = new TimeZoneInfo(timeZone);
        utc = tz->toUTC(year,month,day,hour,minute);
    }
    return utc;
}

planet_positions MainWindow::calcPlanetPositionsFor(
        int latitudeCents,
        int longitudeCents,
        QString timeZone,
        int year,
        int month,
        int day,
        int hour,
        int minute,
        bool usePreloading) {
    SimpleTime utc = makeUTC(timeZone,year,month,day,hour,minute);
    planet_positions p;
    if (usePreloading) {
        preloadIfNotYearIs(utc.year);
        p = ephem_calculateRecForGmt(utc.year,utc.month,utc.day,utc.hour, utc.minute, 0, preloadedYear);
    } else {
        p = ephem_calculateRecForGmt(utc.year,utc.month,utc.day,utc.hour, utc.minute, 0);
    }
    calcAscAndMc(&p, latitudeCents/100.0, longitudeCents/100.0);
    return p;
}


void MainWindow::chartDataChanged(
        QString countryCode,
        QString country,
        QString placeName,
        int latitudeCents,
        int longitudeCents,
        QString timeZone,
        int year,
        int month,
        int day,
        int hour,
        int minute,
        QString chartName) {

    lastChartName = chartName;

    currentChartData.countryCode = countryCode;
    currentChartData.country = country;
    currentChartData.placeName = placeName;
    currentChartData.latitudeCents = latitudeCents;
    currentChartData.longitudeCents = longitudeCents;
    currentChartData.timeZone = timeZone;
    currentChartData.year = year;
    currentChartData.month = month;
    currentChartData.day = day;
    currentChartData.hour = hour;
    currentChartData.minute = minute;

    chartInput->hide();
    ui->centralWidget->show();
    ui->centralWidget->update();
    ui->centralWidget->setFocus();

    SimpleTime utc = makeUTC(timeZone,year,month,day,hour,minute);

    QString utcInfo =
            QString::number(utc.year) + "-" + QString::number(utc.month)+ "-" + QString::number(utc.day) + " "
            + QString::number(utc.hour) + ":" +
            (utc.minute < 10 ? "0" : "") + QString::number(utc.minute);

    QString localtimeInfo =
            QString::number(year) + "-" + QString::number(month)+ "-" + QString::number(day) + " "
            + QString::number(hour) + ":" +
            (minute < 10 ? "0" : "") + QString::number(minute);

    ui->labelTime->setText(localtimeInfo);
    ui->labelTime2->setText("(" + utcInfo + " UTC)");
    ui->labelZone->setText("Zone: " + shortenZone(timeZone));
    ui->labelHouse->setText(chartView->currentHouseSystemName() + " houses");
    ui->labelPlace->setText(country + "/" + placeName +
                             " (" + GeoData::coordinatesToString(latitudeCents,longitudeCents) + ")");

    //planet_positions pp = ephem_calculateRecForGmt(1978, 4, 12, 18, 20, 0); // ,&(this->ephemYear));
    //calcAscAndMc(&pp, 59.44, 10.15);

    //qDebug("Preload if wrong year");
    preloadIfNotYearIs(utc.year);
    //qDebug("Preloading/check done");
    //qDebug("Preloading/check done..calc POS:");
    planet_positions p =
            ephem_calculateRecForGmt(utc.year, utc.month, utc.day,
                                     utc.hour, utc.minute, 0, preloadedYear);
    //qDebug("next calc ASC/MC...");
    calcAscAndMc(&p, latitudeCents/100.0/*59.44*/, longitudeCents/100.0/*10.15*/);
    //qDebug("next removeComp...");
    chartView->removeComparisonPositions();
    //qDebug("next setPos...");
    chartView->setPositions(p);
    //qDebug("next updateLabel...");
    if (chartName.isNull()) {
        ui->labelChartInfo1->setVisible(false);
    } else {
        ui->labelChartInfo1->setVisible(true);
        ui->labelChartInfo1->setText("Chart: " + shortenRight(chartName,20));
    }
    //qDebug("next return...");
}

void MainWindow::adjustChart(int year,int month, int day, int hour, int min) {
    QDateTime dt(QDate(currentChartData.year,currentChartData.month,currentChartData.day),
                 QTime(currentChartData.hour,currentChartData.minute));
    dt = dt.addYears(year);
    dt = dt.addMonths(month);
    dt = dt.addDays(day);
    dt = dt.addSecs((hour*60*60) + (min * 60));


    chartDataChanged(
            currentChartData.countryCode,
            currentChartData.country,
            currentChartData.placeName,
            currentChartData.latitudeCents,
            currentChartData.longitudeCents,
            currentChartData.timeZone,
            dt.date().year(),
            dt.date().month(),
            dt.date().day(),
            dt.time().hour(),
            dt.time().minute());
}

void MainWindow::adjustCompareChart(int year,int month, int day, int hour, int min) {
    QDateTime dt(QDate(compareChartData.year,compareChartData.month,compareChartData.day),
                 QTime(compareChartData.hour,compareChartData.minute));
    dt = dt.addYears(year);
    dt = dt.addMonths(month);
    dt = dt.addDays(day);
    dt = dt.addSecs((hour*60*60) + (min * 60));

    /*ui->labelAnimateInfo->setText(
            QString::number(dt.date().year()) + QString("-") +
            QString::number(dt.date().month()) + QString("-") +
            QString::number(dt.date().day()) + QString(" ") +
            QString::number(dt.time().hour()) + QString(":") +
            QString::number(dt.time().minute()));*/

    chartCompareDataChanged(
            compareChartData.countryCode,
            compareChartData.country,
            compareChartData.placeName,
            compareChartData.latitudeCents,
            compareChartData.longitudeCents,
            compareChartData.timeZone,
            dt.date().year(),
            dt.date().month(),
            dt.date().day(),
            dt.time().hour(),
            dt.time().minute(),
            chartView->isShowingTransits());
}

void MainWindow::chartCompareDataChanged(
        QString countryCode,
        QString country,
        QString placeName,
        int latitudeCents,
        int longitudeCents,
        QString timeZone,
        int year,
        int month,
        int day,
        int hour,
        int minute,
        bool isTransit,
        QString chartName) {

    lastCompareChartName = chartName;

    compareChartData.countryCode = countryCode;
    compareChartData.country = country;
    compareChartData.placeName = placeName;
    compareChartData.latitudeCents = latitudeCents;
    compareChartData.longitudeCents = longitudeCents;
    compareChartData.timeZone = timeZone;
    compareChartData.year = year;
    compareChartData.month = month;
    compareChartData.day = day;
    compareChartData.hour = hour;
    compareChartData.minute = minute;

    chartInput->hide();
    ui->centralWidget->show();
    ui->centralWidget->update();
    ui->centralWidget->setFocus();

    /*TimeZoneInfo* tz = new TimeZoneInfo(timeZone);
    SimpleTime utc = tz->toUTC(year,month,day,hour,minute);*/
    SimpleTime utc = makeUTC(timeZone,year,month,day,hour,minute);

    preloadIfNotYearIs(utc.year);
    planet_positions p =
            ephem_calculateRecForGmt(utc.year, utc.month, utc.day,
                                     utc.hour, utc.minute, 0, preloadedYear);
    calcAscAndMc(&p, latitudeCents/100.0/*59.44*/, longitudeCents/100.0/*10.15*/);

    QString localtimeInfo =
            QString::number(year) + "-" + QString::number(month)+ "-" + QString::number(day) + " "
            + QString::number(hour) + ":" +
            (minute < 10 ? "0" : "") + QString::number(minute);

    if (isTransit) {
        ui->labelChartInfo1->setVisible(true);
        ui->labelChartInfo1->setText(
                (lastChartName.isNull() ? "" : shortenRight(lastChartName,9) + " ") +
                "Transits: " + localtimeInfo + " (" + shortenLeft(timeZone,8) + ")");
        chartView->setTransitPositions(p);
    } else {
        ui->labelChartInfo1->setVisible(true);
        if (lastChartName.isNull()) {
            ui->labelChartInfo1->setText("Comp.to: " + localtimeInfo +
                                         (chartName.isNull() ? "" : " (" + shortenRight(chartName,13)) + ")");
        } else {
            ui->labelChartInfo1->setText(shortenRight(lastChartName,11) +
                    " vs. " + localtimeInfo +
                                         (chartName.isNull() ? "" : " (" + shortenRight(chartName,11)) + ")");
        }
        chartView->setComparisonPositions(p);
    }
}

void MainWindow::newChartDataInputted() {
    chartInput->hide();
    ui->centralWidget->show();
    ui->centralWidget->update();
    ui->centralWidget->setFocus();
}

void MainWindow::inputNewChartData() {
    //setCentralWidget(this->chartInput);
    ui->centralWidget->hide();
    chartInput->show();
    chartInput->update();
    chartInput->repaint();
    chartInput->setFocus();
}

void MainWindow::setupAnimationButtons() {
    const int autoDelay = 2000;
    const int autoInterval = 100;
    ui->btnAnimateBackLarge->setAutoRepeatDelay(autoDelay);
    ui->btnAnimateBackLarge->setAutoRepeatInterval(autoInterval);
    ui->btnAnimateBackStep->setAutoRepeatDelay(autoDelay);
    ui->btnAnimateBackStep->setAutoRepeatInterval(autoInterval);
    ui->btnAnimateForwardLarge->setAutoRepeatDelay(autoDelay);
    ui->btnAnimateForwardLarge->setAutoRepeatInterval(autoInterval);
    ui->btnAnimateForwardStep->setAutoRepeatDelay(autoDelay);
    ui->btnAnimateForwardStep->setAutoRepeatInterval(autoInterval);

    ui->btnAnimateBackLarge->setAutoRepeat(true);
    ui->btnAnimateBackStep->setAutoRepeat(true);
    ui->btnAnimateForwardLarge->setAutoRepeat(true);
    ui->btnAnimateForwardStep->setAutoRepeat(true);

    connect(ui->btnAnimateBackLarge, SIGNAL(clicked()), this, SLOT(animateBackLarge()));
    connect(ui->btnAnimateBackStep, SIGNAL(clicked()), this, SLOT(animateBackStep()));
    connect(ui->btnAnimateForwardLarge, SIGNAL(clicked()), this, SLOT(animateForwardLarge()));
    connect(ui->btnAnimateForwardStep, SIGNAL(clicked()), this, SLOT(animateForwardStep()));
}

/*void MainWindow::fullChartDescriptionChanged(QString desc) {
    //ui->labelDescriptions->setText(desc);
    //ui->labelDescriptions->update();
    descInfoFrame->setBodyText(desc);
    //descInfoFrame->update();
}*/

void MainWindow::aspectTableUpdated(QString html) {
    aspectTableFrame->setBodyText(html);
}

void MainWindow::exitApp() {
    int answer = QMessageBox::question(this, "Quit", "Really quit?",
                                       QMessageBox::Yes, QMessageBox::No);
    if (answer == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::aboutApp() {
    QMessageBox::about(this, "Astrology Toolkit 1.0.1",
                       "Astrology Toolkit 1.0.1 by Leaping Light\n(C) LeapingLight/Roy Andre Gundersen, 2011\n\nFor more information and support, visit http://www.leapinglight.com");
}

MainWindow::~MainWindow()
{
    delete ui;
}
