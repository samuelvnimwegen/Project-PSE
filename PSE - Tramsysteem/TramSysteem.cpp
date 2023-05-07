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

    ENSURE(stations[size - 1] == station, "Laatste huidigStation in de stations-vector moet het nieuwe huidigStation zijn bij addStation");
    return false;
}
 vector<Station *> & TramSysteem::getStations(){
    REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer getStations was gebruikt");

    return stations;
}

void TramSysteem::setStations(const vector<Station *> &stat) {
    REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer setStations was gebruikt");
    stations = stat;
    ENSURE(getStations() == stat, "Postconditie fout bij setHuidigStation");
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







bool TramSysteem::simulate(int tijd) {
    REQUIRE(tijd > 0, "Bij simulate van TramSysteem was de tijd <= 0.");
    REQUIRE(isConsistent(), "Systeem niet consistent bij simulate");
    int aantalTrams = trams.size();
    int counter = 0;
    // Verplaatst telkens de tram 1 plaats per tijdseenheid.
    if (tijd > 0){
        while (counter < tijd){
            for (int i = 0; i < aantalTrams; ++i){
                trams[i]->moveNaarVolgende(output);
            }
            counter += 1;
        }
    }
    return true;
}


bool TramSysteem::isConsistent() {
    // checkt of elk huidigStation een volgend en vorig heeft
    bool volgendEnVorigeCheck = true;
    int size = stations.size();
    for (int i = 0; i < size; ++i){
        if (stations[i]->getVorige() == 0 or stations[i]->getVolgende() == 0){
            volgendEnVorigeCheck = false;
        }
    }
    ENSURE(volgendEnVorigeCheck, "Bij isConsistent van TramSysteem had niet elk huidigStation een volgende of vorig huidigStation");

    // Vector om de voertuigNummers bij te houden.
    vector<int> voertuigNummers;

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
        voertuigNummers.push_back(trams[i]->getVoertuigNummer());
    }

    // Checkt alle voertuigNummers op duplicates
    bool voertuigNummerDuplicates = true;
    size = voertuigNummers.size();
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            if (voertuigNummers[i] == voertuigNummers[j] and i != j){
                voertuigNummerDuplicates = false;
            }
        }
    }
    ENSURE(voertuigNummerDuplicates, "Bij isConsistent van TramSysteem waren er duplicate voertuignummers");


    checkLijnen();
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

TramSysteemOut *TramSysteem::getOutput() const {
    REQUIRE(output != 0, "Bij getOutput van TramSysteemOut was er geen output gemaakt");
    return output;
}

void TramSysteem::setOutput(TramSysteemOut *out) {
    REQUIRE(out != 0, "Bij setOutput van TramSysteemOut was geen geldige output opgegeven");
    TramSysteem::output = out;
    ENSURE(output == out, "Bij setOutput van TramSysteemOut was de verandering niet correct uitgevoerd");
}

vector<Station *> TramSysteem::getStationsVanLijn(const int &spoorNummer) {
    REQUIRE(spoorNummer > 0, "Bij getStationsVanLijn van TramSysteem was het spoornummer <= 0");
    vector<Station*> lijnStations;
    int size = stations.size();
    for (int i = 0; i < size; ++i){
        if (stations[i]->getSpoorNr() == spoorNummer){
            lijnStations.push_back(stations[i]);
        }
    }
    ENSURE(!lijnStations.empty(), "Bij getStationsVanLijn van TramSysteem waren er geen stations met het spoornummer");
    return lijnStations;
}

void TramSysteem::checkLijnen() {
    REQUIRE(!lijnen.empty(), "Bij checkLijnen van TramSysteem waren er geen lijnen om te bekijken");
    int lijnenSize = lijnen.size();
    bool tramKanOpLijn = true;
    for (int i = 0; i < lijnenSize; ++i){
        Lijn* huidigeLijn = lijnen[i];
        int stationSize = huidigeLijn->getStations().size();
        int tramsSize = huidigeLijn->getTrams().size();
        for (int j = 0; j < tramsSize; ++j){
            for (int k = 0; k < stationSize; ++k){
                if (!trams[j]->kanNaar(stations[k])){
                    tramKanOpLijn = false;
                }
            }
        }
    }
    ENSURE(tramKanOpLijn, "Bij checkLijnen van TramSysteem is er een tram die niet naar elk huidigStation op de lijn kan");

}

const vector<Lijn *> &TramSysteem::getLijnen() const {
    REQUIRE(!lijnen.empty(), "Bij getLijnen van TramSysteem was de vector leeg.");
    return lijnen;
}

void TramSysteem::setLijnen(const vector<Lijn *> &lines) {
    REQUIRE(!lines.empty(), "Bij setLijnen van TramSysteem was de vector leeg.");
    TramSysteem::lijnen = lines;
    ENSURE(lijnen == lines, "Bij setLijnen van TramSysteem is de operatie fout uitgevoerd.");
}

void TramSysteem::addLijn(Lijn *ln) {
    REQUIRE(ln != 0, "Bij addLijn van TramSysteem was de lijn == 0");
    lijnen.push_back(ln);
}

Lijn *TramSysteem::findLijn(int ln) {
    REQUIRE(ln > 0, "Bij findLijn van TramSysteem was het lijnNr <= 0");
    int lijnenSize = lijnen.size();
    for (int i = 0; i < lijnenSize; ++i){
        if (lijnen[i]->getLijnnummer() == ln){
            return lijnen[i];
        }
    }
    return 0;
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
    ENSURE(returnElement != 0, "Bij hulpfunctie findStation van tramSysteem bevatte de vector niet het gevraagde huidigStation");
    return returnElement;
}

