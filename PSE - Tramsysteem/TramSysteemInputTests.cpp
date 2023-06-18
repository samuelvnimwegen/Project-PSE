//
// Created by Samuel on 18/06/2023.
//


class TramsysteemTest: public  ::testing::Test{
protected:
    virtual void SetUp(){
    }

    virtual void TearDown(){}
};

// Happy day test:
TEST_F(TramsysteemTest, InputHappyDay){
XMLParser parser = XMLParser();
TramSysteem* tramsysteem = parser.readFile("happyDay.xml");
TramSysteemOut* output = new TramSysteemOut("InputHappyDay.txt", tramsysteem);
tramsysteem->setOutput(output);
EXPECT_TRUE(tramsysteem->getTrams().size() == 4);
EXPECT_TRUE(tramsysteem->getStations().size() == 6);
EXPECT_TRUE(tramsysteem->getLijnen().size() == 2);

Tram* pccTram = tramsysteem->getStations()[2]->getTramInStation();
PCC* pcc = dynamic_cast<PCC*>(pccTram);
EXPECT_FALSE(pcc->isKapot());

EXPECT_FALSE(tramsysteem->getStations()[0]->tramInStation());
EXPECT_TRUE(tramsysteem->getStations()[1]->tramInStation());
EXPECT_TRUE(tramsysteem->getStations()[2]->tramInStation());

output->complete_summary();
output->advanced_summary();
tramsysteem->simulate(1);

EXPECT_FALSE(pcc->isKapot());

EXPECT_TRUE(tramsysteem->getStations()[0]->tramInStation());
EXPECT_FALSE(tramsysteem->getStations()[1]->tramInStation());
EXPECT_TRUE(tramsysteem->getStations()[2]->tramInStation());

output->advanced_summary();

tramsysteem->simulate(1);

EXPECT_TRUE(pcc->isKapot());

output->advanced_summary();

tramsysteem->simulate(1);
EXPECT_TRUE(pcc->isKapot());
output->tram_summary();
output->advanced_summary();

tramsysteem->simulate(1);
EXPECT_FALSE(pcc->isKapot());
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
