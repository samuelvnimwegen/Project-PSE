#include <iostream>
#include "TramSysteem.h"
#include "XML/tinyxml.h"
#include "gtest/gtest.h"
int main(int argc, const char * argv[]) {
    TramSysteem tramsysteem = TramSysteem();
    tramsysteem.openFile();
    tramsysteem.makeTxtFile();
    tramsysteem.move(tramsysteem.getTrams()[0], tramsysteem.getStations()[1]);
    return 0;
}





