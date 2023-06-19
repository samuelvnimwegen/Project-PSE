//
// Created by Samuel on 19/06/2023.
//

#include "TramSysteemUtils.h"

bool fileExists(const string &filename) {
    ifstream file(filename.c_str());
    return file.good();
}

bool FileCompare(const string &filename1, const string &filename2) {
    REQUIRE(fileExists(filename1), "Bij FileCompare bestond file 1 niet");
    REQUIRE(fileExists(filename2), "Bij FileCompare bestond file 2 niet");

    ifstream file1;
    ifstream file2;
    char file1Read, file2Read;
    bool resultaat = true;

    file1.open(filename1.c_str());
    file2.open(filename2.c_str());

    while (resultaat and file1.good() and file2.good()) {
        file1.get(file1Read);
        file2.get(file2Read);
        resultaat = (file1Read == file2Read);
    };
    if (resultaat) {
        resultaat = (!file1.good()) and (!file2.good());
    };

    file1.close();
    file2.close();
    return resultaat;
}

bool isEmpty(const string &filename) {
    ifstream file(filename.c_str());
    return file.peek() == std::ifstream::traits_type::eof();
}

