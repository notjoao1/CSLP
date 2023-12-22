//
// Created by joao on 14/11/2023.
//

#include "BlockDecoding.h"
#include <cmath>

BlockDecoding::BlockDecoding(const string &input_file, const string &output_file) : stream_in(input_file) , output_vid(output_file) {
    this->m = 3;
}

void BlockDecoding::decode() {
    Mat curr_frame, previous_frame;
    read_headers();
    int remaining_frames = stoi(stream_in.read_string());
    cout << "decoding video..." << endl;
    // frame loop
    int frame_counter = 0;
    try {
        while (remaining_frames != 0) {
            if (frame_counter % keyframe_period == 0) {
                cout << "current_frame (INTRA_FRAME): " << frame_counter << endl;
                curr_frame=decodeFrame();
            } else {
                cout << "current_frame (INTER_FRAME): " << frame_counter << endl;
                curr_frame=decodeInterFrame(&curr_frame);
            }

            if (frame_counter==0){
                output_vid.writeHeader(this->width,this->height,this->fps_num, this->fps_denum);
            }
            output_vid.writeFrame(&curr_frame);

            frame_counter++;
            remaining_frames--;
        }
    } catch (Exception e) {
        std::cerr << e.what() << std::endl;
    }
    stream_in.close();

}

void BlockDecoding::read_headers() {
    this->width=stoi(stream_in.read_string());
    this->height=stoi(stream_in.read_string());
    this->keyframe_period=stoi(stream_in.read_string());
    this->block_size=stoi(stream_in.read_string());
    this->search_area=stoi(stream_in.read_string());
    this->fps_num=stoi(stream_in.read_string());
    this->fps_denum=stoi(stream_in.read_string());
}

// f - current frame; p - previous frame
Mat BlockDecoding::decodeInterFrame(const Mat* p) {
    Mat res;
    std::cout << "Decoding interframe" << std::endl;
    vector<Mat> curr_channels, prev_channels;
    split(*p, prev_channels);

    // iterate through channels, both frames have same number
    for (int i = 0; i < p->channels(); ++i) {
        curr_channels.push_back(decodeInterframeChannel(&prev_channels.at(i)));
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
    Mat c_channel = Mat::zeros(height, width, CV_8UC1);
    Mat ref_block, cur_block = Mat::zeros( block_size , block_size , CV_8UC1 ); // b_erro e o erro entre duas matrizes
    int desloc_row,desloc_col;
    int bits_to_read = ceil(log2(search_area));
    for (int i = 0; i < this->height / block_size ; ++i) {
        for (int j = 0; j < this->width / block_size ; ++j) {
            // this->m = int(stream_in.read(8));

            desloc_row= (stream_in.read_bit()) ? -stream_in.read(bits_to_read) : stream_in.read(bits_to_read) ;
            desloc_col= (stream_in.read_bit()) ? -stream_in.read(bits_to_read) : stream_in.read(bits_to_read) ;

            // cout << i << " , " << j << " desloc: "<< desloc_col << " , " << desloc_row << endl;

            ref_block=getBlock(p_channel,i*block_size-desloc_row,j*block_size-desloc_col);
            for (int row=0; row<block_size; row++){
                for(int col=0; col<block_size; col++){
                    int diff = GolombCode::decode_one(16,stream_in);
                    diff = GolombCode::mapUIntToInt( diff );
                    // int diff = (stream_in.read_bit()) ? -GolombCode::decode_one(3,stream_in) : GolombCode::decode_one(3,stream_in);
                    // cout << diff << " , " ;
                    cur_block.at<uchar>(row,col) = ref_block.at<uchar>(row,col) + diff;
                }
                // cout << endl;
            }
            setBlock(&c_channel,&cur_block, i * block_size, j * block_size);
        }
    }
    return c_channel;
}

Mat BlockDecoding::decodeBlockDifference() {
    Mat block = Mat::zeros(block_size, block_size, CV_8UC1);
    // for (int i = 0; i < this->block_size; ++i) {
    //     for (int j = 0; j < this->block_size; ++j) {
    //         for (int row=0; row<block_size; row++)
    //             for(int col=0; col<block_size; col++){
    //                 if(stream_in.read_bit()){
    //                     block.at<uchar>(row,col)=GolombCode::decode_one(diff, 3, this->stream_out);
    //                 }
    //                 diff=int(curr_block.at<uchar>(row,col))- int(ref_block.at<uchar>(row,col));
    //                 stream_out.write_bit(diff < 0 ? 0: 1);
                    
    //             }        }
    // }
    return block;
}

int BlockDecoding::decodeValue() {
    return GolombCode::mapUIntToInt( GolombCode::decode_one(m,stream_in) );
}

Mat BlockDecoding::decodeFrame() {
    Mat frame;
    Mat channels[3];
    for (int i = 0; i < 3; ++i) {
        m = stoi(stream_in.read_string());
        channels[i]=decodeChannel();
    }
    merge(channels, 3, frame);

    return frame;

}

Mat BlockDecoding::decodeChannel() {
    Mat res= Mat::zeros(height, width, CV_8UC1);
    int r; // tem de ser int, pois pode ser negativo
    unsigned char a, b, c, p;

    // decode first row and first column directly
    for (int col = 0; col < width; col++) {
        res.at<uchar>(0,col)=uchar(stream_in.read(8));
    }

    for (int row = 1; row < height; row++) {
        res.at<uchar>(row,0)=uchar(stream_in.read(8));

    }

    for (int row = 1; row < height; row++)
        for (int col = 1; col < width; col++) {
            r=decodeValue();
            a = res.at<uchar>(row, col - 1);
            b = res.at<uchar>(row - 1, col);
            c = res.at<uchar>(row - 1, col - 1);
            p = JPEG_LS(a, b, c);
            res.at<uchar>(row,col)=uchar(r+int(p));
        }
    return res;
}

unsigned char BlockDecoding::JPEG_LS(unsigned char a, unsigned char b, unsigned char c) {
    unsigned char maximum = max(a,b);
    unsigned char minimum = min(a,b);
    if(c >= maximum)
        return minimum;
    else if (c <= minimum)
        return maximum;
    else
        return a + b - c;
}
