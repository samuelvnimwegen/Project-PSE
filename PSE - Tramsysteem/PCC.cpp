//
// Created by Samuel on 05/05/2023.
//

#include "PCC.h"

PCC::PCC() {
    setSnelheid(40);
    setTypeString("PCC");
}

bool PCC::kanNaar(Station * stat) {
    REQUIRE(stat != 0, "Bij kanNaar van PCC was de input 0.");
    return true;
}

int PCC::getAantalDefecten() const {
    REQUIRE(aantalDefecten >= 0, "Bij getAantalDefecten van PCC is het aantal defecten < 0");
    return aantalDefecten;
}

void PCC::setAantalDefecten(int defecten) {
    REQUIRE(defecten >= 0, "Bij setAantalDefecten van PCC is het aantal defecten < 0");
    PCC::aantalDefecten = defecten;
    counter = defecten;
    ENSURE(aantalDefecten == defecten, "Bij setAantalDefecten van PCC is het niet correct uitgevoerd.");
}

int PCC::getReparatieTijd() const {
    REQUIRE(reparatieTijd >= 0, "Bij getReparatieTijd van PCC is de reparatieTijd < 0");
    return reparatieTijd;
}

void PCC::setReparatieTijd(int tijd) {
    REQUIRE(tijd >= 0, "Bij setReparatieTijd van PCC is de tijd < 0");
    PCC::reparatieTijd = tijd;
    ENSURE(reparatieTijd == tijd, "Bij setReparatieTijd van PCC is het niet correct uitgevoerd.");
}

int PCC::getReparatieKost() const {
    REQUIRE(reparatieTijd >= 0, "Bij getReparatieKost van PCC is de reparatieKost < 0");
    return reparatieKost;
}

void PCC::setReparatieKost(int kost) {
    REQUIRE(kost >= 0, "Bij setReparatieKost van PCC is de kost < 0");
    PCC::reparatieKost = kost;
    ENSURE(reparatieKost == kost, "Bij setReparatieKost van PCC is het niet correct uitgevoerd.");
}

bool PCC::isKapot() {
    return kapot;
}

void PCC::moveNaarVolgende(TramSysteemOut *tramSysteemOut) {
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
    PCC::kapot = status;
    ENSURE(kapot == status, "Bij setKapot van PCC was het fout uitgevoerd");
}

void PCC::setCounter(int count) {
    REQUIRE(count >= 0, "Bij setCounter van PCC was de counter kleiner dan 0");
    PCC::counter = count;
    ENSURE(counter == count, "Bij setCounter van PCC was het fout uitgevoerd");
}

int PCC::getResterendeKosten() const {
    REQUIRE(resterendeKosten >= 0, "Bij getResterendeKosten van PCC waren de resterendeKosten kleiner dan 0");
    return resterendeKosten;
}

int PCC::getTotaleKosten() const {
    REQUIRE(resterendeKosten >= 0, "Bij getTotaleKosten van PCC waren de totaleKosten kleiner dan 0");
    return totaleKosten;
}

void PCC::setResterendeKosten(int resterend) {
    REQUIRE(resterend >= 0, "Bij setResterendeKosten van PCC was dit < 0");
    PCC::resterendeKosten = resterend;
    ENSURE(resterendeKosten == resterend, "ij setResterendeKosten van PCC was dit niet correct uitgevoerd");
}

void PCC::setTotaleKosten(int totaal) {
    REQUIRE(totaal >= 0, "Bij setTotaleKosten van PCC was dit < 0");
    PCC::totaleKosten = totaal;
}
