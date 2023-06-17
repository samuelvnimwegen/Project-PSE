//
// Created by Samuel on 24/03/2023.
//

#include "TramSysteemOut.h"
#include "TramSysteem.h"


TramSysteemOut::TramSysteemOut(const string &name, TramSysteem* ts) : filename(name), tramSysteem(ts) {
    REQUIRE(name.substr(name.length() - 4) == ".txt", "Bij TramSysteemOut was het de filename geen .txt file");
    REQUIRE(ts != 0, "Bij TramSysteemOut was het tramsysteem leeg");
    initCheck = this;
    ofstream outfile(name.c_str());
    filename = name;
    outfile << "----- Tramregeling ----- " << endl << endl;

    ifstream file;
    file.open(filename.c_str());
    ENSURE(this->properlyInitialized(), "TramSysteemOut bij TramSysteemOut() niet correct initialised");
    ENSURE(file, "Bij TramSysteemOut moet er een output file aangemaakt zijn");
    ENSURE(getFilename() == name, "Bij TramSysteemOut is de filename niet correct opgeslagen");
    ENSURE(getTramSysteem() == ts, "Bij TramSysteemOut is de het tramsysteem niet correct aangepast");
}

void TramSysteemOut::tram_summary() {
    REQUIRE(!filename.empty(), "Bij tram_summary van TramSysteemOut is er nog geen filenaam aangemaakt");
    REQUIRE(this->properlyInitialized(), "TramSysteemOut bij tram_summary niet correct initialised");
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
    REQUIRE(this->properlyInitialized(), "TramSysteemOut bij station_summary niet correct initialised");
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
    REQUIRE(this->properlyInitialized(), "TramSysteemOut bij complete_summary niet correct initialised");
    REQUIRE(!filename.empty(), "Bij complete_summary is er nog geen filenaam aangemaakt");
    station_summary();
    tram_summary();
}

void TramSysteemOut::advanced_summary() {
    REQUIRE(this->properlyInitialized(), "TramSysteemOut bij advanced_summary niet correct initialised");
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
    REQUIRE(this->properlyInitialized(), "TramSysteemOut bij move niet correct initialised");
    REQUIRE(!filename.empty(), "Bij move is er nog geen filenaam aangemaakt");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    outfile << "Tram " << tram->getVoertuigNummer() << " (" << tram->getTypeString() << ") reed van "
    << begin->getTypeString() <<" " << begin->getNaam() << " naar " << eind->getTypeString() << " "
    << eind->getNaam() << " via lijn " << tram->getLijnNr() << "."<< endl << endl;
}

void TramSysteemOut::herstel(Tram *tram, Station *halte) {
    REQUIRE(this->properlyInitialized(), "TramSysteemOut bij herstel niet correct initialised");
    REQUIRE(!filename.empty(), "Bij herstel is er nog geen filenaam aangemaakt");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    outfile << "Tram " << tram->getVoertuigNummer() << " (" << tram->getTypeString() << ") is bezig met herstel bij "
    << halte->getTypeString() << " " << halte->getNaam() << " op lijn " << tram->getLijnNr() <<"." << endl << endl;
}

void TramSysteemOut::botsing(Tram *tram1, Tram *tram2) {
    REQUIRE(this->properlyInitialized(), "TramSysteemOut bij botsing niet correct initialised");
    REQUIRE(!filename.empty(), "Bij botsing is er nog geen filenaam aangemaakt");
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    outfile << "!!! Botsing van Tram " << tram1->getVoertuigNummer() << " (" << tram1->getTypeString() << ") en Tram "
            << tram2->getVoertuigNummer() << " (" << tram2->getTypeString() << ") bij Station " << tram2->getHuidigStation()->getNaam() <<". !!! " << endl << endl;
}

bool TramSysteemOut::properlyInitialized() {
    return initCheck == this;
}

string TramSysteemOut::getFilename(){
    REQUIRE(this->properlyInitialized(), "Bij getFilename is TramSysteemOut niet correct initialised");
    string result = filename;
    ENSURE(result.substr(result.length() - 4) == ".txt", "Bij getFilename van TramSysteemOut was de filename geen .txt file");
    return result;
}

TramSysteem *TramSysteemOut::getTramSysteem() {
    REQUIRE(this->properlyInitialized(), "Bij getTramSysteem is TramSysteemOut niet correct initialised");
    TramSysteem* result = tramSysteem;
    ENSURE(result != 0, "Bij getTramSysteem van TramSysteemOut was het systeem niet bestaand");
    return result;
}

