//
// Created by Samuel van Nimwegen on 02/03/2023.
//

#include "TramSysteem.h"

// Er waren wat problemen
int stringToInt(const string& s){
    int i;
    std::istringstream(s) >> i;
    return i;
}


// Opent een file
bool TramSysteem::readFile(const string &name) {

    //  XML document
    TiXmlDocument doc;
    // opent XML met deze naam, anders foutmelding:
    if(!doc.LoadFile(name.c_str())) {
        cerr << doc.ErrorDesc() << endl;
        return false;
    };
    // Root = eerste kind: hier STATION
    TiXmlElement* root = doc.FirstChildElement();

    // Checkt of dit kind de nullptr is en geeft dan foutmelding.
    if (root == 0) {
        cerr << "Failed to load file: No root element." << endl;
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
                        station->naam = elem->GetText();
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
                else{
                    cout << "Type niet herkend" << endl;
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
                    cout << "Type niet herkend" << endl;
                }
            }
            addTram(tram);
        }
        else{
            cout << "type niet herkent" << endl;
        }
        root = root->NextSiblingElement();
    }
    return true;
}

TramSysteem::TramSysteem() {}

bool TramSysteem::add_station(Station *station) {
    stations.push_back(station);
    return true;
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

void TramSysteem::addTram(Tram * tr) {
    trams.push_back(tr);
}

void TramSysteem::makeTxtFile(const string& name) {
    ofstream outfile(name.c_str());
    filename = name;
    outfile << "----- Tramregeling ----- " << endl << endl;
}



bool TramSysteem::move(Tram* tram, Station* station) {
    if (filename.empty()){
        cerr << "error: nog geen outputfile gemaakt" << endl;
        return false;
    }
    Station* vorig_station = tram->getStation();
    if (tram->getLijnNr() != station->getSpoorNr()){
        cout << "tram en station niet op dezelfde lijn" << endl;
        return false;
    }
    if (vorig_station == station){
        cout << "het oude station is hetzelfde als het nieuwe station" << endl;
        return false;
    }
    tram->setStation(station);

    ofstream outfile;
    outfile.open(filename.c_str(), ios_base::app);
    outfile << "Tram " << tram->getLijnNr() << " reed van Station " << vorig_station->getNaam() << " naar Station "
    << station->getNaam() << "." << endl << endl;
    outfile.close();
    return true;
}

bool TramSysteem::simulate(int tijd) {
    if (filename.empty()){
        cerr << "error: nog geen outputfile gemaakt" << endl;
        return false;
    }
    int aantalTrams = trams.size();
    int counter = 0;
    if (tijd > 0){
        while (counter < tijd){
            for (int i = 0; i < aantalTrams; ++i){
                if (trams[i]->getStation()->volgende != 0){
                    move(trams[i], trams[i]->getStation()->getVolgende());
                }
            }
            counter += 1;
        }
    }
    else if (tijd < 0){
        int negatieve_tijd = -tijd;
        while (counter < negatieve_tijd){
            for (int i = 0; i < aantalTrams; ++i){
                if (trams[i]->getStation()->vorige != 0){
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
        cerr << "error: nog geen outputfile gemaakt" << endl;
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
    size = getTrams().size();
    for (int i = 0; i < size; ++i){
        Tram* tram = getTrams()[i];
        outfile << "Tram "<<tram->getLijnNr() << " in Station " << tram->getStation()->getNaam() << endl << endl;
    }
    return true;
}

bool TramSysteem::tram_summary() {
    if (filename.empty()){
        cerr << "error: nog geen outputfile gemaakt" << endl;
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
        cerr << "error: nog geen outputfile gemaakt" << endl;
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
