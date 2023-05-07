//
// Created by Samuel on 06/05/2023.
//

#ifndef TRAMSYSTEEM_CPP_LIJN_H
#define TRAMSYSTEEM_CPP_LIJN_H
#include "Tram.h"
#include "Station.h"
#include "vector"

class Lijn {
    int lijnnummer;
    vector<Station*> stations;
    vector<Tram*> trams;
public:
    explicit Lijn(int lijnnummer);

    int getLijnnummer() const;

    void setLijnnummer(int ln);

    const vector<Station *> &getStations() const;

    void setStations(const vector<Station *> &stats);

    const vector<Tram *> &getTrams() const;

    void setTrams(const vector<Tram *> &trms);

    void addStation(Station* station);
    /**
     * REQUIRE(huidigStation != 0, "Bij addStation van Lijn was de pointer == 0");
     */

    void addTram(Tram* tram);
    /**
     * REQUIRE(tram != 0, "Bij addTram van Lijn was de pointer == 0");
     */
};


#endif //TRAMSYSTEEM_CPP_LIJN_H
