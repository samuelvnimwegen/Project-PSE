//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "Tram.h"
#include "TramSysteemOut.h"
#include "PCC.h"
int Tram::getLijnNr() {
    REQUIRE(this->properlyInitialised(), "Tram bij getLijnNr niet correct geïnitieerd");
    int result = lijnNr;
    ENSURE(result >= 0, "Bij getLijnNr van PCC postconditie fout");
    return result;


}

void Tram::setLijnNr(int nr) {
    REQUIRE(this->properlyInitialised(), "Tram bij setLijnNr niet correct geïnitieerd");
    REQUIRE(nr >= 0, "Bij setLijnNr van Tram was de input <= 0");
    lijnNr = nr;
    ENSURE(getLijnNr() == nr, "Bij setLijnNr van Tram postconditie fout");
}

Station * Tram::getBeginStation() {
    REQUIRE(this->properlyInitialised(), "Tram bij getBeginStation niet correct geïnitieerd");
    Station* result = beginStation;
    ENSURE(result != 0 , "Bij getBeginStation van Tram was er geen beginstation");
    return result;
}

void Tram::setBeginStation(Station *stat) {
    REQUIRE(this->properlyInitialised(), "Tram bij setBeginStation niet correct geïnitieerd");
    REQUIRE(stat != 0, "bij setBeginStation van Tram was de input 0");
    beginStation = stat;
    // Als de tram nog niet bij een huidigStation staat, wordt deze op het beginstation gezet.
    if (Tram::huidigStation == 0){
        setHuidigStation(stat);
    }
    ENSURE(this->getHuidigStation() == stat, "Bij setBeginStation van Tram postconditie fout");
}

double Tram::getSnelheid() {
    REQUIRE(this->properlyInitialised(), "Tram bij getSnelheid niet correct geïnitieerd");
    double result = snelheid;
    ENSURE(result >= 0, "Bij getSnelheid van Tram was de snelheid < 0");
    return result;
}

void Tram::setSnelheid(double speed) {
    REQUIRE(this->properlyInitialised(), "Tram bij setSnelheid niet correct geïnitieerd");
    REQUIRE(speed >= 0, "Bij setSnelheid van Tram was de snelheid < 0");
    snelheid = speed;
    ENSURE(this->getSnelheid() == speed, "Bij setSnelheid van Tram postconditie fout");
}

Tram::Tram() : voertuigNummer() {
    beginStation = 0;
    huidigStation = 0;
    snelheid = -1;
    lijnNr = -1;
    initCheck = this;
    ENSURE(this->properlyInitialised(), "Tram bij constructor niet correct geïnitieerd");
}

Station * Tram::getHuidigStation() {
    REQUIRE(this->properlyInitialised(), "Tram bij getHuidigStation niet correct geïnitieerd");
    Station* result = huidigStation;
    ENSURE(result != 0 , "Bij getHuidigStation van Tram postconditie fout");
    return result;
}

void Tram::setHuidigStation(Station *stat) {
    REQUIRE(this->properlyInitialised(), "Tram bij setHuidigStation niet correct geïnitieerd");
    REQUIRE(stat != 0, "Bij setHuidigStation Tram was de input 0");

    // In deze functie wordt de huidige tram van het station ook aangepast.
    if(huidigStation and huidigStation->tramInStation()){
        huidigStation->removeTramVanStation();
    }

    Tram::huidigStation = stat;
    stat->setTramInStation(this);
    ENSURE(this->getHuidigStation() == stat, "Bij setHuidigStation van Tram postconditie fout");
}

int Tram::getVoertuigNummer() {
    REQUIRE(this->properlyInitialised(), "Tram bij getVoertuigNummer niet correct geïnitieerd");
    int result = voertuigNummer;
    ENSURE(result >= 0 , "Bij getVoertuigNummer van Tram postconditie fout");
    return result;
}

void Tram::setVoertuigNummer(int nr) {
    REQUIRE(this->properlyInitialised(), "Tram bij setVoertuigNummer niet correct geïnitieerd");
    REQUIRE(nr > 0, "Bij setVoertuigNummer van Tram is de input <= 0");
    Tram::voertuigNummer = nr;
    ENSURE(this->getVoertuigNummer() == nr, "Bij setVoertuigNummer van Tram postconditie fout" );
}

string Tram::getTypeString(){
    REQUIRE(this->properlyInitialised(), "Tram bij getTypeString niet correct geïnitieerd");
    string result = typeString;
    ENSURE(!result.empty(), "Bij getTypeString van Tram was de typeString leeg.");
    return result;
}

void Tram::setTypeString(const string &tp) {
    REQUIRE(this->properlyInitialised(), "Tram bij setTypeString niet correct geïnitieerd");
    REQUIRE(!tp.empty(), "Bij setTypeString van Tram was de input leeg");
    typeString = tp;
    ENSURE(this->getTypeString() == tp ,"Bij setTypeString van Tram postconditie fout");
}

Tram::~Tram() {

}

void Tram::moveNaarVolgende(TramSysteemOut* tramSysteemOut) {
        REQUIRE(this->properlyInitialised(), "Tram bij moveNaarVolgende niet correct geïnitieerd");
        REQUIRE(this->getLijnNr() == this->getHuidigStation()->getSpoorNr(), "Bij moveNaarVolgende van Tram zijn tram en huidigStation niet op zelfde lijn");
        REQUIRE(this->getHuidigStation() != this->getHuidigStation()->getVolgende(), "Bij moveNaarVolgende van Tram zijn beginstation en eindstation hetzelfde");
        Station* vorige = huidigStation;

        // Checkt of de tram zelf kapot is:
        bool kapot = false;
        if (getTypeString() == "PCC"){
            PCC* pccTram = dynamic_cast<PCC*>(this);
            kapot = pccTram->isKapot();
        }

        // Als het volgende station bezet is En als deze kapot is:
        bool volgendeBezet = false;
        if (huidigStation->getVolgende()->tramInStation() and huidigStation->getVolgende()->getTramInStation()->typeString == "PCC"){
            Tram* tram = huidigStation->getVolgende()->getTramInStation();
            PCC* pccTram = dynamic_cast<PCC*>(tram);
            if (pccTram->isKapot()){
                volgendeBezet = true;
            }
        }

        // Als de tram zelf niet kapot is en de volgende plaats vrij is kan deze bewegen:
        if (!kapot and !volgendeBezet){
            while (!this->kanNaarType(this->getHuidigStation()->getVolgende())){
                setHuidigStation(getHuidigStation()->getVolgende());
            }
            setHuidigStation(getHuidigStation()->getVolgende());
            tramSysteemOut->move(this, vorige, huidigStation);
        }
        // Als ze kapot is, moet ze herstellen
        else if (kapot){
            tramSysteemOut->herstel(this, huidigStation);
        }

        // Als ze kan bewegen en de volgende bezet is is er een botsing.
        else {
            tramSysteemOut->wachten(this, huidigStation->getVolgende()->getTramInStation());
        }

}

bool Tram::properlyInitialised() {
    return initCheck == this;
}

