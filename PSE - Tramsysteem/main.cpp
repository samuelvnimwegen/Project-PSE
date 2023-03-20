#include "TramSysteem.h"


int main(int argc, const char * argv[]) {
    TramSysteem tramsysteem = TramSysteem();
    tramsysteem.readFile("test1.xml");
    tramsysteem.makeTxtFile("tramregeling.txt");
    tramsysteem.complete_summary();
    return 0;
}





