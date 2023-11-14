//
// Created by joao on 14/11/2023.
//

#ifndef GTD_VC_BLOCKENCODING_H
#define GTD_VC_BLOCKENCODING_H

#include <string>
#include "Representation/VideoManipulator.h"
#include "BitStream/BitStreamWrite.h"
#include "Encoding/GolombCode.h"
#include "opencv2/imgproc.hpp"


class BlockEncoding {
public:
    BlockEncoding(const std::string& input_file, const std::string& output_file, int block_size = 8, int search_area = 16, int keyframe_period = 10);
    void encode();
private:
    int block_size, search_area, keyframe_period;
    VideoManipulator video;
    BitStreamWrite stream_out;
    GolombCode golomb;
    int m; // golomb parameter TODO: ver isto depois
    void encodeInterFrame(const Mat& f);
    void encodeIntraFrame(const Mat& f);
    void encodeChannel(const Mat& c);
    void encodeValue(unsigned int v);
    void generate_headers(const Size& frame_size);
    Mat getBlock(const Mat& original_frame, int row, int col);
};


#endif //GTD_VC_BLOCKENCODING_H
