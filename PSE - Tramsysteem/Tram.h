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
public:
    int getLijnNr() const;
    // Getter van het lijnnummer

    void setLijnNr(int nr);
    // Setter van het lijnnummer

    Station *getBeginStation() const;
    // Getter van het beginstation

    void setBeginStation(Station *beginStation);
    // Setter van het beginstation

    double getSnelheid() const;
    // Getter van de snelheid

    void setSnelheid(double snelh);
    // Setter van de snelheid

    Tram();
    // Constructor van de tramklasse

    Station *getStation() const;
    // Getter van het station waar de tram is

    void setStation(Station *stat);
    // Setter van het station waar de tram is
};


#endif //TREIN_TRAM_H