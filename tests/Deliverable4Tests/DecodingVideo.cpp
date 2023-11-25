//
// Created by joao on 09/11/2023.
//

#include "../../src/Decoder.h"

int main(int argc, char* argv[]) {
    BitStreamRead* in = new BitStreamRead("tests/Deliverable5Tests/ola.gtd");
    Decoder d(in, "tests/Deliverable5Tests/testingabc.y4m");
    d.decode();
    return 0;
}