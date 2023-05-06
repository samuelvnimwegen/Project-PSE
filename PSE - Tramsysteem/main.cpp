#include "XMLParser.h"


int main(int argc, const char * argv[]) {
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("beteretest1.xml");
    TramSysteemOut* output = new TramSysteemOut("tramregeling.txt", tramsysteem);
    tramsysteem->setOutput(output);

    output->advanced_summary();
    output->complete_summary();
    tramsysteem->simulate(3);
    return 0;
}





