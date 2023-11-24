//
// Created by joao on 14/11/2023.
//

#ifndef GTD_VC_BLOCKDECODING_H
#define GTD_VC_BLOCKDECODING_H

#include <string>
#include "Representation/VideoManipulator.h"
#include "BitStream/BitStreamWrite.h"
#include "Encoding/GolombCode.h"
#include "opencv2/imgproc.hpp"
#include "Decoder.h"

class BlockDecoding {
public:
    BlockDecoding(const std::string& input_file, const std::string& output_file);
    void decode();
private:
    Mat decodeInterframeChannel(Mat* p_channel);
    Mat getBlock(const Mat *original_frame, int row, int col) const;
    void setBlock(const Mat *original_frame, Mat* block, int row, int col) const;
    Decoder* decoder;
    int width, height,block_size,    keyframe_period,fps;
    BitStreamRead stream_in;
    VideoManipulator video;
    GolombCode golomb;
    int m; // golomb parameter TODO: ver isto depois
    Mat decodeInterFrame(const Mat* previous_frame);
    void read_headers();
    Mat decodeBlockDifference();

};


#endif //GTD_VC_BLOCKDECODING_H
