//
// Created by Samuel on 06/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_LIJN_H
#define TRAMSYSTEEM_CPP_LIJN_H
#include "Tram.h"
#include "Station.h"
#include "vector"

class Lijn {
    Lijn* initCheck;
    int lijnnummer;
    vector<Station*> stations;
    vector<Tram*> trams;
public:
    explicit Lijn(int lijnnummer);
    /*
     * Constructor van Lijn
     *
     * ENSURE(this->properlyInitialised(), "Lijn bij constructor niet correct geïnitieerd");
     */

    bool properlyInitialised();
    /**
     * Checkt of de class juist geïnitieerd is.
     */

    int getLijnnummer();
    /**
     * Getter voor het lijnnummer.
     *
     * REQUIRE(this->properlyInitialised(), "Lijn bij getLijnnummer niet correct geïnitieerd");
     * ENSURE(result >= 0, "Bij getLijnnummer van Lijn postconditie error");
     */

    vector<Station *> getStations();
    /**
     * Getter van de stations
     *
     * REQUIRE(this->properlyInitialised(), "Lijn bij getStations niet correct geïnitieerd");
     * ENSURE(!result.empty(), "Bij getStations van Lijn postconditie error");
     */

    vector<Tram *> getTrams();
    /**
     * Getter van de trams
     *
     * REQUIRE(this->properlyInitialised(), "Lijn bij getTrams niet correct geïnitieerd");
     * ENSURE(!result.empty(), "Bij getTrams van Lijn postconditie fout");
     */

    void addStation(Station* station);
    /**
     * Adder van een station aan de stations.
     *
     * REQUIRE(this->properlyInitialised(), "Lijn bij addStation niet correct geïnitieerd");
     * REQUIRE(huidigStation != 0, "Bij addStation van Lijn was de pointer == 0");
     * ENSURE(this->getStations()[int(this->getStations().size()) - 1] == station, "Bij addStation van Lijn postconditie error");
     */

    void addTram(Tram* tram);
    /**
     * Adder van een tram aan de trams.
     *
     * REQUIRE(tram != 0, "Bij addTram van Lijn was de pointer == 0");
     */
};


#endif //TRAMSYSTEEM_CPP_LIJN_H
