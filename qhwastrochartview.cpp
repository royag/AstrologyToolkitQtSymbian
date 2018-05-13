#include "qhwastrochartview.h"
#include "math.h"
#include <QDebug>
#include <QEvent>

QHWAstroChartView::QHWAstroChartView(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QHWAstroScene(this)),
    isCompareChart(false),
    houseSystem(HOUSES_PLACIDUS),
    lastInfoItem(0),
    currentInfoItem(0)
{  
    this->setScene(m_scene);
    refigureRadius();
    loadPixmaps();

    setInteractive(true);

    connect(m_scene, SIGNAL(longTapHasHappened(QPointF,QGraphicsItem*)), this, SLOT(longTapHasHappened(QPointF,QGraphicsItem*)));
    connect(m_scene, SIGNAL(tickChanged()), this, SLOT(updateLoader()));
    connect(m_scene, SIGNAL(trackingStopped()), this, SLOT(updateLoader()));

    infoFrame = new InfoFrame(this);
    infoFrame->setAutoFillBackground(true);
    infoFrame->setVisible(false);
    infoFrame->setGeometry(geometry());
}

// old yellow:
// #define COLOR_FOREGROUND Qt::black
// #define COLOR_HALFFOREGROUND Qt::gray
// #define RGB_GRADIENT0 QColor::fromRgbF(0.9, 0.9, 0.9, 1)
// #define RGB_GRADIENT1 QColor::fromRgbF(0.9, 0.9, 0.5, 0.5)

#define COLOR_FOREGROUND Qt::white
#define COLOR_HALFFOREGROUND Qt::gray
#define RGB_GRADIENT0 QColor::fromRgbF(0.5, 0.5, 0.5, 1.0)
#define RGB_GRADIENT1 QColor::fromRgbF(0.0, 0.0, 0.0, 0.3)


void QHWAstroChartView::updateLoader() {
    if (m_scene->isTrackingMouse()) {
        QPointF point(
                m_scene->trackingPoint().x(), // + 20,
                m_scene->trackingPoint().y() - 50);

        showWaiter(m_scene->tickCounter()-1, point);
        float cx = point.x() + 16;
        float cy = point.y() + 16;
        QGraphicsPixmapItem* item = asPixmapItem(m_scene->currentItem());
        QPixmap pic = item->pixmap();
        float px = cx - (pic.width() / 2);
        float py = cy - (pic.height() / 2);
        m_selectionPixmap->setPixmap(pic);
        m_selectionPixmap->setPos(px,py);
        m_selectionPixmap->setVisible(true);

        m_LoaderText->setPlainText(textPositionFor(item));
        m_LoaderText->setVisible(true);
        m_LoaderText->setPos(cx-30,cy-40);

        highlightAspectsFor(item);
    } else {
        showWaiter(-1, QPointF(0,0));
        m_selectionPixmap->setVisible(false);
        m_LoaderText->setVisible(false);
        highlightAspectsFor(0);
    }
}

void QHWAstroChartView::longTapHasHappened(QPointF where, QGraphicsItem* who) {
    currentInfoItem = who;
    int planet = planetNo(who);
    int compPlanet = comparisonPlanetNo(who);
    if (planet > -1) {
       infoFrame->setBodyText(infoForPlanet(planet));
    } else if (compPlanet > -1) {
       infoFrame->setBodyText(infoForComparisonPlanet(compPlanet));
    }
    if (planet > -1 || compPlanet > -1) {
        infoFrame->setVisible(true);
    }
}

float QHWAstroChartView::getPositionOfPlanet(int planet) {
    return ephem_positionOfPlanet(planetPositions, planet);
}

float QHWAstroChartView::getPositionOfComparisonPlanet(int planet) {
    return ephem_positionOfPlanet(comparisonPositions, planet);
}

int QHWAstroChartView::houseOfPosition(float pos) {
    for (int i = HOUSE_1; i <= HOUSE_12; i++) {
        float cur = houses[i];
        float next = (i == HOUSE_12 ? houses[HOUSE_1] : houses[i+1]);
        if (cur < next) {
            if (pos >= cur && pos < next) {
                return i;
            }
        } else {
            if (pos >= cur || pos < next) {
                return i;
            }
        }
    }
    return -1; // shouldn't happen
}
/*
int QHWAstroChartView::comparisonHouseOfPosition(float pos) {
    for (int i = HOUSE_1; i <= HOUSE_12; i++) {
        float cur = comparisonHouses[i];
        float next = (i == HOUSE_12 ? comparisonHouses[HOUSE_1] : comparisonHouses[i+1]);
        if (cur < next) {
            if (pos >= cur && pos < next) {
                return i;
            }
        } else {
            if (pos >= cur || pos < next) {
                return i;
            }
        }
    }
    return -1; // shouldn't happen
}
*/

float QHWAstroChartView::getPositionOfHouseCusp(int house) {
    return houses[house];
}
/*
float QHWAstroChartView::getPositionOfCompHouseCusp(int house) {
    return comparisonHouses[house];
}
*/
QGraphicsPixmapItem* QHWAstroChartView::asPixmapItem(QGraphicsItem* item) {
    // NB: COULD in future be something else:
    return static_cast<QGraphicsPixmapItem*>(item);
}

int QHWAstroChartView::planetNo(QGraphicsItem* item) {
    for (int i = SUN; i <= MEDIUM_COELI; i++) {
        if (planetPixmapItems[i] == item) {
            return i;
        }
    }
    return -1;
}

int QHWAstroChartView::comparisonPlanetNo(QGraphicsItem* item) {
    for (int i = SUN; i <= MEDIUM_COELI; i++) {
        if (comparisonPlanetPixmapItems[i] == item) {
            return i;
        }
    }
    return -1;
}

void QHWAstroChartView::refigureRadius() {
    int wr = m_scene->sceneRect().width() / 2;
    int hr = m_scene->sceneRect().height() / 2;
    m_radius = (wr < hr ? wr : hr);
}

