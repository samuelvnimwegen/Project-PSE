//
// Created by Samuel on 05/05/2023.
//

#include "Metrostation.h"

Metrostation::Metrostation() {}

Metrostation::Metrostation(const string &naam, Station *volgende, Station *vorige, int spoorNr) : Station(naam,
                                                                                                          volgende,
                                                                                                          vorige,
                                                                                                          spoorNr) {}
