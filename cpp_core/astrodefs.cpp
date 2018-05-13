#include "astrodefs.h"

#include "qfile.h"
#include "qiodevice.h"
#include "qdatastream.h"
#include "math.h"
#include <QApplication>

#include <QDate>
#include <QDateTime>
#include <QTime>

/////////////////

/*
AspectColors = {
  0 => 0x0000FFFF, #[0,0,255],
  30 => 0x0000FFFF, #[0,0,255],
  45 => 0xFF0000FF, #[255,0,0],
  60 => 0x0000FFFF, #[0,0,255],
  72 => 0x000000FF, #[0,0,0],
  90 => 0xFF0000FF, #[255,0,0],
  120 => 0x0000FFFF, #[0,0,255],
  135 => 0x00FF00FF, #[0,255,0],
  150 => 0x00FF00FF, #[0,255,0],
  180 => 0xFF0000FF #[255,0,0]
}
*/

const char* ephem_nameOfAspect(int aspect) {
    for (int i = 0; i < 10; i++) {
        if (ASPECTS[i] == aspect) {
            return ASPECT_NAMES[i];
        }
    }
    return 0;
}

int ephem_signForPosition(float pos) {
    return floor(pos / 30.0);
}

float ephem_signPosForPosition(float pos) {
    return pos - (ephem_signForPosition(pos) * 30);
}

int ephem_signDegForPosition(float pos) {
    float sp = ephem_signPosForPosition(pos);
    return floor(sp);
}

int ephem_signCDegForPosition(float pos) {
    float sp = ephem_signPosForPosition(pos);
    int sd = ephem_signDegForPosition(pos);
    return floor((sp - sd) * 100);
}

void ephem_positionToChar6(float pos, char* res) {
    char degChar[3] = {0,0,0};
    int deg = ephem_signDegForPosition(pos);
    if (deg < 10) {
        sprintf((char*)&degChar, "0%i", deg);
    } else {
        sprintf((char*)&degChar, "%i", deg);
    }
    //degChar[2] = 0;

    char cdegChar[3] = {0,0,0};
    int cdeg = ephem_signCDegForPosition(pos);
    if (cdeg < 10) {
        sprintf((char*)&cdegChar, "0%i", cdeg);
    } else {
        sprintf((char*)&cdegChar, "%i", cdeg);
    }
    //cdegChar[2] = 0;

    int sign = ephem_signForPosition(pos);

    //char * signName = &(SIGN_SHORT_NAMES[sign]);
    sprintf(res, "%s%s%s", degChar, SIGN_SHORT_NAMES[sign], cdegChar);
}

float ephem_positionOfPlanet(EPHEM_REC rec, int planet) {
    EPHEM_POS pos = 0;
    switch (planet) {
    case SUN: pos = rec.sun; break;
    case MOON: pos = rec.moon; break;
    case MERCURY: pos = rec.mercury; break;
    case VENUS: pos = rec.venus; break;
    case MARS: pos = rec.mars; break;
    case JUPITER: pos = rec.jupiter; break;
    case SATURN: pos = rec.saturn; break;
    case URANUS: pos = rec.uranus; break;
    case NEPTUNE: pos = rec.neptune; break;
    case PLUTO: pos = rec.pluto; break;
    case NODE: pos = rec.node; break;
    }
    return pos / 100.0;
}

void ephem_setPosition(planet_positions &rec, int planet, float pos) {
    switch (planet) {
    case SUN: rec.sun = pos; break;
    case MOON: rec.moon = pos; break;
    case MERCURY: rec.mercury = pos; break;
    case VENUS: rec.venus = pos; break;
    case MARS: rec.mars = pos; break;
    case JUPITER: rec.jupiter = pos; break;
    case SATURN: rec.saturn = pos; break;
    case URANUS: rec.uranus = pos; break;
    case NEPTUNE: rec.neptune = pos; break;
    case PLUTO: rec.pluto = pos; break;
    case NODE: rec.node = pos; break;
    case ASCENDANT: rec.ascendant = pos; break;
    case MEDIUM_COELI: rec.mediumCoeli = pos; break;
    }
}

