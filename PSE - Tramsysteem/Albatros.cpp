//
// Created by Samuel on 05/05/2023.
//

#include "Albatros.h"

Albatros::Albatros() {
    setSnelheid(70);
    setTypeString("Albatros");
}

bool Albatros::kanNaar(Station *stat) {
    REQUIRE(stat != 0, "Bij kanNaar van Albatros was de input 0.");
    return (stat->getTypeString() == "metrostation");
}
