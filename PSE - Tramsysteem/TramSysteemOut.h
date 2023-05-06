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

    void station_summary();

    void complete_summary();

    void advanced_summary();

    void move(Tram* tram, Station* begin, Station* eind);



};


#endif //TRAMSYSTEEM_CPP_TRAMSYSTEEMOUT_H