float ephem_positionOfPlanet(const planet_positions & rec, int planet) {
    float pos = 0;
    switch (planet) {
    case SUN: pos = rec.sun; break;
    case MOON: pos = rec.moon; break;
    case MERCURY: pos = rec.mercury; break;
    case VENUS: pos = rec.venus; break;
    case MARS: pos = rec.mars; break;
    case JUPITER: pos = rec.jupiter; break;
    case SATURN: pos = rec.saturn; break;
    case URANUS: pos = rec.uranus; break;
    case NEPTUNE: pos = rec.neptune; break;
    case PLUTO: pos = rec.pluto; break;
    case NODE: pos = rec.node; break;
    case ASCENDANT: pos = rec.ascendant; break;
    case MEDIUM_COELI: pos = rec.mediumCoeli; break;
    }
    return pos;
}

float hmsToHours(float h, float m, float s) {
    return h + (m / 60.0) + (s / (60.0 * 60.0));
}

float filter360(float n) {
    if (n >= 360.0) {
        return n - 360.0;
    }
    if (n < 0.0) {
        return n + 360.0;
    }
    return n;
}






int dayNoFromMonthDay(int month, int day) {
        if (month == 1)
        {
                return day - 1;
        }
        else if (month > 1 && month <= 12)
        {
                int daysInPassedMonths = 0;
                for (int i = 0; i < month-1; i++) {
                    daysInPassedMonths += EPHEM_DAYS_PER_MONTH[i];
                }
                return daysInPassedMonths + day - 1;
        }
        else
        {
                return -1;
        }
}

float calculateMeanFloat(float a, float b, float percentAfterA) {
        if (a > (b + 180.0)) // Kind of a hack..!.!
        {
                b += 360.0;
        }
        float res = a + (((b - a) * percentAfterA) / 100.0);
        if (res >= 360.0)
        {
                res -= 360.0;
        }
        return res;
}

planet_positions positionsForEphemRec(EPHEM_REC rec) {
    planet_positions pos;
    pos.sideralTime = hmsToHours(rec.sid_h, rec.sid_m, rec.sid_s);
    pos.gmt0sideralTime = pos.sideralTime;
    pos.gmtTime = 0.0;
    pos.weekday = rec.weekday;
    pos.sun = rec.sun / 100.0;
    pos.moon = rec.moon / 100.0;
    pos.mercury = rec.mercury / 100.0;
    pos.venus = rec.venus / 100.0;
    pos.mars = rec.mars / 100.0;
    pos.jupiter = rec.jupiter / 100.0;
    pos.saturn = rec.saturn / 100.0;
    pos.uranus = rec.uranus / 100.0;
    pos.neptune = rec.neptune / 100.0;
    pos.pluto = rec.pluto / 100.0;
    pos.node = rec.node / 100.0;
    pos.ascendant = 0.0;
    pos.mediumCoeli = 270.0;
    return pos;
}

planet_positions NULLpositions() {
    planet_positions pos;
    pos.sideralTime = 0;
    pos.gmtTime = 0.0;
    pos.weekday = 0;
    pos.sun = 0;
    pos.moon = 0;
    pos.mercury = 0;
    pos.venus = 0;
    pos.mars = 0;
    pos.jupiter = 0;
    pos.saturn = 0;
    pos.uranus = 0;
    pos.neptune = 0;
    pos.pluto = 0;
    pos.node = 0;
    pos.ascendant = 0.0;
    pos.mediumCoeli = 0.0;
    return pos;
}

