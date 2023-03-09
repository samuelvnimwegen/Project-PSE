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

    void setNaam(const string &naam);

    Station *getVolgende() const;

    void setVolgende(Station *volgende);

    Station *getVorige() const;

    void setVorige(Station *vorige);

    int getSpoorNr() const;

    void setSpoorNr(int spoorNr);

    Station();



    Station(const string &naam, Station *volgende, Station *vorige, int spoorNr);

};


#endif //TREIN_STATION_H
