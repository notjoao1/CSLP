//
// Created by tiago on 07-11-2023.
//

#include "Decoder.h"


Decoder::Decoder(BitStreamRead* in) {
    this->m = 3; //initialize 'm'
    this->stream_in=in;
}

void Decoder::read_headers() {
    cols=stoi(stream_in->read_string());
    rows=stoi(stream_in->read_string());
    fps=stoi(stream_in->read_string());
    //TODO: read of ColorSpace and check if need to read m once or per frame
}

vector<Mat> Decoder::decode(){
    vector<Mat> video;
    read_headers();
    cout << "decoding video..." << endl;

    Mat curr_frame;
    curr_frame = decodeFrame();
    imshow("First Frame",curr_frame);
    waitKey(0);
    // frame loop
    int counter = 0; // testing stuff
    while (!curr_frame.empty()) {
        cout << "current_frame: " << counter << endl;
        video.push_back(curr_frame);
        curr_frame = decodeFrame();
        counter++;
    }
    return video;
}

Mat Decoder::decodeFrame() {
    Mat frame;
    Mat channels[3];
    for (int i = 0; i < 3; ++i) {
        m = stoi(stream_in->read_string());
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
        res.at<uchar>(0,col)=uchar(GolombCode::decode_one(m, *stream_in));
    }

    std::cout << "rows : " << rows << std::endl;
    for (int row = 1; row < rows; row++) {
        res.at<uchar>(row,0)=uchar(GolombCode::decode_one(m, *stream_in));

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
    return GolombCode::mapUIntToInt( GolombCode::decode_one(m,*stream_in) );
}

int Decoder::getFPS() {
    return this->fps;
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
