//
// Created by Samuel on 05/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_STADSLIJNER_H
#include "Tram.h"
#define TRAMSYSTEEM_CPP_STADSLIJNER_H


class Stadslijner: public Tram{
public:
    Stadslijner();

    bool kanNaar(Station *);
    /**
     * REQUIRE(stat != 0, "Bij kanNaar van Stadslijner was de input 0.");
     */
};


#endif //TRAMSYSTEEM_CPP_STADSLIJNER_H
