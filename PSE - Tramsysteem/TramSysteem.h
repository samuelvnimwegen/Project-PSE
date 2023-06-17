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
    vector<Lijn *> getLijnen() ;
    /*
     * Getter voor alle lijnen in het Tramsysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Bij getLijnen was TramSysteem niet correct geïnitialiseerd");
     * REQUIRE(!lijnen.empty(), "Bij getLijnen van TramSysteem was de vector leeg.");
     * ENSURE(!result.empty(), "Postconditie fout van getLijnen van TramSysteem");
     */

    void setLijnen(const vector<Lijn *> &lines);
    /*
     * Setter voor alle lijnen in het Tramsysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Bij setLijnen was TramSysteem niet correct geïnitialiseerd");
     * REQUIRE(!lines.empty(), "Bij setLijnen van TramSysteem was de vector leeg");
     * ENSURE(getLijnen() == lines, "Bij setLijnen van TramSysteem is de operatie fout uitgevoerd");
     */

    void addLijn(Lijn* ln);
    /*
     * Adder voor een lijn in het Tramsysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Bij addLijn was TramSysteem niet correct geïnitialiseerd");
     * REQUIRE(ln != 0, "Bij addLijn van TramSysteem was de lijn == 0");
     * ENSURE(getLijnen()[int(lijnen.size()) - 1] == ln, "Bij addLijn van TramSysteem was de lijn niet correct toegevoegd");
     */

    Lijn* findLijn(int ln);
    /**
     * Zoekt een lijn met een gegeven lijnnummer.
     *
     * REQUIRE(this->properlyInitialized(), "Bij getOutput was TramSysteem niet correct geïnitialiseerd");
     * REQUIRE(ln > 0, "Bij findLijn van TramSysteem was het lijnNr <= 0");
     * ENSURE(result != 0, "Bij findLijn is de gevraagde lijn niet gevonden");
     */

    TramSysteemOut *getOutput();
    /**
     * Getter voor het outputsysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Bij getOutput was TramSysteem niet correct geïnitialiseerd");
     * ENSURE(result != 0, "Bij getOutput van TramSysteemOut was er geen output gemaakt");
     */

    void setOutput(TramSysteemOut *output);
    /**
     * Setter voor het outputsysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Bij setOutput was TramSysteem niet correct geïnitialiseerd");
     * REQUIRE(out != 0, "Bij setOutput van TramSysteemOut was geen geldige output opgegeven");
     * ENSURE(getOutput() == out, "Bij setOutput van TramSysteemOut was de verandering niet correct uitgevoerd");
     */


    TramSysteem();
    /**
     * Generator voor het TramSysteem.
     *
     * ENSURE(properlyInitialized(), "constructor moet in juiste staat eindigen bij initialisatie bij TramSysteem");
     */

    bool properlyInitialized();
    /*
     * Checkt of het TramSysteem correct is initialised.
     */

    void add_station(Station* station);
    /**
     * Adder voor een station in het TramSysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Bij add_station is Tramsysteem niet juist geïnitialiseerd");
     * REQUIRE(station != 0, "Station moet bestaan bij add_station");
     * ENSURE(getStations()[size - 1] == station, "Laatste huidigStation in de stations-vector moet het nieuwe huidigStation zijn bij addStation");
    */


    void addTram(Tram* tram);
    /**
     * Adder voor een tram in het TramSysteem.
     *
     * REQUIRE(this->properlyInitialized(), "TramSysteem niet geïnitialiseerd wanneer addTram was gebruikt");
     * REQUIRE(tr != 0, "tram moet bestaan bij addTram");
     * ENSURE(getTrams()[size - 1] == tr, "tram moet laatste element in trams-vector zijn bij addTram");
     */

    vector<Station *> &getStations();
    /**
     * Getter voor de stations in het TramSysteem.
     *
     * REQUIRE(this->properlyInitialized(), "TramSysteem niet geïnitialiseerd wanneer getStations was gebruikt");
     * ENSURE(int(result.size()) > 0, "Bij getStations van TramSysteem waren er geen trams");
     */

    void setStations(const vector<Station *> &stat);
    /**
     * Getter voor de stations in het TramSysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Tramsysteem niet geïnitialiseerd wanneer setStations was gebruikt");
     * REQUIRE(int(stat.size()) > 0, "Bij setStations van TramSysteem was de input leeg");
     * ENSURE(getStations() == stat, "Postconditie fout bij setHuidigStation");
     */

    const vector<Tram *> & getTrams();
    /**
     * Getter voor de trams in het TramSysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer getTrams was gebruikt");
     * ENSURE(trams == getTrams(), "Moet alle stat teruggeven bij getTrams");
     */

    void setTrams(const vector<Tram *> &trams);
    /**
     * Setter voor de trams in het TramSysteem.
     *
     * REQUIRE(this->properlyInitialized(), "Tramsysteem niet geïnitialiseerd wanneer setTrams was gebruikt");
     * REQUIRE(int(tr.size()) > 0, "Bij setTrams van TramSysteem was de input leeg");
     * ENSURE(getTrams() == trams, "Postconditie fout bij setTrams");
     */


    void simulate(int tijd);
    /**
     * Simuleert het TramSysteem voor het gegeven aantal tijdintervallen.
     *
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer simulate was gebruikt");
     * REQUIRE(tijd > 0, "Bij simulate van TramSysteem was de tijd <= 0");
     */

    bool isConsistent();
    /**
     * Checkt of een systeem consistent is of niet.
     *
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer isConsistent was gebruikt");
     * REQUIRE(!getLijnen().empty(), "Bij isConsistent van TramSysteem waren er geen lijnen om te bekijken");
     * ENSURE(volgendEnVorigeCheck, "Bij isConsistent van TramSysteem had niet elk huidigStation een correct volgende of vorig huidigStation");
     * ENSURE(voertuigNummerDuplicates, "Bij isConsistent van TramSysteem waren er duplicate voertuignummers");
     * ENSURE(tramKanOpLijn, "Bij isConsistent van TramSysteem is er een tram die niet naar elk huidigStation op de lijn kan");
     */



    vector<Station*> getStationsVanLijn(const int &spoorNummer);
    /**
     * Maakt een vector met alle stations met het gegeven spoornummer.
     *
     * REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer getStationsVanLijn was gebruikt");
     * REQUIRE(spoorNummer > 0, "Bij getStationsVanLijn van TramSysteem was het spoornummer <= 0");
     * ENSURE(!result.empty(), "Bij getStationsVanLijn van TramSysteem waren er geen stations met het spoornummer");
     */

    virtual ~TramSysteem();
    /**
     * Destructor voor het TramSysteem.
     */

};

Station* findStation(const string &naam, const vector<Station*> &stations);
/*
 * Vindt een station met een gegeven naam in de vector met stations.
 *
 * REQUIRE(!stations.empty(), "Bij hulpfunctie findStation van tramSysteem bevatte de vector geen stations");
 * ENSURE(result != 0, "Bij hulpfunctie findStation van tramSysteem bevatte de vector niet het gevraagde huidigStation");
 */


#endif //TREIN_TRAMSYSTEEM_H
