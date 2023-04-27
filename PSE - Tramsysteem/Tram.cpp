//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "Tram.h"

int Tram::getLijnNr() const {
    return lijnNr;
}

void Tram::setLijnNr(int nr) {
    Tram::lijnNr = nr;
}

Station *Tram::getBeginStation() const {
    return beginStation;
}

void Tram::setBeginStation(Station *stat) {
    Tram::beginStation = stat;
    // Als de tram nog niet bij een station staat, wordt deze op het beginstation gezet.
    if (Tram::station == 0){
        Tram::station = stat;
    }
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
    return station;
}

void Tram::setStation(Station *stat) {
    Tram::station = stat;
}

int Tram::getVoertuigNummer() const {
    return voertuigNummer;
}

void Tram::setVoertuigNummer(int voertuigNummer) {
    Tram::voertuigNummer = voertuigNummer;
}

double Tram::getReparatieKosten() const {
    return reparatieKosten;
}

void Tram::setReparatieKosten(double reparatieKosten) {
    Tram::reparatieKosten = reparatieKosten;
}

const string &Tram::getType() const {
    return type;
}

void Tram::setType(const string &type) {
    Tram::type = type;
}
