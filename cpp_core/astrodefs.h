#ifndef ASTRODEFS_H
#define ASTRODEFS_H

struct ef1 {
    int planets[11];
};

#define ASTRO_QT
#ifdef ASTRO_QT

#include "qglobal.h"
#define EPH_I16 quint16
#define EPH_I32 quint32

#endif

#define EPHEM_POS EPH_I16


struct _ef2_day {
    EPH_I16 dummy;
    EPH_I16 weekday;
    EPH_I16 sid_h;
    EPH_I16 sid_m;
    EPH_I16 sid_s;
    EPH_I16 gmt;
    EPH_I16 day;
    EPH_I16 month;
    EPH_I32 year;
    EPH_I16 sun;
    EPH_I16 moon;
    EPH_I16 mercury;
    EPH_I16 venus;
    EPH_I16 mars;
    EPH_I16 jupiter;
    EPH_I16 saturn;
    EPH_I16 uranus;
    EPH_I16 neptune;
    EPH_I16 pluto;
    EPH_I16 node;
};
#define EPHEM_REC _ef2_day

struct planet_positions {
    int weekday;
    float sideralTime;
    float gmt0sideralTime;
    float gmtTime;
    float sun;
    float moon;
    float mercury;
    float venus;
    float mars;
    float jupiter;
    float saturn;
    float uranus;
    float neptune;
    float pluto;
    float node;

    float ascendant;
    float mediumCoeli;

    float latitude;
    float longitude;
    float localSideral;
};


const int SUN = 0;
const int MOON = 1;
const int MERCURY = 2;
const int VENUS = 3;
const int MARS = 4;
const int JUPITER = 5;
const int SATURN = 6;
const int URANUS = 7;
const int NEPTUNE = 8;
const int PLUTO = 9;
const int NODE = 10;

const int ASCENDANT = 11;
const int MEDIUM_COELI = 12;

const int PLANETS[] = {
    SUN,MOON,MERCURY,VENUS,MARS,JUPITER,SATURN,URANUS,NEPTUNE,PLUTO,NODE
};

const int ARIES = 0;
const int TAURUS = 1;
const int GEMINI = 2;
const int CANCER = 3;
const int LEO = 4;
const int VIRGO = 5;
const int LIBRA = 6;
const int SCORPIO = 7;
const int SAGGITARIUS = 8;
const int CAPRICORN = 9;
const int AQUARUIS = 10;
const int PISCES = 11;


const int SIGNS[] = {
    ARIES,TAURUS,GEMINI,CANCER,LEO,VIRGO,LIBRA,SCORPIO,SAGGITARIUS,CAPRICORN,AQUARUIS,PISCES
};

float ephem_positionOfPlanet(EPHEM_REC rec, int planet);
float ephem_positionOfPlanet(const planet_positions & rec, int planet);
int ephem_signForPosition(float pos);
void ephem_setPosition(planet_positions &rec, int planet, float pos);
float hmsToHours(float h, float m, float s);
float filter360(float n);

float calcDistance(float planetPos1, float planetPos2);


const int NUM_ASPECTS = 10;
const int NUM_SIGNS = 12;
const int NUM_PLANETS = 11;

const int ASPECTS[] = {
    0,30,45,60,72,90,120,135,150,180
};

const char ASPECT_NAMES[][13] = {
    "Conjunction", "Semisextile", "Semisquare", "Sextile", "Quintile", "Square",
    "Trine", "Sesquisquare", "Quincunx", "Opposition"
};

const char* ephem_nameOfAspect(int aspect);

/*const float DEFAULT_ORBS[] = {
    8.0,2.0,2.0,4.0,1.0,8.0,8.0,2.0,2.0,8.0
};*/


const float DEFAULT_ORBS[] = {
    9.0, // Conjunction
    2.0, // Semisextile
    2.0, // Semisquare
    4.0, // Sextile
    1.0, // Quintile
    9.0, // Square
    9.0, // Trine
    2.0, // Sesquisquare
    2.0, // Quincunx
    9.0  // Opposition
};

/*const float DEFAULT_ORBS[] = {
    8.0, // Conjunction
    2.0, // Semisextile
    2.0, // Semisquare
    4.0, // Sextile
    1.0, // Quintile
    8.0, // Square
    8.0, // Trine
    2.0, // Sesquisquare
    2.0, // Quincunx
    8.0  // Opposition
};*/

const float DEFAULT_TRANSIT_ORBS[] = {
    4.0, // Conjunction
    0.5, // Semisextile
    0.5, // Semisquare
    1.0, // Sextile
    0.5, // Quintile
    2.0, // Square
    2.0, // Trine
    0.5, // Sesquisquare
    0.5, // Quincunx
    3.0  // Opposition
};
/*const float DEFAULT_TRANSIT_ORBS[] = {
    1.0,0.2,0.2,1.0,0.1,1.0,1.0,0.2,0.2,1.0
};*/