void QHWAstroChartView::resizeEvent(QResizeEvent *event) {
    qDebug("resizeEvent");
    QRect vg = geometry();
    //m_scene->setSceneRect(0,0,vg.width(), vg.height());
    int w = vg.width() - 4;  // substract some to avoid scroll-bar
    int h = vg.height() - 4;

    m_scene->setSceneRect(-w/2,-h/2,w,h);
    refigureRadius();
    redrawChart();
    infoFrame->setGeometry(geometry());
    qDebug("resizeEvent DONE");
}

QColor QHWAstroChartView::colorForAspect(int aspect) {
    int n = 64;
    switch (aspect) {
    case 0: return QColor(n,n,255); //=> 0x0000FFFF, #[0,0,255],
    case 30: return QColor(n,n,255); // => 0x0000FFFF, #[0,0,255],
    case 45: return QColor(255,n,n); // => 0xFF0000FF, #[255,0,0],
    case 60: return QColor(n,n,255); // => 0x0000FFFF, #[0,0,255],
    case 72: return QColor(n,n,n); // => 0x000000FF, #[0,0,0],
    case 90: return QColor(255,n,n); // => 0xFF0000FF, #[255,0,0],
    case 120: return QColor(n,n,255); // => 0x0000FFFF, #[0,0,255],
    case 135: return QColor(n,255,n); // => 0x00FF00FF, #[0,255,0],
    case 150: return QColor(n,255,n); //=> 0x00FF00FF, #[0,255,0],
    case 180: return QColor(255,n,n); // => 0xFF0000FF #[255,0,0]
    default: return COLOR_FOREGROUND;
    }
}

bool QHWAstroChartView::chartHasHouses() {
    return planetPositions.ascendant >= 0;
}

bool QHWAstroChartView::comparisonChartHasHouses() {
    return comparisonPositions.ascendant >= 0 && !isTransitChart;
}

void QHWAstroChartView::showWaiter(int zeroThroughEleven, QPointF pos) {
    qDebug("SHOW WAITER");
    for (int i = 0; i < 12; i++) {
        if (zeroThroughEleven == i) {
            m_waitPixmaps[i]->setVisible(true);
            m_waitPixmaps[i]->setPos(pos);
        } else {
            m_waitPixmaps[i]->setVisible(false);
        }
    }
}

void QHWAstroChartView::loadWaitPixmaps() {
    for (int i = 0; i < 12; i++) {
        m_waitPixmaps[i] = m_scene->addPixmap(QPixmap(
                QString(":/gfx/wait")+
                QString::number(i+1)+
                QString(".png")));
        m_waitPixmaps[i]->setVisible(false);
    }
}

QString QHWAstroChartView::planetImageFile(int planetNo) {
    QString path(":/astrodata/gfx/planets20w/");
    QString fn = path +
        QString(PLANET_NAMES[planetNo]).toLower() +
        ".png";
    return fn;
}

QString QHWAstroChartView::planetImageFile15(int planetNo) {
    QString path(":/astrodata/gfx/planets15/");
    QString fn = path +
        QString(PLANET_NAMES[planetNo]).toLower() +
        ".png";
    return fn;
}

QString QHWAstroChartView::aspectImageFile(int aspect) {
    QString path(":/astrodata/gfx/aspects/");
    QString fn = path +
                 "a" + QString::number(aspect) + ".png";
    return fn;
}

QString QHWAstroChartView::posToString(float pos) {
    char signName[10];
    ephem_positionToChar6(pos, (char*)&signName);
    return QString((char*)&signName);
}

QString QHWAstroChartView::signImageFile(int signNo) {
    QString path(":/astrodata/gfx/signs30/");
    QString fn = path + QString("col_") +
        QString(SIGN_NAMES[signNo]).toLower() +
        ".png";
    return fn;
}

