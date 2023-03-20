//
// Created by Samuel on 16/03/2023.
//
#include "gtest/gtest.h"
#include "TramSysteem.h"

using namespace std;

class TramsysteemTest: public  ::testing::Test{
protected:
    virtual void SetUp(){
    }

    virtual void TearDown(){}
};

TEST_F(TramsysteemTest, test1){
    TramSysteem ts = TramSysteem();
    EXPECT_TRUE(ts.readFile("test1.txt"));
    EXPECT_FALSE(ts.move(ts.getTrams()[0], ts.getTrams()[0]->getBeginStation()->getVolgende()));
    EXPECT_FALSE(ts.complete_summary());
    EXPECT_FALSE(ts.tram_summary());
    EXPECT_FALSE(ts.station_summary());
    ts.makeTxtFile("test1_out.txt");
    EXPECT_TRUE(ts.move(ts.getTrams()[0], ts.getTrams()[0]->getBeginStation()->getVolgende()));
    EXPECT_TRUE(ts.isConsistent());
    EXPECT_TRUE(ts.complete_summary());
    EXPECT_TRUE(ts.tram_summary());
    EXPECT_TRUE(ts.station_summary());
    EXPECT_TRUE(ts.simulate(6));
    EXPECT_TRUE(ts.isConsistent());
    EXPECT_EQ(ts.getTrams()[0]->getLijnNr(), 12);
    EXPECT_EQ(ts.getStations()[0]->getSpoorNr(), 12);
    ts.getStations()[0]->setSpoorNr(11);
    EXPECT_FALSE(ts.isConsistent());

}

TEST_F(TramsysteemTest, test2){
    TramSysteem ts = TramSysteem();
    EXPECT_TRUE(ts.readFile("test2.txt"));
    ts.makeTxtFile("test2_out.txt");
    EXPECT_FALSE(ts.add_station(0));
    Station* stat = new Station();
    EXPECT_TRUE(ts.add_station(stat));
    EXPECT_FALSE(ts.isConsistent());
    EXPECT_FALSE(ts.move(ts.getTrams()[0], stat));
    EXPECT_FALSE(ts.simulate(2));
    EXPECT_FALSE(ts.complete_summary());
}

TEST_F(TramsysteemTest, test3){
    TramSysteem ts = TramSysteem();
    EXPECT_FALSE(ts.readFile("test3.txt"));
}

TEST_F(TramsysteemTest, test4){
    TramSysteem ts = TramSysteem();
    EXPECT_TRUE(ts.readFile("test4.txt"));
    ts.makeTxtFile("test4_out.txt");
    EXPECT_TRUE(ts.station_summary());
    EXPECT_TRUE(ts.tram_summary());
    EXPECT_TRUE(ts.complete_summary());
    EXPECT_FALSE(ts.isConsistent());
    EXPECT_FALSE(ts.simulate(3));
    EXPECT_TRUE(ts.move(ts.getTrams()[0], ts.getStations()[1]));
}
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}