#ifndef ASTROCHART_H
#define ASTROCHART_H

#include <QObject>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include "cpp_core/astrodefs.h"

class AstroChart : public QObject
{
    Q_OBJECT
public:
    explicit AstroChart(QGraphicsScene* scene, QObject *parent = 0);
    void updatePositions(planet_positions pos);
signals:

public slots:

private:
    void loadPixmaps();
    void getXY(float degree, int radius,int &x, int &y);
    double deg2rad(double deg);
    QGraphicsScene* m_scene;
    QGraphicsPixmapItem* m_pmSun;
    QGraphicsPixmapItem* m_pmMoon;
    QGraphicsPixmapItem* m_pmMercury;
    QGraphicsPixmapItem* m_pmVenus;
    QGraphicsPixmapItem* m_pmMars;
    QGraphicsPixmapItem* m_pmJupiter;
    QGraphicsPixmapItem* m_pmSaturn;
    QGraphicsPixmapItem* m_pmUranus;
    QGraphicsPixmapItem* m_pmNeptune;
    QGraphicsPixmapItem* m_pmPluto;
    QGraphicsPixmapItem* m_pmNode;

    QGraphicsLineItem* m_axisAscDesc;
    QGraphicsLineItem* m_axisMcIc;
    void centerAtDegRadius(int deg, int radius, QGraphicsPixmapItem *pm);
    int m_radius;
    int m_zodInnerRadius;

    QGraphicsEllipseItem* m_zodiac1;
    QGraphicsLineItem* m_zodLines[12];
    QGraphicsPixmapItem* m_pmAries;
    QGraphicsPixmapItem* m_pmTaurus;
    QGraphicsPixmapItem* m_pmGemini;
    QGraphicsPixmapItem* m_pmCancer;
    QGraphicsPixmapItem* m_pmLeo;
    QGraphicsPixmapItem* m_pmVirgo;
    QGraphicsPixmapItem* m_pmLibra;
    QGraphicsPixmapItem* m_pmScorpio;
    QGraphicsPixmapItem* m_pmSaggitarius;
    QGraphicsPixmapItem* m_pmCapricorn;
    QGraphicsPixmapItem* m_pmAquarius;
    QGraphicsPixmapItem* m_pmPisces;

    QGraphicsLineItem* m_aspectLines[NUM_PLANETS][NUM_PLANETS];

};

#endif // ASTROCHART_H
