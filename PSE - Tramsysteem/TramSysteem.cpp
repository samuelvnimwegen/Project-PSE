//
// Created by Samuel van Nimwegen on 02/03/2023.
//

#include "TramSysteem.h"



TramSysteem::TramSysteem() {
    initCheck = this;
    ENSURE(properlyInitialized(), "constructor moet in juiste staat eindigen bij initialisatie bij TramSysteem");
}

void TramSysteem::add_station(Station *station) {
    REQUIRE(this->properlyInitialized(), "Bij add_station is Tramsysteem niet juist geïnitialiseerd");
    REQUIRE(station != 0, "Station moet bestaan bij add_station");
    stations.push_back(station);
    int size = stations.size();
    ENSURE(getStations()[size - 1] == station, "Laatste huidigStation in de stations-vector moet het nieuwe huidigStation zijn bij addStation");
}
 vector<Station *> & TramSysteem::getStations(){
    REQUIRE(this->properlyInitialized(), "TramSysteem niet geïnitialiseerd wanneer getStations was gebruikt");
    vector<Station*> result = stations;
    ENSURE(int(result.size()) > 0, "Bij getStations van TramSysteem waren er geen trams");
    return stations;
}

void TramSysteem::setStations(const vector<Station *> &stat) {
    REQUIRE(this->properlyInitialized(), "Tramsysteem niet geïnitialiseerd wanneer setStations was gebruikt");
    REQUIRE(int(stat.size()) > 0, "Bij setStations van TramSysteem was de input leeg");
    stations = stat;
    ENSURE(getStations() == stat, "Postconditie fout bij setHuidigStation");
}

const vector<Tram *> & TramSysteem::getTrams() {
    return trams;
}

void TramSysteem::setTrams(const vector<Tram *> &tr) {
    REQUIRE(this->properlyInitialized(), "Tramsysteem niet geïnitialiseerd wanneer setTrams was gebruikt");
    REQUIRE(int(tr.size()) > 0, "Bij setTrams van TramSysteem was de input leeg");
    trams = tr;
    ENSURE(getTrams() == trams, "Postconditie fout bij setTrams");
}

void TramSysteem::addTram(Tram * tr) {
    REQUIRE(this->properlyInitialized(), "TramSysteem niet geïnitialiseerd wanneer addTram was gebruikt");
    REQUIRE(tr != 0, "tram moet bestaan bij addTram");
    trams.push_back(tr);
    int size = trams.size();
    ENSURE(getTrams()[size - 1] == tr, "tram moet laatste element in trams-vector zijn bij addTram");
}







void TramSysteem::simulate(int tijd) {
    REQUIRE(this->properlyInitialized(), "TramSysteem niet geïnitialiseerd wanneer simulate was gebruikt");
    REQUIRE(tijd > 0, "Bij simulate van TramSysteem was de tijd <= 0");
    int counter = 0;
    vector<Tram*> onbewogen = getTrams();
    // Verplaatst telkens de tram 1 plaats per tijdseenheid.
    while (counter < tijd){
        // Elke tram die kan bewegen verplaatsen totdat alles vaststaat.
        bool beweging = true;
        vector<Tram*> tramVector;
        while (beweging){
            beweging = false;
            for (int i = 0; i < int(onbewogen.size()); ++i){
                if (onbewogen[i]->kanBewegen()){
                    onbewogen[i]->moveNaarVolgende(output);
                    beweging = true;
                }
                else{
                    tramVector.push_back(onbewogen[i]);
                }
            }
            onbewogen = tramVector;
        }
        for (int i = 0; i < int(onbewogen.size()); ++i){
            onbewogen[i]->wacht(output);
        }
        counter += 1;
    }
}


