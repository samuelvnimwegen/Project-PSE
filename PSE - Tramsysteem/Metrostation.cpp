//
// Created by Samuel on 05/05/2023.
//

#include "Metrostation.h"

Metrostation::Metrostation(const string &naam, const int &spoornummer) : Station(naam, spoornummer) {
    setTypeString("Metrostation");
}
