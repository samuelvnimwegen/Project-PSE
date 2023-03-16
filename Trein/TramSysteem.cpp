//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "TramSysteem.h"

int stringToInt(const string& s){
    int i;
    std::istringstream(s) >> i;
    return i;
}


// Opent een file
void TramSysteem::openFile() {

    //  XML document
    TiXmlDocument doc;
    // opent XML met deze naam, anders foutmelding:
    if(!doc.LoadFile("eenCD.xml")) {
        cerr << doc.ErrorDesc() << endl;
    };
    // Root = eerste kind: hier STATION
    TiXmlElement* root = doc.FirstChildElement();

    // Checkt of dit kind de nullptr is en geeft dan foutmelding.
    if (root == nullptr) {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
    }
    while (root != nullptr){
        // x is gelijk aan de naam van dit kind.
        string x = root->Value();
        // Als dit kind als naam STATION heeft: (hier het geval)
        if (x == "STATION"){
            // Maak nieuw station aan:
            Station* station = new Station();
            // Ga alle kinderen van het kind 'STATION' af. Begin bij eerste kind (root->FirstChildElement()),daarna gwn
            // telkens naar volgende kind (elem = elem->NextSiblingElement()), als kind gelijk is aan nullptr aka er is geen kind meer
            // dan stop.
            for(TiXmlElement* elem = root->FirstChildElement(); elem != nullptr;
                elem = elem->NextSiblingElement()) {

                // elemName is bv. naam:
                // elem.value is bv. Antwerpen Centraal:
                string elemName = elem->Value();
                // Als elemName naam is: geef het nieuwe station de naam van de tekst hiervan.
                if (elemName == "naam"){
                    station->naam = elem->GetText();
                }
                else if (elemName == "volgende"){
                    bool gevonden = false;
                    for (int i = 0; i < getStations().size(); ++i){
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
                    for (int i = 0; i < getStations().size(); ++i){
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
            add_station(station);
        }
        else if (x == "TRAM"){
            // Maak nieuwe tram aan:
            Tram* tram = new Tram();

            for(TiXmlElement* elem = root->FirstChildElement(); elem != nullptr;
                elem = elem->NextSiblingElement()) {

                string elemName = elem->Value();

                if (elemName == "lijnNr"){
                    tram->setLijnNr(stringToInt(elem->GetText()));
                }
                else if (elemName == "snelheid"){
                    tram->setSnelheid(stringToInt(elem->GetText()));
                }
                else if (elemName == "beginStation"){
                    bool gevonden = false;
                    for (int i = 0; i < getStations().size(); ++i){
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