bool TramSysteem::consistencyCheck() {
    // checkt of elk huidigStation een volgend en vorig heeft
    REQUIRE(this->properlyInitialized(), "Niet geïnitialiseerd wanneer consistencyCheck was gebruikt");
    REQUIRE(!getLijnen().empty(), "Bij consistencyCheck van TramSysteem waren er geen lijnen om te bekijken");
    REQUIRE(!getStations().empty(), "Bij consistencyCheck van TramSysteem waren er geen stations om te bekijken");
    REQUIRE(!getTrams().empty(), "Bij consistencyCheck van TramSysteem waren er geen trams om te bekijken");

    bool stationsHebbenSpoornummer = true;
    for (int i = 0; i < int(getStations().size()); ++i){
        if (getStations()[i]->getSpoorNr() <=0){
            stationsHebbenSpoornummer = false;
        }
    }

    bool tramsHebbenSpoornummer = true;
    for (int i = 0; i < int(getTrams().size()); ++i){
        if (getTrams()[i]->getLijnNr() <=0){
            tramsHebbenSpoornummer = false;
        }
    }

    bool volgendEnVorigeCheck = true;
    bool zelfdeSpoornummer = true;
    int size = stations.size();
    for (int i = 0; i < size; ++i){
        if (stations[i]->getVorige() == 0 or stations[i]->getVolgende() == 0){
            volgendEnVorigeCheck = false;
        }
        else if (stations[i]->getVorige() == stations[i] or stations[i]->getVolgende() == stations[i]){
            volgendEnVorigeCheck = false;
        }
        if (stations[i]->getSpoorNr() != stations[i]->getVolgende()->getSpoorNr() or stations[i]->getSpoorNr() != stations[i]->getVorige()->getSpoorNr()){
            zelfdeSpoornummer = false;
        }
    }
    ENSURE(volgendEnVorigeCheck, "Bij consistencyCheck van TramSysteem had niet elk huidigStation een correct volgende of vorig huidigStation");
    // Vector om de voertuigNummers bij te houden.
    vector<int> voertuigNummers;

    // Voor alle trams
    size = trams.size();
    bool beginstationGeldig = true;
    bool beginstationGevonden = true;
    for (int i = 0; i < size; ++i){
        // Vergelijkt tramlijn met lijn van beginstation
        if (trams[i]->getBeginStation()->getSpoorNr() != trams[i]->getLijnNr()){
             beginstationGeldig = false;
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
            beginstationGevonden = false;
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

    bool startStationDuplicates = true;
    vector<string> beginStationNamen;
    for (int i = 0; i < int(getTrams().size()); ++i){
        if (!std::count(beginStationNamen.begin(), beginStationNamen.end(), getTrams()[i]->getBeginStation()->getNaam())){
            beginStationNamen.push_back(getTrams()[i]->getBeginStation()->getNaam());
        }
        else{
            startStationDuplicates = false;
        }
    }

    ENSURE(voertuigNummerDuplicates, "Bij consistencyCheck van TramSysteem waren er duplicate voertuignummers");
    ENSURE(beginstationGeldig, "Bij consistencyCheck van TramSysteem kwamen de lijnnummers van een beginstation niet overeen met die van de tram");
    ENSURE(beginstationGevonden, "Bij consistencyCheck van TramSysteem bestond een beginstation niet in het tramsysteem");
    ENSURE(zelfdeSpoornummer, "Bij consistencyCheck van TramSysteem hadden het volgende of vorige station niet hetzelfde spoornummer");
    ENSURE(tramsHebbenSpoornummer, "Bij consistencyCheck van TramSysteem waren er trams zonder- of met een ongeldig spoornummer");
    ENSURE(stationsHebbenSpoornummer, "Bij consistencyCheck van TramSysteem waren er stations zonder- of met een ongeldig spoornummer");
    ENSURE(startStationDuplicates, "Bij consistencyCheck van TramSysteem waren trams met hetzelfde startstation");

    bool kanHeleLijnBereiken = true;
    Station* huidig = getStations()[0];
    Station* begin = huidig;
    vector<Station*> bereikBareStations;
    bereikBareStations.push_back(begin);
    huidig = huidig->getVolgende();
    while (huidig != begin){
        bereikBareStations.push_back(huidig);
        huidig = huidig->getVolgende();
    }
    if (int(findLijn(begin->getSpoorNr())->getStations().size()) > int(bereikBareStations.size())){
        kanHeleLijnBereiken = false;
    }




    ENSURE(kanHeleLijnBereiken, "Bij consistencyCheck van TramSysteem kon niet elk station van de lijn bereikt worden");
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
    size = lijnen.size();
    for (int i = 0; i < size; ++i){
        delete lijnen[i];
    }
    delete output;
}

bool TramSysteem::properlyInitialized() {
    return initCheck == this;
}

TramSysteemOut *TramSysteem::getOutput() {
    REQUIRE(this->properlyInitialized(), "Bij getOutput was TramSysteem niet correct geïnitialiseerd");
    TramSysteemOut* result = output;
    ENSURE(result != 0, "Bij getOutput van TramSysteemOut was er geen output gemaakt");
    return output;
}

void TramSysteem::setOutput(TramSysteemOut *out) {
    REQUIRE(this->properlyInitialized(), "Bij setOutput was TramSysteem niet correct geïnitialiseerd");
    REQUIRE(out != 0, "Bij setOutput van TramSysteemOut was geen geldige output opgegeven");
    output = out;
    ENSURE(getOutput() == out, "Bij setOutput van TramSysteemOut was de verandering niet correct uitgevoerd");
}

vector<Station *> TramSysteem::getStationsVanLijn(const int &spoorNummer) {
    REQUIRE(this->properlyInitialized(), "TramSysteem niet geïnitialiseerd wanneer getStationsVanLijn was gebruikt");
    REQUIRE(spoorNummer > 0, "Bij getStationsVanLijn van TramSysteem was het spoornummer <= 0");
    vector<Station*> result;
    int size = stations.size();
    for (int i = 0; i < size; ++i){
        if (stations[i]->getSpoorNr() == spoorNummer){
            result.push_back(stations[i]);
        }
    }
    ENSURE(!result.empty(), "Bij getStationsVanLijn van TramSysteem waren er geen stations met het spoornummer");
    return result;
}

vector<Lijn *> TramSysteem::getLijnen(){
    REQUIRE(this->properlyInitialized(), "Bij getLijnen was TramSysteem niet correct geïnitialiseerd");
    REQUIRE(!lijnen.empty(), "Bij getLijnen van TramSysteem was de vector leeg.");
    vector<Lijn*> &result = lijnen;
    ENSURE(!result.empty(), "Postconditie fout van getLijnen van TramSysteem");
    return result;
}

void TramSysteem::setLijnen(const vector<Lijn *> &lines) {
    REQUIRE(this->properlyInitialized(), "Bij setLijnen was TramSysteem niet correct geïnitialiseerd");
    REQUIRE(!lines.empty(), "Bij setLijnen van TramSysteem was de vector leeg");
    lijnen = lines;
    ENSURE(getLijnen() == lines, "Bij setLijnen van TramSysteem is de operatie fout uitgevoerd");
}

void TramSysteem::addLijn(Lijn *ln) {
    REQUIRE(this->properlyInitialized(), "Bij addLijn was TramSysteem niet correct geïnitialiseerd");
    REQUIRE(ln != 0, "Bij addLijn van TramSysteem was de lijn == 0");
    lijnen.push_back(ln);
    ENSURE(getLijnen()[int(lijnen.size()) - 1] == ln, "Bij addLijn van TramSysteem was de lijn niet correct toegevoegd");
}

Lijn *TramSysteem::findLijn(int ln) {
    REQUIRE(this->properlyInitialized(), "Bij getOutput was TramSysteem niet correct geïnitialiseerd");
    REQUIRE(ln > 0, "Bij findLijn van TramSysteem was het lijnNr <= 0");
    int lijnenSize = lijnen.size();
    Lijn* result = 0;
    for (int i = 0; i < lijnenSize; ++i){
        if (lijnen[i]->getLijnnummer() == ln){
            result = lijnen[i];
            break;
        }
    }
    return result;
}


Station *findStation(const string &naam, const vector<Station *> &stations) {
    REQUIRE(!stations.empty(), "Bij hulpfunctie findStation van tramSysteem bevatte de vector geen stations");
    int size = stations.size();
    Station* result = 0;
    for (int i = 0; i < size; ++i){
        if (stations[i]->getNaam() == naam){
            result = stations[i];
        }
    }
    ENSURE(result != 0, "Bij hulpfunctie findStation van tramSysteem bevatte de vector niet het gevraagde huidigStation");
    return result;
}

