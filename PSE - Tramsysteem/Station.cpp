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
    REQUIRE(!naam.empty(), "Bij getNaam van huidigStation was de naam leeg");
    return naam;
}

void Station::setNaam(const string &nm) {
    REQUIRE(!nm.empty(), "Bij setNaam van huidigStation was de naam leeg");
    Station::naam = nm;
    ENSURE(naam == nm, "Bij setNaam van huidigStation was de naam niet correct aangepast");
}

Station *Station::getVolgende() const {
    REQUIRE(volgende != 0 , "Bij getVolgende van huidigStation was de input 0");
    return volgende;
}

void Station::setVolgende(Station *vlgd) {
    REQUIRE(vlgd != 0, "Bij setVolgende van huidigStation was de input 0");
    Station::volgende = vlgd;
    ENSURE(volgende == vlgd, "Bij setVolgende van huidigStation is het niet correct uitgevoerd");
}

Station *Station::getVorige() const {
    REQUIRE (vorige != 0,"Bij getVorige van huidigStation was de input 0");
    return vorige;
}

void Station::setVorige(Station *vrg) {
    REQUIRE(vrg != 0, "Bij setVorige van huidigStation was de input 0");
    Station::vorige = vrg;
    ENSURE(vorige == vrg, "Bij setVorige van huidigStation is het niet correct uitgevoerd");

}

int Station::getSpoorNr() const {
    REQUIRE(spoorNr !=0, "Bij getSpoorNr van huidigStation was de naam leeg");
    return spoorNr;
}

void Station::setSpoorNr(int nr) {
    REQUIRE(spoorNr != 0, "Bij setSpoorNr van huidigStation was de naam leeg");
    Station::spoorNr = nr;
    ENSURE(spoorNr = nr, "Bij setSpoorNr van huidigStation was het nummer niet correct aangepast");
}

const string &Station::getTypeString() const {
    REQUIRE(!typeString.empty(), "Bij getTypeString van Station was de string leeg");
    return typeString;
}

void Station::setTypeString(const string &tpString) {
    REQUIRE(!tpString.empty(), "Bij setTypeString van Station was de string leeg");
    Station::typeString = tpString;
    ENSURE(typeString == tpString, "Bij setTypeString van Station is de wijziging niet correct uitgevoerd.");
}

Tram *Station::getTramInStation() const {
    if (!tramInStation.empty()){
        return tramInStation[0];
    }
    else {
        return 0;
    }

}

void Station::addTramAanStation(Tram *tram) {
    REQUIRE(tram != 0, "Bij addTramAanStation van Station was de tram == 0");
    tramInStation.push_back(tram);
    ENSURE(tramInStation[0] == tram, "Bij addTramAanStation van Station was het niet correct uitgevoerd");
}

void Station::removeTramVanStation() {
    REQUIRE(!tramInStation.empty(), "Bij removeTramVanStation van Station was er geen tram aanwezig");
    tramInStation.clear();
    ENSURE(tramInStation.empty(), "Bij removeTramVanStation van Station was het niet correct uitgevoerd");
}





