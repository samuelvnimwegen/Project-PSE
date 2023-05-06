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
