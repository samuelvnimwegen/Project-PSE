//
// Created by Samuel on 05/05/2023.
//

#include "Halte.h"

Halte::Halte(const string &naam, const int &spoornummer) : Station(naam, spoornummer) {
    setTypeString("Halte");
}
