//
// Created by Samuel on 05/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_HALTE_H
#define TRAMSYSTEEM_CPP_HALTE_H
#include "Station.h"

class Halte : public Station{
public:
    Halte(const string &naam, const int &spoornummer);
};


#endif //TRAMSYSTEEM_CPP_HALTE_H
