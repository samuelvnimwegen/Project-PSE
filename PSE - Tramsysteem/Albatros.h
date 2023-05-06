//
// Created by Samuel on 05/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_ALBATROS_H
#include "Tram.h"
#define TRAMSYSTEEM_CPP_ALBATROS_H


class Albatros: public Tram{
public:
    Albatros();
    bool kanNaar(Station * stat);
    /**
     * REQUIRE(stat != 0, "Bij kanNaar van Albatros was de input 0.");
     */
};


#endif //TRAMSYSTEEM_CPP_ALBATROS_H
