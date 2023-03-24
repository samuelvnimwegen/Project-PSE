//
// Created by Samuel on 24/03/2023.
//

#include "TramSysteemOut.h"
void makeTxtFile(const string& name);
/**
 * REQUIRE(name.substr(name.length() - 4) == ".txt", "moet een .txt file zijn");
 */


TramSysteemOut::TramSysteemOut(const string &name) : filename(name) {
    REQUIRE(name.substr(name.length() - 4) == ".txt", "moet een .txt file zijn");
    ofstream outfile(name.c_str());
    filename = name;
    outfile << "----- Tramregeling ----- " << endl << endl;

    ifstream file;
    file.open(filename.c_str());
    ENSURE(file, "file moet aangemaakt zijn");
}
