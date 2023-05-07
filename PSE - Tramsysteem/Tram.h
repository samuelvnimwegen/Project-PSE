//
// Created by Samuel van Nimwegen on 02/03/2023.
//
#include "Station.h"
#ifndef TREIN_TRAM_H
#define TREIN_TRAM_H
class TramSysteemOut;
// Alle waarden / eigenschappen Tram
class Tram {
    int lijnNr;
    Station* beginStation;
    double snelheid;
    Station* huidigStation;
    int voertuigNummer;
    string typeString;
public:
    virtual ~Tram();

    virtual bool isKapot();

    virtual void moveNaarVolgende(TramSysteemOut* tramSysteemOut);

    const string &getTypeString() const;
    /**
     * REQUIRE(!type.empty() , "Bij getType van tram was de input 0");
     */

    void setTypeString(const string &tp);
    /**
     * REQUIRE(!tp.empty() , "Bij getType van tram was de input 0");
     * ENSURE(typeString == tp ,"Bij getType van tram is het niet correct uitgevoerd" );
     */



    int getLijnNr() const;
    /**
     * REQUIRE(lijnNr != 0 , "Bij getLijnNr van tram was de input 0");
     */

    void setLijnNr(int nr);
    /**
     * REQUIRE(lijnNr != 0, "Bij setLijnNr van huidigStation was de naam leeg");
     * ENSURE(lijnNr = nr, "Bij setLijnNr van huidigStation was het nummer niet correct aangepast");
     */

    Station *getBeginStation() const;
    /**
     * REQUIRE(beginStation != 0 , "Bij beginStation van tram was de naam leeg");
     */

    void setBeginStation(Station *beginStation);
    // Setter van het beginstation

    double getSnelheid() const;
    // Getter van de snelheid

    void setSnelheid(double snelh);
    // Setter van de snelheid

    Tram();
    // Constructor van de tramklasse

    Station *getHuidigStation() const;
    /**
     * REQUIRE(huidigStation != 0 , "Bij getHuidigStation van tram was de input 0");
     */

    void setHuidigStation(Station *stat);
    /**
     * REQUIRE(stat != 0, "Bij setHuidigStation tram was de input 0");
     * ENSURE(huidigStation = stat, "Bij setHuidigStation van tram is het niet correct uitgevoerd");
     */

    int getVoertuigNummer() const;
    /**
     * REQUIRE(voertuigNummer != 0 , "Bij getVoertuigNummer van tram was de input 0");
     */


    void setVoertuigNummer(int nr);
    /**
     * REQUIRE(voertuigNummer <= 0, "Bij setVoertuigNummer het nummer <= 0");
     * ENSURE(voertuigNummer = nr, "Bij setVoertuigNummer van tram was het nummer niet correct aangepast" );
     */

    virtual bool kanNaar(Station*) = 0;
};


#endif //TREIN_TRAM_H
