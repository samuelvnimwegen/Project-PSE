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
    REQUIRE(!naam.empty(), "Bij getNaam van station was de naam leeg");
    return naam;
}

void Station::setNaam(const string &nm) {
    REQUIRE(!nm.empty(), "Bij setNaam van station was de naam leeg");
    Station::naam = nm;
    ENSURE(naam == nm, "Bij setNaam van station was de naam niet correct aangepast");
}

Station *Station::getVolgende() const {
    REQUIRE(volgende != 0 , "Bij getVolgende van station was de input 0");
    return volgende;
}

void Station::setVolgende(Station *vlgd) {
    REQUIRE(vlgd != 0, "Bij setVolgende van station was de input 0");
    Station::volgende = vlgd;
    ENSURE(volgende == vlgd, "Bij setVolgende van station is het niet correct uitgevoerd");
}

Station *Station::getVorige() const {
    REQUIRE (vorige != 0,"Bij getVorige van station was de input 0");
    return vorige;
}

void Station::setVorige(Station *vrg) {
    REQUIRE(vrg != 0, "Bij setVorige van station was de input 0");
    Station::vorige = vrg;
    ENSURE(vorige == vrg, "Bij setVorige van station is het niet correct uitgevoerd");

}

int Station::getSpoorNr() const {
    REQUIRE(spoorNr !=0, "Bij getSpoorNr van station was de naam leeg");
    return spoorNr;
}

void Station::setSpoorNr(int nr) {
    REQUIRE(spoorNr != 0, "Bij setSpoorNr van station was de naam leeg");
    Station::spoorNr = nr;
    ENSURE(spoorNr = nr, "Bij setSpoorNr van station was het nummer niet correct aangepast");
}

const string &Station::getType() const {
    REQUIRE(!type.empty() , "Bij getType van station was de naam leeg");
    return type;
}

void Station::setType(const string &tp) {
    REQUIRE(!tp.empty(), "Bij setType van station was de naam leeg");
    Station::type = tp;
    ENSURE(type == tp, "Bij setType van station was de naam niet correct aangepast");
}
