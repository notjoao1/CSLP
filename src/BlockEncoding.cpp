//
// Created by joao on 14/11/2023.
//

#include "BlockEncoding.h"

BlockEncoding::BlockEncoding(const string &input_file, const string &output_file, int block_size, int search_area, int keyframe_period) : video(input_file), stream_out(output_file), block_size(block_size), search_area(search_area), keyframe_period(keyframe_period) {
    int m = 3;
}

void BlockEncoding::encode() {
    Mat curr_frame, previous_frame;
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
            encodeInterFrame(curr_frame, previous_frame);
            cout << "current_frame (INTER_FRAME): " << frame_counter << endl;
        }
        previous_frame = curr_frame.clone();
        curr_frame = video.getNextFrame();
        frame_counter++;
    }
}


void BlockEncoding::encodeValue(unsigned int v) {
    GolombCode::encode(v, this->m, this->stream_out);
}

void BlockEncoding::generate_headers(const Size &frame_size) {
    stream_out.write(to_string(frame_size.width));
    stream_out.write(to_string(frame_size.height));
    stream_out.write(to_string(block_size));
    stream_out.write(to_string(search_area));
    stream_out.write(to_string(keyframe_period));
}

// TODO: estimar 'm' para cada channel?
void BlockEncoding::encodeIntraFrame(const Mat &f) {
    vector<Mat> channels;
    split(f, channels);
    for (auto channel : channels) {
        for (int col = 0; col < channel.cols; ++col) {
            encodeValue(channel.at<uchar>(0, col));
        }

        for (int row = 1; row < channel.rows; row++) {
            encodeValue(channel.at<uchar>(row, 0));
        }

        int r; // tem de ser int, pois pode ser negativo
        unsigned char a, b, c, p;

        for (int row = 1; row < channel.rows; row++)
            for (int col = 1; col < channel.cols; col++) {
                a = channel.at<uchar>(row, col - 1);
                b = channel.at<uchar>(row - 1, col);
                c = channel.at<uchar>(row - 1, col - 1);
                p = JPEG_LS(a, b, c);
                r = int(channel.at<uchar>(row, col)) - int(p);
                encodeValue(GolombCode::mapIntToUInt(r));
            }
    }
}


// TODO: adicionar padding para ter frames divisiveis pelo block_size!!!!!
// f - current frame; p - previous frame
void BlockEncoding::encodeInterFrame(const Mat &f, const Mat &p) {
    std::cout << "Encoding interframe" << std::endl;
    vector<Mat> curr_channels, prev_channels;
    split(f, curr_channels);
    split(p, prev_channels);

    // iterate through channels, both frames have same number
    for (int i = 0; i < f.channels(); ++i) {
        encodeInterframeChannel(curr_channels.at(i), prev_channels.at(i));
    }

}


void BlockEncoding::encodeInterframeChannel(const Mat& c_channel, const Mat& p_channel) {
    Mat curr_block;
    std::cout << "Full current channel: \n" << c_channel << std::endl;
    for (int i = 0; i < c_channel.rows / block_size; ++i) {
        for (int j = 0; j < c_channel.cols / block_size; ++j) {
            curr_block = getBlock(c_channel, i * block_size, j * block_size);
            searchBestBlock(curr_block, p_channel, )
        }
    }
}

Mat BlockEncoding::getBlock(const Mat &original_frame, int row, int col) const {
    // create region of interest for block
    // columns - x-axis; rows - y-axis
    Rect roi(col, row, block_size, block_size);
    Mat block = original_frame(roi);
    return block;
}

unsigned char BlockEncoding::JPEG_LS(unsigned char a, unsigned char b, unsigned char c) {
    unsigned char maximum = max(a,b);
    unsigned char minimum = min(a,b);
    if(c >= maximum)
        return minimum;
    else if (c <= minimum)
        return maximum;
    else
        return a + b - c;
}

std::tuple<Mat, int, int> BlockEncoding::searchBestBlock(const Mat &prev, const Mat &orig_block, int x, int y) {
    int x_start, x_end, y_start, y_end; // loop boundaries

    x_start = x - search_area;
    if (x_start < 0) {
        x_start = 0;
    }

    x_end = x + block_size + (search_area - 1);
    if (x_end > prev.cols) {
        x_end = prev.cols;
    }

    y_start = y - search_area;
    if (y_start < 0) {
        y_start = 0;
    }

    y_end = y + block_size + (search_area - 1);
    if (y_end > prev.rows) {
        y_end = prev.rows;
    }


    for (int i = x_start; i < x_end; ++i) {
        for (int j = y_start; j < y_end; ++j) {

        }
    }

    return {};
}
