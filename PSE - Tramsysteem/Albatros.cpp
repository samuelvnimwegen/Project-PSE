//
// Created by Samuel on 05/05/2023.
//

#include "Albatros.h"

bool Albatros::kanNaarType(Station *stat) {
    REQUIRE(stat != 0, "Bij kanNaarType van Albatros was de input 0");
    return (stat->getTypeString() == "Metrostation");
}

Albatros::Albatros(const int &voertuigNr, const int &lijnNr) : Tram(voertuigNr, lijnNr) {
    REQUIRE(voertuigNr > 0, "Bij de constructor van Albatros was het voertuigNummer <= 0");
    REQUIRE(lijnNr > 0, "Bij de constructor van Albatros was het lijnNummer <= 0");
    setTypeString("Albatros");
    setSnelheid(70);
    setVoertuigNummer(voertuigNr);
    setLijnNr(lijnNr);
}
