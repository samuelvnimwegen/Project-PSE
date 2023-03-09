//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "Station.h"

Station::Station(const string &naam, Station *volgende, Station *vorige, int spoorNr) : naam(naam), volgende(volgende),
                                                                                        vorige(vorige),
                                                                                        spoorNr(spoorNr) {}

Station::Station() {}

const string &Station::getNaam() const {
    return naam;
}

void Station::setNaam(const string &naam) {
    Station::naam = naam;
}

Station *Station::getVolgende() const {
    return volgende;
}

void Station::setVolgende(Station *volgende) {
    Station::volgende = volgende;
}

Station *Station::getVorige() const {
    return vorige;
}

void Station::setVorige(Station *vorige) {
    Station::vorige = vorige;
}

int Station::getSpoorNr() const {
    return spoorNr;
}

void Station::setSpoorNr(int spoorNr) {
    Station::spoorNr = spoorNr;
}
