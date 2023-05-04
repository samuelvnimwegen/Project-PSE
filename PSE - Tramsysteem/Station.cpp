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
    // Deze waarde is -1 zodat duidelijk is dat deze nog niet gekozen is.
}

const string &Station::getNaam() const {
    return naam;
}

void Station::setNaam(const string &nm) {
    REQUIRE(!nm.empty(), "Bij setNaam van station was de naam leeg");
    Station::naam = nm;
    ENSURE(naam == nm, "Bij setNaam van station was de naam niet correct aangepast");
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

const string &Station::getType() const {
    return type;
}

void Station::setType(const string &tp) {
    Station::type = tp;
}
