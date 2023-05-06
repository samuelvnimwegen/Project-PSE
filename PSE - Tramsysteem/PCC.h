//
// Created by Samuel on 05/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_PCC_H
#include "Tram.h"
#define TRAMSYSTEEM_CPP_PCC_H


class PCC: public Tram{
public:
    PCC();

    bool kanNaar(Station*);
    /**
     * REQUIRE(stat != 0, "Bij kanNaar van PCC was de input 0.");
     */
};


#endif //TRAMSYSTEEM_CPP_PCC_H
