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
    /**
     * REQUIRE(lijnnummer >= 0, "Bij getLijnnummer van Lijn was dit < 0");
     */

    const vector<Station *> &getStations() const;
    /**
     * REQUIRE(!stations.empty(), "Bij getStations van Lijn was deze vector leeg");
     */
    const vector<Tram *> &getTrams() const;
    /**
     * REQUIRE(!stations.empty(), "Bij getTrams van Lijn was deze vector leeg");
     */

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
