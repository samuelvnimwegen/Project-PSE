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
    TramSysteem* metroSysteem = new TramSysteem;
    //  XML document
    TiXmlDocument doc;
    REQUIRE(doc.LoadFile(name.c_str()), "Bij readFile in XML_Parser.cc is de file niet correct geladen.");

    // Metronet: hier eerste child element.
    TiXmlElement* metronet = doc.FirstChildElement();

    // Root = eerste kind: hier STATION
    TiXmlElement* huidigMetronetObject = metronet->FirstChildElement();
    REQUIRE(metronet != 0, "Bij readFile in XMLParser.cpp was er geen metronet.");

    // Eerste loop om alle stations en trams aan te maken;
    while (metronet != 0) {
        while (huidigMetronetObject != 0) {
            // x is gelijk aan de naam van dit kind.
            string x = huidigMetronetObject->Value();
            REQUIRE((x == "STATION") or (x == "TRAM"), "Bij readFile van XMLParser was het type geen Station of Tram");
            // Als dit kind als naam STATION heeft: (hier het geval)
            if (x == "STATION") {
                // Maak nieuw huidigStation aan:
                Station *station;
                TiXmlElement *attribuut = huidigMetronetObject->FirstChildElement();
                string attribuutNaam = attribuut->Value();

                // Leest de naam in en slaat deze op.
                REQUIRE(attribuutNaam == "naam", "Bij readFile van XMLParser heeft het ingelezen huidigStation geen naam");
                string naam = attribuut->GetText();

                attribuut = attribuut->NextSiblingElement();
                attribuutNaam = attribuut->Value();

                // Leest het type in en maakt het bijhorende klasse-element aan.
                REQUIRE(attribuutNaam == "type", "Bij readFile van XMLParser heeft het ingelezen huidigStation geen type");
                string type = attribuut->GetText();
                REQUIRE((type == "Halte") or (type == "Metrostation"), "Bij readFile van XMLParser was het huidigStation-type niet herkend");
                if (type == "Metrostation"){
                    station = new Metrostation;
                }
                else {
                    station = new Halte;
                }

                // Naam geven en huidigStation pushen.
                station->setNaam(naam);
                metroSysteem->add_station(station);

            }
            else if (x == "TRAM") {
                // Maak nieuwe tram aan:
                Tram *tram;
                TiXmlElement *attribuut = huidigMetronetObject->FirstChildElement();
                string attribuutNaam = attribuut->Value();

                // Leest het lijnnummer in en slaat deze op.
                REQUIRE(attribuutNaam == "lijnNr", "Bij readFile van XMLParser heeft de ingelezen tram geen lijnNr");
                string lijnString = attribuut->GetText();
                int lijnNr = stringToInt(lijnString);


                attribuut = attribuut->NextSiblingElement();
                attribuutNaam = attribuut->Value();

                // Leest het type in en maakt het bijhorende klasse-element aan.
                REQUIRE(attribuutNaam == "type", "Bij readFile van XMLParser heeft het ingelezen huidigStation geen type");
                string type = attribuut->GetText();
                REQUIRE((type == "Stadslijner") or (type == "PCC") or (type == "Albatros"), "Bij readFile van XMLParser was het huidigStation-type niet herkend");
                if (type == "Stadslijner"){
                    tram = new Stadslijner;
                }
                else if (type == "PCC") {
                    tram = new PCC;
                }
                else {
                    tram = new Albatros;
                }

                // Lijnnummer ingeven
                tram->setLijnNr(lijnNr);

                // Als lijnNr nog niet in metroSysteem zit, er in zetten.
                Lijn* huidigeLijn;
                if (metroSysteem->findLijn(lijnNr) == 0){
                    huidigeLijn = new Lijn(lijnNr);
                    metroSysteem->addLijn(huidigeLijn);
                }
                // Anders de lijn zoeken en opslaan.
                else{
                    huidigeLijn = metroSysteem->findLijn(lijnNr);
                }

                // Tram aan lijn toevoegen:
                huidigeLijn->addTram(tram);

                attribuut = attribuut->NextSiblingElement();
                attribuutNaam = attribuut->Value();

                // Voertuignummer ingeven
                REQUIRE(attribuutNaam == "voertuigNr", "Bij readFile van XMLParser had een tram geen voertuignummer.");
                tram->setVoertuigNummer(stringToInt(attribuut->GetText()));

                attribuut = attribuut->NextSiblingElement();
                attribuutNaam = attribuut->Value();

                // Beginstation van tram ingeven.
                REQUIRE(attribuutNaam == "beginStation", "Bij readFile van XMLParser had een tram geen beginstation.");
                tram->setBeginStation(findStation(attribuut->GetText(), metroSysteem->getStations()));


                // Als het een PCC-tram is: Nog 3 attributen inlezen.
                if (tram->getTypeString() == "PCC"){
                    PCC* huidigeTram = dynamic_cast<PCC *>(tram);
                    huidigeTram->setKapot(false);
                    attribuut = attribuut->NextSiblingElement();
                    attribuutNaam = attribuut->Value();


                    // Aantal defecten:
                    REQUIRE(attribuutNaam == "aantalDefecten", "Bij readFile van XMLParser had een PCC geen aantal defecten");
                    string aantalDefecten = attribuut->GetText();
                    huidigeTram->setAantalDefecten(stringToInt(aantalDefecten));


                    attribuut = attribuut->NextSiblingElement();
                    attribuutNaam = attribuut->Value();

                    // Reparatie tijd:
                    REQUIRE(attribuutNaam == "reparatieTijd", "Bij readFile van XMLParser had een PCC geen reparatieTijd");
                    string reparatieTijd = attribuut->GetText();
                    huidigeTram->setReparatieTijd(stringToInt(reparatieTijd));

                    attribuut = attribuut->NextSiblingElement();
                    attribuutNaam = attribuut->Value();

                    // Reparatie kost:
                    REQUIRE(attribuutNaam == "reparatieKost", "Bij readFile van XMLParser had een PCC geen reparatieKost");
                    string reparatieKost = attribuut->GetText();
                    huidigeTram->setReparatieKost(stringToInt(reparatieKost));
                    huidigeTram->setTotaleKosten(0);
                    huidigeTram->setResterendeKosten(0);
                }


                // Tram in metroSysteem zetten
                metroSysteem->addTram(tram);
            }
            huidigMetronetObject = huidigMetronetObject->NextSiblingElement();
        }
        metronet = metronet->NextSiblingElement();
    }

    // Tweede loop om alle stations te verbinden.
    metronet = doc.FirstChildElement();
    huidigMetronetObject = metronet->FirstChildElement();
    while (metronet != 0){
        while (huidigMetronetObject != 0){
            string x = huidigMetronetObject->Value();
            if (x == "STATION"){
                // Station waarover het gaat opslaan
                TiXmlElement * attribuut = huidigMetronetObject->FirstChildElement();
                Station* stationHuidig = findStation(attribuut->GetText(), metroSysteem->getStations());

                // Naam en type hebben we al gedaan vorige loop
                attribuut = attribuut->NextSiblingElement();
                attribuut = attribuut->NextSiblingElement();

                // Volgende huidigStation zoeken en ingeven.
                string naamAttribuut = attribuut->Value();
                REQUIRE(naamAttribuut == "volgende", "Bij readFile van XMLParser had een huidigStation geen volgende huidigStation");
                stationHuidig->setVolgende(findStation(attribuut->GetText() , metroSysteem->getStations()));

                attribuut = attribuut->NextSiblingElement();

                // Vorige huidigStation zoeken en ingeven.
                naamAttribuut = attribuut->Value();
                REQUIRE(naamAttribuut == "vorige", "Bij readFile van XMLParser had een huidigStation geen vorig huidigStation");
                stationHuidig->setVorige(findStation(attribuut->GetText() , metroSysteem->getStations()));

                attribuut = attribuut->NextSiblingElement();

                // Spoornummer ingeven.
                naamAttribuut = attribuut->Value();
                REQUIRE(naamAttribuut == "spoor", "Bij readFile van XMLParser had een huidigStation geen spoornummer");
                stationHuidig->setSpoorNr(stringToInt(attribuut->GetText()));
            }
            huidigMetronetObject = huidigMetronetObject->NextSiblingElement();
        }
        metronet = metronet->NextSiblingElement();
    }

    // Alle trams en Stations aan de juiste lijnen toevoegen:
    int lijnenSize = metroSysteem->getLijnen().size();
    int stationSize = metroSysteem->getStations().size();

    // Eerst alle stations
    for (int i = 0; i < lijnenSize; ++i){
        Lijn* huidigeLijn = metroSysteem->getLijnen()[i];
        int lijnNr = huidigeLijn->getLijnnummer();

        // Alle stations afgaan:
        for (int j = 0; j < stationSize; ++j){
            Station* huidigStation = metroSysteem->getStations()[j];
            if (huidigStation->getSpoorNr() == lijnNr){
                huidigeLijn->addStation(huidigStation);
            }
        }
    }


    ENSURE(!metroSysteem->getTrams().empty(), "Bij readFile zijn er geen trams aangemaakt in het metroSysteem.");
    ENSURE(!metroSysteem->getStations().empty(), "Bij readFile zijn er geen stations aangemaakt in het metroSysteem.");
    ENSURE(metroSysteem->isConsistent(), "Bij readFile is het metroSysteem niet consistent.");
    tramsystemen.push_back(metroSysteem);
    return metroSysteem;
}