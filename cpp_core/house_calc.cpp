
#include "astrodefs.h"
#include "math.h"
#include "house_calc.h"

float degToRad(float deg) {
    return deg * M_PI / 180.0;
}
double cot(double n) {
    return cos(n)/sin(n);
}
double acot(double n) {
    return atan(1/n);
}

float radToDeg(float rad) {
    return rad * 180.0 / M_PI;
}

inline float eclipticObliquity() {
    return 23.448; // Estimation of the ecliptic obliquity
}

bool mcAboveAsc(float mc, float asc) {
        float desc = filter360(asc + 180.0);
        if (desc > asc) {
                return (mc > desc) || (mc < asc);
        } else {
                return (mc > desc) && (mc < asc);
        }
}

double dsin(double n) {
    return sin(degToRad(n));
}

double dtan(double n) {
    return tan(degToRad(n));
}

double dcot(double n) {
    return cot(degToRad(n));
}

double dacot(double n) {
    return radToDeg(acot(n));
}

double dcos(double n) {
    return cos(degToRad(n));
}

double datan(double n) {
    return radToDeg(atan(n));
}

double dasin(double n) {
    return radToDeg(asin(n));
}

float ascendantFromSideralLatitude(float localSideral, float latitude) {
    float eh = degToRad(eclipticObliquity());

    float ramc = degToRad(localSideral * 15.0);
    float lati = degToRad(latitude);
    float teller = cosf(ramc);
    float nevner = ((0.0 - sinf(ramc)) * cosf(eh) -
            tanf(lati) * sinf(eh));

    float asc_rad = atanf(teller / nevner);
    float asc = radToDeg(asc_rad);
    if (nevner < 0) {
            asc += 180.0;
    }
    return filter360(asc);
}

float mediumCoeliFromSideral(float localSideral) {
    float eh = degToRad(eclipticObliquity());
    float ramc = degToRad(localSideral * 15.0);
    float mc_rad = atanf(tanf(ramc) / cosf(eh));
    float mc = radToDeg(mc_rad);
    if (mc < 0) {
            mc += 180;
    }
    if (radToDeg(ramc) > 180) {
            mc += 180;
    }
    return filter360(mc);
}

float calculateLocalSideral(float gmt0sideraltime, float newGmtTime, float longitude) {
    // 24hours in normal time gives 3 mins 56.6 seconds sideral time.
    // hms2hours(0,3,56.6) / 24) gives 0.00273843
    float hourLength = 0.00273843;
    float localSideral = newGmtTime + gmt0sideraltime +
            (newGmtTime * hourLength) +
            hmsToHours(0, longitude * 4, 0);
    // [above:] the sun spends 4 minutes to pass each of the 360 degrees
    // (360*4=1440mins 1440/60=24hours):
    if (localSideral > 24) {
            localSideral -= 24;
    }
    return localSideral;
}

void calcAscAndMc(planet_positions* pos, float latitude, float longitude) {
    float localSideral = calculateLocalSideral(pos->gmt0sideralTime, pos->gmtTime, longitude);
    float asc = ascendantFromSideralLatitude(localSideral, latitude);
    float mc = mediumCoeliFromSideral(localSideral);
    if (!mcAboveAsc(mc, asc)) {
            if ((latitude > 66) || (latitude < -66)) {
                // We assume this is due to the weird behaviour of the
                // ascendant in the far north (/south ?):
                // We turn the ascendant around 180 degrees,
                // some say we should also turn medium coeli
                    asc = filter360(asc + 180);
            } else {
                    //throw new AstroException("Something wrong with ascendant calculation!");
                // -----------------
                // Hmmm for Hillary Clinton, turning the MC around seems to fix the deal...
                mc = filter360(mc + 180);
                //return; // do nothing
            }
    }
    pos->ascendant = asc;
    pos->mediumCoeli = mc;
    pos->latitude = latitude;
    pos->longitude = longitude;
    pos->localSideral = localSideral;
}

void calcHouses(float *houses, planet_positions &positions, int houseSystem) {
    switch(houseSystem) {
    case HOUSES_NULL:
        calcHousesNULL(houses);
        break;
    case HOUSES_EQUAL_ASC:
        calcHousesEqualASC(houses, positions.ascendant);
        break;
    case HOUSES_WHOLE_VEDIC:
        calcHousesWholeVedic(houses, positions.ascendant);
        break;
    case HOUSES_PORPHYRY:
        calcHousesPorphyry(houses, positions.ascendant, positions.mediumCoeli);
        break;
    case HOUSES_PLACIDUS:
        calcHousesPlacidus(houses, positions.ascendant, positions.mediumCoeli, positions.localSideral, positions.latitude);
        break;
    case HOUSES_KOCH:
        calcHousesKoch(houses, positions.ascendant, positions.mediumCoeli, positions.localSideral, positions.latitude);
        break;
    default:
        calcHousesNULL(houses);
        break;
    }
}

void calcHousesNULL(float *houses) {
    for (int i = 0; i < 12; i++) {
        houses[i] = i*30;
    }
}

