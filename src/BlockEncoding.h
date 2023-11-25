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
    BlockEncoding(const std::string& input_file, const std::string& output_file, int block_size = 4, int search_area = 2, int keyframe_period = 10);
    void encode();
private:
    int block_size, search_area, keyframe_period;
    VideoManipulator video;
    BitStreamWrite stream_out;
    GolombCode golomb;
    int m; // golomb parameter
    void encodeInterFrame(const Mat& f, const Mat& p);
    void encodeIntraFrame(const Mat& f);
    void encodeValue(unsigned int v);
    void encodeBlockDifference(const Mat& block);
    void generate_headers(const Size& frame_size);
    Mat getBlock(const Mat& original_frame, int row, int col) const;
    // returns tuple with best matching block and (x,y) vector
    /*std::tuple<Mat, int, int> searchBestBlock(const Mat& prev_frame, const Mat& curr_block, int x, int y, int rows, int cols);*/
    std::tuple<Mat, int, int> searchBestBlock(const Mat& prev_frame, const Mat& curr_block, int y, int x, int rows, int cols);
    static unsigned char JPEG_LS(unsigned char a,unsigned char b,unsigned char c);

    void encodeInterframeChannel(const Mat& c_channel, const Mat& p_channel);
    int calculateMAD(const Mat &block1, const Mat &block2) const;
};


#endif //GTD_VC_BLOCKENCODING_H
