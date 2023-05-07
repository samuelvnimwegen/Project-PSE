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
        outfile << "\t" << "huidig huidigStation: " << tram->getHuidigStation()->getNaam() << endl;

        if (tram->getTypeString() == "PCC"){
            PCC* pccTram = dynamic_cast<PCC *>(tram);
            outfile << "\t" << "huidige reparatiekosten: " << pccTram->getResterendeKosten() << " euro" << endl;
            outfile << "\t" << "totale reparatiekosten: " << pccTram->getTotaleKosten() << " euro" << endl;
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
    REQUIRE(!filename.empty(), "Bij complete_summary is er nog geen filenaam aangemaakt");
    station_summary();
    tram_summary();
}

void TramSysteemOut::advanced_summary() {
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    int lijnenSize = tramSysteem->getLijnen().size();
    int tramSize = tramSysteem->getTrams().size();

    // Voor alle lijnen in het metronet:
    for (int i = 0; i < lijnenSize; ++i){
        outfile << "Lijn " << tramSysteem->getLijnen()[i]->getLijnnummer() << ":" << endl;

        // De lijn, de vector van alle stations en het beginstation worden opgeslagen.
        Lijn* huidigeLijn = tramSysteem->getLijnen()[i];
        vector<Station*> stationsInLijn = huidigeLijn->getStations();

        int aantalStationsInLijn = stationsInLijn.size();
        string lijn1 = "=";
        string lijn2 = " ";
        for (int j = 0; j < aantalStationsInLijn; ++j){
            Station* huidigStationInLijn = stationsInLijn[j];
            lijn1 += huidigStationInLijn->getNaam() + "===";
            bool bevatStation = false;
            for (int k = 0; k < tramSize; ++k){
                if (tramSysteem->getTrams()[k]->getHuidigStation() == huidigStationInLijn){
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
    REQUIRE(!filename.empty(), "Bij move is er nog geen filenaam aangemaakt");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    outfile << "Tram " << tram->getVoertuigNummer() << " (" << tram->getTypeString() << ") reed van "
    << begin->getTypeString() <<" " << begin->getNaam() << " naar " << eind->getTypeString() << " "
    << eind->getNaam() << " via lijn " << tram->getLijnNr() << "."<< endl << endl;
}

void TramSysteemOut::herstel(Tram *tram, Station *halte) {
    REQUIRE(!filename.empty(), "Bij herstel is er nog geen filenaam aangemaakt");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    outfile << "Tram " << tram->getVoertuigNummer() << " (" << tram->getTypeString() << ") is bezig met herstel bij "
    << halte->getTypeString() << " " << halte->getNaam() << " op lijn " << tram->getLijnNr() <<"." << endl << endl;
}

void TramSysteemOut::botsing(Tram *tram1, Tram *tram2) {
    REQUIRE(!filename.empty(), "Bij botsing is er nog geen filenaam aangemaakt");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    outfile << "!!! Botsing van Tram " << tram1->getVoertuigNummer() << " (" << tram1->getTypeString() << ") en Tram "
            << tram2->getVoertuigNummer() << " (" << tram2->getTypeString() << ") bij Station " << tram2->getHuidigStation()->getNaam() <<". !!! " << endl << endl;
}

