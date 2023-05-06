//
// Created by Samuel van Nimwegen on 02/03/2023.
//

#include "TramSysteem.h"



TramSysteem::TramSysteem() {
    initCheck = this;
    ENSURE(properlyInitialized(), "constructor moet in juiste staat eindigen bij initialisatie bij TramSysteem");
}

bool TramSysteem::add_station(Station *station) {
    REQUIRE((station != 0), "Station moet bestaan bij add_station");
    if (station == 0){
        return false;
    }
    stations.push_back(station);

    int size = stations.size();

    ENSURE(stations[size - 1] == station, "Laatste station in de stations-vector moet het nieuwe station zijn bij addStation");
    return false;
}
 vector<Station *> & TramSysteem::getStations(){
    REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer getStations was gebruikt");

    return stations;
}

void TramSysteem::setStations(const vector<Station *> &stat) {
    REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer setStations was gebruikt");
    stations = stat;
    ENSURE(getStations() == stat, "Postconditie fout bij setStation");
}

const vector<Tram *> & TramSysteem::getTrams() {
    return trams;
}

void TramSysteem::setTrams(const vector<Tram *> &tr) {
    REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer setTrams was gebruikt");
    trams = tr;
    ENSURE(getTrams() == trams, "Postconditie fout bij setTrams");
}

void TramSysteem::addTram(Tram * tr) {
    REQUIRE(tr != 0, "tram moet bestaan bij addTram");
    trams.push_back(tr);
    int size = trams.size();
    ENSURE(trams[size - 1] == tr, "tram moet laatste element in trams-vector zijn bij addTram");
}





void TramSysteem::move(Tram* tram, Station* station, bool forcedMove) {
    REQUIRE(tram->getLijnNr() == station->getSpoorNr(), "Bij move van TramSysteem zijn tram en station niet op zelfde lijn");
    REQUIRE(tram->getStation() != station, "Bij move van TramSysteem zijn beginstation en eindstation hetzelfde");
    while (tram->getStation() != station){
        Station* vorig_station = tram->getStation();
        Station* volgend_station = vorig_station->getVolgende();
        int size = trams.size();
        bool volgendeBezet = false;
        for (int i = 0; i < size; ++i){
            if (tram->getStation() == volgend_station and !forcedMove){
                volgendeBezet = true;
            }
        }
        output->move(tram, vorig_station, volgend_station);
        ENSURE(!volgendeBezet, "Bij move van TramSysteem was het volgende station bezet op de lijn.");
        tram->setStation(vorig_station->getVolgende());

    }
    ENSURE(tram->getStation() == station, "Bij move tram niet op het juiste station uitgekomen");
}

bool TramSysteem::simulate(int tijd) {
    REQUIRE(tijd > 0, "Bij simulate van TramSysteem was de tijd <= 0.");
    REQUIRE(isConsistent(), "Systeem niet consistent bij simulate");
    int aantalTrams = trams.size();
    int counter = 0;
    // Verplaatst telkens de tram 1 plaats per tijdseenheid.
    if (tijd > 0){
        while (counter < tijd){
            for (int i = 0; i < aantalTrams; ++i){
                move(trams[i], trams[i]->getStation()->getVolgende(), true);
            }
            counter += 1;
        }
    }
    return true;
}


bool TramSysteem::isConsistent() {
    // checkt of elk station een volgend en vorig heeft
    int size = stations.size();
    for (int i = 0; i < size; ++i){
        if (stations[i]->getVorige() == 0 or stations[i]->getVolgende() == 0){
            return false;
        }
    }
    // Vector om de lijnnummers bij te houden.
    vector<int> lijnnummers;

    // Voor alle trams
    size = trams.size();
    for (int i = 0; i < size; ++i){
        // Vergelijkt tramlijn met lijn van beginstation
        if (trams[i]->getBeginStation()->getSpoorNr() != trams[i]->getLijnNr()){
            return false;
        }
        // Checkt of beginstation geldig is in het metronet:
        int stationsSize = stations.size();
        bool gevonden = false;
        for (int j = 0; j < stationsSize; ++j){
            if (stations[j] == trams[i]->getBeginStation()){
                gevonden = true;
            }
        }
        if (!gevonden){
            return false;
        }
        lijnnummers.push_back(trams[i]->getLijnNr());
    }

    // Checkt alle lijnnummers op duplicates
    size = lijnnummers.size();
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            if (lijnnummers[i] == lijnnummers[j] and i != j){
                return false;
            }
        }
    }
    return true;
}


TramSysteem::~TramSysteem() {
    int size = stations.size();
    for (int i = 0; i < size; ++i){
        delete stations[i];
    }
    size = trams.size();
    for (int i = 0; i < size; ++i){
        delete trams[i];
    }
}

bool TramSysteem::properlyInitialized() {
    return initCheck == this;
}

const vector<int> &TramSysteem::getLijnen() const {
    return lijnen;
}

void TramSysteem::setLijnen(const vector<int> &ln) {
    TramSysteem::lijnen = ln;
}

void TramSysteem::addLijn(int lijn) {
    lijnen.push_back(lijn);
}

TramSysteemOut *TramSysteem::getOutput() const {
    REQUIRE(output != 0, "Bij getOutput van TramSysteemOut was er geen output gemaakt");
    return output;
}

void TramSysteem::setOutput(TramSysteemOut *out) {
    REQUIRE(out != 0, "Bij setOutput van TramSysteemOut was geen geldige output opgegeven");
    TramSysteem::output = out;
    ENSURE(output == out, "Bij setOutput van TramSysteemOut was de verandering niet correct uitgevoerd");
}


Station *findStation(const string &naam, const vector<Station *> &stations) {
    REQUIRE(!stations.empty(), "Bij hulpfunctie findStation van tramSysteem bevatte de vector geen stations");
    int size = stations.size();
    Station* returnElement = 0;
    for (int i = 0; i < size; ++i){
        if (stations[i]->getNaam() == naam){
            returnElement = stations[i];
        }
    }
    ENSURE(returnElement != 0, "Bij hulpfunctie findStation van tramSysteem bevatte de vector niet het gevraagde station");
    return returnElement;
}