void QHWAstroChartView::loadPixmaps() {
    qDebug("loadPixmaps");
    //m_radius = 175;
    loadWaitPixmaps();
    QRadialGradient gradient(0, 0, m_radius, 0, 0);
        gradient.setColorAt(0, RGB_GRADIENT0);
        gradient.setColorAt(1, RGB_GRADIENT1);
    QBrush zBrush(gradient);
    QPen zPen = QPen(COLOR_HALFFOREGROUND);
    m_zodiac1 = m_scene->addEllipse(-m_radius,-m_radius,m_radius*2,m_radius*2,zPen,zBrush);
    m_zodInnerRadius = m_radius - 35;
    m_zodiacInner = m_scene->addEllipse(-m_zodInnerRadius,-m_zodInnerRadius,m_zodInnerRadius*2,m_zodInnerRadius*2, zPen);


    for (int i = 0; i < 12; i++) {
        int x, y, x2, y2;
        getXY(i*30, m_radius, x, y);
        getXY(i*30, m_zodInnerRadius, x2, y2);
        m_zodLines[i] = m_scene->addLine(x,y,x2,y2,zPen);
    }

    QColor houseColors[4];
    houseColors[ELEM_FIRE] = Qt::red;
    houseColors[ELEM_AIR] = Qt::yellow;
    houseColors[ELEM_EARTH] = Qt::green;
    houseColors[ELEM_WATER] = Qt::blue;

    QFont houseNumberFont;
    houseNumberFont.setPointSize(7);
    houseNumberFont.setBold(false);
    for (int h = HOUSE_1; h <= HOUSE_12; h++) {
        houseNumberItems[h] = m_scene->addText(QString::number(h+1), houseNumberFont);
        houseNumberItems[h]->setDefaultTextColor(
                houseColors[SIGN_AND_HOUSE_ELEMENTS[h]]);
        houseNumberItems[h]->setOpacity(0.5);
    }

    const int numBodies = NUM_PLANETS + 2;
    for (int p1 = 0; p1 < numBodies; p1++) {
        for (int p2 = 0/*p1+1*/; p2 < numBodies; p2++) {
            m_aspectLines[p1][p2] =
                    m_scene->addLine(0,0,0,0,zPen);
            if (p2 <= p1) {
                // these are only interesting for comparison-chart
                m_aspectLines[p1][p2]->setVisible(false);
            }
        }
    }

    for (int i = ARIES; i <= PISCES; i++) {
        signPixmapItems[i] = m_scene->addPixmap(QPixmap(signImageFile(i)));
        //m_scene->addLongTapItem(signPixmapItems[i]);
    }

    QPen penFG = QPen(COLOR_FOREGROUND);
    QPen penHFG = QPen(COLOR_HALFFOREGROUND);

    for (int i = SUN; i <= MEDIUM_COELI; i++) {
        planetPixmapItems[i] = m_scene->addPixmap(QPixmap(planetImageFile(i)));
        m_scene->addLongTapItem(planetPixmapItems[i]);
        planetMarkers[i] = m_scene->addLine(0,0,0,0,penFG);
    }
    for (int i = SUN; i <= MEDIUM_COELI; i++) {
        comparisonPlanetPixmapItems[i] = m_scene->addPixmap(planetPixmapItems[i]->pixmap());
        m_scene->addLongTapItem(comparisonPlanetPixmapItems[i]);
        comparisonPlanetMarkers[i] = m_scene->addLine(0,0,0,0,penHFG);
    }
    setComparionsPlanetsVisible(false);

    QPen penMainAxis = penFG;
    QPen penHouses = penHFG; //QColor(128,128,128));

    m_axisAscDesc = m_scene->addLine(-m_radius,0,m_radius,0, penMainAxis);
    m_axisMcIc = m_scene->addLine(0,-m_radius,0,m_radius, penMainAxis);

    m_axis2nd8th = m_scene->addLine(0,0,0,0, penHouses);
    m_axis3rd9th = m_scene->addLine(0,0,0,0, penHouses);
    m_axis5th11th = m_scene->addLine(0,0,0,0, penHouses);
    m_axis6th12th = m_scene->addLine(0,0,0,0, penHouses);

    m_Loader = m_scene->addPixmap(QPixmap(":/gfx/waiter_snake32.gif"));
    m_Loader->setPos(0,0);
    m_Loader->setVisible(false);

    m_LoaderText = m_scene->addText("");
    m_LoaderText->setPos(0,0);
    m_LoaderText->setDefaultTextColor(COLOR_FOREGROUND);
    QFont loaderFont;
    loaderFont.setPointSize(6);
    m_LoaderText->setFont(loaderFont);
    m_LoaderText->setVisible(false);

    m_selectionPixmap = m_scene->addPixmap(m_waitPixmaps[0]->pixmap()); // to change;
    m_selectionPixmap->setVisible(false);
    qDebug("loadPixmaps DONE");
}

void QHWAstroChartView::setComparionsPlanetsVisible(bool v) {
    for (int i = SUN; i <= MEDIUM_COELI; i++) {
        comparisonPlanetPixmapItems[i]->setVisible(v);
        comparisonPlanetMarkers[i]->setVisible(v);
    }
}

