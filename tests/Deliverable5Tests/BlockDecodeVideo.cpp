//
// Created by JPe_D on 11/25/2023.
//

#include "../../src/BlockDecoding.h"

int main (int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Please provide 2 parameters: <input_file> <output_file>" << std::endl;
    }
    BlockDecoding bd(argv[1], argv[2]);
    bd.decode();
}