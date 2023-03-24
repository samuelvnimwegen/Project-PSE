#include "XMLParser.h"


int main(int argc, const char * argv[]) {
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("test1.xml");
    tramsysteem->makeTxtFile("tramregeling.txt");
    tramsysteem->complete_summary();
    tramsysteem->simulate(1);
    tramsysteem->complete_summary();
    return 0;
}