void QHWAstroChartView::redrawChart() {
    qDebug("redrawChart");
    m_zodInnerRadius = m_radius - 35;
    planet_positions &pp = this->planetPositions;
    planet_positions &pp2 = this->comparisonPositions;

    QRadialGradient gradient(0, 0, m_radius, 0, 0);
         gradient.setColorAt(0, RGB_GRADIENT0);
         gradient.setColorAt(1, RGB_GRADIENT1);
    QBrush zBrush(gradient);
    m_zodiac1->setBrush(zBrush);
    m_zodiac1->setRect(-m_radius,-m_radius,m_radius*2,m_radius*2);
    m_zodiacInner->setRect(-m_zodInnerRadius,-m_zodInnerRadius,m_zodInnerRadius*2,m_zodInnerRadius*2);


    int x; int y;
    int x2; int y2;

    int aries0 = 360 - houses[HOUSE_1];

    getXY(filter360(houses[HOUSE_4]+aries0),m_radius,x,y);
    getXY(filter360(houses[HOUSE_10]+aries0),m_radius,x2,y2);
    m_axisMcIc->setLine(x,y,x2,y2);

    getXY(filter360(houses[HOUSE_2]+aries0),m_zodInnerRadius,x,y);
    getXY(filter360(houses[HOUSE_8]+aries0),m_zodInnerRadius,x2,y2);
    m_axis2nd8th->setLine(x,y,x2,y2);

    getXY(filter360(houses[HOUSE_3]+aries0),m_zodInnerRadius,x,y);
    getXY(filter360(houses[HOUSE_9]+aries0),m_zodInnerRadius,x2,y2);
    m_axis3rd9th->setLine(x,y,x2,y2);

    getXY(filter360(houses[HOUSE_5]+aries0),m_zodInnerRadius,x,y);
    getXY(filter360(houses[HOUSE_11]+aries0),m_zodInnerRadius,x2,y2);
    m_axis5th11th->setLine(x,y,x2,y2);

    getXY(filter360(houses[HOUSE_6]+aries0),m_zodInnerRadius,x,y);
    getXY(filter360(houses[HOUSE_12]+aries0),m_zodInnerRadius,x2,y2);
    m_axis6th12th->setLine(x,y,x2,y2);

    m_axisAscDesc->setLine(-m_radius,0,m_radius,0);

    for (int h = HOUSE_1; h <= HOUSE_12; h++) {
        int nextHouse = (h == HOUSE_12 ? HOUSE_1 : h+1);
        float dist = calcDistance(houses[h], houses[nextHouse]);
        float center = filter360(houses[h] + (dist * 0.5));
        int rad = m_radius / 2;
        getXY(center+aries0,rad,x,y);
        //houseNumberItems[h]->
        QRectF rect = houseNumberItems[h]->boundingRect();

        houseNumberItems[h]->setPos(x-(rect.width()*0.5),y-(rect.height()*0.5));
    }

    int planetRadius = m_radius - 50;

    planet_positions presPos = calcPresentablePositions(pp, 10);
    for (int i = SUN; i <= MEDIUM_COELI; i++) {
        if (i != ASCENDANT && i != MEDIUM_COELI || chartHasHouses()) {
            int radius = (i == ASCENDANT || i == MEDIUM_COELI ? planetRadius + 30 : planetRadius);
            int deg = ephem_positionOfPlanet(presPos, i)+aries0;
            int degActual = ephem_positionOfPlanet(pp, i)+aries0;
            centerAtDegRadius(deg, radius, planetPixmapItems[i]);
            planetPixmapItems[i]->setVisible(true);

            if (i != ASCENDANT && i != MEDIUM_COELI) {
                int x1; int y1; int x2; int y2;
                getXY(degActual, m_zodInnerRadius, x1, y1);
                getXY(degActual, m_zodInnerRadius-3, x2, y2);
                planetMarkers[i]->setLine(x1,y1,x2,y2);
                planetMarkers[i]->setVisible(true);
            } else {
                planetMarkers[i]->setVisible(false);
            }
        } else {
            planetPixmapItems[i]->setVisible(false); // ASC or MC i NON-house chart
            planetMarkers[i]->setVisible(false);
        }
    }

    int planetCompareRadius = planetRadius + (isTransitChart ? 35 : - 20);
    if (isCompareChart) {
        planet_positions presPos2 = calcPresentablePositions(pp2, 10);
        for (int i = SUN; i <= MEDIUM_COELI; i++) {
            if (i != ASCENDANT && i != MEDIUM_COELI || comparisonChartHasHouses()) {
                int radius = (i == ASCENDANT || i == MEDIUM_COELI ? planetCompareRadius - 30 : planetCompareRadius);
                int deg = ephem_positionOfPlanet(presPos2, i)+aries0;
                int degActual = ephem_positionOfPlanet(pp2, i)+aries0;
                centerAtDegRadius(deg, radius, comparisonPlanetPixmapItems[i]);
                comparisonPlanetPixmapItems[i]->setVisible(true);

                int x1; int y1; int x2; int y2;
                getXY(degActual, m_zodInnerRadius, x1, y1);
                getXY(degActual, m_zodInnerRadius-3, x2, y2);
                comparisonPlanetMarkers[i]->setLine(x1,y1,x2,y2);
                comparisonPlanetMarkers[i]->setVisible(true);
            } else {
                comparisonPlanetPixmapItems[i]->setVisible(false); // ASC or MC i NON-house chart
                comparisonPlanetMarkers[i]->setVisible(false);
            }
        }
    } else {
        setComparionsPlanetsVisible(false);
    }

    int signRadius = m_radius - 20;
    for (int i = ARIES; i <= PISCES; i++) {
        centerAtDegRadius(aries0+15+(i*30), signRadius, signPixmapItems[i]);
    }

    for (int i = 0; i < 12; i++) {
        getXY(aries0 + i*30, m_radius, x, y);
        getXY(aries0 + i*30, m_zodInnerRadius, x2, y2);
        m_zodLines[i]->setLine(x,y,x2,y2);
    }

    bool showComparisonAspects = isCompareChart && !isTransitChart;

    // aspects:
    int aspectRadius = planetRadius - 10;
    const int numBodies = NUM_PLANETS + 2;
    for (int p1 = 0; p1 < numBodies; p1++) {
        for (int p2 = 0; p2 < numBodies; p2++) {
            if (!showComparisonAspects && (p2 <= p1)) {
                m_aspectLines[p1][p2]->setVisible(false);
                continue;
            }
            if (!showComparisonAspects && (p1 >= NUM_PLANETS || p2 >= NUM_PLANETS) && !chartHasHouses()) {
                m_aspectLines[p1][p2]->setVisible(false);
                continue;
            } else if (showComparisonAspects) {
                if ((p1 >= NUM_PLANETS && !chartHasHouses()) ||
                    (p2 >= NUM_PLANETS && !comparisonChartHasHouses())) {
                        m_aspectLines[p1][p2]->setVisible(false);
                        continue;
                }
            }
            float pos1 = ephem_positionOfPlanet(pp, p1);
            float pos2;
            if (!showComparisonAspects) {
                pos2 = ephem_positionOfPlanet(pp, p2);
            } else {
                pos2 = ephem_positionOfPlanet(pp2, p2);
            }

            int aspect;
            if (!showComparisonAspects) {
                aspect = getNatalAspect(pos1, pos2);
            } else {
                if (isTransitChart) {
                    aspect = getTransitAspect(pos1, pos2);
                } else {
                    aspect = getSynastryAspect(pos1, pos2);
                }
            }

            if (aspect >= 0) {
                int radius = aspectRadius;
                if (showComparisonAspects) {
                    radius = aspectRadius - 10;
                }
                getXY(aries0 + pos1, radius, x, y);
                getXY(aries0 + pos2, radius, x2, y2);
                m_aspectLines[p1][p2]->setLine(x,y,x2,y2);
                m_aspectLines[p1][p2]->setPen(colorForAspect(aspect));
                m_aspectLines[p1][p2]->update();
                m_aspectLines[p1][p2]->setVisible(true);
            } else {
                m_aspectLines[p1][p2]->setVisible(false);
            }
        }
    }

    //fullChartDescriptionChanged(createFullChartDescription());
    aspectTableChanged(createHTMLaspectTable());
    qDebug("redrawChart DONE");
}

void QHWAstroChartView::highlightAspectsFor(QGraphicsPixmapItem* item) {
    int planet = planetNo(item);
    int cPlanet = comparisonPlanetNo(item);
    for (int p1 = SUN; p1 <= MEDIUM_COELI; p1++) {
        for (int p2 = SUN; p2 <= MEDIUM_COELI; p2++) {
            QGraphicsLineItem* line = m_aspectLines[p1][p2];
            QPen pen;
            if (line != 0) {
                pen = line->pen();
            }
            if (line == 0) {
                continue;
            } else if (cPlanet > -1 && p2 == cPlanet && line->isVisible()) {
                // hilite
                pen.setWidth(3);
                line->setPen(pen);
                line->update();
            } else if (planet > -1 && p1 == planet || p2 == planet && line->isVisible()) {
                // hilite
                pen.setWidth(3);
                line->setPen(pen);
                line->update();
            } else {
                // un-hilite
                pen.setWidth(1);
                line->setPen(pen);
                line->update();
            }
        }
    }
}

