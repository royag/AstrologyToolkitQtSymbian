

module Astrology
  
  class AbstractGeodataReader
    class GeoDataPlace
      attr_accessor :place_name
      attr_accessor :latitude
      attr_accessor :longitude
      attr_accessor :country_code
      attr_accessor :place_no       # record number in file for country_code starting at 0
      def initialize(place_name, latitude, longitude)
        @place_name = place_name
        @latitude = latitude
        @longitude = longitude
      end
      def self.new_from_string(str)
        m = str.match('(.*) \((.*) (.*)\)')
        place_name = m[1]
        la = m[2]
        lo = m[3]
        long = (lo[0,2].to_f + lo[3,2].to_f / 100) * (lo[2,1] == 'E' ? 1 : -1)
        lat = (la[0,2].to_f + la[3,2].to_f / 100) * (la[2,1] == 'N' ? 1 : -1)
        self.new(place_name, lat, long)
      end
      def to_s
        @place_name + ' (' + GeoDataPlace.lat_long_to_s(@latitude, @longitude) + ')'
      end
      def self.lat_long_to_s(lati, longi)
        lati.abs.floor.to_s.rjust(2,'0') +
          (lati < 0 ? 'S' : 'N') +
          (lati.abs*100 - lati.abs.floor*100).floor.to_s.rjust(2,'0') +
          ' ' +
          longi.abs.floor.to_s.rjust(2,'0') +
          (longi < 0 ? 'W' : 'E') +
          (longi.abs*100 - longi.abs.floor*100).floor.to_s.rjust(2,'0')
      end
    end
  end
  
    
  class GeodataReader < AbstractGeodataReader
    def self.load_geo_data(country_code, geo_data_path = GeoDataPath, fname = nil)
      ret = []
      fname ||= geo_data_path + '/' + country_code.downcase + '.geo3s'
      File.open(fname, 'rb') do |f|
        data = nil
        count = 0
        while (data = f.read(Geo3sRecLength)) do
          l = data.unpack(Geo3sPackFormat)
          gdp = GeoDataPlace.new(l[0], l[1], l[2])
          gdp.country_code = country_code
          gdp.place_no = count
          ret << gdp
          count += 1
        end
      end
      ret
    end
    
    def self.load_single_rec(country_code, place_no, geo_data_path = GeoDataPath, fname = nil)
      fname ||= geo_data_path + '/' + country_code.downcase + '.geo3s'
      File.open(fname, 'rb') do |f|
        f.seek(place_no * Geo3sRecLength)
        l = f.read(Geo3sRecLength).unpack(Geo3sPackFormat)
        gdp = GeoDataPlace.new(l[0], l[1], l[2])
        gdp.country_code = country_code
        gdp.place_no = place_no
        gdp
      end
    end
  
    GeoDataPath = File.dirname(__FILE__) + '/geodata3s'
    Geo3sPackFormat = 'Z20ff'
    Geo3sRecLength = 28
  
  end # GeodataReader

  CountryCodes = [
    ['AF', 'AFGHANISTAN', 1] ,
    ['AL', 'ALBANIA', 1] ,
    ['AG', 'ALGERIA', 1] ,
    ['AN', 'ANDORRA', 1] ,
    ['AO', 'ANGOLA', 1] ,
    ['AV', 'ANGUILLA', 1] ,
    ['AC', 'ANTIGUA AND BARBUDA', 1] ,
    ['AR', 'ARGENTINA', 1] ,
    ['AM', 'ARMENIA', 1] ,
    ['AA', 'ARUBA', 1] ,
    ['AT', 'ASHMORE AND CARTIER ISL.', 1] ,
    ['AS', 'AUSTRALIA', 1] ,
    ['AU', 'AUSTRIA', 1] ,
    ['AJ', 'AZERBAIJAN', 1] ,
    ['BF', 'BAHAMAS, THE', 1] ,
    ['BA', 'BAHRAIN', 1] ,
    ['BG', 'BANGLADESH', 1] ,
    ['BB', 'BARBADOS', 1] ,
    ['BS', 'BASSAS DA INDIA', 1] ,
    ['BO', 'BELARUS', 1] ,
    ['BE', 'BELGIUM', 1] ,
    ['BH', 'BELIZE', 1] ,
    ['BN', 'BENIN', 1] ,
    ['BD', 'BERMUDA', 1] ,
    ['BT', 'BHUTAN', 1] ,
    ['BL', 'BOLIVIA', 1] ,
    ['BK', 'BOSNIA AND HERZEGOVINA', 1] ,
    ['BC', 'BOTSWANA', 1] ,
    ['BV', 'BOUVET ISLAND', 1] ,
    ['BR', 'BRAZIL', 1] ,
    ['IO', 'BRITISH INDIAN OCEAN TERR.', 1] ,
    ['VI', 'BRITISH VIRGIN ISLANDS', 1] ,
    ['BX', 'BRUNEI', 1] ,
    ['BU', 'BULGARIA', 1] ,
    ['UV', 'BURKINA FASO', 1] ,
    ['BM', 'BURMA', 1] ,
    ['BY', 'BURUNDI', 1] ,
    ['CB', 'CAMBODIA', 1] ,
    ['CM', 'CAMEROON', 1] ,
    ['CA', 'CANADA', 1] ,
    ['CV', 'CAPE VERDE', 1] ,
    ['CJ', 'CAYMAN ISLANDS', 1] ,
    ['CT', 'CENTRAL AFRICAN REPUBLIC', 1] ,
    ['CD', 'CHAD', 1] ,
    ['CI', 'CHILE', 1] ,
    ['CH', 'CHINA', 1] ,
    ['KT', 'CHRISTMAS ISLAND', 1] ,
    ['IP', 'CLIPPERTON ISLAND', 1] ,
    ['CK', 'COCOS (KEELING) ISLANDS', 1] ,
    ['CO', 'COLOMBIA', 1] ,
    ['CN', 'COMOROS', 1] ,
    ['CF', 'CONGO', 1] ,
    ['CG', 'CONGO, DEM. REP. OF THE', 1] ,
    ['CW', 'COOK ISLANDS', 1] ,
    ['CR', 'CORAL SEA ISLANDS', 1] ,
    ['CS', 'COSTA RICA', 1] ,
    ['IV', "COTE D'IVOIRE", 1] ,
    ['HR', 'CROATIA', 1] ,
    ['CU', 'CUBA', 1] ,
    ['CY', 'CYPRUS', 1] ,
    ['EZ', 'CZECH REPUBLIC', 1] ,
    ['DA', 'DENMARK', 1] ,
    ['DJ', 'DJIBOUTI', 1] ,
    ['DO', 'DOMINICA', 1] ,
    ['DR', 'DOMINICAN REPUBLIC', 1] ,
    ['TT', 'EAST TIMOR', 1] ,
    ['EC', 'ECUADOR', 1] ,
    ['EG', 'EGYPT', 1] ,
    ['ES', 'EL SALVADOR', 1] ,
    ['EK', 'EQUATORIAL GUINEA', 1] ,
    ['ER', 'ERITREA', 1] ,
    ['EN', 'ESTONIA', 1] ,
    ['ET', 'ETHIOPIA', 1] ,
    ['EU', 'EUROPA ISLAND', 1] ,
    ['FK', 'FALKLAND ISLANDS', 1] ,
    ['FO', 'FAROE ISLANDS', 1] ,
    ['FJ', 'FIJI', 1] ,
    ['FI', 'FINLAND', 1] ,
    ['FR', 'FRANCE', 1] ,
    ['FG', 'FRENCH GUIANA', 1] ,
    ['FP', 'FRENCH POLYNESIA', 1] ,
    #['FS', 'FRENCH SOUTHERN AND ANTARCTIC LANDS', 1] ,
    ['GB', 'GABON', 1] ,
    ['GA', 'GAMBIA, THE', 1] ,
    ['GZ', 'GAZA STRIP', 1] ,
    ['GG', 'GEORGIA', 1] ,
    ['GM', 'GERMANY', 1] ,
    ['GH', 'GHANA', 1] ,
    ['GI', 'GIBRALTAR', 1] ,
    ['GO', 'GLORIOSO ISLANDS', 1] ,
    ['GR', 'GREECE', 1] ,
    ['GL', 'GREENLAND', 1] ,
    ['GJ', 'GRENADA', 1] ,
    ['GP', 'GUADELOUPE', 1] ,
    ['GT', 'GUATEMALA', 1] ,
    ['GK', 'GUERNSEY', 1] ,
    ['GV', 'GUINEA', 1] ,
    ['PU', 'GUINEA-BISSAU', 1] ,
    ['GY', 'GUYANA', 1] ,
    ['HA', 'HAITI', 1] ,
    ['HM', 'HEARD ISL. AND MCDONALD ISL.', 1] ,
    ['HO', 'HONDURAS', 1] ,
    ['HK', 'HONG KONG', 1] ,
    ['HU', 'HUNGARY', 1] ,
    ['IC', 'ICELAND', 1] ,
    ['IN', 'INDIA', 1] ,
    ['ID', 'INDONESIA', 1] ,
    ['IR', 'IRAN', 1] ,
    ['IZ', 'IRAQ', 1] ,
    ['EI', 'IRELAND', 1] ,
    ['IM', 'ISLE OF MAN', 1] ,
    ['IS', 'ISRAEL', 1] ,
    ['IT', 'ITALY', 1] ,
    ['JM', 'JAMAICA', 1] ,
    ['JN', 'JAN MAYEN', 1] ,
    ['JA', 'JAPAN', 1] ,
    ['JE', 'JERSEY', 1] ,
    ['JO', 'JORDAN', 1] ,
    ['JU', 'JUAN DE NOVA ISLAND', 1] ,
    ['KZ', 'KAZAKHSTAN', 1] ,
    ['KE', 'KENYA', 1] ,
    ['KR', 'KIRIBATI', 1] ,
    ['KU', 'KUWAIT', 1] ,
    ['KG', 'KYRGYZSTAN', 1] ,
    ['LA', 'LAOS', 1] ,
    ['LG', 'LATVIA', 1] ,
    ['LE', 'LEBANON', 1] ,
    ['LT', 'LESOTHO', 1] ,
    ['LI', 'LIBERIA', 1] ,
    ['LY', 'LIBYA', 1] ,
    ['LS', 'LIECHTENSTEIN', 1] ,
    ['LH', 'LITHUANIA', 1] ,
    ['LU', 'LUXEMBOURG', 1] ,
    ['MC', 'MACAU', 1] ,
    ['MK', 'MACEDONIA, T.F.Y.R.O.', 1] ,
    ['MA', 'MADAGASCAR', 1] ,
    ['MI', 'MALAWI', 1] ,
    ['MY', 'MALAYSIA', 1] ,
    ['MV', 'MALDIVES', 1] ,
    ['ML', 'MALI', 1] ,
    ['MT', 'MALTA', 1] ,
    ['RM', 'MARSHALL ISLANDS', 1] ,
    ['MB', 'MARTINIQUE', 1] ,
    ['MR', 'MAURITANIA', 1] ,
    ['MP', 'MAURITIUS', 1] ,
    ['MF', 'MAYOTTE', 1] ,
    ['MX', 'MEXICO', 1] ,
    ['FM', 'MICRONESIA, F.S.O.', 1] ,
    ['MD', 'MOLDOVA', 1] ,
    ['MN', 'MONACO', 1] ,
    ['MG', 'MONGOLIA', 1] ,
    ['MH', 'MONTSERRAT', 1] ,
    ['MO', 'MOROCCO', 1] ,
    ['MZ', 'MOZAMBIQUE', 1] ,
    ['WA', 'NAMIBIA', 1] ,
    ['NR', 'NAURU', 1] ,
    ['NP', 'NEPAL', 1] ,
    ['NL', 'NETHERLANDS', 1] ,
    ['NT', 'NETHERLANDS ANTILLES', 1] ,
    ['NC', 'NEW CALEDONIA', 1] ,
    ['NZ', 'NEW ZEALAND', 1] ,
    ['NU', 'NICARAGUA', 1] ,
    ['NG', 'NIGER', 1] ,
    ['NI', 'NIGERIA', 1] ,
    ['NE', 'NIUE', 1] ,
    ['NM', "NO MAN'S LAND", 1] ,
    ['NF', 'NORFOLK ISLAND', 1] ,
    ['KN', 'NORTH KOREA', 1] ,
    ['NO', 'NORWAY', 1] ,
    ['OS', 'OCEANS', 1] ,
    ['MU', 'OMAN', 1] ,
    ['PK', 'PAKISTAN', 1] ,
    ['PS', 'PALAU', 1] ,
    ['PM', 'PANAMA', 1] ,
    ['PP', 'PAPUA NEW GUINEA', 1] ,
    ['PF', 'PARACEL ISLANDS', 1] ,
    ['PA', 'PARAGUAY', 1] ,
    ['PE', 'PERU', 1] ,
    ['RP', 'PHILIPPINES', 1] ,
    ['PC', 'PITCAIRN ISLANDS', 1] ,
    ['PL', 'POLAND', 1] ,
    ['PO', 'PORTUGAL', 1] ,
    ['QA', 'QATAR', 1] ,
    ['RE', 'REUNION', 1] ,
    ['RO', 'ROMANIA', 1] ,
    ['RS', 'RUSSIA', 1] ,
    ['RW', 'RWANDA', 1] ,
    ['SH', 'ST HELENA', 1] ,
    ['SC', 'ST KITTS AND NEVIS', 1] ,
    ['ST', 'ST LUCIA', 1] ,
    ['SB', 'ST PIERRE AND MIQUELON', 1] ,
    ['VC', 'ST VINCENT AND THE GR.', 1] ,
    ['WS', 'SAMOA', 1] ,
    ['SM', 'SAN MARINO', 1] ,
    ['TP', 'SAO TOME AND PRINCIPE', 1] ,
    ['SA', 'SAUDI ARABIA', 1] ,
    ['SG', 'SENEGAL', 1] ,
    ['YI', 'SERBIA AND MONTENEGRO', 1] ,
    ['SE', 'SEYCHELLES', 1] ,
    ['SL', 'SIERRA LEONE', 1] ,
    ['SN', 'SINGAPORE', 1] ,
    ['LO', 'SLOVAKIA', 1] ,
    ['SI', 'SLOVENIA', 1] ,
    ['BP', 'SOLOMON ISLANDS', 1] ,
    ['SO', 'SOMALIA', 1] ,
    ['SF', 'SOUTH AFRICA', 1] ,
    ['SX', 'SOUTH GEORGIA AND S.SW.ISL.', 1] ,
    ['KS', 'SOUTH KOREA', 1] ,
    ['SP', 'SPAIN', 1] ,
    ['PG', 'SPRATLY ISLANDS', 1] ,
    ['CE', 'SRI LANKA', 1] ,
    ['SU', 'SUDAN', 1] ,
    ['NS', 'SURINAME', 1] ,
    ['SV', 'SVALBARD', 1] ,
    ['WZ', 'SWAZILAND', 1] ,
    ['SW', 'SWEDEN', 1] ,
    ['SZ', 'SWITZERLAND', 1] ,
    ['SY', 'SYRIA', 1] ,
    ['TW', 'TAIWAN', 1] ,
    ['TI', 'TAJIKISTAN', 1] ,
    ['TZ', 'TANZANIA', 1] ,
    ['TH', 'THAILAND', 1] ,
    ['TO', 'TOGO', 1] ,
    ['TL', 'TOKELAU', 1] ,
    ['TN', 'TONGA', 1] ,
    ['TD', 'TRINIDAD AND TOBAGO', 1] ,
    ['TE', 'TROMELIN ISLAND', 1] ,
    ['TS', 'TUNISIA', 1] ,
    ['TU', 'TURKEY', 1] ,
    ['TX', 'TURKMENISTAN', 1] ,
    ['TK', 'TURKS AND CAICOS ISLANDS', 1] ,
    ['TV', 'TUVALU', 1] ,
    ['UG', 'UGANDA', 1] ,
    ['UP', 'UKRAINE', 1] ,
    ['UF', 'UNDERSEA FEATURES', 1] ,
    ['AE', 'UNITED ARAB EMIRATES', 1] ,
    ['UK', 'UNITED KINGDOM', 1] ,
    ['US', 'UNITED STATES', 0] ,
    ['UY', 'URUGUAY', 1] ,
    ['UZ', 'UZBEKISTAN', 1] ,
    ['NH', 'VANUATU', 1] ,
    ['VT', 'VATICAN CITY', 1] ,
    ['VE', 'VENEZUELA', 1] ,
    ['VM', 'VIETNAM', 1] ,
    ['VQ', 'VIRGIN ISLANDS', 0] ,
    ['WF', 'WALLIS AND FUTUNA', 1] ,
    ['WE', 'WEST BANK', 1] ,
    ['WI', 'WESTERN SAHARA', 1] ,
    ['YM', 'YEMEN', 1] ,
    ['ZA', 'ZAMBIA', 1] ,
    ['ZI', 'ZIMBABWE', 1]
  ]

  UsStateCodes = [
    ['USAL', 'ALABAMA', 1],
    ['USAK', 'ALASKA', 1],
    ['USAR', 'ARKANSAS', 1],
    ['USAS', 'AMERICAN SAMOA', 0],
    ['USAZ', 'ARIZONA', 1],
    ['USCA', 'CALIFORNIA', 1],
    ['USCO', 'COLORADO', 1],
    ['USCT', 'CONNECTICUT', 1],
    ['USDC', 'DISTRICT OF COLUMBIA', 1],
    ['USDE', 'DELAWARE', 1],
    ['USFL', 'FLORIDA', 1],
    ['USFM', 'FED. ST. OF MICRONESIA', 0],
    ['USGA', 'GEORGIA', 1],
    ['USGU', 'GUAM', 0],
    ['USHI', 'HAWAII', 1],
    ['USIA', 'IOWA', 1],
    ['USID', 'IDAHO', 1],
    ['USIL', 'ILLINOIS', 1],
    ['USIN', 'INDIANA', 1],
    ['USKS', 'KANSAS', 1],
    ['USKY', 'KENTUCKY', 1],
    ['USLA', 'LOUISIANA', 1],
    ['USMA', 'MASSACHUSETTS', 1],
    ['USMD', 'MARYLAND', 1],
    ['USME', 'MAINE', 1],
    ['USMH', 'MARSHALL ISLANDS', 0],
    ['USMI', 'MICHIGAN', 1],
    ['USMN', 'MINNESOTA', 1],
    ['USMO', 'MISSOURI', 1],
    ['USMP', 'NORTHERN MARIANA ISL.', 0],
    ['USMS', 'MISSISSIPPI', 1],
    ['USMT', 'MONTANA', 1],
    ['USNC', 'NORTH CAROLINA', 1],
    ['USND', 'NORTH DAKOTA', 1],
    ['USNE', 'NEBRASKA', 1],
    ['USNH', 'NEW HAMPSHIRE', 1],
    ['USNJ', 'NEW JERSEY', 1],
    ['USNM', 'NEW MEXICO', 1],
    ['USNV', 'NEVADA', 1],
    ['USNY', 'NEW YORK', 1],
    ['USOH', 'OHIO', 1],
    ['USOK', 'OKLAHOMA', 1],
    ['USOR', 'OREGON', 1],
    ['USPA', 'PENNSYLVANIA', 1],
    ['USPR', 'PUERTO RICO', 1],
    ['USPW', 'PALAU', 0],
    ['USRI', 'RHODE ISLAND', 1],
    ['USSC', 'SOUTH CAROLINA', 1],
    ['USSD', 'SOUTH DAKOTA', 1],
    ['USTN', 'TENNESSEE', 1],
    ['USTX', 'TEXAS', 1],
    ['USUT', 'UTAH', 1],
    ['USVA', 'VIRGINIA', 1],
    ['USVI', 'VIRGIN ISLANDS', 0],
    ['USVT', 'VERMONT', 1],
    ['USWA', 'WASHINGTON', 1],
    ['USWI', 'WISCONSIN', 1],
    ['USWV', 'WEST VIRGINIA', 1]
  ]  
  
  
  AllCountryCodes = [
    ['AFGHANISTAN', 'AF'], #1
    ['ALBANIA', 'AL'], #1
    ['ALGERIA', 'AG'], #1
    ['ANDORRA', 'AN'], #1
    ['ANGOLA', 'AO'], #1
    ['ANGUILLA', 'AV'], #1
    ['ANTIGUA AND BARBUDA', 'AC'], #1
    ['ARGENTINA', 'AR'], #1
    ['ARMENIA', 'AM'], #1
    ['ARUBA', 'AA'], #1
    #['ASHMORE AND CART. ISL.', 'AT'], #1
    ['AUSTRALIA', 'AS'], #1
    ['AUSTRIA', 'AU'], #1
    ['AZERBAIJAN', 'AJ'], #1
    ['BAHAMAS, THE', 'BF'], #1
    ['BAHRAIN', 'BA'], #1
    ['BANGLADESH', 'BG'], #1
    ['BARBADOS', 'BB'], #1
    #['BASSAS DA INDIA', 'BS'], #1
    ['BELARUS', 'BO'], #1
    ['BELGIUM', 'BE'], #1
    ['BELIZE', 'BH'], #1
    ['BENIN', 'BN'], #1
    ['BERMUDA', 'BD'], #1
    #['BHUTAN', 'BT'], #1
    ['BOLIVIA', 'BL'], #1
    ['BOSNIA AND HERZEGOVINA', 'BK'], #1
    ['BOTSWANA', 'BC'], #1
    #['BOUVET ISLAND', 'BV'], #1
    ['BRAZIL', 'BR'], #1
    #['BRITISH INDIAN OC. TERR.', 'IO'], #1
    ['BRITISH VIRGIN ISLANDS', 'VI'], #1
    ['BRUNEI', 'BX'], #1
    ['BULGARIA', 'BU'], #1
    ['BURKINA FASO', 'UV'], #1
    ['BURMA', 'BM'], #1
    ['BURUNDI', 'BY'], #1
    ['CAMBODIA', 'CB'], #1
    ['CAMEROON', 'CM'], #1
    ['CANADA', 'CA'], #1
    ['CAPE VERDE', 'CV'], #1
    ['CAYMAN ISLANDS', 'CJ'], #1
    ['CENTRAL AFRICAN REP.', 'CT'], #1
    ['CHAD', 'CD'], #1
    ['CHILE', 'CI'], #1
    ['CHINA', 'CH'], #1
    ['CHRISTMAS ISLAND', 'KT'], #1
    #['CLIPPERTON ISLAND', 'IP'], #1
    #['COCOS (KEELING) ISLANDS', 'CK'], #1
    ['COLOMBIA', 'CO'], #1
    ['COMOROS', 'CN'], #1
    ['CONGO', 'CF'], #1
    ['CONGO, D.R.O.T.', 'CG'], #1
    ['COOK ISLANDS', 'CW'], #1
    #['CORAL SEA ISLANDS', 'CR'], #1
    ['COSTA RICA', 'CS'], #1
    ['COTE D IVOIRE', 'IV'], #1
    ['CROATIA', 'HR'], #1
    ['CUBA', 'CU'], #1
    ['CYPRUS', 'CY'], #1
    ['CZECH REPUBLIC', 'EZ'], #1
    ['DENMARK', 'DA'], #1
    ['DJIBOUTI', 'DJ'], #1
    ['DOMINICA', 'DO'], #1
    ['DOMINICAN REPUBLIC', 'DR'], #1
    ['EAST TIMOR', 'TT'], #1
    ['ECUADOR', 'EC'], #1
    ['EGYPT', 'EG'], #1
    ['EL SALVADOR', 'ES'], #1
    ['EQUATORIAL GUINEA', 'EK'], #1
    ['ERITREA', 'ER'], #1
    ['ESTONIA', 'EN'], #1
    ['ETHIOPIA', 'ET'], #1
    #['EUROPA ISLAND', 'EU'], #1
    ['FALKLAND ISLANDS', 'FK'], #1
    ['FAROE ISLANDS', 'FO'], #1
    ['FIJI', 'FJ'], #1
    ['FINLAND', 'FI'], #1
    ['FRANCE', 'FR'], #1
    ['FRENCH GUIANA', 'FG'], #1
    ['FRENCH POLYNESIA', 'FP'], #1
    #['FRENCH SOUTHERN AND ANTARCTIC LANDS', 'FS'], #1
    ['GABON', 'GB'], #1
    ['GAMBIA, THE', 'GA'], #1
    ['GAZA STRIP', 'GZ'], #1
    ['GEORGIA', 'GG'], #1
    ['GERMANY', 'GM'], #1
    ['GHANA', 'GH'], #1
    ['GIBRALTAR', 'GI'], #1
    #['GLORIOSO ISLANDS', 'GO'], #1
    ['GREECE', 'GR'], #1
    ['GREENLAND', 'GL'], #1
    ['GRENADA', 'GJ'], #1
    ['GUADELOUPE', 'GP'], #1
    ['GUATEMALA', 'GT'], #1
    ['GUERNSEY', 'GK'], #1
    ['GUINEA', 'GV'], #1
    ['GUINEA-BISSAU', 'PU'], #1
    ['GUYANA', 'GY'], #1
    ['HAITI', 'HA'], #1
    #['HEARD ISL. AND MCD.ISL.', 'HM'], #1
    ['HONDURAS', 'HO'], #1
    ['HONG KONG', 'HK'], #1
    ['HUNGARY', 'HU'], #1
    ['ICELAND', 'IC'], #1
    ['INDIA', 'IN'], #1
    ['INDONESIA', 'ID'], #1
    ['IRAN', 'IR'], #1
    ['IRAQ', 'IZ'], #1
    ['IRELAND', 'EI'], #1
    ['ISLE OF MAN', 'IM'], #1
    ['ISRAEL', 'IS'], #1  ###### MISSING
    ['ITALY', 'IT'], #1
    ['JAMAICA', 'JM'], #1
    #['JAN MAYEN', 'JN'], #1
    ['JAPAN', 'JA'], #1
    ['JERSEY', 'JE'], #1
    ['JORDAN', 'JO'], #1
    #['JUAN DE NOVA ISLAND', 'JU'], #1
    ['KAZAKHSTAN', 'KZ'], #1
    ['KENYA', 'KE'], #1
    ['KIRIBATI', 'KR'], #1
    ['KUWAIT', 'KU'], #1
    ['KYRGYZSTAN', 'KG'], #1
    ['LAOS', 'LA'], #1
    ['LATVIA', 'LG'], #1
    ['LEBANON', 'LE'], #1
    ['LESOTHO', 'LT'], #1
    ['LIBERIA', 'LI'], #1
    ['LIBYA', 'LY'], #1
    ['LIECHTENSTEIN', 'LS'], #1
    ['LITHUANIA', 'LH'], #1
    ['LUXEMBOURG', 'LU'], #1
    ['MACAU', 'MC'], #1
    ['MACEDONIA, T.F.Y.R.O.', 'MK'], #1
    ['MADAGASCAR', 'MA'], #1
    ['MALAWI', 'MI'], #1
    ['MALAYSIA', 'MY'], #1
    ['MALDIVES', 'MV'], #1
    ['MALI', 'ML'], #1
    ['MALTA', 'MT'], #1
    ['MARSHALL ISLANDS', 'RM'], #1
    ['MARTINIQUE', 'MB'], #1
    ['MAURITANIA', 'MR'], #1
    ['MAURITIUS', 'MP'], #1
    ['MAYOTTE', 'MF'], #1
    ['MEXICO', 'MX'], #1
    ['MICRONESIA, FED.ST.OF', 'FM'], #1
    ['MOLDOVA', 'MD'], #1
    ['MONACO', 'MN'], #1
    ['MONGOLIA', 'MG'], #1
    ['MONTSERRAT', 'MH'], #1
    ['MOROCCO', 'MO'], #1
    ['MOZAMBIQUE', 'MZ'], #1
    ['NAMIBIA', 'WA'], #1
    #['NAURU', 'NR'], #1
    ['NEPAL', 'NP'], #1
    ['NETHERLANDS', 'NL'], #1
    #['NETHERLANDS ANTILLES', 'NT'], #1
    ['NEW CALEDONIA', 'NC'], #1
    ['NEW ZEALAND', 'NZ'], #1
    ['NICARAGUA', 'NU'], #1
    ['NIGER', 'NG'], #1
    ['NIGERIA', 'NI'], #1
    ['NIUE', 'NE'], #1
    #'['NO MANS LAND', 'NM'], #1
    #['NORFOLK ISLAND', 'NF'], #1
    ['NORTH KOREA', 'KN'], #1
    ['NORWAY', 'NO'], #1
    #''['OCEANS', 'OS'], #1
    ['OMAN', 'MU'], #1
    ['PAKISTAN', 'PK'], #1
    ['PALAU', 'PS'], #1
    ['PANAMA', 'PM'], #1
    ['PAPUA NEW GUINEA', 'PP'], #1
    #['PARACEL ISLANDS', 'PF'], #1
    ['PARAGUAY', 'PA'], #1
    ['PERU', 'PE'], #1
    ['PHILIPPINES', 'RP'], #1
    ['PITCAIRN ISLANDS', 'PC'], #1
    ['POLAND', 'PL'], #1
    ['PORTUGAL', 'PO'], #1
    ['QATAR', 'QA'], #1
    ['REUNION', 'RE'], #1
    ['ROMANIA', 'RO'], #1
    ['RUSSIA', 'RS'], #1
    ['RWANDA', 'RW'], #1
    ['ST HELENA', 'SH'], #1
    ['ST KITTS AND NEVIS', 'SC'], #1
    ['ST LUCIA', 'ST'], #1
    ['ST PIERRE AND MIQUELON', 'SB'], #1
    ['ST VINCENT AND THE GR.', 'VC'], #1
    ['SAMOA', 'WS'], #1
    ['SAN MARINO', 'SM'], #1
    ['SAO TOME AND PRINCIPE', 'TP'], #1
    ['SAUDI ARABIA', 'SA'], #1
    ['SENEGAL', 'SG'], #1
    ['SERBIA AND MONTENEGRO', 'YI'], #1
    ['SEYCHELLES', 'SE'], #1
    ['SIERRA LEONE', 'SL'], #1
    ['SINGAPORE', 'SN'], #1
    ['SLOVAKIA', 'LO'], #1
    ['SLOVENIA', 'SI'], #1
    ['SOLOMON ISLANDS', 'BP'], #1
    ['SOMALIA', 'SO'], #1
    ['SOUTH AFRICA', 'SF'], #1
    #['SOUTH GEORGIA T.S.SW.ISL.', 'SX'], #1
    ['SOUTH KOREA', 'KS'], #1
    ['SPAIN', 'SP'], #1
    #['SPRATLY ISLANDS', 'PG'], #1
    ['SRI LANKA', 'CE'], #1
    ['SUDAN', 'SU'], #1
    ['SURINAME', 'NS'], #1
    ['SVALBARD', 'SV'], #1
    ['SWAZILAND', 'WZ'], #1
    ['SWEDEN', 'SW'], #1
    ['SWITZERLAND', 'SZ'], #1
    ['SYRIA', 'SY'], #1
    ['TAIWAN', 'TW'], #1
    ['TAJIKISTAN', 'TI'], #1
    ['TANZANIA', 'TZ'], #1
    ['THAILAND', 'TH'], #1
    ['TOGO', 'TO'], #1
    #['TOKELAU', 'TL'], #1
    ['TONGA', 'TN'], #1
    ['TRINIDAD AND TOBAGO', 'TD'], #1
    #['TROMELIN ISLAND', 'TE'], #1
    ['TUNISIA', 'TS'], #1
    ['TURKEY', 'TU'], #1
    ['TURKMENISTAN', 'TX'], #1
    ['TURKS AND CAICOS ISLANDS', 'TK'], #1
    ['TUVALU', 'TV'], #1
    ['UGANDA', 'UG'], #1
    ['UKRAINE', 'UP'], #1
    #['UNDERSEA FEATURES', 'UF'], #1
    ['UNITED ARAB EMIRATES', 'AE'], #1
    ['UNITED KINGDOM', 'UK'], #1
    #['UNITED STATES', 'US'], #0
    ['URUGUAY', 'UY'], #1
    ['USA/ALABAMA', 'USAL'], #1
    ['USA/ALASKA', 'USAK'], #1
    ['USA/ARKANSAS', 'USAR'], #1
    #['USA/AMERICAN SAMOA', 'USAS'], #0
    ['USA/ARIZONA', 'USAZ'], #1
    ['USA/CALIFORNIA', 'USCA'], #1
    ['USA/COLORADO', 'USCO'], #1
    ['USA/CONNECTICUT', 'USCT'], #1
    ['USA/DISTRICT OF COLUMBIA', 'USDC'], #1
    ['USA/DELAWARE', 'USDE'], #1
    ['USA/FLORIDA', 'USFL'], #1
    #['USA/FED.ST. OF MICRONESIA', 'USFM'], #0
    ['USA/GEORGIA', 'USGA'], #1
    #['USA/GUAM', 'USGU'], #0
    ['USA/HAWAII', 'USHI'], #1
    ['USA/IOWA', 'USIA'], #1
    ['USA/IDAHO', 'USID'], #1
    ['USA/ILLINOIS', 'USIL'], #1
    ['USA/INDIANA', 'USIN'], #1
    ['USA/KANSAS', 'USKS'], #1
    ['USA/KENTUCKY', 'USKY'], #1
    ['USA/LOUISIANA', 'USLA'], #1
    ['USA/MASSACHUSETTS', 'USMA'], #1
    ['USA/MARYLAND', 'USMD'], #1
    ['USA/MAINE', 'USME'], #1
    #['USA/MARSHALL ISLANDS', 'USMH'], #0
    ['USA/MICHIGAN', 'USMI'], #1
    ['USA/MINNESOTA', 'USMN'], #1
    ['USA/MISSOURI', 'USMO'], #1
    #['USA/NORTHERN MARIANA ISL.', 'USMP'], #0
    ['USA/MISSISSIPPI', 'USMS'], #1
    ['USA/MONTANA', 'USMT'], #1
    ['USA/NORTH CAROLINA', 'USNC'], #1
    ['USA/NORTH DAKOTA', 'USND'], #1
    ['USA/NEBRASKA', 'USNE'], #1
    ['USA/NEW HAMPSHIRE', 'USNH'], #1
    ['USA/NEW JERSEY', 'USNJ'], #1
    ['USA/NEW MEXICO', 'USNM'], #1
    ['USA/NEVADA', 'USNV'], #1
    ['USA/NEW YORK', 'USNY'], #1
    ['USA/OHIO', 'USOH'], #1
    ['USA/OKLAHOMA', 'USOK'], #1
    ['USA/OREGON', 'USOR'], #1
    ['USA/PENNSYLVANIA', 'USPA'], #1
    ['USA/PUERTO RICO', 'USPR'], #1
    #['USA/PALAU', 'USPW'], #0
    ['USA/RHODE ISLAND', 'USRI'], #1
    ['USA/SOUTH CAROLINA', 'USSC'], #1
    ['USA/SOUTH DAKOTA', 'USSD'], #1
    ['USA/TENNESSEE', 'USTN'], #1
    ['USA/TEXAS', 'USTX'], #1
    ['USA/UTAH', 'USUT'], #1
    ['USA/VIRGINIA', 'USVA'], #1
    #['USA/VIRGIN ISLANDS', 'USVI'], #0
    ['USA/VERMONT', 'USVT'], #1
    ['USA/WASHINGTON', 'USWA'], #1
    ['USA/WISCONSIN', 'USWI'], #1
    ['USA/WEST VIRGINIA', 'USWV'], #1
    ['UZBEKISTAN', 'UZ'], #1
    ['VANUATU', 'NH'], #1
    #['VATICAN CITY', 'VT'], #1
    ['VENEZUELA', 'VE'], #1
    ['VIETNAM', 'VM'], #1
    #['VIRGIN ISLANDS', 'VQ'], #0
    ['WALLIS AND FUTUNA', 'WF'], #1
    #['WEST BANK', 'WE'], #1
    #['WESTERN SAHARA', 'WI'], #1
    ['YEMEN', 'YM'], #1
    ['ZAMBIA', 'ZA'], #1
    ['ZIMBABWE', 'ZI']
  ]
  
  
  CustomPlaces = {
	"IS" => [
	
AbstractGeodataReader::GeoDataPlace.new("Acre/'Akko",	32.55,	35.04),
AbstractGeodataReader::GeoDataPlace.new("Afula",	32.37,	35.17),
AbstractGeodataReader::GeoDataPlace.new("Akko",	32.55,	35.04),
AbstractGeodataReader::GeoDataPlace.new("Al Quds/Jerusalem",	31.47,	35.10),
AbstractGeodataReader::GeoDataPlace.new("Arad",	31.15,	35.12),
AbstractGeodataReader::GeoDataPlace.new("Ashdod",	31.49,	34.35),
AbstractGeodataReader::GeoDataPlace.new("Asheqelon",	31.42,	34.35),
AbstractGeodataReader::GeoDataPlace.new("Bat Yam",	32.02,	34.44),
AbstractGeodataReader::GeoDataPlace.new("Ber Manuha",	30.19,	35.08),
AbstractGeodataReader::GeoDataPlace.new("Ber Sheva", 	31.15,	34.48),
AbstractGeodataReader::GeoDataPlace.new("Beersheba/Ber Sheva",	31.15,	34.48),
AbstractGeodataReader::GeoDataPlace.new("Bene Beraq",	32.06,	34.51),
AbstractGeodataReader::GeoDataPlace.new("Bet She'an",	32.30,	35.30),
AbstractGeodataReader::GeoDataPlace.new("Bet Shemesh",	31.44,	35.00),
AbstractGeodataReader::GeoDataPlace.new("Birein",	30.50,	34.28),
AbstractGeodataReader::GeoDataPlace.new("Bor Mashash",	31.07,	34.50),
AbstractGeodataReader::GeoDataPlace.new("Caesarea",	32.30,	34.53),
AbstractGeodataReader::GeoDataPlace.new("Daliyat el Karmel",	32.43,	35.02),
AbstractGeodataReader::GeoDataPlace.new("Dimona",	31.02,	35.01),
AbstractGeodataReader::GeoDataPlace.new("Elat",	29.30,	34.56),
AbstractGeodataReader::GeoDataPlace.new("En 'Avrona",	29.43,	35.00),
AbstractGeodataReader::GeoDataPlace.new("Galilee/Hagalil",	32.53,	35.18),
AbstractGeodataReader::GeoDataPlace.new("Ha 'Arava",	30.50,	35.20),
AbstractGeodataReader::GeoDataPlace.new("Hadarom",	31.00,	35.00),
AbstractGeodataReader::GeoDataPlace.new("Hadera",	32.27,	34.55),
AbstractGeodataReader::GeoDataPlace.new("Hagalil",	32.53,	35.18),
AbstractGeodataReader::GeoDataPlace.new("Haifa/Hefa",	32.46,	35.00),
AbstractGeodataReader::GeoDataPlace.new("Hamerkaz",	32.15,	34.55),
AbstractGeodataReader::GeoDataPlace.new("Hanegev",	30.50,	35.00),
AbstractGeodataReader::GeoDataPlace.new("Har Yehuda",	31.35,	34.57),
AbstractGeodataReader::GeoDataPlace.new("Hazafon",	32.40,	35.20),
AbstractGeodataReader::GeoDataPlace.new("Hefa",	32.46,	35.00),
AbstractGeodataReader::GeoDataPlace.new("Hefa",	32.40,	35.00),
AbstractGeodataReader::GeoDataPlace.new("Herzliyya",	32.10,	34.50),
AbstractGeodataReader::GeoDataPlace.new("Hiyyon, N.",	30.25,	35.10),
AbstractGeodataReader::GeoDataPlace.new("Jaffa/Tel Aviv-Yafo",	32.04,	34.48),
AbstractGeodataReader::GeoDataPlace.new("Jerusalem",	31.47,	35.10),
AbstractGeodataReader::GeoDataPlace.new("Judaea/Har Yehuda",	31.35,	34.57),
AbstractGeodataReader::GeoDataPlace.new("Karmil",	32.55,	35.18),
AbstractGeodataReader::GeoDataPlace.new("Kafar Sava",	32.11,	34.54),
AbstractGeodataReader::GeoDataPlace.new("Lod",	31.57,	34.54),
AbstractGeodataReader::GeoDataPlace.new("Lydda/Lod.", 	31.57,	34.54),
AbstractGeodataReader::GeoDataPlace.new("Me'ona", 	33.01,	35.15),
AbstractGeodataReader::GeoDataPlace.new("Mifraz Hefa",	32.52,	35.0),
AbstractGeodataReader::GeoDataPlace.new("Mizpe Ramon",	30.34,	34.49),
AbstractGeodataReader::GeoDataPlace.new("Nahariyya",	33.01,	35.05),
AbstractGeodataReader::GeoDataPlace.new("Nazareth/Nazerat", 	32.42,	35.17),
AbstractGeodataReader::GeoDataPlace.new("Nazerat",	32.42,	35.17),
AbstractGeodataReader::GeoDataPlace.new("Netanya",	32.20,	34.51),
AbstractGeodataReader::GeoDataPlace.new("Paran",	30.20,	35.10),
AbstractGeodataReader::GeoDataPlace.new("Pardes hanna -Karkur",	32.28,	34.57),
AbstractGeodataReader::GeoDataPlace.new("Petah Tiqwa",	32.06,	34.53),
AbstractGeodataReader::GeoDataPlace.new("Qezi'ot", 	30.52,	34.26),
AbstractGeodataReader::GeoDataPlace.new("Qiryat Ata",	32.47,	35.06),
AbstractGeodataReader::GeoDataPlace.new("Qirya Gat",	31.44,	34.44),
AbstractGeodataReader::GeoDataPlace.new("Qiryat Mal'akhi",	31.44,	34.44),
AbstractGeodataReader::GeoDataPlace.new("Qiryat Shermona",	33.13,	35.35),
AbstractGeodataReader::GeoDataPlace.new("Qiryat Yam",	32.51,	35.04),
AbstractGeodataReader::GeoDataPlace.new("Ramat Gan", 	32.04,	34.48),
AbstractGeodataReader::GeoDataPlace.new("Ramla",	31.55,	34.52),
AbstractGeodataReader::GeoDataPlace.new("Rehovot",	31.54,	34.48),
AbstractGeodataReader::GeoDataPlace.new("Rishon le Ziyyon", 	31.58,	34.48),
AbstractGeodataReader::GeoDataPlace.new("Sede Boqer",	30.52,	34.47),
AbstractGeodataReader::GeoDataPlace.new("Sederot",	31.32,	34.37),
AbstractGeodataReader::GeoDataPlace.new("Tel Megiddo",	31.34,	34.51),
AbstractGeodataReader::GeoDataPlace.new("Umm el Fahm",	32.31,	35.9),
AbstractGeodataReader::GeoDataPlace.new("Yam Kinneret",	32.45,	35.35),
AbstractGeodataReader::GeoDataPlace.new("Yotvata",	29.55,	35.2),
AbstractGeodataReader::GeoDataPlace.new("Zefat",	32.58,	35.29)  
	]
  } 
  
  
