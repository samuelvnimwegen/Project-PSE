//
// Created by Samuel on 19/06/2023.
//

#include "gtest/gtest.h"
#include "fstream"
#include "TramSysteem.h"
#include "XMLParser.h"


class TramSysteemOutputTest: public  ::testing::Test{
protected:
    virtual void SetUp(){
    }

    virtual void TearDown(){}
};

// Vergelijkt de testfiles
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gebaseerd op de FileCompare test in TicTacToe.git van Serge Demeyer:
////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TramSysteemOutputTest, FileCompare) {
    ofstream file;
    file.open("testOutput/file1.txt");
    file.close();
    file.open("testOutput/file2.txt");
    file.close();

    EXPECT_TRUE(fileExists("testOutput/file1.txt"));
    EXPECT_TRUE(fileExists("testOutput/file2.txt"));
    EXPECT_TRUE(isEmpty("testOutput/file1.txt"));
    EXPECT_TRUE(isEmpty("testOutput/file2.txt"));


    // Vergelijkt 2 lege files
    EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    // Vergelijkt een lege en niet-lege file
    file.open("testOutput/file1.txt");
    file << "xxx" << endl << "yyy";
    file.close();
    EXPECT_TRUE(fileExists("testOutput/file1.txt"));
    EXPECT_FALSE(isEmpty("testOutput/file1.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    // Vergelijkt 2 gelijke files
    file.open("testOutput/file2.txt");
    file << "xxx" << endl << "yyy";
    file.close();
    EXPECT_TRUE(fileExists("testOutput/file2.txt"));
    EXPECT_FALSE(isEmpty("testOutput/file2.txt"));

    EXPECT_TRUE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_TRUE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    // Vergelijkt 2 files die 1 character verschillen
    file.open("testOutput/file2.txt");
    file << "xxx" << endl << "xyy";
    file.close();
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    // Vergelijkt 2 files waarvan de lengte verschilt
    file.open("testOutput/file2.txt");
    file << "xxx" << endl << "yy";
    file.close();
    EXPECT_FALSE(FileCompare("testOutput/file1.txt", "testOutput/file2.txt"));
    EXPECT_FALSE(FileCompare("testOutput/file2.txt", "testOutput/file1.txt"));

    // Vergelijkt bestaande file met niet-bestaande file.
    EXPECT_DEATH(
            FileCompare("testOutput/file1.txt", "testOutput/nonexisting.txt"), "Bij FileCompare bestond file 2 niet");
    EXPECT_DEATH(
            FileCompare("testOutput/nonexisting.txt", "testOutput/file1.txt"), "Bij FileCompare bestond file 1 niet");
}


// Happy day scenario:
TEST_F(TramSysteemOutputTest, TramSysteemOutputHappyDay){
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("testOutput/TramSysteemOutputHappyDay.xml");
    TramSysteemOut* output = new TramSysteemOut("testOutput/TramSysteemOutputHappyDay.txt", tramsysteem);
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

    EXPECT_TRUE(FileCompare("testOutput/TramSysteemOutputHappyDay.txt", "testOutput/TramSysteemOutputHappyDayExpected.txt"));
}

// Happy day met kleine modificatie:
TEST_F(TramSysteemOutputTest, TramSysteemOutputAlmostHappyDay){
    XMLParser parser = XMLParser();
    TramSysteem* tramsysteem = parser.readFile("testOutput/TramSysteemOutputHappyDay.xml");
    TramSysteemOut* output = new TramSysteemOut("testOutput/TramSysteemOutputHappyDay.txt", tramsysteem);
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

    EXPECT_FALSE(FileCompare("testOutput/TramSysteemOutputHappyDay.txt", "testOutput/TramSysteemOutputHappyDayExpected.txt"));
}

// Extra tests:
TEST_F(TramSysteemOutputTest, extraTests){
    XMLParser parser = XMLParser();

    string filename = "testOutput/TramSysteemOutput1.xml";
    TramSysteem* tramSysteem = parser.readFile(filename);
    TramSysteemOut* tramSysteemOut = new TramSysteemOut("testOutput/TramSysteemOutput1.txt", tramSysteem);
    tramSysteem->setOutput(tramSysteemOut);

    tramSysteemOut->complete_summary();
    tramSysteemOut->advanced_summary();
    for (int i = 0; i < 5; ++i){
        tramSysteem->simulate(1);
        tramSysteemOut->advanced_summary();
    }

    EXPECT_TRUE(FileCompare("testOutput/TramSysteemOutput1.txt", "testOutput/TramSysteemOutput1Expected.txt"));

    filename = "testOutput/TramSysteemOutput2.xml";
    tramSysteem = parser.readFile(filename);
    tramSysteemOut = new TramSysteemOut("testOutput/TramSysteemOutput2.txt", tramSysteem);
    tramSysteem->setOutput(tramSysteemOut);

    tramSysteemOut->complete_summary();
    tramSysteemOut->advanced_summary();
    for (int i = 0; i < 5; ++i){
        tramSysteem->simulate(1);
        tramSysteemOut->advanced_summary();
    }

    EXPECT_TRUE(FileCompare("testOutput/TramSysteemOutput2.txt", "testOutput/TramSysteemOutput2Expected.txt"));

}

// Foutmeldingen van de exporter:
TEST_F(TramSysteemOutputTest, exceptions){
    TramSysteem* tramSysteem = new TramSysteem;
    EXPECT_DEATH(TramSysteemOut("noTxtFile.pdf", tramSysteem), "Bij TramSysteemOut was het de filename geen .txt file");
    TramSysteemOut* tramSysteemOut = new TramSysteemOut("testOutput/TramSysteemOutput1.txt", tramSysteem);
    EXPECT_TRUE(tramSysteemOut->properlyInitialized());

    EXPECT_DEATH(tramSysteemOut->wachten(0, 0) ,"Bij wachten van TramSysteemOut was 1 van de trams 0");
    EXPECT_DEATH(tramSysteemOut->herstel(0, 0) ,"Bij herstel van TramSysteemOut was een input 0");
    EXPECT_DEATH(tramSysteemOut->move(0, 0, 0), "Bij move van TramSysteemOut was een input 0");
}