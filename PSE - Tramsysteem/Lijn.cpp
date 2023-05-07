//
// Created by Samuel on 06/05/2023.
//

#include "Lijn.h"

int Lijn::getLijnnummer() const {
    REQUIRE(lijnnummer >= 0, "Bij getLijnnummer van Lijn was dit < 0");
    return lijnnummer;
}


const vector<Station *> &Lijn::getStations() const {
    REQUIRE(!stations.empty(), "Bij getStations van Lijn was deze vector leeg");
    return stations;
}

const vector<Tram *> &Lijn::getTrams() const {
    REQUIRE(!stations.empty(), "Bij getTrams van Lijn was deze vector leeg");
    return trams;
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
