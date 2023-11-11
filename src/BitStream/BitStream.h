//
// Created by Kikom on 03/10/2023.
//

#ifndef GTD_VC_BITSTREAM_H
#define GTD_VC_BITSTREAM_H

#include "vector"
#include "fstream"

#include "BitStreamRead.h"
#include "BitStreamWrite.h"

class BitStream {
public:
    static BitStreamRead readFromFile(const std::string& filename) {
        return BitStreamRead(filename);
    }

    static BitStreamWrite writeToFile(const std::string& filename) {
        return BitStreamWrite(filename);
    }
};


#endif //GTD_VC_BITSTREAM_H
