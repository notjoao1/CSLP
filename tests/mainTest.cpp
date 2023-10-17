//
// Created by JPe_D on 10/13/2023.
//

#include "BitStream_Tests.cpp"
#include "golombtest.cpp"
#include <iostream>

int main() {
    std::string f_name_single = "tests/singlebitstest.bin";
    std::string f_name_mult = "tests/multiplebitstest.bin";
    std::string f_name_golomb = "tests/golombtest.bin";

    if (SingleBitsTest(f_name_single)) {
        std::cout << "BitStream: WRITE SINGLE BITS - Test succeeded.\n";
    } else {
        std::cerr << "BitStream: WRITE SINGLE BITS - Test failed\n";
    }

    if (MultipleBitsTest(f_name_mult)) {
        std::cout << "BitStream: WRITE MULTIPLE BITS - Test succeeded.\n";
    } else {
        std::cerr << "BitStream: WRITE MULTIPLE BITS - Test failed.\n";
    }

    if (Golomb_test(100000, 4, f_name_golomb)) {
        std::cout << "Golomb: ENCODING AND DECODING - Test succeeded.\n";
    } else {
        std::cerr << "Golomb: ENCODING AND DECODING - Test failed.\n";
    }

}