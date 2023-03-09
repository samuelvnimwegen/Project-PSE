//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "TramSysteem.h"

void TramSysteem::openFile(string) {
    TiXmlDocument doc;
    if(!doc.LoadFile("eenCD.xml")) {
        cerr << doc.ErrorDesc() << endl;
    };

    TiXmlElement* root = doc.FirstChildElement();
    if (root == nullptr) {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
    }

    for(TiXmlElement* elem = root->FirstChildElement(); elem != nullptr;
        elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        if(elemName == "ARTIST" or elemName == "TITLE") {
            cout << elemName << ": "<< elem->GetText() << endl;
        }
    }
}
