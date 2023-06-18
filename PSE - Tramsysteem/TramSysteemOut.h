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
    TramSysteemOut* initCheck;
    string filename;
    TramSysteem* tramSysteem;
public:
    explicit TramSysteemOut(const string &filename, TramSysteem* ts);
    /**
     * Generator van het outputSysteem.
     *
     * REQUIRE(name.substr(name.length() - 4) == ".txt", "Bij TramSysteemOut was het de filename geen .txt file");
     * REQUIRE(ts != 0, "Bij TramSysteemOut was het tramsysteem leeg");
     * ENSURE(this->properlyInitialized(), "TramSysteemOut bij TramSysteemOut() niet correct initialised");
     * ENSURE(file, "Bij TramSysteemOut moet er een output file aangemaakt zijn");
     * ENSURE(getFilename() == name, "Bij TramSysteemOut is de filename niet correct opgeslagen");
     */

    string getFilename();
    /*
     * Getter voor de filename
     *
     * REQUIRE(this->properlyInitialized(), "Bij getFilename is TramSysteemOut niet correct initialised");
     * ENSURE(result.substr(result.length() - 4) == ".txt", "Bij getFilename van TramSysteemOut was de filename geen .txt file");
     */

    TramSysteem *getTramSysteem();
    /*
     * Getter voor het tramsysteem
     *
     * REQUIRE(this->properlyInitialized(), "Bij getTramSysteem is TramSysteemOut niet correct initialised");
     * ENSURE(result != 0, "Bij getTramSysteem van TramSysteemOut was het systeem niet bestaand");
     */

    bool properlyInitialized();
    /*
     * Checkt of het TramSysteemOut correct is initialised.
     */

    void tram_summary();
    /**
     * Maakt een tram-summary.
     *
     * REQUIRE(this->properlyInitialized(), "TramSysteemOut bij tram_summary niet correct initialised");
     * REQUIRE(!filename.empty(), "Bij tram_summary van TramSysteemOut is er nog geen filenaam aangemaakt");
     */
    void station_summary();
    /**
     * Maakt een station-summary.
     *
     * REQUIRE(this->properlyInitialized(), "TramSysteemOut bij station_summary niet correct initialised");
     * REQUIRE(!filename.empty(), "Bij station_summary is er nog geen filenaam aangemaakt");
     */

    void complete_summary();
    /**
     * Maakt een complete summary.
     *
     * REQUIRE(this->properlyInitialized(), "TramSysteemOut bij complete_summary niet correct initialised");
     * REQUIRE(!filename.empty(), "Bij complete_summary is er nog geen filenaam aangemaakt");
     */

    void advanced_summary();
    /**
     * Maakt een advanced summary.
     *
     * REQUIRE(this->properlyInitialized(), "TramSysteemOut bij advanced_summary niet correct initialised");
     * REQUIRE(!filename.empty(), "Bij advanced_summary is er nog geen filenaam aangemaakt");
     */

    void move(Tram* tram, Station* begin, Station* eind);
    /**
     * Maakt de verplaatsing boodschap bij een verplaatsing
     *
     * REQUIRE(this->properlyInitialized(), "TramSysteemOut bij move niet correct initialised");
     * REQUIRE(!filename.empty(), "Bij move is er nog geen filenaam aangemaakt");
     */

    void herstel(Tram* tram, Station* halte);
    /**
     * Maakt een herstel boodschap bij een verplaatsing.
     *
     * REQUIRE(this->properlyInitialized(), "TramSysteemOut bij herstel niet correct initialised");
     * REQUIRE(!filename.empty(), "Bij herstel is er nog geen filenaam aangemaakt");
     */

    void botsing(Tram* tram1, Tram* tram2);
    /**
     * REQUIRE(this->properlyInitialized(), "TramSysteemOut bij botsing niet correct initialised");
     * REQUIRE(!filename.empty(), "Bij botsing is er nog geen filenaam aangemaakt");
     */

    void wachten(Tram* tram1, Tram* tram2);
    /**
     *
     */

};


#endif //TRAMSYSTEEM_CPP_TRAMSYSTEEMOUT_H
