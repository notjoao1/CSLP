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
    void encodeInterframeChannel(const Mat& c_channel, const Mat& p_channel);   // TODO: mudar pa private, está public para testing
private:
    int block_size, search_area, keyframe_period;
    VideoManipulator video;
    BitStreamWrite stream_out;
    GolombCode golomb;
    int m; // golomb parameter TODO: ver isto depois
    void encodeInterFrame(const Mat& f, const Mat& p);
    void encodeIntraFrame(const Mat& f);
    void encodeValue(unsigned int v);
    void generate_headers(const Size& frame_size);
    Mat getBlock(const Mat& original_frame, int row, int col) const;
    // returns tuple with best matching block and (x,y) vector
    std::tuple<Mat, int, int> searchBestBlock(const Mat& prev, const Mat& orig_block, int x, int y);
    static unsigned char JPEG_LS(unsigned char a,unsigned char b,unsigned char c);

};


#endif //GTD_VC_BLOCKENCODING_H
