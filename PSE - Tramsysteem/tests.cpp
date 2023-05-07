//
// Created by Samuel on 16/03/2023.
//
#include "gtest/gtest.h"
#include "XMLParser.h"
using namespace std;

class TramsysteemTest: public  ::testing::Test{
protected:
    virtual void SetUp(){
    }

    virtual void TearDown(){}
};

// Happy day test:
TEST_F(TramsysteemTest, happyDay){
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("happyDay.xml");
    TramSysteemOut* output = new TramSysteemOut("tramregeling.txt", tramsysteem);
    tramsysteem->setOutput(output);
    EXPECT_TRUE(tramsysteem->getTrams().size() == 4);
    EXPECT_TRUE(tramsysteem->getStations().size() == 6);
    EXPECT_TRUE(tramsysteem->getLijnen().size() == 2);

    Tram* tram1 = tramsysteem->getStations()[1]->getTramInStation();
    Tram* tram2 = tramsysteem->getStations()[2]->getTramInStation();
    EXPECT_FALSE(tram1->isKapot());
    EXPECT_FALSE(tram2->isKapot());

    EXPECT_TRUE(tramsysteem->getStations()[0]->getTramInStation() == 0);
    EXPECT_TRUE(tramsysteem->getStations()[1]->getTramInStation() != 0);
    EXPECT_TRUE(tramsysteem->getStations()[2]->getTramInStation() != 0);

    output->complete_summary();
    output->advanced_summary();
    tramsysteem->simulate(1);

    EXPECT_FALSE(tram1->isKapot());
    EXPECT_FALSE(tram2->isKapot());

    EXPECT_TRUE(tramsysteem->getStations()[0]->getTramInStation() != 0);
    EXPECT_TRUE(tramsysteem->getStations()[1]->getTramInStation() == 0);
    EXPECT_TRUE(tramsysteem->getStations()[2]->getTramInStation() != 0);

    output->complete_summary();
    output->advanced_summary();

    tramsysteem->simulate(1);

    EXPECT_TRUE(tram1->isKapot());
    EXPECT_TRUE(tram2->isKapot());

    output->advanced_summary();

    tramsysteem->simulate(2);
    EXPECT_FALSE(tram1->isKapot());
    EXPECT_FALSE(tram2->isKapot());

    output->complete_summary();
    output->advanced_summary();
}


// Checkt of alle vorige of volgende stations correct zijn van alle stations.
TEST_F(TramsysteemTest, inconsistentieTest){
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("inconsistentie.xml");
    TramSysteemOut* output = new TramSysteemOut("tramregeling.txt", tramsysteem);
    tramsysteem->setOutput(output);
}
// Elke tram moet bij elk station van zijn lijn kunnen komen.
TEST_F(TramsysteemTest, lijnCorrectheidsTest){
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("lijnCorrectheid.xml");
    TramSysteemOut* output = new TramSysteemOut("tramregeling.txt", tramsysteem);
    tramsysteem->setOutput(output);
}
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}