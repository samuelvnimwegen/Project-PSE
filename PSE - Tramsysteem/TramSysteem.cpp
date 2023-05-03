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





void TramSysteem::move(Tram* tram, Station* station) {
    REQUIRE(!filename.empty(), "Bij move is er nog geen filenaam aangemaakt");
    REQUIRE(tram->getLijnNr() == station->getSpoorNr(), "Bij move tram en station niet op zelfde lijn");
    REQUIRE(tram->getStation() != station, "Bij move zijn beginstation en eindstation hetzelfde");
    while (tram->getStation() != station){
        Station* vorig_station = tram->getStation();
        Station* volgend_station = vorig_station->getVolgende();
        bool bevatTram = false;
        int size = trams.size();
        for (int i = 0; i < size; ++i){
            if (tram->getStation() == volgend_station){
                bevatTram = true;
            }
        }
        if (bevatTram){
            return;
        }
        tram->setStation(vorig_station->getVolgende());
        ofstream outfile;
        outfile.open(filename.c_str(), ios_base::app);
        outfile << "Tram " << tram->getLijnNr() << " reed van Station " << vorig_station->getNaam() << " naar Station "
                << volgend_station->getNaam() << "." << endl << endl;
        outfile.close();
    }
    ENSURE(tram->getStation() == station, "Bij move tram niet op het juiste station uitgekomen");
}

bool TramSysteem::simulate(int tijd) {
    REQUIRE(!filename.empty(), "Bij simulate is er nog geen filenaam aangemaakt");
    REQUIRE(isConsistent(), "Systeem niet consistent bij simulate");
    int aantalTrams = trams.size();
    int counter = 0;
    // Verplaatst telkens de tram 1 plaats per tijdseenheid.
    if (tijd > 0){
        while (counter < tijd){
            for (int i = 0; i < aantalTrams; ++i){
                if (trams[i]->getStation()->getVolgende() != 0){
                    move(trams[i], trams[i]->getStation()->getVolgende());
                }
            }
            counter += 1;
        }
    }
    // Om terug in de tijd te gaan (tijd < 0)
    else if (tijd < 0){
        int negatieve_tijd = -tijd;
        while (counter < negatieve_tijd){
            for (int i = 0; i < aantalTrams; ++i){
                if (trams[i]->getStation()->getVorige() != 0){
                    move(trams[i], trams[i]->getStation()->getVorige());
                }
            }
            counter += 1;
        }
    }
    return true;
}

bool TramSysteem::complete_summary() {
    REQUIRE(!filename.empty(), "Bij complete_summary is er nog geen filenaam aangemaakt");
    REQUIRE(isConsistent(), "Systeem niet consistent bij complete_summary");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    int size = getStations().size();
    // Voor elk station wordt het volgende station en het vorige weergeven.
    for (int i = 0; i < size; ++i){
        Station* station = getStations()[i];
        outfile << "Station " <<station->getNaam() << endl;
        if (station->getVorige() != 0){
            outfile << "<- Station " << station->getVorige()->getNaam() << endl;
        }
        if (station->getVolgende() != 0){
            outfile << "-> Station " << station->getVolgende()->getNaam() << endl;
        }
        if (station->getSpoorNr() != -1){
            outfile << "Spoor " << station->getSpoorNr() << endl;
        }
        outfile << endl;
    }

    // Alle trams worden gedisplayd.
    size = getTrams().size();
    for (int i = 0; i < size; ++i){
        Tram* tram = getTrams()[i];
        outfile << "Tram "<<tram->getLijnNr() << " in Station " << tram->getStation()->getNaam() << endl << endl;
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
