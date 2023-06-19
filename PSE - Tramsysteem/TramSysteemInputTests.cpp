//
// Created by Samuel on 18/06/2023.
//

#include "fstream"
#include "TramSysteemUtils.h"

class TramSysteemInputTest: public  ::testing::Test{
protected:
    virtual void SetUp(){
    }

    virtual void TearDown(){}
};


// Happy day test:
TEST_F(TramSysteemInputTest, TramSysteemInputHappyDay){
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("testInput/TramSysteemInputHappyDay.xml");
    TramSysteemOut* output = new TramSysteemOut("testInput/TramSysteemInputHappyDay.txt", tramsysteem);
    tramsysteem->setOutput(output);
    EXPECT_TRUE(int(tramsysteem->getTrams().size()) == 5);
    EXPECT_TRUE(int(tramsysteem->getStations().size()) == 9);
    EXPECT_TRUE(int(tramsysteem->getLijnen().size()) == 2);

    Tram* pccTram = tramsysteem->getStations()[2]->getTramInStation();
    PCC* pcc = dynamic_cast<PCC*>(pccTram);
    EXPECT_FALSE(pcc->isKapot());

    EXPECT_TRUE(tramsysteem->getStations()[0]->tramInStation());
    EXPECT_TRUE(tramsysteem->getStations()[1]->tramInStation());
    EXPECT_TRUE(tramsysteem->getStations()[2]->tramInStation());

    output->advanced_summary();
    tramsysteem->simulate(1);

    EXPECT_FALSE(pcc->isKapot());

    EXPECT_TRUE(tramsysteem->getStations()[0]->tramInStation());
    EXPECT_TRUE(tramsysteem->getStations()[1]->tramInStation());
    EXPECT_FALSE(tramsysteem->getStations()[2]->tramInStation());

    output->advanced_summary();
    tramsysteem->simulate(1);

    EXPECT_TRUE(tramsysteem->getStations()[0]->tramInStation());
    EXPECT_TRUE(tramsysteem->getStations()[1]->tramInStation());
    EXPECT_FALSE(tramsysteem->getStations()[2]->tramInStation());
    EXPECT_TRUE(pcc->isKapot());

    output->advanced_summary();

    tramsysteem->simulate(1);
    EXPECT_TRUE(tramsysteem->getStations()[0]->tramInStation());
    EXPECT_TRUE(tramsysteem->getStations()[1]->tramInStation());
    EXPECT_FALSE(tramsysteem->getStations()[2]->tramInStation());
    EXPECT_TRUE(pcc->isKapot());

    output->advanced_summary();
    tramsysteem->simulate(1);

    EXPECT_TRUE(tramsysteem->getStations()[0]->tramInStation());
    EXPECT_TRUE(tramsysteem->getStations()[1]->tramInStation());
    EXPECT_FALSE(tramsysteem->getStations()[2]->tramInStation());
    EXPECT_FALSE(pcc->isKapot());
    EXPECT_TRUE(pcc->kanBewegen());


    output->advanced_summary();
    tramsysteem->simulate(1);

    EXPECT_FALSE(tramsysteem->getStations()[0]->tramInStation());
    EXPECT_TRUE(tramsysteem->getStations()[1]->tramInStation());
    EXPECT_FALSE(tramsysteem->getStations()[2]->tramInStation());

    output->advanced_summary();

}

TEST_F(TramSysteemInputTest, TramSysteemInputSyntax){
    XMLParser parser = XMLParser();

    // missende "<"
    string filename = "testInput/Syntax1.xml";
    EXPECT_TRUE(fileExists(filename));
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile in XML_Parser.cc was er een syntax-error.");

    // missende ">"
    filename = "testInput/Syntax2.xml";
    EXPECT_TRUE(fileExists(filename));
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile in XML_Parser.cc was er een syntax-error.");

    // extra "/"
    filename = "testInput/Syntax3.xml";
    EXPECT_TRUE(fileExists(filename));
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile in XML_Parser.cc was er een syntax-error.");

    // te weinig "/"
    filename = "testInput/Syntax4.xml";
    EXPECT_TRUE(fileExists(filename));
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile in XML_Parser.cc was er een syntax-error.");

}

TEST_F(TramSysteemInputTest, TramSysteemConsistentie){
    XMLParser parser = XMLParser();

    string filename = "testInput/Consistentie1.xml";
    TramSysteem* tramSysteem = parser.readFile(filename);
    TramSysteemOut* tramSysteemOut = new TramSysteemOut("testInput/Consistentie1.txt", tramSysteem);
    tramSysteem->setOutput(tramSysteemOut);

    tramSysteemOut->complete_summary();
    tramSysteemOut->advanced_summary();
    for (int i = 0; i < 5; ++i){
        tramSysteem->simulate(1);
        tramSysteemOut->advanced_summary();
    }

    filename = "testInput/Consistentie2.xml";
    tramSysteem = parser.readFile(filename);
    tramSysteemOut = new TramSysteemOut("testInput/Consistentie2.txt", tramSysteem);
    tramSysteem->setOutput(tramSysteemOut);

    tramSysteemOut->complete_summary();
    tramSysteemOut->advanced_summary();
    for (int i = 0; i < 5; ++i){
        tramSysteem->simulate(1);
        tramSysteemOut->advanced_summary();
    }

}

TEST_F(TramSysteemInputTest, TramSysteemInconsistentie){
    XMLParser parser = XMLParser();

    // Station mist een volgende
    string filename = "testInput/Inconsistentie1.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile van XMLParser had een huidigStation geen volgende");

    // Station mist een spoornummer
    filename = "testInput/Inconsistentie2.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile van XMLParser had een huidigStation geen spoornummer");

    // Tram mist een beginstation
    filename = "testInput/Inconsistentie3.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile van XMLParser had een tram geen beginstation.");

    // Onbekend type tram
    filename = "testInput/Inconsistentie4.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile van XMLParser was het huidig Tram-type niet herkend");

    // Onbekend type station
    filename = "testInput/Inconsistentie5.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile van XMLParser was het huidig Station-type niet herkend");

    // Onovereenkomende lijnnummers startstation en tram:
    filename = "testInput/Inconsistentie6.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij consistencyCheck van TramSysteem kwamen de lijnnummers van een beginstation niet overeen met die van de tram");

    // Volgend station niet op lijn
    filename = "testInput/Inconsistentie7.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij consistencyCheck van TramSysteem hadden het volgende of vorige station niet hetzelfde spoornummer");

    // Gedupliceerde voertuignummers
    filename = "testInput/Inconsistentie8.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij consistencyCheck van TramSysteem waren er duplicate voertuignummers");


    // Gedupliceerde namen van tramstations
    filename = "testInput/Inconsistentie9.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij readFile van XMLParser was er al een station met dezelfde naam");


    // Verschillende trams met hetzelfde beginstation
    filename = "testInput/Inconsistentie10.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij consistencyCheck van TramSysteem waren trams met hetzelfde startstation");

    // Niet alle stations op lijn zijn bereikbaar.
    filename = "testInput/Inconsistentie11.xml";
    EXPECT_DEATH(parser.readFile(filename), "Bij consistencyCheck van TramSysteem kon niet elk station van de lijn bereikt worden");

}

