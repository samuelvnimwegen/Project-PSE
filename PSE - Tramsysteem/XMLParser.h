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
     *
     */
};


#endif //TRAMSYSTEEM_CPP_XMLPARSER_H
