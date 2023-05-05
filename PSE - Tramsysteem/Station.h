//
// Created by Space Movie 1992 on 02/03/2023.
//
#include "iostream"
#include "DesignByContract.h"
using namespace std;
#ifndef TREIN_STATION_H
#define TREIN_STATION_H

// Alle eigenschappen / waarden station
class Station {
    string naam;
    string type;
    Station* volgende;
    Station* vorige;
    int spoorNr;

public:
    const string &getType() const;
    /**
     * REQUIRE(!type.empty() , "Bij getType van station was de naam leeg");
     */

    void setType(const string &tp);
    /**
     * REQUIRE(!tp.empty(), "Bij setType van station was de naam leeg");
     * ENSURE(type == tp, "Bij setType van station was de naam niet correct aangepast");
     */


    const string &getNaam() const;
    /**
     * REQUIRE(naam.empty(), "Bij getNaam van station was de naam leeg");
     */

    void setNaam(const string &nm);
    /**
     * REQUIRE(!nm.empty(), "Bij setNaam van station was de naam leeg");
     * ENSURE(naam == nm, "Bij setNaam van station was de naam niet correct aangepast");
     */

    Station *getVolgende() const;
    /**
     * REQUIRE(volgende != 0 , "Bij getVolgende van station was de input 0");
     */

    void setVolgende(Station *vlgd);
    /**
     * REQUIRE(vlgd != 0, "Bij setVolgende van station was de input 0");
     * ENSURE(volgende == vlgd, "Bij setVolgende van station is het niet correct uitgevoerd");
     */

    Station *getVorige() const;
    /**
     * REQUIRE (vorige != 0,"Bij getVorige van station was de input 0");
     */

    void setVorige(Station *vrg);
    /**
     * REQUIRE(vrg != 0, "Bij setVorige van station was de input 0");
     * ENSURE(vorige == vrg, "Bij setVorige van station is het niet correct uitgevoerd");
     */

    int getSpoorNr() const;
    /**
     * REQUIRE(spoorNr !=0, "Bij getSpoorNr van station was de naam leeg");
     */

    void setSpoorNr(int nr);
    /**
     * REQUIRE(spoorNr != 0, "Bij setSpoorNr van station was de naam leeg");
     * ENSURE(spoorNr = nr, "Bij setSpoorNr van station was het nummer niet correct aangepast");
     */

    Station();
    // constructor

    Station(const string &naam, Station *volgende, Station *vorige, int spoorNr);

};


#endif //TREIN_STATION_H
