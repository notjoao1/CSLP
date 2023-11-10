//
// Created by tiago on 07-11-2023.
//

#include "Decoder.h"


Decoder::Decoder(const string &input_file):stream_in(input_file) {
    m = 3; //initialize 'm'
}

void Decoder::read_headers() {
    rows=stoi(stream_in.read_string());
    cols=stoi(stream_in.read_string());
    //TODO: read of ColorSpace and check if need to read m once or per frame
}

vector<Mat> Decoder::decode(){
    vector<Mat> video;
    read_headers();
    cout << "decoding video..." << endl;

    Mat curr_frame;
    curr_frame = decodeFrame();
    // frame loop
    int counter = 0; // testing stuff
    while (!curr_frame.empty()) {
        cout << "current_frame: " << counter << endl;
        imshow("Current Frame",curr_frame);
        waitKey(0);
        video.at(0)=curr_frame;
        curr_frame = decodeFrame();
        counter++;
    }
    return video;
}

Mat Decoder::decodeFrame() {
    Mat frame;
    std::vector<Mat> channels;
    for (int i = 0; i < 3; ++i) {
        int tempM= stoi(stream_in.read_string()); //temp m TODO: check if necessary
        channels[i]=decodeChannel();
    }
    merge(channels,frame);

}

Mat Decoder::decodeChannel() {
    Mat res= Mat::zeros(rows, cols, uchar());
    int r; // tem de ser int, pois pode ser negativo
    unsigned char a, b, c, p;

    // decode first row and first column directly
    for (int col = 0; col < cols; col++) {
        res.at<uchar>(1,col)=uchar(decodeValue());
    }

    for (int row = 1; row < rows; row++) {
        res.at<uchar>(row,1)=uchar(decodeValue());
    }

    for (int row = 1; row < rows; row++)
        for (int col = 1; col < cols; col++) {
            r=decodeValue();
            a = res.at<uchar>(row, col - 1);
            b = res.at<uchar>(row - 1, col);
            c = res.at<uchar>(row - 1, col - 1);
            p = JPEG_LS(a, b, c);
            res.at<uchar>(row,col)=uchar(r+int(p));
        }
    return res;
}

int Decoder::decodeValue() {
    return GolombCode::decode_one(m,stream_in);
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
