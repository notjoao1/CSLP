//
// Created by joao on 14/11/2023.
//

#include "BlockEncoding.h"
#include <cmath>



BlockEncoding::BlockEncoding(const string &input_file, const string &output_file, int block_size, int search_area, int keyframe_period, int quantization) : input_video(input_file), stream_out(output_file), block_size(block_size), search_area(search_area), keyframe_period(keyframe_period), quantization(quantization) {
    m = 0;  // initialize 'm'
}

void BlockEncoding::encode() {
    Mat curr_frame;
    Mat previous_frame = Mat::zeros(720, 1280, CV_8UC1);
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
    stream_out.write(to_string(input_video.get_frame_width()));
    stream_out.write(to_string(input_video.get_frame_height()));
    stream_out.write(to_string(keyframe_period));
    stream_out.write(to_string(block_size));
    stream_out.write(to_string(search_area));
    stream_out.write(to_string(quantization));
    stream_out.write(to_string(input_video.get_fps_numerator()));
    stream_out.write(to_string(input_video.get_fps_denominator()));
    stream_out.write(to_string(input_video.get_number_of_frames()));
}

void BlockEncoding::encodeIntraFrame(const Mat &f) {
    vector<Mat> channels;
    split(f, channels);
    for (auto channel : channels) {
        unsigned int e[(channel.cols - 1)*(channel.rows - 1)];

        // Pre compute error values
        int r; // tem de ser int, pois pode ser negativo
        unsigned char a, b, c, p;

        for (int row = 1; row < channel.rows; row++)
            for (int col = 1; col < channel.cols; col++) {
                a = channel.at<uchar>(row, col - 1);
                b = channel.at<uchar>(row - 1, col);
                c = channel.at<uchar>(row - 1, col - 1);
                p = JPEG_LS(a, b, c);
                r = int(channel.at<uchar>(row, col)) - int(p);
                e[(col - 1) + (row - 1) * (channel.cols - 1)] = GolombCode::mapIntToUInt(r);
            }

        // estimate 'm' based on values that will be encoded
        m = GolombCode::estimate(e,channel.cols - 1,channel.rows - 1);

        // write 'm' and encoded channel values
        stream_out.write(to_string(m));

        // encode first row and first column directly
        for (int col = 0; col < channel.cols; col++) {
            //stream_out->write(8, channel.at<uchar>(0, col));
            stream_out.write(8, channel.at<uchar>(0, col));
        }

        for (int row = 1; row < channel.rows; row++) {
            //stream_out->write(8, channel.at<uchar>(row, 0));
            stream_out.write(8, channel.at<uchar>(row, 0));

        }
        for (int i = 0; i < (channel.rows-1) * (channel.cols-1); i++)
            encodeValue( e[i] );
    }
}




// f - current frame; p - previous frame
void BlockEncoding::encodeInterFrame(const Mat &f, const Mat &p) {
    vector<Mat> curr_channels, prev_channels;
    split(f, curr_channels);
    split(p, prev_channels);

    // iterate through channels, both frames have same number
    for (int i = 0; i < f.channels(); ++i) {
        encodeInterframeChannel(pad(curr_channels.at(i)), pad(prev_channels.at(i)));
    }

}


void BlockEncoding::encodeInterframeChannel(const Mat& c_channel, const Mat& p_channel) {
    Mat curr_block, b_erro; // b_erro - error between the two matrices
    Mat decoder_values=Mat::zeros(block_size, block_size, CV_8UC1);
    int rows = c_channel.rows, cols = c_channel.cols;
    int bits_to_write = ceil(log2(search_area));
    int diff=0;
    for (int i = 0; i < rows / block_size ; ++i) {
        for (int j = 0; j < cols / block_size ; ++j) {
            curr_block = getBlock(c_channel, i * block_size, j * block_size);
            auto [ref_block, desloc_row, desloc_col] = searchBestBlock(p_channel, curr_block, i * block_size, j * block_size, rows, cols);
            ref_block.copyTo(decoder_values);
            stream_out.write_bit( ( desloc_row < 0 ) ? 1 : 0 );
            stream_out.write(bits_to_write, ( desloc_row < 0 ) ? -desloc_row : desloc_row );
            stream_out.write_bit( ( desloc_col < 0 ) ? 1 : 0 );
            stream_out.write(bits_to_write, ( desloc_col < 0 ) ? -desloc_col : desloc_col);
            
            // cout << i << " , " << j << " desloc: "<< desloc_col << " , " << desloc_row << endl;

            for (int row=0; row<block_size; row++){
                for(int col=0; col<block_size; col++){
                    diff=int(decoder_values.at<uchar>(row,col))- int(ref_block.at<uchar>(row,col));
                    decoder_values.at<uchar>(row, col) = ref_block.at<uchar>(row,col) + ((diff >> quantization) << quantization);

                    // stream_out.write_bit( (diff < 0) ? 1: 0);
                    // GolombCode::encode(diff, 3, this->stream_out);
                    // cout << GolombCode::mapIntToUInt(diff) << " , " ;
                    GolombCode::encode( GolombCode::mapIntToUInt(diff >> quantization) , 16 , stream_out );
                }
                // cout << endl;
            }
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


            if (locy < 0 || locy + block_size - 1 > rows ||
                locx < 0 || locx + block_size - 1 > cols ||
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

    cols = cols + block_size - cols % block_size;
    rows = rows + block_size - rows % block_size;

    Mat padded_mat = Mat::zeros(rows , cols, CV_8UC1);

    cv::Rect roi(0, 0, frame.cols, frame.rows);
    frame.copyTo(padded_mat(roi));

    for(int i = 0 ; i < frame.cols ; i++){
        for(int p = 0 ; p < block_size - frame.cols % block_size ; p++){
            padded_mat.at<uchar>( frame.rows + p , i ) = frame.at<uchar>( frame.rows -1 ,i );
        }
    }

    for(int i = 0 ; i < rows ; i++){
        for(int p = 0 ; p < block_size - frame.rows % block_size ; p++){
            padded_mat.at<uchar>( i , frame.cols + p ) = padded_mat.at<uchar>( i , frame.cols - 1 );
        }
    }

    return padded_mat;
}


