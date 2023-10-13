//
// Created by JPe_D on 10/13/2023.
//

#include "../src/BitStream.h"
#include <string>
#include <filesystem>
#include <iostream>



bool SingleBitsTest(const std::string& filepath) {
    BitStreamWrite write_stream(filepath);

    // get random 64 bit unsigned int
    srand(time(NULL));
    unsigned long long bits_to_write = 0;
    for (int i = 0; i < 64; ++i) {
        bits_to_write = bits_to_write * 2 + rand() % 2;
    }

    // write to buffer bit by bit
    unsigned long long mask, single_bit;
    for (int i = 63; i >= 0; --i) {
        mask = 1ULL << i;
        single_bit = bits_to_write & mask;
        write_stream.write_bit((single_bit >> i) != 0);
    }

    // flush buffer to file
    write_stream.close();

    // read written bits
    BitStreamRead read_stream(filepath);
    unsigned long long bits_from_write = read_stream.read(64);

    // clean test files
    try {
        std::filesystem::remove(filepath);
    } catch (const std::filesystem::filesystem_error& err){
        std::cout << "error cleaning test files: " << err.what() << std::endl;
    }

    if (bits_from_write == bits_to_write)
        return true;
    return false;
}


bool MultipleBitsTest(const std::string& filepath) {
    BitStreamWrite write_stream(filepath);

    // get random 64 bit unsigned int
    srand(time(NULL));
    unsigned long long bits_to_write = 0;
    for (int i = 0; i < 64; ++i) {
        bits_to_write = bits_to_write * 2 + rand() % 2;
    }

    // write whole 64 bit number to buffer
    write_stream.write(64, bits_to_write);

    // flush buffer to file
    write_stream.close();

    // read written bits
    BitStreamRead read_stream(filepath);
    unsigned long long bits_from_write = read_stream.read(64);

    // clean test files
    try {
        std::filesystem::remove(filepath);
    } catch (const std::filesystem::filesystem_error& err){
        std::cout << "error cleaning test files: " << err.what() << std::endl;
    }

    if (bits_from_write == bits_to_write)
        return true;
    return false;
}
