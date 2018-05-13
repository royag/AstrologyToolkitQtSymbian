#ifndef QHWASTROCHARTVIEW_H
#define QHWASTROCHARTVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include "cpp_core/astrodefs.h"
#include <QColor>
#include <QMouseEvent>
#include "cpp_core/house_calc.h"
#include "qhwastroscene.h"
#include "infoframe.h"
#include <QGraphicsTextItem>

class QHWAstroChartView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QHWAstroChartView(QWidget *parent = 0);
    virtual ~QHWAstroChartView();
    bool isComparisonChart();
    bool isShowingTransits();

    float getPositionOfPlanet(int planet);
    float getPositionOfComparisonPlanet(int planet);
    int houseOfPosition(float pos);
    //int comparisonHouseOfPosition(float pos);
    float getPositionOfHouseCusp(int house);
    //float getPositionOfCompHouseCusp(int house);

    static QString planetImageFile(int planetNo);
    static QString planetImageFile15(int planetNo);
    static QString signImageFile(int signNo);
    static QString aspectImageFile(int aspect);
    static QString posToString(float pos);

    static QString htmlPlanetImage(int planet);
    static QString htmlPlanetImage15(int planet);
    static QString htmlSignImage(int sign);
    static QString htmlAspectImage(int aspect);

    static QString queryForAspect(int planet1, int planet2, int aspect, bool transit=false, bool synastry=false);
    static QString queryForTransitAspect(int transPlanet, int nativePlanet, int aspect);
    static QString queryForComparisonAspect(int planet1, int planet2, int aspect);
    static QString queryForPlanetInSign(int planet, int sign);
    static QString queryForPlanetInHouse(int planet, int house);
    static QString queryForTransitInHouse(int planet, int house);
    static QString queryForComparisonInHouse(int planet, int house);

    QString infoForPlanet(int planet);
    QString infoForComparisonPlanet(int planet);
    QString infoForSynastryPlanet(int planet); //, bool reverse);
    QString infoForTransitPlanet(int planet);
    InfoFrame* infoFrame;

protected:
    virtual void resizeEvent(QResizeEvent *event);
    void redrawChart();
    QColor colorForAspect(int aspect);
    void highlightAspectsFor(QGraphicsPixmapItem*);
    QString textPositionFor(QGraphicsPixmapItem*);

signals:
    /*void wantPlanetInfo(int planet);
    void wantComparisonPlanetInfo(int planet);
    void wantAspectInfo(int planet1, int planet2);*/
    //void fullChartDescriptionChanged(QString);
    void aspectTableChanged(QString);

public slots:
    void setPositions(planet_positions planetPositions, int houseSystem = -1);
    void changeHouseSystem(int houseSystem);
    void setComparisonPositions(planet_positions planetPositions);
    void setTransitPositions(planet_positions planetPositions);
    void removeComparisonPositions();
    void refigureRadius();
    //void pressedItem(QGraphicsItem *);
    //void movedToItem(QGraphicsItem *);
    //void releaseOnItem(QGraphicsItem *);
    //void showInfoOnItem(QGraphicsItem *);
    /*void showPlanetInfo(int planet);
    void showComparisonPlanetInfo(int planet);
    void showAspectInfo(int planet1, int planet2);*/
    QString currentHouseSystemName();

protected slots:
    void longTapHasHappened(QPointF where, QGraphicsItem* who);
    void updateLoader();
protected:
    void setComparionsPlanetsVisible(bool v);
    int planetNo(QGraphicsItem*);
    int comparisonPlanetNo(QGraphicsItem*);
    QGraphicsPixmapItem* asPixmapItem(QGraphicsItem*);
    //QString createFullChartDescription();
    QString createHTMLaspectTable();



private:
    int getNatalAspect(int p1, int p2);
    int getSynastryAspect(int p1, int p2);
    int getTransitAspect(int p1, int p2);
    QGraphicsItem* currentInfoItem;
    void showWaiter(int,QPointF);
    void loadWaitPixmaps();
    QGraphicsPixmapItem* m_waitPixmaps[12];
    QGraphicsPixmapItem* m_selectionPixmap;
    QGraphicsItem *lastInfoItem;
    int houseSystem;
    float houses[12];
    //float comparisonHouses[12];
    bool chartHasHouses();
    bool comparisonChartHasHouses();
    void loadPixmaps();
    void getXY(float degree, int radius,int &x, int &y);
    double deg2rad(double deg);
    QHWAstroScene* m_scene;

    QGraphicsPixmapItem* planetPixmapItems[13];
    QGraphicsPixmapItem* comparisonPlanetPixmapItems[13];

    QGraphicsLineItem* planetMarkers[13];
    QGraphicsLineItem* comparisonPlanetMarkers[13];

    QGraphicsPixmapItem* signPixmapItems[12];

    QGraphicsTextItem* houseNumberItems[12];

    QGraphicsPixmapItem* m_Loader;
    QGraphicsTextItem* m_LoaderText;


    QGraphicsLineItem* m_axisAscDesc;
    QGraphicsLineItem* m_axisMcIc;
    QGraphicsLineItem* m_axis2nd8th;
    QGraphicsLineItem* m_axis3rd9th;
    QGraphicsLineItem* m_axis5th11th;
    QGraphicsLineItem* m_axis6th12th;

    void centerAtDegRadius(int deg, int radius, QGraphicsPixmapItem *pm);
    int m_radius;
    int m_zodInnerRadius;

    QGraphicsEllipseItem* m_zodiac1;
    QGraphicsEllipseItem* m_zodiacInner;
    QGraphicsLineItem* m_zodLines[12];

    bool isCompareChart;
    bool isTransitChart;
    planet_positions planetPositions;
    planet_positions comparisonPositions;

    planet_positions calcPresentablePositions(const planet_positions &realPos, int minDistance);

    QGraphicsLineItem* m_aspectLines[NUM_PLANETS+2][NUM_PLANETS+2];

};

#endif // QHWASTROCHARTVIEW_H
