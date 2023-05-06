//
// Created by Samuel on 05/05/2023.
//

#include "Stadslijner.h"

Stadslijner::Stadslijner() {
    setSnelheid(70);
    setTypeString("Stadslijner");
}

bool Stadslijner::kanNaar(Station * stat) {
    REQUIRE(stat != 0, "Bij kanNaar van Stadslijner was de input 0.");
    return (stat->getTypeString() == "Metrostation");
}
