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
    Station* initCheck;
    string naam;
    string typeString;
    Station* volgende;
    Station* vorige;
    Tram* huidigeTram;
    int spoorNr;

public:
    Station(const string &naam, const int &spoornummer);
    /**
     * Lege constructor van Station.
     *
     * ENSURE(this->properlyInitialised(), "Station bij constructor niet correct geïnitialiseerd");
     */

    Station(const string &naam, Station *volgende, Station *vorige, int spoorNr);
    /**
     * Constructor met argumenten van Station.
     *
     * REQUIRE(!naam.empty(), "Bij Station was de naam leeg");
     * REQUIRE(volgende != 0, "Bij Station was het volgende station niet bestaand");
     * REQUIRE(vorige != 0, "Bij Station was het vorige station niet bestaand");
     * REQUIRE(spoorNr < 0, "Bij Station was het spoorNr kleiner dan 0");
     * ENSURE(this->properlyInitialised(), "Station bij constructor niet correct geïnitialiseerd");
     */

    bool properlyInitialised();
    /*
     * Checkt of het station correct geïnitialiseerd is.
     */

    bool tramInStation();
    /**
     * Checkt of er een tram in het station is.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij tramInStation niet correct geïnitialiseerd");
     */

    Tram *getTramInStation();
    /**
     * Getter voor huidige tram in het station.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij getTramInStation niet correct geïnitialiseerd");
     * REQUIRE(this->tramInStation(), "Bij getTramInStation van Station was geen tram in het station");
     * ENSURE(result != 0, "Bij getTramInStation van Station postconditie fout");
     */

    void removeTramVanStation();
    /*
     * Verwijdert tram van het station.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij removeTramVanStation niet correct geïnitialiseerd");
     * REQUIRE(this->tramInStation(), "Bij removeTramVanStation van Station was er geen tram aanwezig");
     * ENSURE(!this->tramInStation(), "Bij removeTramVanStation van Station was het niet correct uitgevoerd");
     */

    void setTramInStation(Tram *tram);
    /**
     * Setter van de tram in het station.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij setTramInStation niet correct geïnitialiseerd");
     * REQUIRE(tram != 0, "Bij setTramInStation van Station bestond de tram niet");
     * ENSURE(getTramInStation() == tram, "Bij setTramInStation van Station postconditie fout");
     */

    string getTypeString();
    /**
     * Getter voor de typeString.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij getTypeString niet correct geïnitialiseerd");
     * ENSURE(!result.empty(), "Bij getTypeString van Station was de string leeg");
     */

    void setTypeString(const string &typeString);
    /**
     * Setter voor de typeString.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij setTypeString niet correct geïnitialiseerd");
     * REQUIRE(!tpString.empty(), "Bij setTypeString van Station was de string leeg");
     * ENSURE(this->getTypeString() == tpString, "Bij setTypeString van Station is de wijziging niet correct uitgevoerd.");
     */

    string getNaam();
    /**
     * Getter voor de naam.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij getNaam niet correct geïnitialiseerd");
     * ENSURE(!result.empty(), "Bij getNaam van Station was de naam leeg");
     */

    void setNaam(const string &nm);
    /**
     * Setter voor de naam
     *
     * REQUIRE(this->properlyInitialised(), "Station bij getNaam niet correct geïnitialiseerd");
     * REQUIRE(!nm.empty(), "Bij setNaam van Station was de naam leeg");
     * ENSURE(this->getNaam() == nm, "Bij setNaam van Station was de naam niet correct aangepast");
     */

    Station *getVolgende();
    /**
     * Getter van het volgende station.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij getVolgende niet correct geïnitialiseerd");
     * ENSURE(result != 0 , "Bij getVolgende van Station was er geen volgend station");
     */

    void setVolgende(Station *next);
    /**
     * Setter van het volgende station.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij setVolgende niet correct geïnitialiseerd");
     * REQUIRE(next != 0, "Bij setVolgende van Station was de input 0");
     * ENSURE(this->getVolgende() == next, "Bij setVolgende van Station is het niet correct uitgevoerd");
     */

    Station *getVorige();
    /**
     * Getter van het vorige station.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij getVorige niet correct geïnitialiseerd");
     * ENSURE(result != 0, "Bij getVorige van Station postconditie fout");
     */

    void setVorige(Station *previous);
    /**
     * Setter van het vorige station.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij setVorige niet correct geïnitialiseerd");
     * REQUIRE(previous != 0, "Bij setVorige van Station was de input 0");
     * ENSURE(this->getVorige() == previous, "Bij setVorige van Station is het niet correct uitgevoerd");
     */

    int getSpoorNr();
    /**
     * Getter voor spoornummer.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij getSpoorNr niet correct geïnitialiseerd");
     * ENSURE(result >= 0, "Bij getSpoorNr van Station was het nummer kleiner dan 0");
     */

    void setSpoorNr(int nr);
    /**
     * Setter voor spoornummer.
     *
     * REQUIRE(this->properlyInitialised(), "Station bij setSpoorNr niet correct geïnitialiseerd");
     * REQUIRE(spoorNr != 0, "Bij setSpoorNr van Station was de naam leeg");
     * ENSURE(this->getSpoorNr() == nr, "Bij setSpoorNr van Station was het nummer niet correct aangepast");
     */



};


#endif //TREIN_STATION_H
