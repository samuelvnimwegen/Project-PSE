#include "TramSysteem.h"


int main(int argc, const char * argv[]) {
    TramSysteem tramsysteem = TramSysteem();
    tramsysteem.readFile("test1.xml");
    tramsysteem.makeTxtFile("tramregeling.txt");
    tramsysteem.tram_summary();
    tramsysteem.simulate(1);
    tramsysteem.tram_summary();
    return 0;
}





