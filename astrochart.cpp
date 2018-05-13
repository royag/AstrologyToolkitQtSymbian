#include "astrochart.h"
#include "math.h"

AstroChart::AstroChart(QGraphicsScene* scene, QObject *parent) :
    QObject(parent)
{
    this->m_scene = scene;
    //scene->setBackgroundBrush(QBrush(QColor(Qt::white)));
    loadPixmaps();
}

void AstroChart::loadPixmaps() {
    m_radius = 175;

    QRadialGradient gradient(0, 0, m_radius, 0, 0);
         gradient.setColorAt(0, QColor::fromRgbF(0.6, 0.6, 1, 1));
         gradient.setColorAt(1, QColor::fromRgbF(0.1, 0, 0.1, 0.5));
    QBrush zBrush(gradient);
    QPen zPen = QPen(Qt::white);
    m_zodiac1 = m_scene->addEllipse(-m_radius,-m_radius,m_radius*2,m_radius*2,zPen,zBrush);
    m_zodInnerRadius = m_radius - 35;
    m_scene->addEllipse(-m_zodInnerRadius,-m_zodInnerRadius,m_zodInnerRadius*2,m_zodInnerRadius*2, zPen);


    for (int i = 0; i < 12; i++) {
        int x, y, x2, y2;
        getXY(i*30, m_radius, x, y);
        getXY(i*30, m_zodInnerRadius, x2, y2);
        m_zodLines[i] = m_scene->addLine(x,y,x2,y2,zPen);
    }

    for (int p1 = 0; p1 < NUM_PLANETS; p1++) {
        for (int p2 = p1+1; p2 < NUM_PLANETS; p2++) {
            m_aspectLines[p1][p2] =
                    m_scene->addLine(0,0,0,0,zPen);
        }
    }


    m_pmAries = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_aries.png"));
    m_pmTaurus = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_taurus.png"));
    m_pmGemini = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_gemini.png"));
    m_pmCancer = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_cancer.png"));
    m_pmLeo = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_leo.png"));
    m_pmVirgo = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_virgo.png"));
    m_pmLibra = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_libra.png"));
    m_pmScorpio = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_scorpio.png"));
    m_pmSaggitarius = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_sagitarius.png"));
    m_pmCapricorn = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_capricorn.png"));
    m_pmAquarius = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_aquarius.png"));
    m_pmPisces = m_scene->addPixmap(QPixmap(":/astrodata/gfx/signs30/wt_pisces.png"));

    QString planetPath = ":/astrodata/gfx/planets15/";
    m_pmSun = m_scene->addPixmap(QPixmap(planetPath+"sun.png"));
    m_pmMoon = m_scene->addPixmap(QPixmap(planetPath+"moon.png"));
    m_pmMercury = m_scene->addPixmap(QPixmap(planetPath+"mercury.png"));
    m_pmVenus = m_scene->addPixmap(QPixmap(planetPath+"venus.png"));
    m_pmMars = m_scene->addPixmap(QPixmap(planetPath+"mars.png"));
    m_pmJupiter = m_scene->addPixmap(QPixmap(planetPath+"jupiter.png"));
    m_pmSaturn = m_scene->addPixmap(QPixmap(planetPath+"saturn.png"));
    m_pmUranus = m_scene->addPixmap(QPixmap(planetPath+"uranus.png"));
    m_pmNeptune = m_scene->addPixmap(QPixmap(planetPath+"neptune.png"));
    m_pmPluto = m_scene->addPixmap(QPixmap(planetPath+"pluto.png"));
    m_pmNode = m_scene->addPixmap(QPixmap(planetPath+"sun.png"));

    m_axisAscDesc = m_scene->addLine(-m_radius,0,m_radius,0);
    m_axisMcIc = m_scene->addLine(0,-m_radius,0,m_radius);
}

