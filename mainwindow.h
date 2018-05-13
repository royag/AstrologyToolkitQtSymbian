#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFrame>
//#include "astrochart.h"
#include "qhwastrochartview.h"

#include "cpp_core/astrodefs.h"
#include <QListWidget>
//#include "hwqt/hwqwertyinput.h"
#include "cpp_core/geodata.h"
//#include "hwqt/hwcomboinput.h"
#include "mychartinput.h"
#include <QAction>

#include <QGeoPositionInfoSource>
#include <QGeoPositionInfo>
#include "cpp_core/timezoneinfo.h"
#include "mychartopenwindow.h"

#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>

QTM_USE_NAMESPACE

namespace Ui {
    class MainWindow;
}

class ChartData {
public:
    QString countryCode;
    QString country;
    QString placeName;
    int latitudeCents;
    int longitudeCents;
    QString timeZone;
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static SimpleTime makeUTC(QString timeZone,int year,int month,int day,int hour,int minute);

public slots:
    void newChartDataInputted();
    void inputNewChartData();
    void inputDataCancelled();
    void chartOpenCancelled();
    void vipChartOpenCancelled();
    void searchResultChartOpenCancelled();
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
            int minute,
            QString chartName = QString::null);
    void chartCompareDataChanged(
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
            int minute,
            bool isTransit,
            QString chartName = QString::null);
    void setAnimateToolVisible(bool isIt);
    void animateBackLarge();
    void animateBackStep();
    void animateForwardLarge();
    void animateForwardStep();
    void adjustCompareChart(int year,int month, int day, int hour, int min);
    void adjustChart(int year,int month, int day, int hour, int min);
    //void fullChartDescriptionChanged(QString desc);
    void aspectTableUpdated(QString html);

    void searchForPlacement(int planet, int sign, int house, int aspect, int planet2);
    void searchForPlanetInHouse(int planet, int house);
    void searchForPlanetInSign(int planet, int sign);
    void searchForAspect(int planet, int planet2, int aspect);

protected:
    virtual void resizeEvent(QResizeEvent *);

    planet_positions calcPositionsForChart(QString chartFile);
    planet_positions calcPlanetPositionsFor(
            int latitudeCents,
            int longitudeCents,
            QString timeZone,
            int year,
            int month,
            int day,
            int hour,
            int minute,
            bool usePreloading = false);


protected slots:
    void exitApp();
    void aboutApp();

    void setLayoutVertical(bool);

    void saveChart();
    void openChart();
    void openCompareChart();
    void chartHereAndNow();
    void openVIPChart();
    void openVIPCompareChart();
    void chartNowWithoutGPS();
    void positionUpdated(QGeoPositionInfo posInfo);
    void positionUpdateTimedOut();
    void showTransits();
    void animateOnOff();

    void chartFileSelected(QString);
    void vipChartFileSelected(QString);
    void chartCompareFileSelected(QString);
    void vipChartCompareFileSelected(QString);
    void searchResultChartFileSelected(QString);

    void chartCompareFileCancelled();
    void vipChartCompareFileCancelled();

    void setHousesNULL();
    void setHousesEqualASC();
    void setHousesWholeVedic();
    void setHousesPorphyry();
    void setHousesPlacidus();
    void setHousesKoch();

    void loadChartFile(QString fn);
    void loadCompareChartFile(QString fn);


    /*void showPlanetInfo(int planet);
    void showComparisonPlanetInfo(int planet);
    void showAspectInfo(int planet1, int planet2);*/


private:
    void showChartOpener(MyChartOpenWindow* opener);
    void hideDialogWindow(QWidget* window);
    QHBoxLayout* mainLayoutHorizontal;
    QVBoxLayout* mainLayoutVertical;

    QString filterFileName(const QString & fn);
    EPHEM_YEAR* preloadedYear;
    void preloadIfNotYearIs(int year);
    QGeoPositionInfoSource* geoInfoSource;
    ChartData currentChartData;
    ChartData compareChartData;
    QHWAstroChartView *chartView;
    //QLabel *labelTransitInfo;
    //QLabel *labelHelp;
    MyChartInput *chartInput;
    QString m_country;
    QList<GeoCountryInfo>* m_countryInfo;
    QFrame* m_inputFrame;
    Ui::MainWindow *ui;
    //void populateGraphics();
    void testZone();
    QListWidget* m_selectList;
    QString shortenLeft(QString s, int len);
    QString shortenRight(QString s, int len);
    QString shortenZone(QString tzone);
    QString lastChartName;
    QString lastCompareChartName;


    QAction* actionNewChart;
    QAction* actionChartNow;
    //QAction* actionEditChart;
    QAction* actionSaveChart;
    QAction* actionOpenChart;
    QAction* actionChartVIP;
    QAction* actionShowTransits;
    QAction* actionOpenCompareChart;
    QAction* actionTransits;
    QAction* actionAnimateOnOff;

    QAction* actionHousesNULL;
    QAction* actionHousesEqualASC;
    QAction* actionHousesWholeVedic;
    QAction* actionHousesPorphyry;
    QAction* actionHousesPlacidus;
    QAction* actionHousesKoch;
    //InfoFrame* descInfoFrame;
    InfoFrame* aspectTableFrame;
    MyChartOpenWindow* chartOpener;
    MyChartOpenWindow* vipChartOpener;
    MyChartOpenWindow* searchResultChartOpener;

    MyChartOpenWindow* chartCompareOpener;
    MyChartOpenWindow* vipChartCompareOpener;

    void setupAnimationButtons();
};

#endif // MAINWINDOW_H
