//
// DEMO MAIN
// Created by sergei on 21.09.18.
// Lab 1 var(8,7)
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

/************************************************/
/******** EXAMPLES OF PRINT HELPERS *************/
void intPrintHelper(int val) {
    std::cout << "v(" << val << ")";
}

template<typename T>
void vecPrintHelper(std::vector<T> val) {
    std::cout << "{ ";
    for (auto el : val) {
        std::cout << el << " ";
    }
    std::cout << "} ";
}


void stringPrintHelper(std::string val) {
    std::cout << "\"" << val << "\" ";
}

void doublePrintHelper(double val) {
    std::cout.precision(3);
    std::cout << std::fixed;
    std::cout << val << " ";
}

int main() {
    testing::InitGoogleTest();
    auto res = RUN_ALL_TESTS();
    return 0;
}