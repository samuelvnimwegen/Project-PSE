#include "TramSysteem.h"


int main(int argc, const char * argv[]) {
    TramSysteem tramsysteem = TramSysteem();
    tramsysteem.readFile("test1.xml");
    tramsysteem.makeTxtFile("tramregeling.txt");
    tramsysteem.station_summary();
    return 0;
}





