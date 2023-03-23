//
// Created by Samuel van Nimwegen on 02/03/2023.
//

#include "TramSysteem.h"

// Hulpfunctie die strings van integers naar integers omzet.
int stringToInt(const string& s){
    int i;
    std::istringstream(s) >> i;
    return i;
}



bool TramSysteem::readFile(const string &name) {

    //  XML document
    TiXmlDocument doc;
    // opent XML met deze naam, anders foutmelding:
    if(!doc.LoadFile(name.c_str())) {
        return false;
    };
    // Root = eerste kind: hier STATION
    TiXmlElement* root = doc.FirstChildElement();

    // Checkt of dit kind de nullptr is en geeft dan foutmelding.
    if (root == 0) {
        doc.Clear();
        return false;
    }
    while (root != 0){
        // x is gelijk aan de naam van dit kind.
        string x = root->Value();
        // Als dit kind als naam STATION heeft: (hier het geval)
        if (x == "STATION"){
            // Maak nieuw station aan:
            Station* station;
            // Ga alle kinderen van het kind 'STATION' af. Begin bij eerste kind (root->FirstChildElement()),daarna gwn
            // telkens naar volgende kind (elem = elem->NextSiblingElement()), als kind gelijk is aan nullptr aka er is geen kind meer
            // dan stop.
            for(TiXmlElement* elem = root->FirstChildElement(); elem != 0;
                elem = elem->NextSiblingElement()) {
                int size = getStations().size();
                // elemName is bv. naam:
                // elem.value is bv. Antwerpen Centraal:
                string elemName = elem->Value();
                // Als elemName naam is: geef het nieuwe station de naam van de tekst hiervan.
                if (elemName == "naam"){
                    string naam = elem->GetText();
                    // Checkt of er al een station met deze naam in het systeem staat.
                    bool gevonden = false;
                    for (int i = 0; i < size; ++i){
                        if (getStations()[i]->getNaam() == naam){
                            station = getStations()[i];
                            gevonden = true;
                        }
                    }
                    // Als het station nog niet eerder vermeld was, wordt deze gemaakt.
                    if (!gevonden){
                        station = new Station();
                        station->setNaam(elem->GetText());
                        add_station(station);
                    }

                }
                else if (elemName == "volgende"){
                    bool gevonden = false;
                    for (int i = 0; i < size; ++i){
                        if (getStations()[i]->getNaam() == elem->GetText()){
                            station->setVolgende(getStations()[i]);
                            gevonden= true;
                        }
                    }
                    // Als station nog niet eerder vermeld was, wordt deze toegevoegd.
                    if (!gevonden){
                        Station * st = new Station();
                        st->setNaam(elem->GetText());
                        add_station(st);
                        station->setVolgende(st);
                    }

                }
                else if (elemName == "vorige"){
                    bool gevonden = false;
                    for (int i = 0; i < size; ++i){
                        if (getStations()[i]->getNaam() == elem->GetText()){
                            station->setVorige(getStations()[i]);
                            gevonden= true;
                        }
                    }
                    // Als station nog niet eerder vermeld was, wordt deze toegevoegd.
                    if (!gevonden){
                        Station * st = new Station();
                        st->setNaam(elem->GetText());
                        add_station(st);
                        station->setVorige(st);
                    }

                }
                else if (elemName == "spoorNr"){
                    int nr = stringToInt(elem->GetText());
                    station->setSpoorNr(nr);
                }
            }
        }
        else if (x == "TRAM"){
            // Maak nieuwe tram aan:
            Tram* tram = new Tram();

            for(TiXmlElement* elem = root->FirstChildElement(); elem != 0;
                elem = elem->NextSiblingElement()) {
                int size = getStations().size();
                string elemName = elem->Value();

                if (elemName == "lijnNr"){
                    tram->setLijnNr(stringToInt(elem->GetText()));
                }
                else if (elemName == "snelheid"){
                    tram->setSnelheid(stringToInt(elem->GetText()));
                }
                else if (elemName == "beginStation"){
                    bool gevonden = false;
                    for (int i = 0; i < size; ++i){
                        if (getStations()[i]->getNaam() == elem->GetText()){
                            tram->setBeginStation(getStations()[i]);
                            gevonden= true;
                        }
                    }
                    // Als station nog niet eerder vermeld was, wordt deze toegevoegd.
                    if (!gevonden){
                        Station * st = new Station();
                        st->setNaam(elem->GetText());
                        add_station(st);
                        tram->setBeginStation(st);
                    }

                }
                else{
                }
            }
            addTram(tram);
        }
        else{
        }
        root = root->NextSiblingElement();
    }
    if (trams.empty() or stations.empty()){
        return false;
    }
    return true;
}

TramSysteem::TramSysteem() {}

bool TramSysteem::add_station(Station *station) {
    if (station == 0){
        return false;
    }
    stations.push_back(station);

    int size = stations.size();
    if (stations[size - 1] == station){
        return true;
    }
    return false;
}
 vector<Station *> & TramSysteem::getStations() {
    return stations;
}

void TramSysteem::setStations(const vector<Station *> &statio) {
    stations = statio;
}

const vector<Tram *> &TramSysteem::getTrams() const {
    return trams;
}

void TramSysteem::setTrams(const vector<Tram *> &tr) {
    trams = tr;
}

bool TramSysteem::addTram(Tram * tr) {
    if (tr == 0){
        return false;
    }
    trams.push_back(tr);

    int size = trams.size();
    if (trams[size - 1] == tr){
        return true;
    }
    return false;
}

void TramSysteem::makeTxtFile(const string& name) {
    ofstream outfile(name.c_str());
    filename = name;
    outfile << "----- Tramregeling ----- " << endl << endl;

}



bool TramSysteem::move(Tram* tram, Station* station) {
    if (filename.empty()){
        return false;
    }
    Station* vorig_station = tram->getStation();
    if (tram->getLijnNr() != station->getSpoorNr()){
        return false;
    }
    if (vorig_station == station){
        return false;
    }
    tram->setStation(station);
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);
    outfile << "Tram " << tram->getLijnNr() << " reed van Station " << vorig_station->getNaam() << " naar Station "
    << station->getNaam() << "." << endl << endl;
    outfile.close();

    if (tram->getStation() == station){
        return true;
    }
    return false;
}

bool TramSysteem::simulate(int tijd) {
    if (filename.empty()){
        return false;
    }
    if (!isConsistent()){
        return false;
    }
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
    if (filename.empty()){
        return false;
    }
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


bool TramSysteem::tram_summary() {
    if (filename.empty()){
        return false;
    }
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    int size = getTrams().size();
    for (int i = 0; i < size; ++i){
        Tram* tram = getTrams()[i];
        outfile << "Tram "<<tram->getLijnNr() << " in Station " << tram->getStation()->getNaam() << endl << endl;
    }
    return true;
}

bool TramSysteem::station_summary() {
    if (filename.empty()){
        return false;
    }
    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);

    int size = getStations().size();
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
