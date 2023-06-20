//
// Created by Samuel on 18/06/2023.
//

#include "TramSysteem.h"
#include "gtest/gtest.h"
#include "XMLParser.h"

class TramSysteemDomainTest: public ::testing::Test{
protected:
    friend class TramSysteem;
    TramSysteem* tramsysteem;
    Metrostation* metrostation1;
    Halte* halte;
    Metrostation* metrostation2;
    Metrostation* metrostation3;
    PCC* pcc;
    Stadslijner* stadslijner;
    Lijn* lijn;

    virtual void SetUp(){
        tramsysteem = new TramSysteem;

        metrostation1 = new Metrostation("A", 7);
        halte = new Halte("B", 7);
        metrostation2 = new Metrostation("C", 7);
        metrostation3 = new Metrostation("D", 7);

        metrostation1->setVolgende(halte);
        halte->setVolgende(metrostation2);
        metrostation2->setVolgende(metrostation3);
        metrostation3->setVolgende(metrostation1);

        metrostation1->setVorige(metrostation3);
        metrostation3->setVorige(metrostation2);
        metrostation2->setVorige(halte);
        halte->setVorige(metrostation1);

        tramsysteem->add_station(metrostation1);
        tramsysteem->add_station(halte);
        tramsysteem->add_station(metrostation2);
        tramsysteem->add_station(metrostation3);

        lijn = new Lijn(7);
        tramsysteem->addLijn(lijn);
        lijn->addStation(metrostation1);
        lijn->addStation(halte);
        lijn->addStation(metrostation2);
        lijn->addStation(metrostation3);

        pcc = new PCC(99, 7, 2, 2, 700);
        stadslijner = new Stadslijner(88, 7);

        pcc->setBeginStation(metrostation2);

        stadslijner->setBeginStation(metrostation1);

        lijn->addTram(pcc);
        lijn->addTram(stadslijner);

        tramsysteem->addTram(pcc);
        tramsysteem->addTram(stadslijner);
    }
    virtual void TearDown(){}
};

// Test of alles juist geïnitieerd is.
TEST_F(TramSysteemDomainTest, DefaultConstructor){
    EXPECT_TRUE(tramsysteem->properlyInitialized());
    EXPECT_TRUE(tramsysteem->consistencyCheck());
    for (int i = 0; i < int(tramsysteem->getTrams().size()); ++i){
        EXPECT_TRUE(tramsysteem->getTrams()[i]->properlyInitialised());
    }
    for (int i = 0; i < int(tramsysteem->getLijnen().size()); ++i){
        EXPECT_TRUE(tramsysteem->getLijnen()[i]->properlyInitialised());
    }
    for (int i = 0; i < int(tramsysteem->getStations().size()); ++i){
        EXPECT_TRUE(tramsysteem->getStations()[i]->properlyInitialised());
    }
}

