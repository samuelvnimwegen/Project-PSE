//
// Created by Samuel on 24/03/2023.
//

#include "XMLParser.h"

// Hulpfunctie die strings van integers naar integers omzet.
int stringToInt(const string& s){
    int i;
    std::istringstream(s) >> i;
    return i;
}

TramSysteem* XMLParser::readFile(const string &name) {
    TramSysteem* systeem = new TramSysteem;
    //  XML document
    TiXmlDocument doc;

    // opent XML met deze naam, anders foutmelding:
    if(!doc.LoadFile(name.c_str())) {
        return 0;
    };
    // Root = eerste kind: hier STATION
    TiXmlElement* root = doc.FirstChildElement();

    // Checkt of dit kind de nullptr is en geeft dan foutmelding.
    if (root == 0) {
        doc.Clear();
        return 0;
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
                int size = systeem->getStations().size();
                // elemName is bv. naam:
                // elem.value is bv. Antwerpen Centraal:
                string elemName = elem->Value();
                // Als elemName naam is: geef het nieuwe station de naam van de tekst hiervan.
                if (elemName == "naam"){
                    string naam = elem->GetText();
                    // Checkt of er al een station met deze naam in het systeem staat.
                    bool gevonden = 0;
                    for (int i = 0; i < size; ++i){
                        if (systeem->getStations()[i]->getNaam() == naam){
                            station = systeem->getStations()[i];
                            gevonden = true;
                        }
                    }
                    // Als het station nog niet eerder vermeld was, wordt deze gemaakt.
                    if (!gevonden){
                        station = new Station();
                        station->setNaam(elem->GetText());
                        systeem->add_station(station);
                    }

                }
                else if (elemName == "volgende"){
                    bool gevonden = 0;
                    for (int i = 0; i < size; ++i){
                        if (systeem->getStations()[i]->getNaam() == elem->GetText()){
                            station->setVolgende(systeem->getStations()[i]);
                            gevonden= true;
                        }
                    }
                    // Als station nog niet eerder vermeld was, wordt deze toegevoegd.
                    if (!gevonden){
                        Station * st = new Station();
                        st->setNaam(elem->GetText());
                        systeem->add_station(st);
                        station->setVolgende(st);
                    }

                }
                else if (elemName == "vorige"){
                    bool gevonden = 0;
                    for (int i = 0; i < size; ++i){
                        if (systeem->getStations()[i]->getNaam() == elem->GetText()){
                            station->setVorige(systeem->getStations()[i]);
                            gevonden= true;
                        }
                    }
                    // Als station nog niet eerder vermeld was, wordt deze toegevoegd.
                    if (!gevonden){
                        Station * st = new Station();
                        st->setNaam(elem->GetText());
                        systeem->add_station(st);
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
                int size = systeem->getStations().size();
                string elemName = elem->Value();

                if (elemName == "lijnNr"){
                    tram->setLijnNr(stringToInt(elem->GetText()));
                }
                else if (elemName == "snelheid"){
                    tram->setSnelheid(stringToInt(elem->GetText()));
                }
                else if (elemName == "voertuigNr"){
                    tram->setVoertuigNummer(stringToInt(elem->GetText()));
                }
                else if (elemName == "beginStation"){
                    bool gevonden = 0;
                    for (int i = 0; i < size; ++i){
                        if (systeem->getStations()[i]->getNaam() == elem->GetText()){
                            tram->setBeginStation(systeem->getStations()[i]);
                            gevonden= true;
                        }
                    }
                    // Als station nog niet eerder vermeld was, wordt deze toegevoegd.
                    if (!gevonden){
                        Station * st = new Station();
                        st->setNaam(elem->GetText());
                        systeem->add_station(st);
                        tram->setBeginStation(st);
                    }

                }
                else{
                }
            }
            systeem->addTram(tram);
        }
        else{
        }
        root = root->NextSiblingElement();
    }
    if (systeem->getTrams().empty() or systeem->getStations().empty()){
        return 0;
    }
    tramsystemen.push_back(systeem);
    return systeem;
}