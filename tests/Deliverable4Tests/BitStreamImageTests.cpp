//
// Created by JPe_D on 11/14/2023.
//

#include "opencv2/opencv.hpp"
#include "../../src/BitStream/BitStreamWrite.h"
#include "../../src/BitStream/BitStreamRead.h"

using namespace cv;

void writeImage(const cv::Mat& frame, BitStreamWrite* stream) {
    Mat channels[3];
    split(frame, channels);
    for (auto & channel : channels)
        for (int i = 0; i < frame.rows; i++)
            for (int j = 0; j < frame.cols; ++j) {
                stream->write(8, channel.at<uchar>(i, j));
            }
}


cv::Mat readImage(BitStreamRead* stream, int rows, int cols) {
    Mat frame;
    Mat channels[3];
    Mat curr_frame;
    for (auto & channel : channels) {
        curr_frame = Mat::zeros(rows, cols, CV_8UC1);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                curr_frame.at<uchar>(i, j) = stream->read(8);
            }
        }
        channel = curr_frame.clone();
    }
    merge(channels, 3, frame);

    return frame;
}

int main() {
    Mat img = cv::imread("tests/Deliverable4Tests/videos/star.png");
    imshow("img original", img);
    waitKey(0);
    BitStreamWrite out("tests/Deliverable4Tests/newimgRAW.gtd");
    writeImage(img, &out);
    out.close();
    BitStreamRead in("tests/Deliverable4Tests/newimgRAW.gtd");
    Mat img_after_read = readImage(&in, img.rows, img.cols);
    std::cout << "made it here" << std::endl;
    imshow("img after reading", img_after_read);
    waitKey(0);
    return 0;
}