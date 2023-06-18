//
// Created by Samuel on 06/05/2023.
//

#include "Lijn.h"

int Lijn::getLijnnummer() {
    REQUIRE(this->properlyInitialised(), "Lijn bij getLijnnummer niet correct geïnitieerd");
    int result = lijnnummer;
    ENSURE(result >= 0, "Bij getLijnnummer van Lijn postconditie error");
    return result;
}


vector<Station *> Lijn::getStations() {
    REQUIRE(this->properlyInitialised(), "Lijn bij getStations niet correct geïnitieerd");
    vector<Station*> result = stations;
    ENSURE(!result.empty(), "Bij getStations van Lijn postconditie error");
    return result;
}

vector<Tram *> Lijn::getTrams() {
    REQUIRE(this->properlyInitialised(), "Lijn bij getTrams niet correct geïnitieerd");
    vector<Tram*> result = trams;
    ENSURE(!result.empty(), "Bij getTrams van Lijn postconditie fout");
    return result;
}


Lijn::Lijn(int lijnnummer) : lijnnummer(lijnnummer) {
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Lijn bij constructor niet correct geïnitieerd");
}

void Lijn::addStation(Station *station) {
    REQUIRE(this->properlyInitialised(), "Lijn bij addStation niet correct geïnitieerd");
    REQUIRE(station != 0, "Bij addStation van Lijn was de pointer == 0");
    stations.push_back(station);
    ENSURE(this->getStations()[int(this->getStations().size()) - 1] == station, "Bij addStation van Lijn postconditie fout");
}

void Lijn::addTram(Tram *tram) {
    REQUIRE(this->properlyInitialised(), "Lijn bij addTram niet correct geïnitieerd");
    REQUIRE(tram != 0, "Bij addTram van Lijn was de pointer == 0");
    trams.push_back(tram);
    ENSURE(this->getTrams()[int(this->getTrams().size()) - 1] == tram, "Bij addTram van Lijn postconditie fout");
}

bool Lijn::properlyInitialised() {
    return initCheck == this;
}
