//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "Tram.h"
#include "TramSysteemOut.h"

int Tram::getLijnNr() const {
    REQUIRE(lijnNr != 0 , "Bij getLijnNr van tram was de input 0");
    return lijnNr;

}

void Tram::setLijnNr(int nr) {
    REQUIRE(lijnNr != 0, "Bij setLijnNr van huidigStation was de naam leeg");
    Tram::lijnNr = nr;
    ENSURE(lijnNr = nr, "Bij setLijnNr van huidigStation was het nummer niet correct aangepast");

}

Station *Tram::getBeginStation() const {
    REQUIRE(beginStation != 0 , "Bij beginStation van tram was de naam leeg");
    return beginStation;
}

void Tram::setBeginStation(Station *stat) {
    REQUIRE(stat != 0, "bij setBeginStatino van Tram was er geen geldige pointer gegeven.");
    Tram::beginStation = stat;
    // Als de tram nog niet bij een huidigStation staat, wordt deze op het beginstation gezet.
    if (Tram::huidigStation == 0){
        setHuidigStation(stat);
    }
    ENSURE(huidigStation == stat, "Bij setBeginStation van Tram de aanpassing niet correct doorgevoerd.");
}

double Tram::getSnelheid() const {
    return snelheid;
}

void Tram::setSnelheid(double snelh) {
    Tram::snelheid = snelh;
}

Tram::Tram() {
    beginStation = 0;
    huidigStation = 0;
    snelheid = -1;
    lijnNr = -1;
}

Station *Tram::getHuidigStation() const {
    REQUIRE(huidigStation != 0 , "Bij getHuidigStation van tram was de input 0");
    return huidigStation;
}

void Tram::setHuidigStation(Station *stat) {
    REQUIRE(stat != 0, "Bij setHuidigStation tram was de input 0");
    // In deze functie wordt de huidige tram van het station ook aangepast.
    if(huidigStation != 0){
        huidigStation->removeTramVanStation();
    }

    Tram::huidigStation = stat;
    stat->addTramAanStation(this);
    ENSURE(huidigStation = stat, "Bij setHuidigStation van tram is het niet correct uitgevoerd");
}

int Tram::getVoertuigNummer() const {
    REQUIRE(voertuigNummer >= 0 , "Bij getVoertuigNummer van tram was de input 0");
    return voertuigNummer;
}

void Tram::setVoertuigNummer(int nr) {
    REQUIRE(nr > 0, "Bij setVoertuigNummer het nummer <= 0");
    Tram::voertuigNummer = nr;
    ENSURE(voertuigNummer = nr, "Bij setVoertuigNummer van tram was het nummer niet correct aangepast" );
}

const string &Tram::getTypeString() const {
    REQUIRE(!typeString.empty() , "Bij getType van tram was de input 0");
    return typeString;
}

void Tram::setTypeString(const string &tp) {
    REQUIRE(!tp.empty() , "Bij getType van tram was de input 0");
    typeString = tp;
    ENSURE(typeString == tp ,"Bij getType van tram is het niet correct uitgevoerd" );
}

Tram::~Tram() {

}

void Tram::moveNaarVolgende(TramSysteemOut* tramSysteemOut) {
        REQUIRE(lijnNr == huidigStation->getSpoorNr(), "Bij moveNaarVolgende van Tram zijn tram en huidigStation niet op zelfde lijn");
        REQUIRE(huidigStation != huidigStation->getVolgende(), "Bij moveNaarVolgende van Tram zijn beginstation en eindstation hetzelfde");
        Station* vorige = huidigStation;

        // Als het volgende station bezet is En als deze kapot is:
        bool volgendeBezet = false;
        if (huidigStation->getVolgende()->getTramInStation() != 0){
            if( huidigStation->getVolgende()->getTramInStation()->isKapot()){
                volgendeBezet = true;
            }
        }

        // Als de tram zelf niet kapot is en de volgende plaats vrij is kan deze bewegen:
        if (!isKapot() and !volgendeBezet){
            setHuidigStation(huidigStation->getVolgende());
            tramSysteemOut->move(this, vorige, huidigStation);
        }
        // Als ze kapot is, moet ze herstellen
        else if (isKapot()){
            tramSysteemOut->herstel(this, huidigStation);
        }

        // Als ze kan bewegen en de volgende bezet is is er een botsing.
        else if (volgendeBezet and !isKapot()){
            tramSysteemOut->botsing(this, huidigStation->getVolgende()->getTramInStation());
        }

        ENSURE(!(volgendeBezet and !isKapot()), "Bij moveNaarVolgende van Tram was het volgende station bezet op de lijn wat in een botsing resulteert.");
}

bool Tram::isKapot() {
    return false;
}