planet_positions calculateMean(planet_positions rec1, planet_positions rec2, float percentAfterRec1) {
        planet_positions res;
        res.ascendant = 0.0; // NullHouses - Houses corresponds to signs
        res.mediumCoeli = 270.0;
        res.gmt0sideralTime = rec1.gmt0sideralTime;

        res.weekday = rec1.weekday;

        if (rec1.sideralTime > rec2.sideralTime)
        {
                float sidTime = calculateMeanFloat(rec1.sideralTime, rec2.sideralTime + 24.0, percentAfterRec1);
                if (sidTime >= 24.0)
                {
                        res.sideralTime = sidTime - 24;
                }
                else
                {
                        res.sideralTime = sidTime;
                }
        }
        else
        {
                res.sideralTime = calculateMeanFloat(rec1.sideralTime, rec2.sideralTime, percentAfterRec1);
        }

        /*if ((rec1.Gmt != 0) || (rec2.Gmt != 0))
        {
                throw new AstroException("Cannot calculate from records not based on GMT 0:00");
        }*/
        /*res.Day = rec1.Day;
        res.Month = rec1.Month;
        res.Year = rec1.Year;*/


        res.sun = calculateMeanFloat(rec1.sun, rec2.sun, percentAfterRec1);
        res.moon = calculateMeanFloat(rec1.moon, rec2.moon, percentAfterRec1);
        res.mercury = calculateMeanFloat(rec1.mercury, rec2.mercury, percentAfterRec1);
        res.venus = calculateMeanFloat(rec1.venus, rec2.venus, percentAfterRec1);
        res.mars = calculateMeanFloat(rec1.mars, rec2.mars, percentAfterRec1);
        res.jupiter = calculateMeanFloat(rec1.jupiter, rec2.jupiter, percentAfterRec1);
        res.saturn = calculateMeanFloat(rec1.saturn, rec2.saturn, percentAfterRec1);
        res.uranus = calculateMeanFloat(rec1.uranus, rec2.uranus, percentAfterRec1);
        res.neptune = calculateMeanFloat(rec1.neptune, rec2.neptune, percentAfterRec1);
        res.pluto = calculateMeanFloat(rec1.pluto, rec2.pluto, percentAfterRec1);
        res.node = calculateMeanFloat(rec1.node, rec2.node, percentAfterRec1);

        return res;
}

planet_positions ephem_calculateRecForGmt(EPH_I16 year, int dayNo, float gmtHour, EPHEM_YEAR* preLoadedYear = 0,
                                          int verifyMonth = 0, int verifyDay = 0) {
    EPHEM_YEAR y1;
    EPHEM_REC rec1;
    EPHEM_REC rec2;
    if (preLoadedYear != 0 && preLoadedYear->days[0].year == year) {
        y1 = *preLoadedYear;
    } else {
        ephem_readYear(year, &y1);
    }
    if (dayNo == 365) {
        EPHEM_YEAR y2;
        ephem_readYear(year + 1, &y2);
        rec1 = y1.days[365];
        rec2 = y2.days[0];
    } else {
        rec1 = y1.days[dayNo];
        rec2 = y1.days[dayNo+1];
    }
    if (verifyMonth != 0 && rec1.month != verifyMonth) {
        return NULLpositions();
    }
    if (verifyDay != 0 && rec1.day != verifyDay) {
        return NULLpositions();
    }
    planet_positions ret = calculateMean(positionsForEphemRec(rec1), positionsForEphemRec(rec2), (gmtHour * 100) / 24);
    ret.gmtTime = gmtHour;

    return ret;
}

planet_positions ephem_calculateRecForGmt(int year, int month, int day, int h, int m, int s, EPHEM_YEAR* preLoadedYear) {
    planet_positions ret = ephem_calculateRecForGmt(year,
                                    dayNoFromMonthDay(month, day),
                                    hmsToHours(h,m,s), preLoadedYear, month, day);
    // NEW:
    //ret.sideralTime = (float)calcGmtSideralTime(year,month,day,h,m);
    return ret;
}

/// aspects etc:

float calcDistance(float planetPos1, float planetPos2) {
    float d = -1;
    if (planetPos1 > planetPos2) {
        d = planetPos1 - planetPos2;
    } else {
        d = planetPos2 - planetPos1;
    }
    if (d > 180) {
        d = 360 - d;
    }
    return d;
}

int getAspect(float pos1, float pos2, const float* orbs) {
    float dist = calcDistance(pos1, pos2);
    if (dist < 0) {
        return -1;
    }
    for (int i = 0; i < NUM_ASPECTS; i++) {
        /*float asp = ASPECTS[i];
        float orb = orbs[i];
        float lower = asp - orb;
        float upper = asp + orbs;*/
        if (dist >= (ASPECTS[i] - orbs[i]) &&
            (dist <= (ASPECTS[i] + orbs[i]))) {
            return ASPECTS[i];
        }
    }
    return -1;
}

