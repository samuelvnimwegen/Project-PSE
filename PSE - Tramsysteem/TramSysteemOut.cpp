//
// Created by Samuel on 24/03/2023.
//

#include "TramSysteemOut.h"
#include "TramSysteem.h"


TramSysteemOut::TramSysteemOut(const string &name, TramSysteem* ts) : filename(name), tramSysteem(ts) {
    REQUIRE(name.substr(name.length() - 4) == ".txt", "moet een .txt file zijn");
    ofstream outfile(name.c_str());
    filename = name;
    outfile << "----- Tramregeling ----- " << endl << endl;

    ifstream file;
    file.open(filename.c_str());
    ENSURE(file, "file moet aangemaakt zijn");
}

void TramSysteemOut::tram_summary() {
    REQUIRE(!filename.empty(), "Bij tram_summary is er nog geen filenaam aangemaakt");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);
    outfile << "--== TRAMS ==--" << endl;
    int size = tramSysteem->getTrams().size();
    for (int i = 0; i < size; ++i){
        Tram* tram = tramSysteem->getTrams()[i];
        outfile << "Tram "<<tram->getLijnNr() << " nr " << tram->getVoertuigNummer() << endl ;
        outfile << "\t" << "type: " << tram->getTypeString() << endl;
        outfile << "\t" << "snelheid: " << tram->getSnelheid() << endl;
        outfile << "\t" << "huidig station: " << tram->getStation()->getNaam() << endl;

        if (tram->getTypeString() == "PCC"){
            PCC* pccTram = dynamic_cast<PCC *>(tram);
            outfile << "\t" << "reparatiekosten: " << pccTram->getReparatieKost() << " euro" << endl;
        }
        outfile << endl;
    }
}

void TramSysteemOut::station_summary() {
    REQUIRE(!filename.empty(), "Bij station_summary is er nog geen filenaam aangemaakt");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);
    outfile << "--== STATIONS ==--" << endl;
    int size = tramSysteem->getStations().size();
    for (int i = 0; i < size; ++i){
        Station* station = tramSysteem->getStations()[i];
        outfile << "= Station " <<station->getNaam()<< " =" << endl;
        outfile << "* Spoor " << station->getSpoorNr() << ":" << endl;
        outfile << "<- Station " << station->getVorige()->getNaam() << endl;
        outfile << "-> Station " << station->getVolgende()->getNaam() << endl;
        outfile << endl;
    }
}

void TramSysteemOut::complete_summary() {
    station_summary();
    tram_summary();
}

void TramSysteemOut::advanced_summary() {
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    int lijnenSize = tramSysteem->getLijnen().size();
    int stationSize = tramSysteem->getStations().size();
    int tramSize = tramSysteem->getTrams().size();

    for (int i = 0; i < lijnenSize; ++i){
        outfile << "Lijn " << tramSysteem->getLijnen()[i] << ":" << endl;
        Lijn* huidigeLijn = tramSysteem->getLijnen()[i];

        vector<Station*> stationsInLijn;
        Station* beginStation = 0;
        for (int j = 0; j < stationSize; ++j){
            Station* huidigStation = tramSysteem->getStations()[j];
            if (huidigStation->getSpoorNr() == huidigeLijn->getLijnnummer()){
                beginStation = huidigStation;
                j = stationSize;
            }
        }
        stationsInLijn.push_back(beginStation);
        Station* huidigStation = beginStation->getVolgende();
        int aantalStationsInLijn = 1;
        while (huidigStation != beginStation){
            stationsInLijn.push_back(huidigStation);
            huidigStation = huidigStation->getVolgende();
            aantalStationsInLijn += 1;
        }
        string lijn1 = "=";
        string lijn2 = " ";
        for (int j = 0; j < aantalStationsInLijn; ++j){
            Station* huidigStationInLijn = stationsInLijn[j];
            lijn1 += huidigStationInLijn->getNaam() + "===";
            bool bevatStation = false;
            for (int k = 0; k < tramSize; ++k){
                if (tramSysteem->getTrams()[i]->getStation() == huidigStationInLijn){
                    bevatStation = true;
                }
            }
            if (bevatStation){
                lijn2 += "T   ";
            }
            else{
                lijn2 += "    ";
            }
        }
        lijn1 = lijn1.substr(0, lijn1.size() - 2);
        lijn2 = lijn2.substr(0, lijn2.size() - 2);
        outfile << lijn1 << endl << lijn2 << endl << endl;
    }
}

void TramSysteemOut::move(Tram* tram, Station *begin, Station *eind) {
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    outfile << "Tram " << tram->getVoertuigNummer() << " (" << tram->getTypeString() << ") reed van "
    << begin->getTypeString() <<" " << begin->getNaam() << " naar " << eind->getTypeString() << " "
    << eind->getNaam() << " via lijn " << tram->getLijnNr() << "."<< endl << endl;
}

