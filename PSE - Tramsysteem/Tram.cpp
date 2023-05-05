//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "Tram.h"

int Tram::getLijnNr() const {
    REQUIRE(lijnNr != 0 , "Bij getLijnNr van tram was de input 0");
    return lijnNr;

}

void Tram::setLijnNr(int nr) {
    REQUIRE(lijnNr != 0, "Bij setLijnNr van station was de naam leeg");
    Tram::lijnNr = nr;
    ENSURE(lijnNr = nr, "Bij setLijnNr van station was het nummer niet correct aangepast");

}

Station *Tram::getBeginStation() const {
    REQUIRE(beginStation != 0 , "Bij beginStation van tram was de naam leeg");
    return beginStation;
}

void Tram::setBeginStation(Station *stat) {
    REQUIRE();
    Tram::beginStation = stat;
    // Als de tram nog niet bij een station staat, wordt deze op het beginstation gezet.
    if (Tram::station == 0){
        Tram::station = stat;
    }
    ENSURE();
}

double Tram::getSnelheid() const {
    return snelheid;
}

void Tram::setSnelheid(double snelh) {
    Tram::snelheid = snelh;
}

Tram::Tram() {
    beginStation = 0;
    station = 0;
    snelheid = -1;
    lijnNr = -1;
}

Station *Tram::getStation() const {
    REQUIRE(station != 0 , "Bij getStation van tram was de input 0");
    return station;
}

void Tram::setStation(Station *stat) {
    REQUIRE(stat != 0, "Bij setStation tram was de input 0");
    Tram::station = stat;
    ENSURE(station = stat, "Bij setStation van tram is het niet correct uitgevoerd");
}

int Tram::getVoertuigNummer() const {
    REQUIRE(voertuigNummer != 0 , "Bij getVoertuigNummer van tram was de input 0");
    return voertuigNummer;
}

void Tram::setVoertuigNummer(int nr) {
    REQUIRE(voertuigNummer != 0, "Bij setVoertuigNummer van tram was de naam leeg");
    Tram::voertuigNummer = nr;
    ENSURE(voertuigNummer = nr, "Bij setVoertuigNummer van tram was het nummer niet correct aangepast" );
}

double Tram::getReparatieKosten() const {
    REQUIRE(reparatieKosten != 0 , "Bij getReparatieKosten van tram was de input 0");
    return reparatieKosten;
}

void Tram::setReparatieKosten(double rk) {
    Tram::reparatieKosten = rk;
}

const string &Tram::getType() const {
    REQUIRE(!type.empty() , "Bij getType van tram was de input 0");
    return type;
}

void Tram::setType(const string &tp) {
    REQUIRE(!type.empty() , "Bij getType van tram was de input 0");
    Tram::type = tp;
    ENSURE(type == tp ,"Bij getType van tram is het niet correct uitgevoerd" );

}
