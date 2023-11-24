//
// Created by joao on 14/11/2023.
//

#include "BlockDecoding.h"

BlockDecoding::BlockDecoding(const string &input_file, const string &output_file) : stream_in(input_file), video(output_file){
    this->m = 3;
    Decoder d(&stream_in);
    decoder=&d;
}

void BlockDecoding::decode() {
    Mat curr_frame, previous_frame;
    read_headers();
    cout << "decoding video..." << endl;
    // frame loop
    int frame_counter = 0;
    while (!curr_frame.empty()) {
        if (frame_counter % keyframe_period == 0) {
            curr_frame=this->decoder->decodeFrame();
            cout << "current_frame (INTRA_FRAME): " << frame_counter << endl;
        } else {
            curr_frame=decodeInterFrame(&curr_frame);
            cout << "current_frame (INTER_FRAME): " << frame_counter << endl;
        }
        if (frame_counter==0){
            video.writeHeader(this->width,this->height,this->fps);
        }
        video.writeFrame(&curr_frame);
        frame_counter++;
    }
}

void BlockDecoding::read_headers() {
    this->width=stoi(stream_in.read_string());
    this->height=stoi(stream_in.read_string());
    this->keyframe_period=stoi(stream_in.read_string());
    this->block_size=stoi(stream_in.read_string());
    this->fps=stoi(stream_in.read_string());
}

// TODO: adicionar padding para ter frames divisiveis pelo block_size!!!!!
// f - current frame; p - previous frame
Mat BlockDecoding::decodeInterFrame(const Mat* p) {
    Mat res;
    std::cout << "Decoding interframe" << std::endl;
    vector<Mat> curr_channels, prev_channels;
    split(*p, prev_channels);

    // iterate through channels, both frames have same number
    for (int i = 0; i < p->channels(); ++i) {
        curr_channels.at(i)= decodeInterframeChannel(&prev_channels.at(i));
    }
    merge(curr_channels,res);
    return res;
}

void BlockDecoding::setBlock(const Mat *original_frame, Mat* block, int row, int col) const{
    // create region of interest for block
    // columns - x-axis; rows - y-axis
    Rect roi(col, row, block_size, block_size);
    block->copyTo((*original_frame)(roi));
}

Mat BlockDecoding::getBlock(const Mat *original_frame, int row, int col) const{
    // create region of interest for block
    // columns - x-axis; rows - y-axis
    Rect roi(col, row, block_size, block_size);
    Mat block = original_frame->operator()(roi);
    return block;
}

Mat BlockDecoding::decodeInterframeChannel(Mat* p_channel) {
    Mat c_channel;
    Mat curr_block, b_erro; // b_erro é o erro entre duas matrizes
    for (int i = 0; i < this->height / block_size - 1; ++i) {
        for (int j = 0; j < this->width / block_size - 1; ++j) {
            b_erro = decodeBlockDifference();
            curr_block=getBlock(p_channel,i*block_size,j*block_size)+b_erro;
            setBlock(&c_channel,&curr_block, i * block_size, j * block_size); //TODO: refactor to use vectors
        }
    }
    return c_channel;
}

Mat BlockDecoding::decodeBlockDifference() {
    Mat block;
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            block.at<uchar>(i,j)=this->decoder->decodeValue();
        }
    }
}

