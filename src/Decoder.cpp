//
// Created by tiago on 07-11-2023.
//

#include "Decoder.h"


Decoder::Decoder(BitStreamRead* in, const std::string& output_fname) : output_vid(output_fname) {
    this->m = 3; //initialize 'm'
    this->stream_in=in;
}

//TODO: read of ColorSpace
void Decoder::read_headers() {
    cols=stoi(stream_in->read_string());
    rows=stoi(stream_in->read_string());
    fps_num=stoi(stream_in->read_string());
    fps_denominator = stoi(stream_in->read_string());
    quantization = stoi(stream_in->read_string());
}

void Decoder::decode(){
    read_headers();
    cout << "decoding video..." << endl;

    // write headers to output file
    output_vid.writeHeader(cols, rows, fps_num, fps_denominator);

    // total frames to be read
    int missing_frames = stoi(stream_in->read_string()); // read total number of frames

    Mat curr_frame;

    // read first frame
    curr_frame = decodeFrame();
    output_vid.writeFrame(&curr_frame);
    missing_frames--;
    // frame loop
    while (missing_frames > 0) {
        curr_frame = decodeFrame();
        output_vid.writeFrame(&curr_frame);
        missing_frames--;
    }
    output_vid.closeFile();
    stream_in->close();
}

Mat Decoder::decodeFrame() {
    Mat frame;
    Mat channels[3];
    for (int i = 0; i < 3; ++i) {
        string abc = stream_in->read_string();
        std::cout << "read from stream value - " << abc << std::endl;
        m = stoi(abc);
        std::cout << "m - " << m << std::endl;
        channels[i]=decodeChannel();
    }
    merge(channels, 3, frame);
    return frame;

}

Mat Decoder::decodeChannel() {
    Mat res= Mat::zeros(rows, cols, CV_8UC1);
    int r; // tem de ser int, pois pode ser negativo
    unsigned char a, b, c, p;

    // decode first row and first column directly
    for (int col = 0; col < cols; col++) {
        res.at<uchar>(0,col)=uchar(stream_in->read(8));
    }

    for (int row = 1; row < rows; row++) {
        res.at<uchar>(row,0)=uchar(stream_in->read(8));

    }

    for (int row = 1; row < rows; row++)
        for (int col = 1; col < cols; col++) {
            r=decodeValue() << quantization;
            a = res.at<uchar>(row, col - 1);
            b = res.at<uchar>(row - 1, col);
            c = res.at<uchar>(row - 1, col - 1);
            p = JPEG_LS(a, b, c);
            res.at<uchar>(row,col)=uchar(r+int(p));
        }
    std::cout << "whole channel sum " << sum(res) << std::endl;
    imshow("whole channel", res);
    waitKey(0);
    return res;
}

int Decoder::decodeValue() {
    return GolombCode::mapUIntToInt( GolombCode::decode_one(m,*stream_in) );
}

unsigned char Decoder::JPEG_LS(unsigned char a, unsigned char b, unsigned char c) {
    unsigned char maximum = max(a,b);
    unsigned char minimum = min(a,b);
    if(c >= maximum)
        return minimum;
    else if (c <= minimum)
        return maximum;
    else
        return a + b - c;
}