void AstroChart::updatePositions(planet_positions pp) {
    int x; int y;
    int x2; int y2;

    int aries0 = 360 - pp.ascendant;
    int mc = round(pp.mediumCoeli);
    getXY(mc+aries0,m_radius,x,y);
    getXY(mc+aries0-180,m_radius,x2,y2);
    m_axisMcIc->setLine(x,y,x2,y2);

    int planetRadius = m_radius - 50;

    centerAtDegRadius(pp.sun+aries0, planetRadius, m_pmSun);
    centerAtDegRadius(pp.moon+aries0, planetRadius, m_pmMoon);
    centerAtDegRadius(pp.mercury+aries0, planetRadius, m_pmMercury);
    centerAtDegRadius(pp.venus+aries0, planetRadius, m_pmVenus);
    centerAtDegRadius(pp.mars+aries0, planetRadius, m_pmMars);
    centerAtDegRadius(pp.jupiter+aries0, planetRadius, m_pmJupiter);
    centerAtDegRadius(pp.saturn+aries0, planetRadius, m_pmSaturn);
    centerAtDegRadius(pp.uranus+aries0, planetRadius, m_pmUranus);
    centerAtDegRadius(pp.neptune+aries0, planetRadius, m_pmNeptune);
    centerAtDegRadius(pp.pluto+aries0, planetRadius, m_pmPluto);
    centerAtDegRadius(pp.node+aries0, planetRadius, m_pmNode);

    int signRadius = m_radius - 20;
    centerAtDegRadius(aries0+15+0, signRadius, m_pmAries);
    centerAtDegRadius(aries0+15+30, signRadius, m_pmTaurus);
    centerAtDegRadius(aries0+15+60, signRadius, m_pmGemini);
    centerAtDegRadius(aries0+15+90, signRadius, m_pmCancer);
    centerAtDegRadius(aries0+15+120, signRadius, m_pmLeo);
    centerAtDegRadius(aries0+15+150, signRadius, m_pmVirgo);
    centerAtDegRadius(aries0+15+180, signRadius, m_pmLibra);
    centerAtDegRadius(aries0+15+210, signRadius, m_pmScorpio);
    centerAtDegRadius(aries0+15+240, signRadius, m_pmSaggitarius);
    centerAtDegRadius(aries0+15+270, signRadius, m_pmCapricorn);
    centerAtDegRadius(aries0+15+300, signRadius, m_pmAquarius);
    centerAtDegRadius(aries0+15+330, signRadius, m_pmPisces);


    for (int i = 0; i < 12; i++) {
        getXY(aries0 + i*30, m_radius, x, y);
        getXY(aries0 + i*30, m_zodInnerRadius, x2, y2);
        m_zodLines[i]->setLine(x,y,x2,y2);
    }

    // aspects:
    int aspectRadius = planetRadius - 10;
    for (int p1 = 0; p1 < NUM_PLANETS; p1++) {
        for (int p2 = p1+1; p2 < NUM_PLANETS; p2++) {
            float pos1 = ephem_positionOfPlanet(pp, p1);
            float pos2 = ephem_positionOfPlanet(pp, p2);
            int aspect = getAspect(pos1, pos2);
            if (aspect >= 0) {
                getXY(aries0 + pos1, aspectRadius, x, y);
                getXY(aries0 + pos2, aspectRadius, x2, y2);
                m_aspectLines[p1][p2]->setLine(x,y,x2,y2);
                m_aspectLines[p1][p2]->setVisible(true);
            } else {
                m_aspectLines[p1][p2]->setVisible(false);
            }
        }
    }


    /*getXY(pp.sun+aries0,x,y); m_pmSun->setPos(x,y);
    getXY(pp.moon+aries0,x,y); m_pmMoon->setPos(x,y);
    getXY(pp.mercury+aries0,x,y); m_pmMercury->setPos(x,y);
    getXY(pp.venus+aries0,x,y); m_pmVenus->setPos(x,y);
    getXY(pp.mars+aries0,x,y); m_pmMars->setPos(x,y);
    getXY(pp.jupiter+aries0,x,y); m_pmJupiter->setPos(x,y);
    getXY(pp.saturn+aries0,x,y); m_pmSaturn->setPos(x,y);
    getXY(pp.uranus+aries0,x,y); m_pmUranus->setPos(x,y);
    getXY(pp.neptune+aries0,x,y); m_pmNeptune->setPos(x,y);
    getXY(pp.pluto+aries0,x,y); m_pmPluto->setPos(x,y);
    getXY(pp.node+aries0,x,y); m_pmNode->setPos(x,y);*/

}

void AstroChart::centerAtDegRadius(int deg, int radius, QGraphicsPixmapItem *pm) {
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
void AstroChart::getXY(float degree, int radius, int &x, int &y) {
  degree -= 180;
  if (degree < 0) { degree += 360; }
  if (degree > 360) { degree -= 360; }


  double sinPos = sin(deg2rad(degree));
  double cosPos = cos(deg2rad(degree));

  x = (int)(0 + (cosPos * radius));
  y = -(int)(0 + (sinPos * radius));
}

double AstroChart::deg2rad(double deg) {
    return deg * (M_PI / 180 );
}

