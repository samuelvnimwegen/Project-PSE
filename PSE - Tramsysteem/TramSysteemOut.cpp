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
        outfile << "\t" << "type: " << tram->getType() << endl;
        outfile << "\t" << "snelheid: " << tram->getSnelheid() << endl;
        outfile << "\t" << "huidig station: " << tram->getStation()->getNaam() << endl;
        outfile << "\t" << "reparatiekosten: " << tram->getReparatieKosten() << " euro" << endl << endl;
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

