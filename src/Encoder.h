//
// Created by JPe_D on 11/2/2023.
//

#ifndef GTD_VC_ENCODER_H
#define GTD_VC_ENCODER_H

#include "Representation/VideoManipulator.h"
#include "BitStream/BitStreamWrite.h"
#include "Encoding/GolombCode.h"
#include "opencv2/imgproc.hpp"



class Encoder {
private:
    VideoManipulator video;
    BitStreamWrite stream_out;
    GolombCode golomb;
    int m; // golomb parameter TODO: ver isto depois
    void encodeFrame(const Mat& f);
    void encodeChannel(const Mat& c);
    void encodeValue(unsigned int v);
    void generate_headers(const Size& frame_size);
    static unsigned char JPEG_LS(unsigned char a,unsigned char b,unsigned char c);
public:
    Encoder(const std::string& input_file, const std::string& output_file);
    void encode();

};


#endif //GTD_VC_ENCODER_H
