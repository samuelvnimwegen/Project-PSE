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

    void setType(const string &tp);

    const string &getNaam() const;
    // Getter van de naam van het statimomn

    void setNaam(const string &nm);
    /**
     * REQUIRE(!nm.empty(), "Bij setNaam van station was de naam leeg");
     * ENSURE(naam == nm, "Bij setNaam van station was de naam niet correct aangepast");
     */

    Station *getVolgende() const;
    // Getter van het volgende station

    void setVolgende(Station *vlgd);
    // Setter van het volgende station

    Station *getVorige() const;
    // Getter van het vorige station

    void setVorige(Station *vrg);
    // Setter van het vorige station

    int getSpoorNr() const;
    // Getter van het spoornummer

    void setSpoorNr(int nr);
    // Setter van het spoornummer

    Station();
    // constructor


    Station(const string &naam, Station *volgende, Station *vorige, int spoorNr);

};


#endif //TREIN_STATION_H
