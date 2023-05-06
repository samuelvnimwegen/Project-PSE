#include "XMLParser.h"


int main(int argc, const char * argv[]) {
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("beteretest1.xml");
    TramSysteemOut output("tramregeling.txt", tramsysteem);
    output.advanced_summary();
    output.complete_summary();
    return 0;
}