ExtraPlaces = {
	"NI" => [
	AbstractGeodataReader::GeoDataPlace.new("Lagos",	6.25,	3.27)
	],
	"NO" => [
	AbstractGeodataReader::GeoDataPlace.new("Hammerfest",	70.39,	23.41)
	],
	"CH" => [
	AbstractGeodataReader::GeoDataPlace.new("Tengster, Tibet",	36.32,	101.12)
	],
	"IZ" => [
	AbstractGeodataReader::GeoDataPlace.new("Tikrit", 34.35, 43.37),
	AbstractGeodataReader::GeoDataPlace.new("Basrah",30.30, 47.50),
	AbstractGeodataReader::GeoDataPlace.new("Babylon ",32.34, 44.22),
	AbstractGeodataReader::GeoDataPlace.new("Mosul " ,36.15, 43.05),
	AbstractGeodataReader::GeoDataPlace.new("Arbil" ,36.15,44.05),
	AbstractGeodataReader::GeoDataPlace.new("Kirkuk" ,35.30,44.21),
	AbstractGeodataReader::GeoDataPlace.new("Sulaymaniyah", 35.35,45.29),
	AbstractGeodataReader::GeoDataPlace.new("Najaf" ,32.03,44.15),
	AbstractGeodataReader::GeoDataPlace.new("Karbala", 32.36,44.03),
	AbstractGeodataReader::GeoDataPlace.new("Nasiriyah", 31.00,46.15),
	AbstractGeodataReader::GeoDataPlace.new("Hillah" ,32.30,44.25),
	AbstractGeodataReader::GeoDataPlace.new("Ramadi" ,33.25,43.20),
	AbstractGeodataReader::GeoDataPlace.new("Diwaniyah", 32.00,45.00),
	AbstractGeodataReader::GeoDataPlace.new("Kut", 32.30,46.00),
	AbstractGeodataReader::GeoDataPlace.new("Amarah", 31.55,47.15),
	AbstractGeodataReader::GeoDataPlace.new("Diyala", 33.14,44.31),
	AbstractGeodataReader::GeoDataPlace.new("Fallujah", 33.20,43.55),
	AbstractGeodataReader::GeoDataPlace.new("Samarra", 34.12,43.52)
	],
	"IR" => [
	AbstractGeodataReader::GeoDataPlace.new("Garmsar",35.20,52.25),
	AbstractGeodataReader::GeoDataPlace.new("Mashhad",36.20,59.35),
	AbstractGeodataReader::GeoDataPlace.new("Esfahan",32.39,51.43),
	AbstractGeodataReader::GeoDataPlace.new("Tabriz",38.70,46.20),
	AbstractGeodataReader::GeoDataPlace.new("Karaj",35.48,51.00),
	AbstractGeodataReader::GeoDataPlace.new("Fars",29.30,55.00),
	AbstractGeodataReader::GeoDataPlace.new("Ahvaz",31.20,48.40),
	AbstractGeodataReader::GeoDataPlace.new("Qom",34.40,51.00),
	AbstractGeodataReader::GeoDataPlace.new("Kermanshah/Bakhtaran",34.23,47.00),
	AbstractGeodataReader::GeoDataPlace.new("Orumiyeh",37.40,45.00),
	AbstractGeodataReader::GeoDataPlace.new("Zahedan Fars",28.46,53.52),
	AbstractGeodataReader::GeoDataPlace.new("Rasht",37.20,49.40),
	AbstractGeodataReader::GeoDataPlace.new("Kerman",30.00,57.00),
	AbstractGeodataReader::GeoDataPlace.new("Yazd",32.0,55.0),
	AbstractGeodataReader::GeoDataPlace.new("Bandar Abbas",27.15,56.15),
	AbstractGeodataReader::GeoDataPlace.new("Eslamshahr",35.40,51.50)
	],
	"UK" => [
	AbstractGeodataReader::GeoDataPlace.new("Sandringham",	52.51, 0.31)
	]
	
}  

