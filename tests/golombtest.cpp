//
// Created by Kikom on 13/10/2023.
//

#include "../src/BitStream/BitStream.h"
#include "../src/Encoding/GolombCode.h"
#include "iostream"
#include <filesystem>


bool Golomb_test(int TEST_SIZE, int m, const std::string& filepath){
    BitStreamWrite file = BitStream::writeToFile(filepath);
    for(int a = 0 ; a < TEST_SIZE ; a++)
        GolombCode::encode(a,m,file);
    file.close();

    auto file2 = BitStream::readFromFile(filepath);
    bool pass = true;
    for(int a = 0 ; a < TEST_SIZE ; a++){
        int g = GolombCode::decode_one(m,file2);
        if(g!=a){
            pass = false;
            std::cout << "Failed at "<< a << " got " << g << std::endl;
        }
    }
    file2.close();

    // clean test files
    try {
        std::filesystem::remove(filepath);
    } catch (const std::filesystem::filesystem_error& err){
        std::cout << "error cleaning test files: " << err.what() << std::endl;
    }

    return pass;
}
