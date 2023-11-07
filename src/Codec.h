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
    Codec(const std::string& input_file, const std::string& output_file);
    void encodeVideo();
    void decodeVideo();
    void encodeFrame();
    void decodeFrame();
    void encodeChannel();
    void decodeChannel();
    static unsigned char JPEG_LS(unsigned char a,unsigned char b,unsigned char c,unsigned char x);

private:
    VideoManipulator v;
    BitStreamWrite writeStream;
    BitStreamWrite readStream;

};


#endif //GTD_VC_CODEC_H
