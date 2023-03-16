//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "Tram.h"

int Tram::getLijnNr() const {
    return lijnNr;
}

void Tram::setLijnNr(int nr) {
    Tram::lijnNr = nr;
}

Station *Tram::getBeginStation() const {
    return beginStation;
}

void Tram::setBeginStation(Station *stat) {
    Tram::beginStation = stat;
}

double Tram::getSnelheid() const {
    return snelheid;
}

void Tram::setSnelheid(double snelh) {
    Tram::snelheid = snelh;
}

Tram::Tram() {
    beginStation = 0;
}
