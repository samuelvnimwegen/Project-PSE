//
// Created by Samuel on 05/05/2023.
//

#include "PCC.h"

PCC::PCC() : aantalDefecten(), reparatieTijd(), reparatieKost(), kapot(), counter(), resterendeKosten(), totaleKosten() {
    setSnelheid(40);
    setTypeString("PCC");
    initCheck = this;
    ENSURE(this->properlyInitiated(), "PCC bij constructor niet correct geïnitieerd");
}

bool PCC::kanNaarType(Station * stat) {
    REQUIRE(this->properlyInitiated(), "PCC bij kanNaarType niet correct geïnitieerd");
    REQUIRE(stat != 0, "Bij kanNaarType van PCC was de input 0.");
    return true;
}

int PCC::getAantalDefecten() {
    REQUIRE(this->properlyInitiated(), "PCC bij getAantalDefecten niet correct geïnitieerd");
    int result = aantalDefecten;
    ENSURE(result >= 0, "Bij getAantalDefecten van PCC is het aantal defecten < 0");
    return result;
}

void PCC::setAantalDefecten(int defecten) {
    REQUIRE(this->properlyInitiated(), "PCC bij setAantalDefecten niet correct geïnitieerd");
    REQUIRE(defecten >= 0, "Bij setAantalDefecten van PCC is het aantal defecten < 0");
    aantalDefecten = defecten;
    counter = defecten;
    ENSURE(this->getAantalDefecten() == defecten, "Bij setAantalDefecten van PCC postconditie fout");
}

int PCC::getReparatieTijd() {
    REQUIRE(this->properlyInitiated(), "PCC bij getReparatieTijd niet correct geïnitieerd");
    int result = reparatieTijd;
    REQUIRE(result >= 0, "Bij getReparatieTijd van PCC postconditie fout");
    return result;
}

void PCC::setReparatieTijd(int tijd) {
    REQUIRE(this->properlyInitiated(), "PCC bij setReparatieTijd niet correct geïnitieerd");
    REQUIRE(tijd >= 0, "Bij setReparatieTijd van PCC is de tijd < 0");
    PCC::reparatieTijd = tijd;
    ENSURE(this->getReparatieTijd() == tijd, "Bij setReparatieTijd van PCC is het niet correct uitgevoerd.");
}

int PCC::getReparatieKost() {
    REQUIRE(this->properlyInitiated(), "PCC bij getReparatieKost niet correct geïnitieerd");
    int result = reparatieKost;
    ENSURE(result >= 0, "Bij getReparatieKost van PCC postconditie error");
    return result;
}

void PCC::setReparatieKost(int kost) {
    REQUIRE(this->properlyInitiated(), "PCC bij setReparatieKost niet correct geïnitieerd");
    REQUIRE(kost >= 0, "Bij setReparatieKost van PCC is de kost < 0");
    reparatieKost = kost;
    ENSURE(this->getReparatieKost() == kost, "Bij setReparatieKost van PCC is het niet correct uitgevoerd.");
}

bool PCC::isKapot() {
    REQUIRE(this->properlyInitiated(), "PCC bij isKapot niet correct geïnitieerd");
    return kapot;
}

void PCC::moveNaarVolgende(TramSysteemOut *tramSysteemOut) {
    REQUIRE(this->properlyInitiated(), "PCC bij moveNaarVolgende niet correct geïnitieerd");
    REQUIRE(tramSysteemOut != 0, "Bij moveNaarVolgende van PCC was tramSysteemOut == 0");
    Tram::moveNaarVolgende(tramSysteemOut);
    // Counter aanpassen:
    counter -= 1;
    // Als de counter 0 is:
    if (counter == 0){
        // Als hij kapot is: dan is hij nu hersteld.
        if (kapot){
            kapot = false;
            counter = aantalDefecten;
            totaleKosten += resterendeKosten;
            resterendeKosten = 0;
        }
        // Als hij niet kapot is: dan is hij nu kapot
        else{
            kapot = true;
            counter = reparatieTijd;
            resterendeKosten = reparatieKost;
        }
    }
    // Als hij kapot is en de counter niet 0 is: gedeeltelijk de reparatiekosten er al vanaf halen.
    else if (kapot){
        resterendeKosten -= reparatieKost / reparatieTijd;
        totaleKosten += reparatieKost / reparatieTijd;
    }
}

void PCC::setKapot(bool status) {
    REQUIRE(this->properlyInitiated(), "PCC bij setKapot niet correct geïnitieerd");
    PCC::kapot = status;
    ENSURE(this->isKapot() == status, "Bij setKapot van PCC postconditie error");
}

int PCC::getResterendeKosten() {
    REQUIRE(this->properlyInitiated(), "PCC bij getResterendeKosten niet correct geïnitieerd");
    int result = resterendeKosten;
    ENSURE(result >= 0, "Bij getResterendeKosten van PCC postconditie fout");
    return result;
}

int PCC::getTotaleKosten() {
    REQUIRE(this->properlyInitiated(), "PCC bij getTotaleKosten niet correct geïnitieerd");
    int result = totaleKosten;
    ENSURE(result >= 0, "Bij getTotaleKosten van PCC postconditie fout");
    return result;
}

void PCC::setResterendeKosten(int resterend) {
    REQUIRE(this->properlyInitiated(), "PCC bij setResterendeKosten niet correct geïnitieerd");
    REQUIRE(resterend >= 0, "Bij setResterendeKosten van PCC was dit < 0");
    PCC::resterendeKosten = resterend;
    ENSURE(this->getResterendeKosten() == resterend, "Bij setResterendeKosten van PCC postconditie fout");
}

void PCC::setTotaleKosten(int totaal) {
    REQUIRE(this->properlyInitiated(), "PCC bij setTotaleKosten niet correct geïnitieerd");
    REQUIRE(totaal >= 0, "Bij setTotaleKosten van PCC was dit < 0");
    totaleKosten = totaal;
    ENSURE(this->getTotaleKosten() == totaal, "Bij setTotaleKosten van PCC postconditie fout");
}

bool PCC::properlyInitiated() {
    return initCheck == this;
}
