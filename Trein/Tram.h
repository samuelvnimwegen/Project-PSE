//
// Created by Space Movie 1992 on 02/03/2023.
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

    void setLijnNr(int nr);

    Station *getBeginStation() const;

    void setBeginStation(Station *beginStation);

    double getSnelheid() const;

    void setSnelheid(double snelh);

    Tram();

    Station *getStation() const;

    void setStation(Station *stat);
};


#endif //TREIN_TRAM_H