QString QHWAstroChartView::textPositionFor(QGraphicsPixmapItem* item) {
    int planet = planetNo(item);
    int cPlanet = comparisonPlanetNo(item);
    if (planet > -1) {
        return posToString(ephem_positionOfPlanet(planetPositions, planet));
    } else if (cPlanet > -1) {
        return posToString(ephem_positionOfPlanet(comparisonPositions, cPlanet));
    } else {
        return "";
    }
}

planet_positions QHWAstroChartView::calcPresentablePositions(const planet_positions &realPos, int minDistance) {
    qDebug("calcPresentablePositions");
    planet_positions ret = duplicate(realPos);

    float pos1;
    float pos2;
    float dist;
    bool allOk = false;
    int cnt = 0;
    int maxCnt = 10;
    // TODO: Figure out better algorithm ?
    while (!allOk) {
        allOk = true;
        for (int p1 = SUN; p1 <= NODE; p1++) {
            pos1 = ephem_positionOfPlanet(ret, p1);
            for (int p2 = SUN; p2 <= NODE; p2++) {
                if (p1 == p2) {
                    continue;
                }
                pos2 = ephem_positionOfPlanet(ret, p2);
                dist = calcDistance(pos1, pos2);
                if (dist < minDistance) {
                    allOk = false;
                    float delta = minDistance - dist;
                    float p1attempt = filter360(pos1-delta/2-0.1);
                    float p2attempt = filter360(pos2+delta/2+0.1);
                    if (!(calcDistance(p1attempt, p2attempt) >= minDistance)) {
                        p1attempt = filter360(pos1+delta/2+0.1);
                        p2attempt = filter360(pos2-delta/2-0.1);
                    }
                    ephem_setPosition(ret, p1, p1attempt);
                    ephem_setPosition(ret, p2, p2attempt);
                }
            }

        }
        cnt++;
        if (cnt >= maxCnt) {
            break;
        }
    }
    qDebug("presentationAttemts=%d", cnt);

    qDebug("calcPresentablePositions DONE");
    return ret;
}

void QHWAstroChartView::setPositions(planet_positions pp, int houseSystem) {
    if (houseSystem >= 0) {
        this->houseSystem = houseSystem;
    }
    planetPositions = pp;
    calcHouses((float*)&houses, pp, this->houseSystem);
    redrawChart();

    if (infoFrame->isVisible()) {
        // update planetInfo is showing planetInfo:
        longTapHasHappened(QPointF(), currentInfoItem);
    }
}

void QHWAstroChartView::changeHouseSystem(int houseSystem) {
    if (houseSystem >= 0) {
        this->houseSystem = houseSystem;
    }
    calcHouses((float*)&houses, planetPositions, this->houseSystem);
    /*if (isCompareChart && !isTransitChart) {
        calcHouses((float*)&comparisonHouses, comparisonPositions, this->houseSystem);
    }*/
    redrawChart();

    if (infoFrame->isVisible()) {
        // update planetInfo is showing planetInfo:
        longTapHasHappened(QPointF(), currentInfoItem);
    }
}

QString QHWAstroChartView::currentHouseSystemName() {
    return QString(HOUSE_SYSTEM_NAMES[this->houseSystem]);
}

void QHWAstroChartView::setComparisonPositions(planet_positions pp) {
    comparisonPositions = pp;
    //calcHouses((float*)&comparisonHouses, pp, this->houseSystem);
    isCompareChart = true;
    isTransitChart = false;
    redrawChart();

    if (infoFrame->isVisible()) {
        // update planetInfo is showing planetInfo:
        longTapHasHappened(QPointF(), currentInfoItem);
    }
}

void QHWAstroChartView::setTransitPositions(planet_positions pp) {
    comparisonPositions = pp;
    isCompareChart = true;
    isTransitChart = true;
    redrawChart();

    if (infoFrame->isVisible()) {
        // update planetInfo is showing planetInfo:
        longTapHasHappened(QPointF(), currentInfoItem);
    }
}


void QHWAstroChartView::removeComparisonPositions() {
    isCompareChart = false;
    isTransitChart = false;
    redrawChart();
}

bool QHWAstroChartView::isComparisonChart() {
    return isCompareChart;
}

bool QHWAstroChartView::isShowingTransits() {
    return isCompareChart && isTransitChart;
}

void QHWAstroChartView::centerAtDegRadius(int deg, int radius, QGraphicsPixmapItem *pm) {
    //qDebug("centerAtDegRadius");
    int x; int y;
    getXY(deg, radius, x, y);
    int w = pm->boundingRect().width();
    int h = pm->boundingRect().height();
    pm->setPos(x-(w/2),y-(h/2));
    //pm->boundingRect().setCoords(x-5,y-5,x+5,y+5);
    //pm->boundingRect().adjust();
}

/** Calculates the x- and y- coordinates in the target picture
    corresponding to a specific degree in the circle,
    and a specific distance from the centre of the circle.
    &param degree 0 = east(left), 90 = north(down), 180=west(right), 270=south(up)
    &param radius distance from centre of chart-circle
    &param &x here is returned the x-coordinate corresponding to the specified position
    &param &y here is returned the y-coordinate corresponding to the specified position
 */
void QHWAstroChartView::getXY(float degree, int radius, int &x, int &y) {
  degree -= 180;
  if (degree < 0) { degree += 360; }
  if (degree > 360) { degree -= 360; }


  double sinPos = sin(deg2rad(degree));
  double cosPos = cos(deg2rad(degree));

  x =  +              (int)(0 + (cosPos * radius));
  y =                -(int)(0 + (sinPos * radius));
}

/////////////////////////////////////////////////////////////777
//// INFO STUFF:


