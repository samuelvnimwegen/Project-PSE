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


// Bevat het volledige tramsysteem en bevat alle andere classes.
class TramSysteem {
    vector<Station*> stations;
    vector<Tram*> trams;
    string filename;

public:
    bool add_station(Station* station);
    /* Deze functie voegt een station toe aan het systeem
     * Preconditie: station != 0 en is een Station*
     * Postconditie: stations[station.size() - 1] == station
    */

    bool readFile(const string &name);
    /* Deze functie leest een XML-file met de ingegeven bestandsnaam.
     * Preconditie: de XML-file met de gegeven naam bestaat.
     * Postconditie: !trams.empty() and !stations.empty()
     */

    TramSysteem();
    // Maakt een tramsysteem aan.

    bool addTram(Tram* tram);
    /* Voegt een tram aan het systeem toe.
     * Preconditie: tram != 0
     * Postconditie: trams[trams.size() - 1] == tram
     */

    vector<Station *> &getStations();
    // Getter voor de stations

    void setStations(const vector<Station *> &stations);
    // Setter voor de stations

    const vector<Tram *> &getTrams() const;
    // Getter voor de trams

    void setTrams(const vector<Tram *> &trams);
    // Setter voor de trams

    void makeTxtFile(const string& name);
    // Maakt een .txt file aan waarin alle bewerkingen worden genoteerd.

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
