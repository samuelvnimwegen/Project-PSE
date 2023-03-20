//
// Created by Samuel on 16/03/2023.
//
#include "gtest/gtest.h"
#include "XML/tinyxml.h"
#include "cmath"

using namespace std;

class LargestTest: public  ::testing::Test{
protected:
    virtual void SetUp(){
    }

    virtual void TearDown(){}
};

TEST_F(LargestTest, SimpleTest){
    EXPECT_EQ(3, 4);
}
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}