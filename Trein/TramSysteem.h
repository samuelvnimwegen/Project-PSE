//
// Created by Space Movie 1992 on 02/03/2023.
//
#include "Tram.h"
#include "Station.h"
#include "XML/tinyxml.h"
#include "vector"
#ifndef TREIN_TRAMSYSTEEM_H
#define TREIN_TRAMSYSTEEM_H


// Hier komt het systeem: hier zitten beide classes tram en station in.
// Of zelf waarden heeft, nog te zien.
class TramSysteem {
    vector<Station> stations;
    vector<Tram> trams;
public:
    static void openFile();
    TramSysteem();
};


#endif //TREIN_TRAMSYSTEEM_H
