//
// Created by Samuel on 24/03/2023.
//

#ifndef TRAMSYSTEEM_CPP_TRAMSYSTEEMOUT_H
#define TRAMSYSTEEM_CPP_TRAMSYSTEEMOUT_H
#include "iostream"
#include "DesignByContract.h"
#include "fstream"
#include "ostream"
#include "Station.h"
#include "Tram.h"

using namespace std;
class TramSysteem;
class TramSysteemOut {
    string filename;
    TramSysteem* tramSysteem;
public:
    explicit TramSysteemOut(const string &filename, TramSysteem* ts);
    /** REQUIRE(name.substr(name.length() - 4) == ".txt", "moet een .txt file zijn");
     *  ENSURE(file, "file moet aangemaakt zijn");
     */

    void tram_summary();
    /**
     * REQUIRE(!filename.empty(), "Bij tram_summary is er nog geen filenaam aangemaakt");
     */
    void station_summary();
    /**
     * REQUIRE(!filename.empty(), "Bij station_summary is er nog geen filenaam aangemaakt");
     */

    void complete_summary();
    /**
     *  REQUIRE(!filename.empty(), "Bij complete_summary is er nog geen filenaam aangemaakt");
     */

    void advanced_summary();
    /**
     *  REQUIRE(!filename.empty(), "Bij advanced_summary is er nog geen filenaam aangemaakt");
     */

    void move(Tram* tram, Station* begin, Station* eind);
    /**
     * REQUIRE(!filename.empty(), "Bij move is er nog geen filenaam aangemaakt");
     */

    void herstel(Tram* tram, Station* halte);
    /**
     * REQUIRE(!filename.empty(), "Bij herstel is er nog geen filenaam aangemaakt");
     */

    void botsing(Tram* tram1, Tram* tram2);
    /**
     * REQUIRE(!filename.empty(), "Bij botsing is er nog geen filenaam aangemaakt");
     */

};


#endif //TRAMSYSTEEM_CPP_TRAMSYSTEEMOUT_H
