//
// Created by Samuel on 24/03/2023.
//

#ifndef TRAMSYSTEEM_CPP_XMLPARSER_H
#define TRAMSYSTEEM_CPP_XMLPARSER_H
#include "TramSysteem.h"
#include "iostream"


class XMLParser {
    string filename;
    vector<TramSysteem*> tramsystemen;
public:
    TramSysteem* readFile(const string &name);
    /**
     * REQUIRE(doc.LoadFile(name.c_str()), "Bij readFile in XML_Parser.cc is de file niet correct geladen.");
     * REQUIRE(metronet != 0, "Bij readFile in XMLParser.cpp was er geen metronet.");
     * ENSURE(!metroSysteem->getTrams().empty(), "Bij readFile zijn er geen trams aangemaakt in het metroSysteem.");
     * ENSURE(!metroSysteem->getStations().empty(), "Bij readFile zijn er geen stations aangemaakt in het metroSysteem.");
     * ENSURE(metroSysteem->isConsistent(), "Bij readFile is het metroSysteem niet consistent.");
     */
};


#endif //TRAMSYSTEEM_CPP_XMLPARSER_H