// De happyDay test
TEST_F(TramSysteemDomainTest, HappyDay){
    EXPECT_TRUE(tramsysteem->consistencyCheck());
    EXPECT_TRUE(tramsysteem->properlyInitialized());

    TramSysteemOut* tramSysteemOut = new TramSysteemOut("testDomain/TramSysteemDomainHappyDay.txt", tramsysteem);
    tramsysteem->setOutput(tramSysteemOut);
    EXPECT_TRUE(tramSysteemOut->properlyInitialized());

    tramSysteemOut->advanced_summary();

    EXPECT_TRUE(pcc->getHuidigStation() == pcc->getBeginStation());
    EXPECT_TRUE(stadslijner->getHuidigStation() == stadslijner->getBeginStation());
    EXPECT_TRUE(pcc->kanBewegen());
    EXPECT_FALSE(stadslijner->kanBewegen());
    EXPECT_FALSE(stadslijner->kanNaarType(stadslijner->getHuidigStation()->getVolgende()));
    EXPECT_TRUE(pcc->kanNaarType(pcc->getHuidigStation()->getVolgende()));

    pcc->moveNaarVolgende(tramSysteemOut);
    tramSysteemOut->advanced_summary();

    EXPECT_FALSE(pcc->getHuidigStation() == pcc->getBeginStation());
    EXPECT_TRUE(stadslijner->getHuidigStation() == stadslijner->getBeginStation());
    EXPECT_FALSE(pcc->kanBewegen());
    EXPECT_TRUE(stadslijner->kanBewegen());
    EXPECT_FALSE(stadslijner->kanNaarType(stadslijner->getHuidigStation()->getVolgende()));
    EXPECT_TRUE(pcc->kanNaarType(pcc->getHuidigStation()->getVolgende()));

    stadslijner->moveNaarVolgende(tramSysteemOut);
    tramSysteemOut->advanced_summary();

    EXPECT_FALSE(pcc->getHuidigStation() == pcc->getBeginStation());
    EXPECT_FALSE(stadslijner->getHuidigStation() == stadslijner->getBeginStation());
    EXPECT_TRUE(pcc->kanBewegen());
    EXPECT_FALSE(stadslijner->kanBewegen());
    EXPECT_TRUE(stadslijner->kanNaarType(stadslijner->getHuidigStation()->getVolgende()));
    EXPECT_TRUE(pcc->kanNaarType(pcc->getHuidigStation()->getVolgende()));

    tramsysteem->simulate(1);
    tramSysteemOut->advanced_summary();

    EXPECT_FALSE(pcc->getHuidigStation() == pcc->getBeginStation());
    EXPECT_FALSE(stadslijner->getHuidigStation() == stadslijner->getBeginStation());
    EXPECT_FALSE(pcc->kanBewegen());
    EXPECT_FALSE(stadslijner->kanBewegen());
    EXPECT_TRUE(stadslijner->kanNaarType(stadslijner->getHuidigStation()->getVolgende()));
    EXPECT_TRUE(pcc->kanNaarType(pcc->getHuidigStation()->getVolgende()));
    EXPECT_TRUE(pcc->isKapot());

    Station* huidigPcc = pcc->getHuidigStation();
    Station* huidigStadslijner = stadslijner->getHuidigStation();

    tramsysteem->simulate(2);

    EXPECT_TRUE(huidigPcc == pcc->getHuidigStation());
    EXPECT_TRUE(huidigStadslijner == stadslijner->getHuidigStation());
    EXPECT_FALSE(pcc->isKapot());
    EXPECT_TRUE(pcc->kanBewegen());

    tramsysteem->simulate(1);

    EXPECT_FALSE(huidigPcc == pcc->getHuidigStation());
    EXPECT_FALSE(huidigStadslijner == stadslijner->getHuidigStation());
    EXPECT_FALSE(pcc->isKapot());
    EXPECT_TRUE(pcc->kanBewegen());
}

TEST_F(TramSysteemDomainTest, IllegalMovement){
    TramSysteemOut* tramSysteemOut = new TramSysteemOut("testDomain/TramSysteemDomainIllegalMovement.txt", tramsysteem);
    tramsysteem->setOutput(tramSysteemOut);
    EXPECT_TRUE(tramsysteem->properlyInitialized());
    EXPECT_TRUE(tramSysteemOut->properlyInitialized());

    tramSysteemOut->advanced_summary();
    EXPECT_DEATH(stadslijner->moveNaarVolgende(tramSysteemOut), "Bij moveNaarVolgende van Tram kan de tram niet bewegen");

    tramsysteem->simulate(1);
    tramSysteemOut->advanced_summary();

    EXPECT_TRUE(pcc->kanBewegen());
    EXPECT_FALSE(stadslijner->kanBewegen());
    EXPECT_DEATH(stadslijner->moveNaarVolgende(tramSysteemOut), "Bij moveNaarVolgende van Tram kan de tram niet bewegen");

    tramsysteem->simulate(2);
    tramSysteemOut->advanced_summary();

    EXPECT_FALSE(stadslijner->kanBewegen());
    EXPECT_FALSE(pcc->kanBewegen());
    EXPECT_DEATH(stadslijner->moveNaarVolgende(tramSysteemOut), "Bij moveNaarVolgende van Tram kan de tram niet bewegen");
    EXPECT_DEATH(pcc->moveNaarVolgende(tramSysteemOut), "Bij moveNaarVolgende van PCC was de tram kapot");


}