Testing = false
  
class GeodataReader
def self.createCountryRec(name,code)
  d = nil
  if CustomPlaces[code]
    d = CustomPlaces[code]
  else
    d = GeodataReader.load_geo_data(code, "geodata3s")
	if ExtraPlaces[code]
		d = (d + ExtraPlaces[code]).sort_by {|rec| [ rec.place_name ]}
	end
  end
  res = ""
  i = 0
  d.each do |rec| 
    puts rec if Testing
	i += 1+ rec.place_name.size() + 4
	res += [rec.place_name.size(), rec.place_name, (rec.latitude*100), (rec.longitude*100)].pack("CA#{rec.place_name.size()}ss");
  end
  if (i != res.size())
	#throw Exception("ugh");
	puts "-----ERROR"
  end
  pt = "CA#{code.size()}CA#{name.size()}S"
  #puts pt
  rec_header = [code.size(), code, name.size(), name, res.size()].pack(pt);
  rec_header + res  
end
end

all = ""


if Testing 
	puts "HEI - TESTING"
	GeodataReader.createCountryRec("someplace","UK")
	#GeodataReader.createCountryRec("UKRAIN","UP")
else

	AllCountryCodes.each do |cc|
		puts cc
		all += GeodataReader.createCountryRec(cc[0],cc[1])
	end

	puts "writing #{all.size()} bytes"

	f = File.open("geodata.dat", "wb")
	f.write(all)
	f.close()
	puts "done"
end
  
end

