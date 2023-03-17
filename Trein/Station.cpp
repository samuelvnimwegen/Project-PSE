//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "Station.h"

Station::Station(const string &naam, Station *volgende, Station *vorige, int spoorNr) : naam(naam), volgende(volgende),
                                                                                        vorige(vorige),
                                                                                        spoorNr(spoorNr) {}

Station::Station() {
    volgende = 0;
    vorige = 0;
    spoorNr = -1;
}

const string &Station::getNaam() const {
    return naam;
}

void Station::setNaam(const string &nm) {
    Station::naam = nm;
}

Station *Station::getVolgende() const {
    return volgende;
}

void Station::setVolgende(Station *vlgd) {
    Station::volgende = vlgd;
}

Station *Station::getVorige() const {
    return vorige;
}

void Station::setVorige(Station *vrg) {
    Station::vorige = vrg;
}

int Station::getSpoorNr() const {
    return spoorNr;
}

void Station::setSpoorNr(int nr) {
    Station::spoorNr = nr;
}
