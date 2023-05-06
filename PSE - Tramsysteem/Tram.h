//
// Created by Samuel van Nimwegen on 02/03/2023.
//
#include "Station.h"
#ifndef TREIN_TRAM_H
#define TREIN_TRAM_H

// Alle waarden / eigenschappen Tram
class Tram {
    int lijnNr;
    Station* beginStation;
    double snelheid;
    Station* station;
    int voertuigNummer;
    double reparatieKosten;
    string typeString;
public:
    virtual ~Tram();

    const string &getTypeString() const;
    /**
     * REQUIRE(!type.empty() , "Bij getType van tram was de input 0");
     */

    void setTypeString(const string &tp);
    /**
     * REQUIRE(!tp.empty() , "Bij getType van tram was de input 0");
     * ENSURE(typeString == tp ,"Bij getType van tram is het niet correct uitgevoerd" );
     */


    double getReparatieKosten() const;
    /**
     * REQUIRE(reparatieKosten != 0 , "Bij getReparatieKosten van tram was de input 0");
     */

    void setReparatieKosten(double rk);

    int getLijnNr() const;
    /**
     * REQUIRE(lijnNr != 0 , "Bij getLijnNr van tram was de input 0");
     */

    void setLijnNr(int nr);
    /**
     * REQUIRE(lijnNr != 0, "Bij setLijnNr van station was de naam leeg");
     * ENSURE(lijnNr = nr, "Bij setLijnNr van station was het nummer niet correct aangepast");
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

    Station *getStation() const;
    /**
     * REQUIRE(station != 0 , "Bij getStation van tram was de input 0");
     */

    void setStation(Station *stat);
    /**
     * REQUIRE(stat != 0, "Bij setStation tram was de input 0");
     * ENSURE(station = stat, "Bij setStation van tram is het niet correct uitgevoerd");
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
