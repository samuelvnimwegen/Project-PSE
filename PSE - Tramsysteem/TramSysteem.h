//
// Created by Space Movie 1992 on 02/03/2023.
//
#ifndef TREIN_TRAMSYSTEEM_H
#define TREIN_TRAMSYSTEEM_H
#include "Tram.h"
#include "Station.h"
#include "XML/tinyxml.h"
#include "vector"
#include "sstream"
#include "fstream"
#include "DesignByContract.h"

// Bevat het volledige tramsysteem en bevat alle andere classes.
class TramSysteem {
    TramSysteem* initCheck;
    vector<Station*> stations;
    vector<Tram*> trams;
    string filename;
public:
    TramSysteem();
    /**
     * ENSURE(properlyInitialized(), "constructor moet in juiste staat eindigen bij initialisatie bij TramSysteem");
     */

    bool properlyInitialized();

    bool add_station(Station* station);
    /**
     * REQUIRE((station != 0), "Station moet bestaan bij add_station");
     * ENSURE(stations[size - 1] == station, "Laatste station in de stations-vector moet het nieuwe station zijn bij addStation");
    */


    void addTram(Tram* tram);
    /**
     * REQUIRE(tr != 0, "tram moet bestaan bij addTram");
     * ENSURE(trams[size - 1] == tr, "tram moet laatste element in trams-vector zijn bij addTram");
     */

    vector<Station *> &getStations();
    /**
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer getStations was gebruikt");
     * ENSURE(stat == getStations(), "Moet alle stat teruggeven bij getStations");
     */

    void setStations(const vector<Station *> &stat);
    /**
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer setStations was gebruikt");
     * ENSURE(getStations() == stat, "Postconditie fout bij setStation");
     */

    const vector<Tram *> &getTrams() const;
    // Getter voor de trams

    void setTrams(const vector<Tram *> &trams);
    // Setter voor de trams

    bool move(Tram*, Station*);
    // Verplaatst een tram naar een gegeven station:
    // Preconditie: Station ligt op de lijn, er moet een outputfile zijn en het moet een nieuw station zijn.
    // Postconditie: tram->getStation() == station

    bool simulate(int tijd);
    // Simuleert het circuit voor een gegeven aantal stappen (werkt ook voor negatieve getallen om terug in de tijd te gaan).
    // Preconditie: zelfde condities als de move functie + moet consistent zijn.

    bool complete_summary();
    // Geeft een compleet overzicht van alle stations en trams in de txt file.
    // Preconditie: er is een txt file geopend

    bool tram_summary();
    // Geeft een overzicht van alle trams in de txt file.
    // Preconditie: er is een txt file geopend

    bool station_summary();
    // Geeft een overzicht van alle stations in de txt file.
    // Preconditie: er is een txt file geopend

    bool isConsistent();
    // Checkt of het tramsysteem consistent is

    virtual ~TramSysteem();
    // Destructor die alle stations en trams verwijderd
};


#endif //TREIN_TRAMSYSTEEM_H
