//
// Created by Space Movie 1992 on 02/03/2023.
//
#include "iostream"
#include "DesignByContract.h"
#include "vector"
using namespace std;
#ifndef TREIN_STATION_H
#define TREIN_STATION_H

class Tram;
// Alle eigenschappen / waarden huidigStation
class Station {
    string naam;
    string typeString;
    Station* volgende;
    Station* vorige;
    vector<Tram*> tramInStation;
    int spoorNr;

public:
    Tram *getTramInStation() const;

    void removeTramVanStation();
    /**
     * REQUIRE(!tramInStation.empty(), "Bij removeTramVanStation van Station was er geen tram aanwezig");
     * ENSURE(tramInStation.empty(), "Bij removeTramVanStation van Station was het niet correct uitgevoerd");
     */

    void addTramAanStation(Tram *tram);
    /**
     * ENSURE(tramInStation == tram, "Bij addTramAanStation van Station was het niet correct uitgevoerd");
     */

    const string &getTypeString() const;
    /**
     * REQUIRE(!typeString.empty(), "Bij getTypeString van Station was de string leeg");
     */

    void setTypeString(const string &typeString);
    /**
     * REQUIRE(!tpString.empty(), "Bij setTypeString van Station was de string leeg");
     * ENSURE(typeString == tpString, "Bij setTypeString van Station is de wijziging niet correct uitgevoerd.");
     */

    const string &getNaam() const;
    /**
     * REQUIRE(naam.empty(), "Bij getNaam van huidigStation was de naam leeg");
     */

    void setNaam(const string &nm);
    /**
     * REQUIRE(!nm.empty(), "Bij setNaam van huidigStation was de naam leeg");
     * ENSURE(naam == nm, "Bij setNaam van huidigStation was de naam niet correct aangepast");
     */

    Station *getVolgende() const;
    /**
     * REQUIRE(volgende != 0 , "Bij getVolgende van huidigStation was de input 0");
     */

    void setVolgende(Station *vlgd);
    /**
     * REQUIRE(vlgd != 0, "Bij setVolgende van huidigStation was de input 0");
     * ENSURE(volgende == vlgd, "Bij setVolgende van huidigStation is het niet correct uitgevoerd");
     */

    Station *getVorige() const;
    /**
     * REQUIRE (vorige != 0,"Bij getVorige van huidigStation was de input 0");
     */

    void setVorige(Station *vrg);
    /**
     * REQUIRE(vrg != 0, "Bij setVorige van huidigStation was de input 0");
     * ENSURE(vorige == vrg, "Bij setVorige van huidigStation is het niet correct uitgevoerd");
     */

    int getSpoorNr() const;
    /**
     * REQUIRE(spoorNr !=0, "Bij getSpoorNr van huidigStation was de naam leeg");
     */

    void setSpoorNr(int nr);
    /**
     * REQUIRE(spoorNr != 0, "Bij setSpoorNr van huidigStation was de naam leeg");
     * ENSURE(spoorNr = nr, "Bij setSpoorNr van huidigStation was het nummer niet correct aangepast");
     */

    Station();
    // constructor

    Station(const string &naam, Station *volgende, Station *vorige, int spoorNr);

};


#endif //TREIN_STATION_H
