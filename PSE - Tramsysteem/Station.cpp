//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "Station.h"

Station::Station(const string &naam, Station *volgende, Station *vorige, int spoorNr) :
        naam(naam), volgende(volgende), vorige(vorige), huidigeTram(0), spoorNr(spoorNr) {
    REQUIRE(!naam.empty(), "Bij Station was de naam leeg");
    REQUIRE(volgende != 0, "Bij Station was het volgende station niet bestaand");
    REQUIRE(vorige != 0, "Bij Station was het vorige station niet bestaand");
    REQUIRE(spoorNr < 0, "Bij Station was het spoorNr kleiner dan 0");
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Station bij constructor niet correct geïnitialiseerd");
}

string Station::getNaam() {
    REQUIRE(this->properlyInitialised(), "Station bij getNaam niet correct geïnitialiseerd");
    string result = naam;
    ENSURE(!result.empty(), "Bij getNaam van Station was de naam leeg");
    return result;
}

void Station::setNaam(const string &nm) {
    REQUIRE(this->properlyInitialised(), "Station bij getNaam niet correct geïnitialiseerd");
    REQUIRE(!nm.empty(), "Bij setNaam van Station was de naam leeg");
    naam = nm;
    ENSURE(this->getNaam() == nm, "Bij setNaam van Station was de naam niet correct aangepast");
}

Station *Station::getVolgende() {
    REQUIRE(this->properlyInitialised(), "Station bij getVolgende niet correct geïnitialiseerd");
    Station* result = volgende;
    ENSURE(result != 0 , "Bij getVolgende van Station was er geen volgend station");
    return result;
}

void Station::setVolgende(Station *next) {
    REQUIRE(this->properlyInitialised(), "Station bij getVolgende niet correct geïnitialiseerd");
    REQUIRE(next != 0, "Bij setVolgende van Station was de input 0");
    Station::volgende = next;
    ENSURE(this->getVolgende() == next, "Bij setVolgende van Station is het niet correct uitgevoerd");
}

Station *Station::getVorige() {
    REQUIRE(this->properlyInitialised(), "Station bij getVorige niet correct geïnitialiseerd");
    Station* result = vorige;
    ENSURE(result != 0, "Bij getVorige van Station postconditie fout");
    return result;
}

void Station::setVorige(Station *previous) {
    REQUIRE(this->properlyInitialised(), "Station bij setVorige niet correct geïnitialiseerd");
    REQUIRE(previous != 0, "Bij setVorige van Station was de input 0");
    Station::vorige = previous;
    ENSURE(this->getVorige() == previous, "Bij setVorige van Station is het niet correct uitgevoerd");

}

int Station::getSpoorNr() {
    REQUIRE(this->properlyInitialised(), "Station bij getSpoorNr niet correct geïnitialiseerd");
    int result = spoorNr;
    ENSURE(result >= 0, "Bij getSpoorNr van Station was het nummer kleiner dan 0");
    return result;
}

void Station::setSpoorNr(int nr) {
    REQUIRE(this->properlyInitialised(), "Station bij setSpoorNr niet correct geïnitialiseerd");
    REQUIRE(nr != 0, "Bij setSpoorNr van Station was de naam leeg");
    spoorNr = nr;
    ENSURE(this->getSpoorNr() == nr, "Bij setSpoorNr van Station was het nummer niet correct aangepast");
}

string Station::getTypeString(){
    REQUIRE(this->properlyInitialised(), "Station bij getTypeString niet correct geïnitialiseerd");
    string result = typeString;
    ENSURE(!result.empty(), "Bij getTypeString van Station was de string leeg");
    return result;
}

void Station::setTypeString(const string &tpString) {
    REQUIRE(this->properlyInitialised(), "Station bij setTypeString niet correct geïnitialiseerd");
    REQUIRE(!tpString.empty(), "Bij setTypeString van Station was de string leeg");
    Station::typeString = tpString;
    ENSURE(this->getTypeString() == tpString, "Bij setTypeString van Station is de wijziging niet correct uitgevoerd.");
}

Tram *Station::getTramInStation() {
    REQUIRE(this->properlyInitialised(), "Station bij getTramInStation niet correct geïnitialiseerd");
    REQUIRE(this->tramInStation(), "Bij getTramInStation van Station was geen tram in het station");
    Tram* result = huidigeTram;
    ENSURE(result != 0, "Bij getTramInStation van Station postconditie fout");
    return result;
}

void Station::setTramInStation(Tram *tram) {
    REQUIRE(this->properlyInitialised(), "Station bij setTramInStation niet correct geïnitialiseerd");
    REQUIRE(tram != 0, "Bij setTramInStation van Station bestond de tram niet");
    huidigeTram = tram;
    ENSURE(getTramInStation() == tram, "Bij setTramInStation van Station postconditie fout");
}

void Station::removeTramVanStation() {
    REQUIRE(this->properlyInitialised(), "Station bij removeTramVanStation niet correct geïnitialiseerd");
    REQUIRE(this->tramInStation(), "Bij removeTramVanStation van Station was er geen tram aanwezig");
    huidigeTram = 0;
    ENSURE(!this->tramInStation(), "Bij removeTramVanStation van Station was het niet correct uitgevoerd");
}

bool Station::properlyInitialised() {
    return initCheck == this;
}

Station::Station() : initCheck(), volgende(), vorige(), huidigeTram(), spoorNr() {
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Station bij constructor niet correct geïnitialiseerd");
}

bool Station::tramInStation() {
    REQUIRE(this->properlyInitialised(), "Station bij tramInStation niet correct geïnitialiseerd");
    return huidigeTram != 0;
}





