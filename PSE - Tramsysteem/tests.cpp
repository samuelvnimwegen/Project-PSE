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

// Deze tests halten het programma:

// Checkt of alle vorige of volgende stations correct zijn van alle stations.
TEST_F(TramsysteemTest, inconsistentieTest){
    XMLParser parser = XMLParser();
    EXPECT_DEATH(parser.readFile("inconsistentie.xml"), "Bij isConsistent van TramSysteem had niet elk huidigStation een correct volgende of vorig huidigStation");
}
// Elke tram moet bij elk station van zijn lijn kunnen komen.
TEST_F(TramsysteemTest, lijnCorrectheidsTest){
    XMLParser parser = XMLParser();
    EXPECT_DEATH(parser.readFile("lijnCorrectheid.xml"), "Bij isConsistent van TramSysteem had niet elk huidigStation een correct volgende of vorig huidigStation");
}

TEST_F(TramsysteemTest, botsing){
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("botsing.xml");
    TramSysteemOut* output = new TramSysteemOut("tramregeling.txt", tramsysteem);
    tramsysteem->setOutput(output);
    EXPECT_TRUE(tramsysteem->getTrams().size() == 2);
    EXPECT_TRUE(tramsysteem->getStations().size() == 3);
    EXPECT_TRUE(tramsysteem->getLijnen().size() == 1);

    Tram* tram1 = tramsysteem->getStations()[1]->getTramInStation();
    Tram* tram2 = tramsysteem->getStations()[2]->getTramInStation();
    EXPECT_FALSE(tram1->isKapot());
    EXPECT_FALSE(tram2->isKapot());
    EXPECT_TRUE(tram1->kanNaarType(tram1->getHuidigStation()->getVolgende()));

    EXPECT_TRUE(tramsysteem->getStations()[0]->getTramInStation() == 0);
    EXPECT_TRUE(tramsysteem->getStations()[1]->getTramInStation() != 0);
    EXPECT_TRUE(tramsysteem->getStations()[2]->getTramInStation() != 0);

    output->complete_summary();
    output->advanced_summary();
    tramsysteem->simulate(2);

    EXPECT_FALSE(tram1->isKapot());
    EXPECT_TRUE(tram2->isKapot());

    output->advanced_summary();
    output->complete_summary();

    EXPECT_DEATH(tramsysteem->simulate(1), "Bij moveNaarVolgende van Tram was het volgende station bezet op de lijn wat in een botsing resulteert.");
}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}