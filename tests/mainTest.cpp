//
// Created by JPe_D on 10/13/2023.
//

#include "BitStream_Tests.cpp"
#include <iostream>

int main() {
    if (SingleBitsTest()) {
        std::cerr << "WRITE SINGLE BITS - Test succeeded!\n";
    } else {
        std::cerr << "WRITE SINGLE BITS - Test failed\n";
    }

    if (MultipleBitsTest()) {
        std::cerr << "WRITE MULTIPLE BITS - Test succeeded!\n";
    } else {
        std::cerr << "WRITE MULTIPLE BITS - Test failed\n";
    }

    BitStreamCleanFiles();

}