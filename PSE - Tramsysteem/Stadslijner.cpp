//
// Created by Samuel on 05/05/2023.
//

#include "Stadslijner.h"

bool Stadslijner::kanNaarType(Station * stat) {
    REQUIRE(stat != 0, "Bij kanNaarType van Stadslijner was de input 0.");
    return (stat->getTypeString() == "Metrostation");
}

Stadslijner::Stadslijner(const int &voertuigNr, const int &lijnNr) : Tram(voertuigNr, lijnNr) {
    REQUIRE(voertuigNr > 0, "Bij de constructor van Stadslijner was het voertuigNummer <= 0");
    REQUIRE(lijnNr > 0, "Bij de constructor van Stadslijner was het lijnNummer <= 0");
    setSnelheid(70);
    setTypeString("Stadslijner");
    setVoertuigNummer(voertuigNr);
    setLijnNr(lijnNr);
}
