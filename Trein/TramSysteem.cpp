//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "TramSysteem.h"
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

    // x is gelijk aan de naam van dit kind.
    string x = root->Value();
    // Als dit kind als naam STATION heeft: (hier het geval)
    if (x == "STATION"){
        // Maak nieuw station aan:
        auto* station = new Station();
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
                for (auto stat: getStations()){
                    if (stat->getNaam() == elem->GetText()){
                        station->setVolgende(stat);
                        gevonden= true;
                    }
                }
                // Als station nog niet eerder vermeld was, wordt deze toegevoegd.
                if (!gevonden){
                    auto * st = new Station();
                    st->setNaam(elem->GetText());
                    add_station(st);
                    station->setVolgende(st);
                }

            }
            else if (elemName == "vorige"){
                bool gevonden = false;
                for (auto stat: getStations()){
                    if (stat->getNaam() == elem->GetText()){
                        station->setVorige(stat);
                        gevonden= true;
                    }
                }
                // Als station nog niet eerder vermeld was, wordt deze toegevoegd.
                if (!gevonden){
                    auto * st = new Station();
                    st->setNaam(elem->GetText());
                    add_station(st);
                    station->setVorige(st);
                }

            }


            else if (elemName == "spoorNr"){
                int nr = stoi(elem->GetText());
                station->setSpoorNr(nr);
            }
            else{
                cout << "Type niet herkend" << endl;
            }
            cout << elemName <<": " << elem->GetText() << endl;
        }
    }

}

TramSysteem::TramSysteem() {}
