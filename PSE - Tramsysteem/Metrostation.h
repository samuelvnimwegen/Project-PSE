//
// Created by Samuel on 05/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_METROSTATION_H
#define TRAMSYSTEEM_CPP_METROSTATION_H
#include "Station.h"

class Metrostation: public Station{
public:
    Metrostation(const string &naam, Station *volgende, Station *vorige, int spoorNr);

    Metrostation();
};


#endif //TRAMSYSTEEM_CPP_METROSTATION_H
