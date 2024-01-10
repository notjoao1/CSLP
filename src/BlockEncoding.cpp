//
// Created by joao on 14/11/2023.
//

#include "BlockEncoding.h"
#include <cmath>


BlockEncoding::BlockEncoding(const string &input_file, const string &output_file, int block_size, int search_area, int keyframe_period, int quantizationY, int quantizationU, int quantizationV) : input_video(input_file), stream_out(output_file), block_size(block_size), search_area(search_area), keyframe_period(keyframe_period), quantizationY(quantizationY), quantizationU(quantizationU), quantizationV(quantizationV) {
    m = 0;  // initialize 'm'
}

void BlockEncoding::encode() {
    Mat curr_frame, previous_frame;
    generate_headers();
    cout << "encoding video with motion estimation..." << endl;
    // frame loop
    int frame_counter = 0;
    while (input_video.nextFrame(curr_frame)) {
        if (frame_counter % keyframe_period == 0) {
            cout << "current_frame (INTRA_FRAME): " << frame_counter << endl;
            encodeIntraFrame(curr_frame);
        } else {
            cout << "current_frame (INTER_FRAME): " << frame_counter << endl;
            encodeInterFrame(curr_frame, previous_frame);
        }
        curr_frame.copyTo(previous_frame);
        frame_counter++;
    }
    stream_out.close();
}


void BlockEncoding::encodeValue(unsigned int v) {
    GolombCode::encode(v, this->m, this->stream_out);
}

void BlockEncoding::generate_headers() {
    int padded_width = input_video.get_frame_width() + ( block_size - input_video.get_frame_width() % block_size) % block_size;
    int padded_height = input_video.get_frame_height() + ( block_size - input_video.get_frame_height() % block_size) % block_size;
    stream_out.write(to_string(padded_width));
    stream_out.write(to_string(padded_height));
    stream_out.write(to_string(input_video.get_frame_width())); // original width
    stream_out.write(to_string(input_video.get_frame_height())); // original height
    stream_out.write(to_string(keyframe_period));
    stream_out.write(to_string(block_size));
    stream_out.write(to_string(search_area));
    stream_out.write(to_string(quantizationY));
    stream_out.write(to_string(quantizationU));
    stream_out.write(to_string(quantizationV));
    stream_out.write(to_string(input_video.get_fps_numerator()));
    stream_out.write(to_string(input_video.get_fps_denominator()));
    stream_out.write(to_string(input_video.get_number_of_frames()));
}

void BlockEncoding::encodeIntraFrame(Mat &f) {
    vector<Mat> channels;
    vector<Mat> decoder_channels;
    split(f, channels);
    vector<int> quantizations = { quantizationY, quantizationU, quantizationV };
    Mat padded_channel;
    for (int n = 0; n < 3; n++) {
        padded_channel  = pad(channels[n]);
        unsigned int e[(padded_channel.cols - 1)*(padded_channel.rows - 1)];
        // mat that will have values received in decoder, for lossy encoding
        Mat decoder_values = Mat::zeros(padded_channel.rows, padded_channel.cols, CV_8UC1);

        padded_channel.copyTo(decoder_values);

        // Pre compute error values
        int r; // tem de ser int, pois pode ser negativo
        unsigned char a, b, c, p;

        for (int row = 1; row < padded_channel.rows; row++)
            for (int col = 1; col < padded_channel.cols; col++) {
                a = decoder_values.at<uchar>(row, col - 1);
                b = decoder_values.at<uchar>(row - 1, col);
                c = decoder_values.at<uchar>(row - 1, col - 1);
                p = JPEG_LS(a, b, c);
                r = int(decoder_values.at<uchar>(row, col)) - int(p);

                // simulate decoder process
                int reconstructed_val = p + ((r >> quantizations[n]) << quantizations[n]);
                decoder_values.at<uchar>(row, col) = reconstructed_val < 0 ? 0 : reconstructed_val;
                e[(col - 1) + (row - 1) * (padded_channel.cols - 1)] = GolombCode::mapIntToUInt(r >> quantizations[n]);
            }

        // estimate 'm' based on values that will be encoded
        m = GolombCode::estimate(e,padded_channel.cols - 1,padded_channel.rows - 1);

        // write 'm' and encoded channel values
        stream_out.write(to_string(m));

        // encode first row and first column directly
        for (int col = 0; col < padded_channel.cols; col++) {
            stream_out.write(8, padded_channel.at<uchar>(0, col));
        }

        for (int row = 1; row < padded_channel.rows; row++) {
            stream_out.write(8, padded_channel.at<uchar>(row, 0));

        }
        for (int i = 0; i < (padded_channel.rows-1) * (padded_channel.cols-1); i++)
            encodeValue( e[i] );
        decoder_channels.push_back(decoder_values);
    }
    merge(decoder_channels, f);
}




// f - current frame; p - previous frame
void BlockEncoding::encodeInterFrame(const Mat &f, const Mat &p) {
    vector<Mat> curr_channels, prev_channels;
    split(f, curr_channels);
    split(p, prev_channels);
    vector<int> quantizations = { quantizationY, quantizationU, quantizationV };
    // iterate through channels, both frames have same number
    for (int i = 0; i < f.channels(); ++i) {
        encodeInterframeChannel(pad(curr_channels.at(i)), pad(prev_channels.at(i)), quantizations[i]);
    }
    merge(curr_channels, f);
}


