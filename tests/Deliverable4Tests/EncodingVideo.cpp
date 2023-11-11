//
// Created by joao on 09/11/2023.
//

#include "../../src/Encoder.h"

int main(int argc, char* argv[]) {
    if(argc < 3)
        return 1;
    Encoder e(argv[1], argv[2]);
    e.encode();
    return 0;
}