//
// Created by joao on 09/11/2023.
//

#include "../../src/Encoder.h"

int main(int argc, char* argv[]) {
    VideoManipulator* v = new VideoManipulator(argv[1]);
    BitStreamWrite* stream = new BitStreamWrite(argv[2]);
    if(argc < 3)
        return 1;
    Encoder e(v, stream);
    e.encode();
    return 0;
}