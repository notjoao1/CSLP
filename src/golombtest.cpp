//
// Created by Kikom on 13/10/2023.
//

#include "BitStream.h"
#include "GolombCode.h"
#include "iostream"

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
    if(pass)
        std::cout << "Passed" << std::endl;
    else
        std::cout << "Failed" << std::endl;
    file2.close();
    return pass;
}