struct chart_rgb {
    float r;
    float g;
    float b;
};

const chart_rgb chart_rgb_red = {0,1.0,0};
const chart_rgb chart_rgb_green = {0,1.0,0};
const chart_rgb chart_rgb_blue = {0,0,1.0};
const chart_rgb chart_rgb_black = {0,0,1.0};



const chart_rgb colors[] = {
    chart_rgb_blue, // 0
    chart_rgb_blue, // 20
    chart_rgb_red,  // 45
    chart_rgb_blue, // 60
    chart_rgb_black,    // 72
    chart_rgb_red,  // 90
    chart_rgb_blue, // 120
    chart_rgb_green,    // 135
    chart_rgb_green,    // 150
    chart_rgb_red   // 180
};

#define ELEM_FIRE 0
#define ELEM_AIR 1
#define ELEM_EARTH 2
#define ELEM_WATER 3

const int SIGN_AND_HOUSE_ELEMENTS[] = {
    ELEM_FIRE, ELEM_EARTH, ELEM_AIR, ELEM_WATER,
    ELEM_FIRE, ELEM_EARTH, ELEM_AIR, ELEM_WATER,
    ELEM_FIRE, ELEM_EARTH, ELEM_AIR, ELEM_WATER,
    ELEM_FIRE, ELEM_EARTH, ELEM_AIR, ELEM_WATER,
};

int getAspect(float pos1, float pos2, const float* orbs = (const float*)&DEFAULT_ORBS);

planet_positions duplicate(const planet_positions &pp);

const int EPHEM_DAYS_PER_MONTH[] = {
    31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

const char SIGN_NAMES[][12] = {
    "Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo", "Libra", "Scorpio", "Saggitarius", "Capricorn", "Aquarius", "Pisces"
};

const char SIGN_SHORT_NAMES[][3] = {
    "Ar","Ta","Gm","Cn","Le","Vi","Li","Sc","Sg","Cp","Aq","Pi"
};

const char PLANET_NAMES[][13] = {
    "Sun", "Moon", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto", "Node", "Ascendant", "MC"
};

const char PLANET_FULL_NAMES[][13] = {
    "Sun", "Moon", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto", "North Node", "Ascendant", "Medium Coeli"
};

struct EPHEM_YEAR {
    EPHEM_REC days[366];
};

// Must be implemented:
int ephem_readYear(int year, EPHEM_YEAR* target);
planet_positions ephem_calculateRecForGmt(int year, int month, int day, int h, int m, int s, EPHEM_YEAR* preLoadedYear = 0);
void ephem_positionToChar6(float pos, char* res);
// Implemented in header:


const char SIMPLE_PLANET_PREFIX[] = "The person's ";
const char SIMPLE_PLANET_DESC[][150] = {
    "vitality, identity and inner \"self\"",
    "personality, habits, character and general behaviour ",
    "communicative and mental abilities",
    "ability for friendship, partnership, love and harmony",
    "ability for courage, pioneering and to become energetic and \"heated\"",
    "optimism, inspiration and tendency to expansion",
    "feelings of limitations and obstacles, as well as abilities for control, caution and long term learning",
    "will to revolution, rebellious freedom and innovation (possibly perversion/fanaticism)",
    "tendencies toward love, religiosity and inspiration (possibly vagueness/confusion)",
    "tendencies/abilities for rebirth, or destruction and renewal",
    "north node"
};

const char SIMPLE_SIGN_PREFIX[] = " is expressed in a ";
const char SIMPLE_SIGN_POSTFIX[] = " way";
const char SIMPLE_SIGN_DESC[][100] = {
    "assertive, self-assured, aggressive",
    "possessive",
    "communicative, changing",
    "emotional, protective",
    "creative, joyous",
    "critical, detailed",
    "harmonic, unifying",
    "passionate, secretive, penetrating",
    "wide, open, free",
    "cautious, cold, ambitious",
    "scientific, detached",
    "dreaming, with a sense of the intangible; and often confusing"
};

const char SIMPLE_HOUSE_PREFIX[] = " in areas concerning ";
const char SIMPLE_HOUSE_DESC[][120] = {
    "the person him-/herself",
    "the person's possessions and emotions",
    "short conversations, thoughts, as well as close people like brothers, sisters and neighbours",
    "the Home - or that from which one comes/derives",
    "creativity, joys, love, children (\"the good life\")",
    "services, work and also health",
    "others in close companionship, partners",
    "others possessions (like inheritance), collective emotions. Birth, sex and death",
    "deeper studies, longer travels",
    "career, publicity, the area outside the home - or than one rises up to",
    "non-intimate contacts, friend, social groups/organizations",
    "the hidden and the subconscious, withdrawal, serving through sacrifying"
};

#endif // ASTRODEFS_H
