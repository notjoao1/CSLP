//
// Created by joao on 31/10/2023.
//

#ifndef GTD_VC_CODEC_H
#define GTD_VC_CODEC_H

#include "Representation/VideoManipulator.h"
#include "BitStream/BitStreamWrite.h"
#include <algorithm>

using namespace std;

class Codec {
public:
    Codec(VideoManipulator v, BitStreamWrite stream);
    void encode();
    void decode();
    static unsigned char JPEG_LS(unsigned char a,unsigned char b,unsigned char c,unsigned char x);

private:
};


#endif //GTD_VC_CODEC_H
