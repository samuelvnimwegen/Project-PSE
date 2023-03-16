//
// Created by Space Movie 1992 on 02/03/2023.
//
#include "iostream"
using namespace std;
#ifndef TREIN_STATION_H
#define TREIN_STATION_H

// Alle eigenschappen / waarden station
class Station {
public:
    string naam;
    Station* volgende;
    Station* vorige;
    int spoorNr;

    const string &getNaam() const;

    void setNaam(const string &nm);

    Station *getVolgende() const;

    void setVolgende(Station *vlgd);

    Station *getVorige() const;

    void setVorige(Station *vrg);

    int getSpoorNr() const;

    void setSpoorNr(int nr);

    Station();



    Station(const string &naam, Station *volgende, Station *vorige, int spoorNr);

};


#endif //TREIN_STATION_H
