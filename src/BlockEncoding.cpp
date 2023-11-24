//
// Created by joao on 14/11/2023.
//

#include "BlockEncoding.h"

BlockEncoding::BlockEncoding(const string &input_file, const string &output_file, int block_size, int search_area, int keyframe_period) : video(input_file), stream_out(output_file), block_size(block_size), search_area(search_area), keyframe_period(keyframe_period) {
    m = 3;
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


// TODO: adicionar padding para ter frames divisiveis pelo block_size!!!!! meter valores de 0 padded
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
    Mat curr_block, b_erro; // b_erro é o erro entre duas matrizes
    int rows = c_channel.rows, cols = c_channel.cols;
    //std::cout << "Full current channel: \n" << c_channel << std::endl;
    for (int i = 0; i < rows / block_size - 1; ++i) {
        for (int j = 0; j < cols / block_size - 1; ++j) {
            curr_block = getBlock(c_channel, i * block_size, j * block_size);
            auto [ref_block, desloc_row, desloc_col] = searchBestBlock(p_channel, curr_block, i, j, rows, cols);
            b_erro = curr_block - ref_block;
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

// Calculate mean absolute difference between 2 blocks
int BlockEncoding::calculateMAD(const Mat& block1, const Mat& block2) const {
    int mad = 0;
    for (int i = 0; i < block_size; ++i) {
        for (int j = 0; j < block_size; ++j) {
            mad += std::abs(block1.at<uchar>(i, j) - block2.at<uchar>(i, j));
        }
    }

    cv::Mat diff;
    cv::absdiff(block1, block2, diff);
    //std::cout << "MAD by OPENCV: " << cv::sum(diff)[0] / (block_size * block_size) << std::endl;
    //std::cout << "MAD by ME: " << mad / (block_size * block_size) << std::endl;
    return mad/(block_size * block_size);
}

std::tuple<Mat, int, int> BlockEncoding::searchBestBlock(const Mat& prev_frame, const Mat& curr_block, int b_row, int b_col, int rows, int cols) {
    // precompute boundaries
    int start_col = (b_col - search_area < 0) ? 0 : b_col - search_area;
    int end_col = (b_col + block_size + search_area > cols) ? cols - block_size : b_col + search_area;

    int start_row = (b_row - search_area < 0) ? 0 : b_row - search_area;
    int end_row = (b_row + block_size + search_area > rows) ? rows - block_size : b_row + search_area;

    int best_match_row = b_row;
    int best_match_col = b_col;
    int min_mad = INT_MAX;
    Mat ref_block;

    #pragma omp parallel for
    for (int col = start_col; col < end_col; ++col) {
        for (int row = start_row; row < end_row; ++row) {
            ref_block = getBlock(prev_frame, row, col);
            int mad = calculateMAD(curr_block, ref_block);
            if (mad < min_mad) {
                min_mad = mad;
                best_match_row = col;
                best_match_col = row;
                if (min_mad == 0)  // found perfect match, no point searching more
                    break;
            }
        }
    }

    best_match_row = best_match_row - b_row;
    best_match_col = best_match_col - b_col;

    return {ref_block, best_match_row, best_match_col};
}

