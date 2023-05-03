//
// Created by Samuel on 24/03/2023.
//

#ifndef TRAMSYSTEEM_CPP_TRAMSYSTEEMOUT_H
#define TRAMSYSTEEM_CPP_TRAMSYSTEEMOUT_H
#include "iostream"
#include "DesignByContract.h"
#include "fstream"
#include "ostream"


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

};


#endif //TRAMSYSTEEM_CPP_TRAMSYSTEEMOUT_H
