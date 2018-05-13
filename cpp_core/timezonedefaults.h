#ifndef TIMEZONEDEFAULTS_H
#define TIMEZONEDEFAULTS_H

#include <QString>
#include <QList>
#include <QStringList>

#define ifCCeqCCaddZtoLISTandINC(cc1,cc2,zone,list,i) if (cc1.compare(cc2,Qt::CaseSensitive) == 0) {list.append(zone);i++;}

class TimeZoneDefaults {
public:
    static int addDefaultZonesForCountry(const QString &countryCode, QStringList &list) {
        int i = 0;
        // USA:
        ifCCeqCCaddZtoLISTandINC(countryCode,"USAK","America/Anchorage",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USNY","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USVA","America/Louisville",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USAL","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USND","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USHI","Pacific/Honolulu",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USRI","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USDE","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USMD","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USMN","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USNE","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USCO","America/Denver",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USME","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USMO","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USIA","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USWY","America/Denver",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USKY","America/Louisville",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USOH","America/Detroit",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USIL","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USAZ","America/Phoenix",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USOR","America/Los_Angeles",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USNH","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USGA","America/Louisville",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USTN","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USTX","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USSC","America/Louisville",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USIN","America/Indiana/Indianapolis",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USID","America/Boise",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USCT","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USNJ","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USPA","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USFL","America/Louisville",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USMI","America/Detroit",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USMS","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USAR","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USOK","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USSD","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USWI","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USMT","America/Boise",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USVT","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USKS","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USCA","America/Los_Angeles",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USNV","America/Los_Angeles",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USDC","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USMA","America/New_York",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USWV","America/Louisville",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USNM","America/Denver",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USUT","America/Boise",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USNC","America/Louisville",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USLA","America/Chicago",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"USWA","America/Los_Angeles",list,i);

        // REST OF WORLD:
        ifCCeqCCaddZtoLISTandINC(countryCode,"UK","Europe/London",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SI","Europe/Ljubljana",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"IT","Europe/Rome",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"GR","Europe/Athens",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CY","Europe/Nicosia",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AL","Europe/Tirane",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"JA","Asia/Tokyo",list,i);

        //multiple:
        // Russia (today?)
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Europe/Moscow",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Europe/Kaliningrad",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Yekaterinburg",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Omsk",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Krasnoyarsk",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Irkutsk",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Yakutsk",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Vladivostok",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Magadan",list,i);
        // Russia (additional/historic?)
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Europe/Samara",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Europe/Volgograd",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Anadyr",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Kamchatka",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Novosibirsk",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Novokuznetsk",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RS","Asia/Sakhalin",list,i);


        ifCCeqCCaddZtoLISTandINC(countryCode,"TU","Europe/Istanbul",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"NO","Europe/Oslo",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"MN","Europe/Monaco",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"MD","Europe/Chisinau",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"FR","Europe/Paris",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"EG","Africa/Cairo",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"HU","Europe/Budapest",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"GI","Europe/Gibraltar",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BO","Europe/Minsk",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AN","Europe/Andorra",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"LO","Europe/Bratislava",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"FI","Europe/Helsinki",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BE","Europe/Brussels",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SW","Europe/Stockholm",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"IC","Atlantic/Reykjavik",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"EI","Europe/Dublin",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"PK","Asia/Karachi",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"YI","Europe/Belgrade",list,i);

        //multiple:
        // UKRAINE:
        ifCCeqCCaddZtoLISTandINC(countryCode,"UP","Europe/Kiev",list,i);
        // UKRAINE - for historic purposes ? :
        ifCCeqCCaddZtoLISTandINC(countryCode,"UP","Europe/Simferopol",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"UP","Europe/Uzhgorod",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"UP","Europe/Zaporozhy",list,i);

        ifCCeqCCaddZtoLISTandINC(countryCode,"LG","Europe/Riga",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"IZ","Asia/Baghdad",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"PL","Europe/Warsaw",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"LH","Europe/Vilnius",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"GM","Europe/Berlin",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SZ","Europe/Zurich",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SP","Europe/Madrid",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RO","Europe/Bucharest",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"MT","Europe/Malta",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"LS","Europe/Vaduz",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"DA","Europe/Copenhagen",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"KS","Asia/Seoul",list,i);


        //multiple:
        // CHINA:
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Shanghai",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Harbin",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Chongqing",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Urumqi",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Kashgar",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Hong_Kong",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Ulaanbaatar",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Hovd",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Choibalsan",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Macau",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CH","Asia/Taipei",list,i);


        //multiple:
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Whitehorse",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Vancouver",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Yellowknife",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Edmonton",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Regine",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Winnipeg",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Thunder_Bay",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Montreal",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/Halifax",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CA","America/St_Johns",list,i);

        ifCCeqCCaddZtoLISTandINC(countryCode,"VT","Europe/Vatican",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"NL","Europe/Amsterdam",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"MK","Europe/Skopje",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BU","Europe/Sofia",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"PO","Europe/Lisbon",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"LU","Europe/Luxembourg",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"EN","Europe/Tallinn",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BK","Europe/Sarajevo",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AU","Europe/Vienna",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"HR","Europe/Zagreb",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"EZ","Europe/Prague",list,i);


        //// Multiple:
        // Brazil:
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Sao_Paulo",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Noronha",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Belem",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Fortaleza",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Recife",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Araguaina",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Maceio",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Bahia",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Campo_Grande",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Cuiaba",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Santarem",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Porto_Velho",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Boa_Vista",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Manaus",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Eirunepe",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BR","America/Rio_Branco",list,i);

/*
The tz database contains 16 zones for Brazil.coordinates	TZ	comments	UTC offset	DST	Notes
-0351-03225	America/Noronha	Atlantic islands	-02:00	-
-0127-04829	America/Belem	Amapa, E Para	-03:00	-
-0343-03830	America/Fortaleza	NE Brazil (MA, PI, CE, RN, PB)	-03:00	-
-0803-03454	America/Recife	Pernambuco	-03:00	-
-0712-04812	America/Araguaina	Tocantins	-03:00	-
-0940-03543	America/Maceio	Alagoas, Sergipe	-03:00	-
-1259-03831	America/Bahia	Bahia	-03:00	-
-2332-04637	America/Sao_Paulo	S & SE Brazil (GO, DF, MG, ES, RJ, SP, PR, SC, RS)	-03:00	-02:00
-2027-05437	America/Campo_Grande	Mato Grosso do Sul	-04:00	-03:00
-1535-05605	America/Cuiaba	Mato Grosso	-04:00	-03:00
-0226-05452	America/Santarem	W Para	-03:00	-
-0846-06354	America/Porto_Velho	Rondonia	-04:00	-
+0249-06040	America/Boa_Vista	Roraima	-04:00	-
-0308-06001	America/Manaus	E Amazonas	-04:00	-
-0640-06952	America/Eirunepe	W Amazonas	-04:00	-
-0958-06748	America/Rio_Branco	Acre	-04:00

 */


        //// Multiple:
        // ARGENTINA:
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Buenos_Aires",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Cordoba",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Salta",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Jujuy",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Tucuman",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Catamarca",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/La_Rioja",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/San_Juan",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Mendoza",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/San_Luis",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Rio_Gallegos",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AR","America/Argentina/Ushuaia",list,i);

        //// Multiple:
        // AUSTRALIA:
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Adelaide",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Brisbane",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Broken_Hill",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Darwin",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Hobart",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Lindeman",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Lord_Howe",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Melbourne",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Perth",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AS","Australia/Sydney",list,i);



        // Asia/Calcutta is same as IST (Indian Standard Time)
        ifCCeqCCaddZtoLISTandINC(countryCode,"IN","Asia/Calcutta",list,i);
        // Sri LAnka:
        ifCCeqCCaddZtoLISTandINC(countryCode,"CE","Asia/Calcutta",list,i);
        // Bangladesh:
        ifCCeqCCaddZtoLISTandINC(countryCode,"BG","Asia/Dhaka",list,i);


        // MISC:
        ifCCeqCCaddZtoLISTandINC(countryCode,"MO","Africa/Casablanca",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"TS","Africa/Tunis",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"LY","Africa/Tripoli",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SF","Africa/Johannesburg",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"NI","Africa/Lagos",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"TZ","Africa/Dar_es_Salaam",list,i);


        ifCCeqCCaddZtoLISTandINC(countryCode,"SY","Asia/Damascus",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"YM","Asia/Aden",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"KU","Asia/Kuwait",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"IR","Asia/Tehran",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"ID","Asia/Jakarta",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"HK","Asia/Hong_Kong",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CB","Asia/Phnom_Penh",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BA","Asia/Bahrain",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"VM","Asia/Ho_Chi_Minh",list,i);

        ifCCeqCCaddZtoLISTandINC(countryCode,"VE","America/Caracas",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"BL","America/La_Paz",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CU","America/Havana",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"CI","America/Santiago",list,i);

        ifCCeqCCaddZtoLISTandINC(countryCode,"IS","Asia/Jerusalem",list,i);

        ifCCeqCCaddZtoLISTandINC(countryCode,"MX","America/Mexico_City",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"MU","Asia/Muscat",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"PM","America/Panama",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"PA","America/Asuncion",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"RP","Asia/Manila",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"PE","America/Lima",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SN","Asia/Singapore",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SO","Africa/Mogadishu",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SU","Africa/Khartoum",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SV","Arctic/Longyearbyen",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"AE","Asia/Dubai",list,i);
        ifCCeqCCaddZtoLISTandINC(countryCode,"SA","Asia/Riyadh",list,i);


        /*

MX - MEXICO		America/Mexico_City
MU - OMAN		Asia/Muscat

PM - PANAMA		America/Panama
PA - PARAGUAY	America/Asuncion
RP - PHILIPPINES	Asia/Manila
??QATAR
PE - PERU		America/Lima
SN - SINGAPORE	Asia/Singapore
SO - SOMALIA		Africa/Mogadishu
SU - SUDAN		Africa/Khartoum
SV - SVALBARD	Arctic/Longyearbyen
AE - UNITED ARAB EMIRATES	Asia/Dubai
SA - SAUDI ARABIA	Asia/Riyadh
         */

        return i;
    }
};



/*


  #Russia:
  #Europe/Moscow
  #Europe/Kaliningrad
  #Europe/Samara
  #Am/Dawson_Creek: Canada
  #Am/Thunder_Bay: Canada/Ontario

  #Am/Los_Angeles: California (CA) (Western)

  #Am/Boise: Idaho (ID) (mountain (left))
  #Am/Phoenix: Arizona (AZ) (Mountain (left))
  #Am/Denver: Colorado (CO) (Mountain (right))

  #Am/Chicago: ILlinois (IL)(Central)

  #Am/Louisville: Kentucky (KY) (Eastern (very left))
  #Am/New_York: New York   (NY) (Eastern (very east))
  #Am/Detroit: Michigan (MI)(Eastern (very left))

  #USA:
  #WA,OR,NV,CA - Pacific time:  "America/Los_Angeles (CA)" ??
  #AZ,CO,ID,MT,NM,UT,WY(Wyoming?MISSING!) - Montain time
  #ND,SD,NE,KS,OK,TX,,MN,IA,MO,AR,LA,,WI,IL,IN,TN,MS,AL - Central time
  #MI,OH,KY,GA,,PA,MD,WV,VA,NC,SC,FL,,NY,NJ,DE,,ME,MA,NH,VT,RI,CT - Eastern
  # Alaska: Alaska-time# Hawaii: Hawaii-time

DefaultZonesUsa = {
    'WA' => 'America/Los_Angeles',
    'OR' => 'America/Los_Angeles',
    'NV' => 'America/Los_Angeles',
    'CA' => 'America/Los_Angeles', #CA - Western
    'AZ' => 'America/Phoenix', #AZ - Mountain
    'ID' => 'America/Boise',
    'UT' => 'America/Boise',
    'MT' => 'America/Boise', #ID - Mountain
    'WY' => 'America/Denver',
    'CO' => 'America/Denver',
    'NM' => 'America/Denver', #CO - Mountain
    'ND' => 'America/Chicago',
    'SD' => 'America/Chicago',
    'NE' => 'America/Chicago',
    'KS' => 'America/Chicago',
    'OK' => 'America/Chicago',
    'TX' => 'America/Chicago',
    'MN' => 'America/Chicago',
    'IA' => 'America/Chicago',
    'MO' => 'America/Chicago',
    'AR' => 'America/Chicago',
    'LA' => 'America/Chicago',
    'WI' => 'America/Chicago',
    'IL' => 'America/Chicago',
    'TN' => 'America/Chicago',
    'MS' => 'America/Chicago',
    'AL' => 'America/Chicago', #IL - Central
    'IN' => 'America/Indiana/Indianapolis', #IN - central(summer)/eastern(winter)
    'MI' => 'America/Detroit',
    'OH' => 'America/Detroit', #MI - Eastern
    'KY' => 'America/Louisville',
    'GA' => 'America/Louisville',
    'FL' => 'America/Louisville',
    'WV' => 'America/Louisville',
    'VA' => 'America/Louisville',
    'NC' => 'America/Louisville',
    'SC' => 'America/Louisville', #KY - Eastern
    'NY' => 'America/New_York',
    'PA' => 'America/New_York',
    'MD' => 'America/New_York',
    'DE' => 'America/New_York',
    'NJ' => 'America/New_York',
    'CT' => 'America/New_York',
    'RI' => 'America/New_York',
    'VT' => 'America/New_York',
    'MA' => 'America/New_York',
    'NH' => 'America/New_York',
    'ME' => 'America/New_York',
    'DC' => 'America/New_York', #NY
    'HI' => 'Pacific/Honolulu'   #HI - Hawaii
  }


  DefaultZones = {
    'AL' => 'Europe/Tirane',      #Albania
    'AN' => 'Europe/Andorra',     #Andorra
    'AU' => 'Europe/Vienna',      #Austria
    'BE' => 'Europe/Brussels',    #Belgium
    'BK' => 'Europe/Sarajevo',    #Bosnia and Herzegovina
    'BO' => 'Europe/Minsk',       #Belarus
    'BU' => 'Europe/Sofia',       #Bulgaria
    'CY' => 'Europe/Nicosia',     #Cyprus
    'DA' => 'Europe/Copenhagen',  #Denmark
    'EI' => 'Europe/Dublin',      #Ireland
    'EN' => 'Europe/Tallinn',     #Estonia
    'EZ' => 'Europe/Prague',      #Check Rebublic
    'FI' => 'Europe/Helsinki',    #Finland
    'FR' => 'Europe/Paris',       #France
    'GI' => 'Europe/Gibraltar',   #Gibraltar
    'GR' => 'Europe/Athens',      #Greece
    'GM' => 'Europe/Berlin',      #Germany
    'HR' => 'Europe/Zagreb',      #Croatia
    'HU' => 'Europe/Budapest',    #Hungary
    'IC' => 'Atlantic/Reykjavik', #Iceland
    'IT' => 'Europe/Rome',        #Italy
    'LG' => 'Europe/Riga',        #Latvia
    'LH' => 'Europe/Vilnius',     #Lithuania
    'LO' => 'Europe/Bratislava',  #Slovakia
    'LS' => 'Europe/Vaduz',       #Liechtenstein
    'LU' => 'Europe/Luxembourg',  #Luxembourg
    'MD' => 'Europe/Chisinau',    #Moldova
    'MK' => 'Europe/Skopje',      #Macedonia
    'MN' => 'Europe/Monaco',      #Monaco
    'MT' => 'Europe/Malta',       #Malta
    'NL' => 'Europe/Amsterdam',   #Netherlands
    'NO' => 'Europe/Oslo',        #Norway
    'PO' => 'Europe/Lisbon',      #Portugal
    'PL' => 'Europe/Warsaw',      #Poland
    'RO' => 'Europe/Bucharest',   #Romania
    'SI' => 'Europe/Ljubljana',   #Slovenia
    'SP' => 'Europe/Madrid',      #Spain
    'SW' => 'Europe/Stockholm',   #Sweden
    'SZ' => 'Europe/Zurich',      #Switzerland
    'TU' => 'Europe/Istanbul',      #Turkey
    'UK' => 'Europe/London',      #United Kingdom

    'UP' => ['Europe/Simferopol', #Ukraine
      'Europe/Uzhgorod',
      'Europe/Zaporozhy'],
    'RS' => ['Europe/Moscow',      #Russia
      'Europe/Kaliningrad',
      'Asia/Irkutsk',
      'Asia/Krasnoyarsk',
      'Asia/Sakhalin',
      'Asia/Vladivostok',
      'Asia/Yakutsk'],

    'VT' => 'Europe/Vatican',     #Vatican City
    'YI' => 'Europe/Belgrade',    #Serbia and Montenegro

    'CA' => ['America/Whitehorse', #Canada
      'America/Vancouver',
      'America/Yellowknife',
      'America/Edmonton',
      'America/Regine',
      'America/Winnipeg',
      'America/Thunder_Bay',
      'America/Montreal',
      'America/Halifax',
      'America/St_Johns'],

    'IZ' => 'Asia/Baghdad',       #Iraq
    'JA' => 'Asia/Tokyo',         #Japan
    'KS' => 'Asia/Seoul',         #South Korea
    'PK' => 'Asia/Karachi',       #Pakistan

    'EG' => 'Africa/Cairo'       #Egypt
  }





*/



#endif // TIMEZONEDEFAULTS_H
