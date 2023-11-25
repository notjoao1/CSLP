//
// Created by JPe_D on 11/2/2023.
//

#include "Encoder.h"
#include <vector>

using namespace std;

Encoder::Encoder(VideoManipulator* in, BitStreamWrite* out) {
    this->m = 12; // initialize 'm'
    this->video = in;
    this->stream_out = out;
}

// TODO: falta o "video_format"
void Encoder::generate_headers(const Size& frame_size) {
    stream_out->write(to_string(frame_size.width));
    stream_out->write(to_string(frame_size.height));
    stream_out->write(to_string(video->getFPS()));
}

// Receives multi-channel Mat
void Encoder::encodeFrame(const Mat& f) {
    std::vector<Mat> channels;
    split(f, channels);
    for (int i = 0; i < f.channels(); ++i) {
        encodeChannel(channels[i]);
    }
}

// Receives single channel Mat
void Encoder::encodeChannel(const Mat& channel) {
    // array that will be used to estimate 'm' parameter
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
    stream_out->write(to_string(m));

    // encode first row and first column directly
    for (int col = 0; col < channel.cols; col++) {
        //stream_out->write(8, channel.at<uchar>(0, col));
        stream_out->write(8, channel.at<uchar>(0, col));
    }

    for (int row = 1; row < channel.rows; row++) {
        //stream_out->write(8, channel.at<uchar>(row, 0));
        stream_out->write(8, channel.at<uchar>(row, 0));

    }
    for (int i = 0; i < (channel.rows-1) * (channel.cols-1); i++)
        encodeValue( e[i] );

}

void Encoder::encodeValue(unsigned int v) {
    GolombCode::encode(v, this->m, *stream_out);
}

void Encoder::encode() {
    Mat curr_frame;
    curr_frame = video->getNextFrame();
    generate_headers(curr_frame.size());
    cout << "encoding video..." << endl;

    // frame loop
    int counter = 0; // testing stuff
    while (!curr_frame.empty()) {
        cout << "current_frame: " << counter << endl;
        encodeFrame(curr_frame);
        curr_frame = video->getNextFrame();
        counter++;
    }
}

unsigned char Encoder::JPEG_LS(unsigned char a, unsigned char b, unsigned char c) {
    unsigned char maximum = max(a,b);
    unsigned char minimum = min(a,b);
    if(c >= maximum)
        return minimum;
    else if (c <= minimum)
        return maximum;
    else
        return a + b - c;
}


