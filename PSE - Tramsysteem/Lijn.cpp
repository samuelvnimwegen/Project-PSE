//
// Created by Samuel on 06/05/2023.
//

#include "Lijn.h"

int Lijn::getLijnnummer() const {
    return lijnnummer;
}

void Lijn::setLijnnummer(int ln) {
    Lijn::lijnnummer = ln;
}

const vector<Station *> &Lijn::getStations() const {
    return stations;
}

void Lijn::setStations(const vector<Station *> &stats) {
    Lijn::stations = stats;
}

const vector<Tram *> &Lijn::getTrams() const {
    return trams;
}

void Lijn::setTrams(const vector<Tram *> &trms) {
    Lijn::trams = trms;
}

Lijn::Lijn(int lijnnummer) : lijnnummer(lijnnummer) {}

void Lijn::addStation(Station *station) {
    REQUIRE(station != 0, "Bij addStation van Lijn was de pointer == 0");
    stations.push_back(station);
}

void Lijn::addTram(Tram *tram) {
    REQUIRE(tram != 0, "Bij addTram van Lijn was de pointer == 0");
    trams.push_back(tram);
}