planet_positions duplicate(const planet_positions &pp) {
    planet_positions ret;
    memcpy(&ret, &pp, sizeof(planet_positions));

    /*ret.weekday;
    ret.sideralTime;
    ret.gmt0sideralTime;
    ret.gmtTime;
    ret.sun;
    ret.moon;
    ret.mercury;
    ret.venus;
    ret.mars;
    ret.jupiter;
    ret.saturn;
    ret.uranus;
    ret.neptune;
    ret.pluto;
    ret.node;

    ret.ascendant;
    ret.mediumCoeli;*/
    return ret;
}


/////////////////
// QT dependant:

/*double calcGmtSideralTime(int year, int month, int day, int hour, int minute) {
    QDate date(2000,1,1);
    QTime time(12,0,0);
    QDateTime gmt2000(date, time, Qt::UTC);

    QDate date2(year,month,day);
    QTime time2(hour,minute,0);
    QDateTime gmtBirth(date2, time2, Qt::UTC);

    double secs = gmt2000.secsTo(gmtBirth);
    double days = secs / (double)86400;
    double GMST = 18.697374558 + 24.06570982441908 * days;

    long gmstLong = (long)(GMST * 10000);
    long hoursTimes10000 = gmstLong % (24 * 10000);
    double gmtSideralTime = (double)hoursTimes10000 / (double)10000;

    if (gmtSideralTime < 0) {
        gmtSideralTime = 24 + gmtSideralTime;
    }
    return gmtSideralTime;
}*/
double calcGmtSideralTime(int year, int month, int day, int hour, int minute) {
    QDate date(2000,1,1);
    QTime time(12,0,0);
    QDateTime gmt2000(date, time, Qt::UTC);

    QDate date2(year,month,day);
    QTime time2(hour,minute,0);
    QDateTime gmtBirth(date2, time2, Qt::UTC);

    double secs = gmt2000.secsTo(gmtBirth);
    double days = secs / (double)86400;
    double GMST = 18.697374558 + 24.06570982441908 * days;

    double ST = GMST;
    if (ST < 0) ST = -ST;
    double twentyFours = floor(ST / 24.0);
    ST = ST - (twentyFours * 24);
    while (ST >= 24) {
        ST -= 24.0;
    }
    if (GMST < 0) {
        ST = -ST;
    }

    //double gmstLong = (double)(GMST * 10000);
    //double hoursTimes10000 = gmstLong % (24 * 10000);
    double gmtSideralTime = ST; //(double)hoursTimes10000 / (double)10000;

    if (gmtSideralTime < 0) {
        gmtSideralTime = 24 + gmtSideralTime;
    }
    return gmtSideralTime;
}


EPHEM_REC readDay(QDataStream* in) {
    EPHEM_REC ret;
    *in >> ret.dummy;
    *in >> ret.weekday;
    *in >> ret.sid_h;
    *in >> ret.sid_m;
    *in >> ret.sid_s;
    *in >> ret.gmt;
    *in >> ret.day;
    *in >> ret.month;
    *in >> ret.year;
    *in >> ret.sun;
    *in >> ret.moon;
    *in >> ret.mercury;
    *in >> ret.venus;
    *in >> ret.mars;
    *in >> ret.jupiter;
    *in >> ret.saturn;
    *in >> ret.uranus;
    *in >> ret.neptune;
    *in >> ret.pluto;
    *in >> ret.node;
    return ret;
}

void readYear(QDataStream *in, EPHEM_YEAR * target) {
    for (int i = 0; i < 366; i++) {
        target->days[i] = readDay(in);
    }
}

 int readYear(QString year, EPHEM_YEAR * target) {
    //qDebug("Reading year %i", year);
    QString ef2Path = QApplication::applicationDirPath();
    // ":/astrodata/ef2"
    //qDebug("Reading year %i", year);
    QFile f(ef2Path +"/"+year+".ef2");
    bool ok = f.open(QIODevice::ReadOnly);

    if (!ok) {
        return -1;
    }

    QDataStream in(&f);
    in.setByteOrder(QDataStream::LittleEndian);
    readYear(&in, target);

    f.close();
    return 0;
}

int ephem_readYear(int year, EPHEM_YEAR * target) {
    return readYear(QString::number(year), target);
}
