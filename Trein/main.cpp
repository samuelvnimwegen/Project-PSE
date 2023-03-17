#include <iostream>
#include "TramSysteem.h"
#include "XML/tinyxml.h"
#include "gtest/gtest.h"
int main(int argc, const char * argv[]) {
    TramSysteem tramsysteem = TramSysteem();
    tramsysteem.openFile();
    cout << tramsysteem.getStations()[2]->getNaam() << endl;
    return 0;
}





