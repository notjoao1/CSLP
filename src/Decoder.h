//
// Created by tiago on 07-11-2023.
//

#ifndef GTD_VC_DECODER_H
#define GTD_VC_DECODER_H


#include "BitStream/BitStreamRead.h"
#include "Encoding/GolombCode.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include "Y4MWriter.h"

using namespace cv;
using namespace std;

class Decoder {
private:
    BitStreamRead* stream_in;
    GolombCode golomb;
    Y4MWriter output_vid;
    int m; // golomb parameter TODO: ver isto depois
    int cols;
    int rows;
    int fps;

public:
    void read_headers();
    Mat decodeFrame();
    Mat decodeChannel();
    int decodeValue();
    static unsigned char JPEG_LS(unsigned char a, unsigned char b, unsigned char c);
    Decoder(BitStreamRead* in, const std::string& output_fname);
    void decode();

};




#endif //GTD_VC_DECODER_H
