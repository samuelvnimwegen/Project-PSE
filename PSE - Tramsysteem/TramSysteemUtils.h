//
// Created by Samuel on 19/06/2023.
//

#ifndef TRAMSYSTEEM_CPP_TRAMSYSTEEMUTILS_H
#define TRAMSYSTEEM_CPP_TRAMSYSTEEMUTILS_H
#include "iostream"
#include "fstream"
#include "DesignByContract.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gebaseerd op de TicTacToeUtils.h in TicTacToe.git van Serge Demeyer:
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Checkt of file bestaat.
bool fileExists(const string &filename);

// Vergelijkt 2 files.
bool FileCompare(const string &filename1, const string &filename2);

// Kijkt of file empty is.
bool isEmpty(const string &filename);


#endif //TRAMSYSTEEM_CPP_TRAMSYSTEEMUTILS_H