QString QHWAstroChartView::queryForAspect(int planet1, int planet2, int aspect, bool transit, bool synastry) {
    QString query =
    QString(PLANET_FULL_NAMES[planet1]) + " " +
            QString(ephem_nameOfAspect(aspect)) + " " +
            QString(PLANET_FULL_NAMES[planet2]);
    if (transit) {
        query = "transit " + query;
    }
    if (synastry) {
        query = "synastry " + query;
    }
    if (!transit && !synastry) {
        query += "|" + QString::number(planet1) + ",-1,-1," +
                 QString::number(aspect) + "," + QString::number(planet2);
    }
    return query;
}

QString QHWAstroChartView::queryForTransitAspect(int transPlanet, int nativePlanet, int aspect) {
    return queryForAspect(transPlanet, nativePlanet, aspect, true, false);
}

QString QHWAstroChartView::queryForComparisonAspect(int planet1, int planet2, int aspect) {
    return queryForAspect(planet1, planet2, aspect, false, true);
}

QString QHWAstroChartView::queryForPlanetInSign(int planet, int sign) {
    QString query =
         QString(PLANET_FULL_NAMES[planet]) + " in " +
         QString(SIGN_NAMES[sign]);
    query += "|" + QString::number(planet) + "," + QString::number(sign) + ",-1,-1,-1,-1";
    return query;
}

QString QHWAstroChartView::queryForPlanetInHouse(int planet, int house) {
    QString query =
         QString(PLANET_FULL_NAMES[planet]) + " in " +
         QString(HOUSE_NAMES[house]) + " house";
    query += "|" + QString::number(planet) + ",-1," + QString::number(house) + ",-1,-1,-1";
    return query;
}

QString QHWAstroChartView::queryForTransitInHouse(int planet, int house) {
    QString query =
            "transit " +
         QString(PLANET_FULL_NAMES[planet]) + " in " +
         QString(HOUSE_NAMES[house]) + " house";
    return query;
}

QString QHWAstroChartView::queryForComparisonInHouse(int planet, int house) {
    QString query =
            "synastry " +
         QString(PLANET_FULL_NAMES[planet]) + " in " +
         QString(HOUSE_NAMES[house]) + " house";
    return query;
}

QString QHWAstroChartView::htmlPlanetImage(int planet) {
    return "<img src='" + planetImageFile(planet) + "'>";
}

QString QHWAstroChartView::htmlPlanetImage15(int planet) {
    return "<img src='" + planetImageFile15(planet) + "'>";
}

QString QHWAstroChartView::htmlAspectImage(int aspect) {
    return "<img src='" + aspectImageFile(aspect) + "'>";
}

QString QHWAstroChartView::htmlSignImage(int sign) {
    return "<img src='" + signImageFile(sign) + "'>";
}

#define LINK_START(href) QString("<a href='") + href + QString("'>")
#define LINK_END QString("</a>")
#define LINK(href,caption) LINK_START(href) + QString(caption) + LINK_END
#define TABLE_START QString("<table>")
#define TABLE_START_PARAM(param) QString("<table ")+QString(param) + QString(">")
#define TABLE_END QString("</table>")
#define TABLE(content) TABLE_START + content + TABLE_END
#define TR_START QString("<tr>")
#define TR_END QString("</tr>")
#define TR(content) TR_START + content + TR_END
#define TD_START QString("<td>")
#define TD_START_CS(cs) QString("<td colspan=")+QString::number(cs)+QString(">")
#define TD_END QString("</td>")
#define TD(content) TD_START + content + TD_END
#define TD_PARAM(content,param) QString("<td ")+QString(param) + QString(">") + content + TD_END
#define TD_CS(cs,content) TD_START_CS(cs) + content + TD_END
#define BR QString("<br>")

QString QHWAstroChartView::infoForPlanet(int planet) {
    qDebug("infoForPlanet");
    /*if (isComparisonChart() && !isTransitChart) {
        return infoForSynastryPlanet(planet, true);
    }*/
    QString name(PLANET_NAMES[planet]);
    float pos = ephem_positionOfPlanet(planetPositions, planet);
    int sign = ephem_signForPosition(pos);
    int house = houseOfPosition(pos);

    bool showNextHouseToo = false;
    int nextHouse = (house == HOUSE_12 ? HOUSE_1 : house + 1);
    if (getNatalAspect(pos, getPositionOfHouseCusp(nextHouse)) == 0) {
        showNextHouseToo = true;
    }

    QString head = TABLE(
            TR(TD(htmlPlanetImage(planet)) +
               TD("<b>" + name + "</b>") +
               TD(posToString(pos))));

    bool isCardinalHouse = (planet == ASCENDANT || planet == MEDIUM_COELI);

    QString positionInfo =
        LINK(queryForPlanetInSign(planet, sign), QString(PLANET_NAMES[planet]) + tr(" in ") + QString(SIGN_NAMES[sign]));

    if (!isCardinalHouse) {
        positionInfo += BR +
                        LINK(queryForPlanetInHouse(planet, house), QString(PLANET_NAMES[planet]) + tr(" in ") + QString(HOUSE_NAMES[house]) + tr(" house"));
        if (showNextHouseToo) {
            positionInfo += BR +
                    LINK(queryForPlanetInHouse(planet, nextHouse), QString(PLANET_NAMES[planet]) + tr(" conjunct ") + QString(HOUSE_NAMES[nextHouse]) + tr(" house"));

        }
    }

    QString aspectInfo = TABLE_START_PARAM("width=100%") +
                         TR(TD("Aspects") + TD("Pos") + TD("Orb"));
    for (int p2 = SUN; p2 <= MEDIUM_COELI; p2++) {
        if (p2 != planet && (chartHasHouses() || p2 < ASCENDANT)) {
            float pos2 = ephem_positionOfPlanet(planetPositions, p2);
            int aspect = getNatalAspect(pos, pos2);
            if (aspect > -1) {
                float orb = calcDistance(pos, pos2) - aspect;
                if (orb < 0) { orb = -orb; }
                QString orbStr = QString::number(orb,'f',2);
                aspectInfo = aspectInfo +
                             TR(
                                TD(LINK(queryForAspect(planet,p2,aspect),
                                    QString(ephem_nameOfAspect(aspect)) + " " +
                                    QString(PLANET_NAMES[p2]))) +
                                TD(posToString(pos2)) +
                                TD(orbStr));
            }
        }
    }

    qDebug("infoForPlanet DONE");
    return head + BR + positionInfo + BR + aspectInfo;
}

