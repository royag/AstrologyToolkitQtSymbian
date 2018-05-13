#ifndef HOUSE_CALC_H
#define HOUSE_CALC_H

#include "astrodefs.h"


#define HOUSES_NULL 0
#define HOUSES_EQUAL_ASC 1
#define HOUSES_WHOLE_VEDIC 2
#define HOUSES_PORPHYRY 3
#define HOUSES_PLACIDUS 4
#define HOUSES_KOCH 5

#define HOUSE_1 0
#define HOUSE_2 1
#define HOUSE_3 2
#define HOUSE_4 3
#define HOUSE_5 4
#define HOUSE_6 5
#define HOUSE_7 6
#define HOUSE_8 7
#define HOUSE_9 8
#define HOUSE_10 9
#define HOUSE_11 10
#define HOUSE_12 11

const char HOUSE_NAMES[][5] = {
    "1st", "2nd", "3rd", "4th", "5th", "6th",
    "7th", "8th", "9th", "10th", "11th", "12th"
};

const char HOUSE_SYSTEM_NAMES[][10] = {
    "NULL", "Equal", "Whole", "Porphyry", "Placidus", "Koch"
};


float ascendantFromSideralLatitude(float localSideral, float latitude);
float mediumCoeliFromSideral(float localSideral);
float calculateLocalSideral(float gmt0sideral, float newGmtTime, float longitude);

void calcAscAndMc(planet_positions*, float latitude, float longitude);

void calcHouses(float *houses, planet_positions &positions, int houseSystem);

void placProc(double &D11, double &D12, double &D2, double &D3,
              double H11, double H12, double H2, double H3,
              double f, double e);

void calcHousesNULL(float *houses);
void calcHousesEqualASC(float *houses, float asc);
void calcHousesWholeVedic(float *houses, float asc);
void calcHousesPorphyry(float *houses, float asc, float mc);
void calcHousesPlacidus(float *houses, float asc, float mc, float localSideral, float latitude);
void calcHousesKoch(float *houses, float asc, float mc, float localSideral, float latitude);

float degToRad(float deg);

float radToDeg(float rad);

double cot(double);
double acot(double);

double dsin(double);
double dtan(double);
double dcot(double);
double dacot(double);
double dcos(double);
double datan(double);
double dasin(double);

int houses_houseOfPosition(float pos, float *houses);

#endif // HOUSE_CALC_H
