//
// Created by Space Movie 1992 on 02/03/2023.
//

#include "TramSysteem.h"

void TramSysteem::openFile() {
    TiXmlDocument doc;
    if(!doc.LoadFile("eenCD.xml")) {
        cerr << doc.ErrorDesc() << endl;
    };

    TiXmlElement* root = doc.FirstChildElement();
    if (root == nullptr) {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
    }
    if (root->GetText() == "STATION"){
        cout << "station" << endl;
        for(TiXmlElement* elem = root->FirstChildElement(); elem != nullptr;
            elem = elem->NextSiblingElement()) {
            string elemName = elem->Value();

            cout << elemName <<": " << elem->GetText() << endl;
        }
    }

}

TramSysteem::TramSysteem() {}
