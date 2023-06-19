//
// Created by Samuel on 05/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_STADSLIJNER_H
#include "Tram.h"
#define TRAMSYSTEEM_CPP_STADSLIJNER_H


class Stadslijner: public Tram{
public:
    Stadslijner(const int &voertuigNr, const int &lijnNr);
    /*
     * Constructor voor de stadslijner
     *
     * REQUIRE(voertuigNr > 0, "Bij de constructor van Stadslijner was het voertuigNummer <= 0");
     * REQUIRE(lijnNr > 0, "Bij de constructor van Stadslijner was het lijnNummer <= 0");
     */

    bool kanNaarType(Station *);
    /**
     * REQUIRE(stat != 0, "Bij kanNaarType van Stadslijner was de input 0.");
     */
};


#endif //TRAMSYSTEEM_CPP_STADSLIJNER_H