void calcHousesEqualASC(float *houses, float asc) {
    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            houses[i] = asc;
        } else {
            houses[i] = filter360(houses[i-1] + 30);
        }
    }
}

void calcHousesWholeVedic(float *houses, float asc) {
    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            houses[i] = ephem_signForPosition(asc) * 30.0;
        } else {
            houses[i] = filter360(houses[i-1] + 30);
        }
    }
}

void calcHousesPorphyry(float *houses, float asc, float mc) {
    float fourthQuadSize = calcDistance(mc, asc);
    float signSizeQ4 = fourthQuadSize / 3.0;
    float firstQuadSize = 180 - fourthQuadSize;
    float signSizeQ1 = firstQuadSize / 3.0;
    houses[0] = asc;
    houses[1] = filter360(asc + signSizeQ1);
    houses[2] = filter360(asc + signSizeQ1 * 2);
    const float ic = houses[3] = filter360(mc + 180.0); // IC/4th
    houses[4] = filter360(ic + signSizeQ4);
    houses[5] = filter360(ic + signSizeQ4 * 2);
    const float dec = houses[6] = filter360(asc + 180.0); // Descendant/7th
    houses[7] = filter360(dec + signSizeQ1);
    houses[8] = filter360(dec + signSizeQ1 * 2);
    houses[9] = mc; // MC/10th
    houses[10] = filter360(mc + signSizeQ4);
    houses[11] = filter360(mc + signSizeQ4*2);
}

int houses_houseOfPosition(float pos, float *houses) {
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

    double cuspPlacidus(double deg, double FF, bool fNeg, float localSideral, float latitude)
        {
            double AA = degToRad(latitude);
            if (AA == 0) {
                AA = 0.0001;
            }
            double RA = degToRad(localSideral * 15.0);
            double OB = degToRad(eclipticObliquity());
            double LO;
            double R1;
            double XS;
            double X;
            int i;
            R1 = RA + radToDeg(deg);
            X = (fNeg ? 1.0 : -1.0);
            for (i = 1; i <= 10; i++) {

            /* This formula works except at 0 latitude (AA == 0.0). */

            XS = X*sin(R1)*tan(OB)*tan(AA == 0.0 ? 0.0001 : AA);
            XS = acos(XS);
            if (XS < 0.0)
                XS += M_PI;
                R1 = RA + (fNeg ? M_PI-(XS/FF) : (XS/FF));
            }
            LO = atan(tan(R1)/cos(OB));
            if (LO < 0.0) {
                 LO += M_PI;
            }
            if (sin(R1) < 0.0) {
                LO += M_PI;
            }
            return radToDeg(LO);
        }

        void calcHousesPlacidus(float *houses, float asc, float mc, float localSideral, float latitude)
        {
            houses[1 - 1] = asc;
            houses[4 - 1] = mc + 180.0f;
            houses[5 - 1] = (float)cuspPlacidus(30.0, 3.0, false, localSideral, latitude) + 180.0f;
            houses[6 - 1] = (float)cuspPlacidus(60.0, 1.5, false, localSideral, latitude) + 180.0f;
            houses[2 - 1] = (float)cuspPlacidus(120.0, 1.5, true, localSideral, latitude);
            houses[3 - 1] = (float)cuspPlacidus(150.0, 3.0, true, localSideral, latitude);
            for (int i = 0; i < 12; i++) {
            if (i < 6)
                houses[i] = filter360(houses[i]/*+is.rSid*/);
            else
                houses[i] = filter360(houses[i - 6] + 180.0f); //rDegHalf);
            }
        }

        double Angle(double x, double y)
        {
          double a;

          if (x != 0.0) {
            if (y != 0.0)
              a = atan(y/x);
            else
              a = x < 0.0 ? M_PI : 0.0;
          } else
            a = y < 0.0 ? -(M_PI/2) : (M_PI/2);
          if (a < 0.0)
            a += M_PI;
          if (y < 0.0)
              a += M_PI;
          return a;
        }

        void calcHousesKoch(float *houses, float asc, float mc, float localSideral, float latitude)
        {
            double A1, A2, A3, KN, D, X;
            int i;
            double AA = degToRad(latitude);
            if (AA == 0) {
                AA = 0.0001;
            }
            double RA = degToRad(localSideral * 15.0);
            double OB = degToRad(eclipticObliquity());
            A1 = sin(RA) * tan(AA) * tan(OB);
            A1 = asin(A1);
            for (i = 1; i <= 12; i++) {
                D = filter360(60.0f+30.0f*(float)i);
                A2 = D/90.0-1.0; KN = 1.0;
                if (D >= 180.0) {
                    KN = -1.0;
                    A2 = D/90.0-3.0;
                }
                A3 = degToRad(filter360((float)(radToDeg(RA) + D + A2 * radToDeg(A1))));
                X = Angle(cos(A3) * cos(OB) - KN * tan(AA) * sin(OB), sin(A3));
                houses[i - 1] = filter360((float)radToDeg(X));
            }
        }