QString QHWAstroChartView::infoForComparisonPlanet(int planet) {
    if (isTransitChart) {
        return infoForTransitPlanet(planet);
    } else {
        return infoForSynastryPlanet(planet); //, false);
    }
}

QString QHWAstroChartView::infoForSynastryPlanet(int planet) { //, bool reverse) {
    //return "SYN INFO";
    QString name(PLANET_NAMES[planet]);
    float pos = 0.0;
    //if (reverse) {
    //    pos = ephem_positionOfPlanet(planetPositions , planet);
    //} else {
        pos = ephem_positionOfPlanet(comparisonPositions , planet);
    //}

    int house = 0;
    /*if (reverse) {
        house = comparisonHouseOfPosition(pos);
    } else {
*/
  house = houseOfPosition(pos);
    //}

    bool showNextHouseToo = false;
    int nextHouse = (house == HOUSE_12 ? HOUSE_1 : house + 1);
    /*if (reverse) {
        if (getSynastryAspect(pos,getPositionOfCompHouseCusp(nextHouse))) {
            showNextHouseToo = true;
        }
    } else {*/
        if (getSynastryAspect(pos,getPositionOfHouseCusp(nextHouse))) {
            showNextHouseToo = true;
        }
    //}

    QString head = TABLE(
            TR(TD(htmlPlanetImage(planet)) +
               TD("<b>Synastry " + name + "</b>") +
               TD(posToString(pos))));

    QString positionInfo =
        LINK(queryForComparisonInHouse(planet, house), "Synastry " + QString(PLANET_NAMES[planet]) + tr(" in ") + QString(HOUSE_NAMES[house]) + tr(" house"));

    if (showNextHouseToo) {
        positionInfo += BR +
                LINK(queryForComparisonInHouse(planet, nextHouse), "Synastry " + QString(PLANET_NAMES[planet]) + tr(" conjunct ") + QString(HOUSE_NAMES[nextHouse]) + tr(" house"));

    }

    QString aspectInfo = TABLE_START_PARAM("width=100%") +
                         TR(TD("Aspects") + TD("Pos") + TD("Orb"));
    for (int p2 = SUN; p2 <= MEDIUM_COELI; p2++) {
        if (/*((!reverse && */chartHasHouses()/*) || (reverse && comparisonChartHasHouses()))*/ || p2 < ASCENDANT) {

            float pos2 = 0;
            /*if (reverse) {
                pos2 = ephem_positionOfPlanet(comparisonPositions, p2);
            } else {*/
                pos2 = ephem_positionOfPlanet(planetPositions, p2);
            //}
            int aspect = getSynastryAspect(pos, pos2);
            if (aspect > -1) {
                float orb = calcDistance(pos, pos2) - aspect;
                if (orb < 0) { orb = -orb; }
                QString orbStr = QString::number(orb,'f',2);
                aspectInfo = aspectInfo +
                             TR(
                                TD(LINK(queryForComparisonAspect(planet,p2,aspect),
                                    QString(ephem_nameOfAspect(aspect)) + " natal " +
                                    QString(PLANET_NAMES[p2]))) +
                                TD(posToString(pos2)) +
                                TD(orbStr));
            }
        }
    }

    return head + BR + positionInfo + BR + aspectInfo;

}

QString QHWAstroChartView::infoForTransitPlanet(int planet) {
    qDebug("infoForTransitPlanet");
    QString name(PLANET_NAMES[planet]);
    float pos = ephem_positionOfPlanet(comparisonPositions, planet);
    int house = houseOfPosition(pos);

    bool showNextHouseToo = false;
    int nextHouse = (house == HOUSE_12 ? HOUSE_1 : house + 1);
    if (getTransitAspect(pos, getPositionOfHouseCusp(nextHouse)) == 0) {
        showNextHouseToo = true;
    }

    QString head = TABLE(
            TR(TD(htmlPlanetImage(planet)) +
               TD("<b>Transit " + name + "</b>") +
               TD(posToString(pos))));

    QString positionInfo =
        LINK(queryForTransitInHouse(planet, house), "Transit " + QString(PLANET_NAMES[planet]) + tr(" in ") + QString(HOUSE_NAMES[house]) + tr(" house"));

    if (showNextHouseToo) {
        positionInfo += BR +
                LINK(queryForTransitInHouse(planet, nextHouse), "Transit " + QString(PLANET_NAMES[planet]) + tr(" conjunct ") + QString(HOUSE_NAMES[nextHouse]) + tr(" house"));

    }

    QString aspectInfo = TABLE_START_PARAM("width=100%") +
                         TR(TD("Aspects") + TD("Pos") + TD("Orb"));
    for (int p2 = SUN; p2 <= MEDIUM_COELI; p2++) {
        if (chartHasHouses() || p2 < ASCENDANT) {
            float pos2 = ephem_positionOfPlanet(planetPositions, p2);
            int aspect = getTransitAspect(pos, pos2);
            if (aspect > -1) {
                float orb = calcDistance(pos, pos2) - aspect;
                if (orb < 0) { orb = -orb; }
                QString orbStr = QString::number(orb,'f',2);
                aspectInfo = aspectInfo +
                             TR(
                                TD(LINK(queryForTransitAspect(planet,p2,aspect),
                                    QString(ephem_nameOfAspect(aspect)) + " natal " +
                                    QString(PLANET_NAMES[p2]))) +
                                TD(posToString(pos2)) +
                                TD(orbStr));
            }
        }
    }

    qDebug("infoForTransitPlanet donW");
    return head + BR + positionInfo + BR + aspectInfo;
}

