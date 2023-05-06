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