void BlockEncoding::encodeInterframeChannel(const Mat& c_channel, const Mat& p_channel, int quantization) {
    Mat curr_block, b_erro; // b_erro - error between the two matrices
    int rows = c_channel.rows, cols = c_channel.cols;
    int bits_to_write = ceil(log2(search_area));
    int quantized_diff=0;
    unsigned int diffs[block_size * block_size];

    for (int i = 0; i < rows / block_size ; ++i) {
        for (int j = 0; j < cols / block_size ; ++j) {
            curr_block = getBlock(c_channel, i * block_size, j * block_size);
            auto [ref_block, desloc_row, desloc_col] = searchBestBlock(p_channel, curr_block, i * block_size, j * block_size, rows, cols);


            for (int row=0; row<block_size; row++){
                for(int col=0; col<block_size; col++){
                    quantized_diff=(int(curr_block.at<uchar>(row,col))- int(ref_block.at<uchar>(row,col))) >> quantization;
                    int reconstructed_value = ref_block.at<uchar>(row,col) + ((quantized_diff) << quantization);
                    diffs[row * block_size + col] = GolombCode::mapIntToUInt(quantized_diff);
                    curr_block.at<uchar>(row, col) = reconstructed_value < 0 ? 0 : reconstructed_value;
                }

            }
            m = GolombCode::estimate(diffs, block_size, block_size);
            stream_out.write(8, m);
            stream_out.write_bit( ( desloc_row < 0 ) ? 1 : 0 );
            stream_out.write(bits_to_write, ( desloc_row < 0 ) ? -desloc_row : desloc_row );
            stream_out.write_bit( ( desloc_col < 0 ) ? 1 : 0 );
            stream_out.write(bits_to_write, ( desloc_col < 0 ) ? -desloc_col : desloc_col);


            if (m != 0) {
                for (int i = 0; i < block_size * block_size; i++) {
                    encodeValue( diffs[i] );
                }
            }

            setBlock(&c_channel, &curr_block, i * block_size, j * block_size);
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
    return mad/(block_size * block_size);
}


static std::tuple<int, int> min_and_index_of( const int arr[] , int siz ) {

    double min = arr[0];
    int min_index = 0;

    for(int i = 1 ; i < siz ; i++){
        if( arr[i] < min ){
            min = arr[i];
            min_index = i;
        }
    }
    return { min , min_index };
}


int LOCATIONS[9][2] = {{0,0},{0, -1}, {-1, 0}, {1, 0}, {0, 1} , {1, -1}, {-1, 1}, {1, 1}, {-1, -1} };

std::tuple<Mat, int, int> BlockEncoding::searchBestBlock(const Mat& prev_frame, const Mat& curr_block, int y, int x, int rows, int cols) {
    int costs[9];
    int step_size = 2;

    int curx = x ;
    int cury = y ;

    while(step_size > 1){
        for (int i = 0; i < 9; ++i) {
            costs[i] = INT_MAX;
        }

        #pragma omp parallel for
        for( int loc = 0 ; loc < 9 ; loc++ ){
            int locy = cury + LOCATIONS[loc][1]*step_size;
            int locx = curx + LOCATIONS[loc][0]*step_size;


            if (locy < 0 || locy + block_size - 1 >= rows ||
                locx < 0 || locx + block_size - 1 >= cols ||
                abs(locx - x) >= search_area || abs(locy - y) >= search_area) {
                continue;
            }

            costs[loc] = calculateMAD( curr_block , getBlock( prev_frame , locy , locx ) );
        }


        auto [ mincosts , index ] = min_and_index_of(costs,9);

        cury = cury + LOCATIONS[index][1]*step_size;
        curx = curx + LOCATIONS[index][0]*step_size;

        if(index == 0) {
            step_size = step_size/2;
        }
    }

    return { getBlock( prev_frame , cury , curx ) , y - cury , x - curx };

}




// Writes golomb-encoded error values row by row
void BlockEncoding::encodeBlockDifference(const Mat &block) {
    for (int i = 0; i < block.rows; ++i) {
        for (int j = 0; j < block.cols; ++j) {
            stream_out.write_bit( ( block.at<int>(i,j) < 0 ) ? 1 : 0 );
            GolombCode::encode(block.at<int>(i, j), 3, this->stream_out);
        }
    }
}

Mat BlockEncoding::pad(const Mat &frame) const {
    int cols = frame.cols;
    int rows = frame.rows;

    if( cols % block_size == 0 && rows % block_size == 0 )
        return frame;

    cols = cols + (block_size - cols % block_size) % block_size;
    rows = rows + (block_size - rows % block_size) % block_size;

    Mat padded_mat = Mat::zeros(rows , cols, CV_8UC1);

    cv::Rect roi(0, 0, frame.cols, frame.rows);
    frame.copyTo(padded_mat(roi));
    return padded_mat;
}

void BlockEncoding::setBlock(const cv::Mat *original_frame, cv::Mat *block, int row, int col) const {
    // create region of interest for block
    // columns - x-axis; rows - y-axis
    Rect roi(col, row, block_size, block_size);
    block->copyTo((*original_frame)(roi));
}