/*QString QHWAstroChartView::createFullChartDescription() {
    qDebug("createFullChartDescription");
    QString desc = "";
    //desc += TABLE_START;
    /*for (int planet = 0; planet < NUM_PLANETS; planet++) {
        float pos = ephem_positionOfPlanet(planetPositions, planet);
        int sign = ephem_signForPosition(pos);
        int house = houseOfPosition(pos);

        bool showNextHouseToo = false;
        int nextHouse = (house == HOUSE_12 ? HOUSE_1 : house + 1);
        if (getNatalAspect(pos, getPositionOfHouseCusp(nextHouse)) == 0) {
            showNextHouseToo = true;
        }

        desc += QString(SIMPLE_PLANET_PREFIX) + QString(SIMPLE_PLANET_DESC[planet]) + QString(" ") +
                LINK(queryForPlanetInSign(planet, sign), QString("(") + QString(PLANET_NAMES[planet]) + QString(")")) +
                QString(SIMPLE_SIGN_PREFIX) + QString(SIMPLE_SIGN_DESC[sign]) + QString(SIMPLE_SIGN_POSTFIX) + QString(" ") +
                LINK(queryForPlanetInSign(planet, sign), QString("(") + QString(SIGN_NAMES[sign]) + QString(")")) +
                QString(SIMPLE_HOUSE_PREFIX) + QString(SIMPLE_HOUSE_DESC[house]) + QString(" ") +
                LINK(queryForPlanetInHouse(planet, house), QString("(") + QString(HOUSE_NAMES[house]) + QString(" house)"));

        if (showNextHouseToo) {
            desc += QString(" or ") +
                    QString(SIMPLE_HOUSE_PREFIX) + QString(SIMPLE_HOUSE_DESC[nextHouse]) + QString(" ") +
                    LINK(queryForPlanetInHouse(planet, nextHouse), QString("(") + QString(HOUSE_NAMES[nextHouse]) + QString(" house)"));
        }

        desc += BR + BR;
    }
    //desc += TABLE_END;*/
/*    qDebug("createFullChartDescription DONE");
    return desc;
}*/

/*
QString QHWAstroChartView::createHTMLaspectTable() {
    QString ret = "";
    ret += TABLE_START_PARAM("border=1");

    QString tdParam = "VALIGN=MIDDLE ALIGN=CENTER WIDTH=19 HEIGHT=19";

    ret += TR_START + TD("");
    for (int p = 1; p < NUM_PLANETS + 2; p++) {
        ret += TD_PARAM(htmlPlanetImage15(p), tdParam);
    }
    ret += TR_END;

    for (int p1 = 0; p1 < NUM_PLANETS + 2; p1++) {
        ret += TR_START;
        ret += TD_PARAM(htmlPlanetImage15(p1), tdParam);
        float pos1 = ephem_positionOfPlanet(planetPositions, p1);
        for (int p2 = 1; p2 < NUM_PLANETS + 2; p2++) {
            float pos2 = ephem_positionOfPlanet(planetPositions, p2);
            int aspect = getAspect(pos1, pos2);
            if (aspect >= 0) {
                ret += TD_PARAM(htmlAspectImage(aspect), tdParam);
            } else {
                ret += TD("");
            }
        }
        ret += TR_END;
    }
    ret += TABLE_END;
    return ret;
}
*/
QString QHWAstroChartView::createHTMLaspectTable() {
    qDebug("createHTMLaspectTable");
    QString ret = "";
    ret += TABLE_START_PARAM("border=0");

    QString tdParam = "VALIGN=MIDDLE ALIGN=CENTER WIDTH=23 HEIGHT=23";
    QString tdParamAsp = tdParam + QString(" style=\"background: #eeeeee;\"");

     //QString tdParamAsp = "style=\"background: red;\"";

    ret += TR_START;
    ret += TD_PARAM(htmlPlanetImage(0), tdParam);
    ret += TR_END;
    for (int p1 = 1; p1 < NUM_PLANETS + 2; p1++) {
        float pos1 = ephem_positionOfPlanet(planetPositions, p1);
        ret += TR_START;
        for (int p2 = 0; p2 < p1 && p2 < ASCENDANT; p2++) {
            float pos2 = ephem_positionOfPlanet(planetPositions, p2);
            int aspect = getNatalAspect(pos1, pos2);
            if (aspect >= 0) {
                ret += TD_PARAM(htmlAspectImage(aspect), tdParamAsp);
            } else {
                ret += TD_PARAM("", tdParamAsp);
            }
        }
        ret += TD_PARAM(htmlPlanetImage(p1), tdParam);
        ret += TR_END;
    }
/*

    ret += TR_START + TD("");
    for (int p = 1; p < NUM_PLANETS + 2; p++) {
        ret += TD_PARAM(htmlPlanetImage15(p), tdParam);
    }
    ret += TR_END;

    for (int p1 = 0; p1 < NUM_PLANETS + 2; p1++) {
        ret += TR_START;
        ret += TD_PARAM(htmlPlanetImage15(p1), tdParam);
        float pos1 = ephem_positionOfPlanet(planetPositions, p1);
        for (int p2 = 1; p2 < NUM_PLANETS + 2; p2++) {
            float pos2 = ephem_positionOfPlanet(planetPositions, p2);
            int aspect = getAspect(pos1, pos2);
            if (aspect >= 0) {
                ret += TD_PARAM(htmlAspectImage(aspect), tdParam);
            } else {
                ret += TD("");
            }
        }
        ret += TR_END;
    }
    */
    ret += TABLE_END;
    qDebug("createHTMLaspectTable DONE");
    return ret;
}

int QHWAstroChartView::getNatalAspect(int p1, int p2) {
    //qDebug("getNatalAspect");
    return getAspect(p1, p2, (const float*)&DEFAULT_ORBS);
}

int QHWAstroChartView::getSynastryAspect(int p1, int p2) {
    //qDebug("getSynastryAspect");
    return getAspect(p1, p2, (const float*)&DEFAULT_TRANSIT_ORBS);
}

int QHWAstroChartView::getTransitAspect(int p1, int p2) {
    //qDebug("getTransitAspect");
    return getAspect(p1, p2, (const float*)&DEFAULT_TRANSIT_ORBS);
}


double QHWAstroChartView::deg2rad(double deg) {
    return deg * (M_PI / 180 );
}

QHWAstroChartView::~QHWAstroChartView() {

}


