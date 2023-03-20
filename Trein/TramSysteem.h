//
// Created by Space Movie 1992 on 02/03/2023.
//
#ifndef TREIN_TRAMSYSTEEM_H
#define TREIN_TRAMSYSTEEM_H
#include "Tram.h"
#include "Station.h"
#include "XML/tinyxml.h"
#include "vector"
#include "sstream"
#include "fstream"



class TramSysteem {
    vector<Station*> stations;
    vector<Tram*> trams;
    string filename;
public:
    bool add_station(Station* station);

    bool readFile(const string &name);

    TramSysteem();

    void addTram(Tram*);

    vector<Station *> &getStations();

    void setStations(const vector<Station *> &stations);

    const vector<Tram *> &getTrams() const;

    void setTrams(const vector<Tram *> &trams);

    void makeTxtFile(const string& name);

    bool move(Tram*, Station*);

    bool simulate(int tijd);

    bool complete_summary();

    bool tram_summary();

    bool station_summary();
};


#endif //TREIN_TRAMSYSTEEM_H
