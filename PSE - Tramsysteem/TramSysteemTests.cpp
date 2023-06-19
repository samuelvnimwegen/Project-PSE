//
// Created by Samuel on 16/03/2023.
//
#include "gtest/gtest.h"
#include "XMLParser.h"
using namespace std;

#include "TramSysteemDomainTests.cpp"
#include "TramSysteemInputTests.cpp"
#include "TramSysteemOutputTests.cpp"

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}