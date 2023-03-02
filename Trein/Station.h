//
// Created by Space Movie 1992 on 02/03/2023.
//
#include "iostream"
using namespace std;
#ifndef TREIN_STATION_H
#define TREIN_STATION_H


class Station {
public:
    string naam;
    Station* volgende;
    Station* vorige;
    int spoorNr;
};


#endif //TREIN_STATION_H
