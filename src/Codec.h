//
// Created by joao on 31/10/2023.
//

#ifndef GTD_VC_CODEC_H
#define GTD_VC_CODEC_H

#include "Representation/VideoManipulator.h"
#include "BitStream/BitStreamWrite.h"

class Codec {
public:
    Codec(VideoManipulator v, BitStreamWrite stream);
    void encode();
    void decode();

private:
};


#endif //GTD_VC_CODEC_H
