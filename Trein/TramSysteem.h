//
// Created by Space Movie 1992 on 02/03/2023.
//
#ifndef TREIN_TRAMSYSTEEM_H
#define TREIN_TRAMSYSTEEM_H
#include "Tram.h"
#include "Station.h"
#include "XML/tinyxml.h"
#include "vector"



// Hier komt het systeem: hier zitten beide classes tram en station in.
// Of zelf waarden heeft, nog te zien.
class TramSysteem {
    vector<Station*> stations;
    vector<Tram*> trams;
public:
    static bool add_station(Station* station);
    static void openFile();
    TramSysteem();

    static const vector<Station *> &getStations();

    void setStations(const vector<Station *> &stations);

    const vector<Tram *> &getTrams() const;

    void setTrams(const vector<Tram *> &trams);
};


#endif //TREIN_TRAMSYSTEEM_H
