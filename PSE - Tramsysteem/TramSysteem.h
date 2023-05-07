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
#include "DesignByContract.h"
#include "TramSysteemOut.h"
#include "algorithm"
#include "PCC.h"
#include "Albatros.h"
#include "Stadslijner.h"
#include "Halte.h"
#include "Metrostation.h"
#include "Lijn.h"


// Bevat het volledige tramsysteem en bevat alle andere classes.
class TramSysteem {
    TramSysteem* initCheck;
    vector<Station*> stations;
    vector<Tram*> trams;
    vector<Lijn*> lijnen;
    TramSysteemOut* output;
public:
    const vector<Lijn *> &getLijnen() const;

    void setLijnen(const vector<Lijn *> &lines);

public:
    void addLijn(Lijn* ln);
    /*
     * REQUIRE(ln != 0, "Bij addLijn van TramSysteem was de lijn == 0");
     */

    Lijn* findLijn(int ln);
    /**
     * REQUIRE(ln > 0, "Bij findLijn van TramSysteem was het lijnNr <= 0");
     */

    TramSysteemOut *getOutput() const;
    /**
     * REQUIRE(output != 0, "Bij getOutput van TramSysteemOut was er geen output gemaakt");
     */

    void setOutput(TramSysteemOut *output);
    /**
     * REQUIRE(out != 0, "Bij setOutput van TramSysteemOut was geen geldige output opgegeven");
     * ENSURE(output == out, "Bij setOutput van TramSysteemOut was de verandering niet correct uitgevoerd");
     */


    TramSysteem();
    /**
     * ENSURE(properlyInitialized(), "constructor moet in juiste staat eindigen bij initialisatie bij TramSysteem");
     */

    bool properlyInitialized();

    bool add_station(Station* station);
    /**
     * REQUIRE((huidigStation != 0), "Station moet bestaan bij add_station");
     * ENSURE(stations[size - 1] == huidigStation, "Laatste huidigStation in de stations-vector moet het nieuwe huidigStation zijn bij addStation");
    */


    void addTram(Tram* tram);
    /**
     * REQUIRE(tr != 0, "tram moet bestaan bij addTram");
     * ENSURE(trams[size - 1] == tr, "tram moet laatste element in trams-vector zijn bij addTram");
     */

    vector<Station *> &getStations();


    void setStations(const vector<Station *> &stat);
    /**
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer setStations was gebruikt");
     * ENSURE(getStations() == stat, "Postconditie fout bij setHuidigStation");
     */

    const vector<Tram *> & getTrams();
    /**
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer getTrams was gebruikt");
     * ENSURE(trams == getTrams(), "Moet alle stat teruggeven bij getTrams");
     */

    void setTrams(const vector<Tram *> &trams);
    /**
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer setTrams was gebruikt");
     * ENSURE(getTrams() == trams, "Postconditie fout bij setTrams");
     */


    bool simulate(int tijd);
    /**
     * REQUIRE(tijd > 0, "Bij simulate van TramSysteem was de tijd <= 0.");
     * REQUIRE(isConsistent(), "Systeem niet consistent bij simulate");
     */

    bool isConsistent();
    // Checkt of het tramsysteem consistent is

    vector<Station*> getStationsVanLijn(const int &lijn);
    /**
     * REQUIRE(spoorNummer > 0, "Bij getStationsVanLijn van TramSysteem was het spoornummer <= 0");
     * ENSURE(!lijnStations.empty(), "Bij getStationsVanLijn van TramSysteem waren er geen stations met het spoornummer");
     */

    void checkLijnen();

    virtual ~TramSysteem();
    // Destructor die alle stations en trams verwijderd

};

Station* findStation(const string &naam, const vector<Station*> &stations);


#endif //TREIN_TRAMSYSTEEM_H
