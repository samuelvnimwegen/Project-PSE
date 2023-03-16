//
// Created by Space Movie 1992 on 02/03/2023.
//
#ifndef TREIN_TRAMSYSTEEM_H
#define TREIN_TRAMSYSTEEM_H
#include "Tram.h"
#include "Station.h"
#include "XML/tinyxml.h"
#include "vector"
#include "gtest/include/gtest/gtest.h"
#define nullptr 0


// Hier komt het systeem: hier zitten beide classes tram en station in.
// Of zelf waarden heeft, nog te zien.
class TramSysteem {
    vector<Station*> stations;
    vector<Tram*> trams;
public:
    bool add_station(Station* station);
    void openFile();
    TramSysteem();

    void addTram(Tram*);

    vector<Station *> &getStations();

    void setStations(const vector<Station *> &stations);

    const vector<Tram *> &getTrams() const;

    void setTrams(const vector<Tram *> &trams);


};


#endif //TREIN_TRAMSYSTEEM_H
