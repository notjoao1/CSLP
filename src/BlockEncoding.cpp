//
// Created by joao on 14/11/2023.
//

#include "BlockEncoding.h"

BlockEncoding::BlockEncoding(const string &input_file, const string &output_file, int block_size, int search_area, int keyframe_period) : video(input_file), stream_out(output_file), block_size(block_size), search_area(search_area), keyframe_period(keyframe_period) {
}

void BlockEncoding::encode() {
    Mat curr_frame;
    curr_frame = video.getNextFrame();
    generate_headers(curr_frame.size());
    cout << "encoding video..." << endl;

    // frame loop
    int frame_counter = 0;
    while (!curr_frame.empty()) {
        if (frame_counter % keyframe_period == 0) {
            encodeIntraFrame(curr_frame);
            cout << "current_frame (INTRA_FRAME): " << frame_counter << endl;
        } else {
            encodeInterFrame(curr_frame);
            cout << "current_frame (INTER_FRAME): " << frame_counter << endl;
        }
        curr_frame = video.getNextFrame();
        frame_counter++;
    }
}

void BlockEncoding::encodeChannel(const Mat &c) {

}

void BlockEncoding::encodeValue(unsigned int v) {

}

void BlockEncoding::generate_headers(const Size &frame_size) {

}

void BlockEncoding::encodeIntraFrame(const Mat &f) {

}

void BlockEncoding::encodeInterFrame(const Mat &f) {

}

Mat BlockEncoding::getBlock(const Mat &original_frame, int x, int y) {
    // create region of interest for block
    Rect roi(x, y, block_size, block_size);
    Mat block = original_frame(roi);
    return block;
}

