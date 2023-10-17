//
// Created by Kikom on 17/10/2023.
//

#include "Threshold.h"

Mat Threshold::apply(cv::Mat frame) {
    Mat result;

    Mat return_frame = Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1);
    for(int i = 0; i < frame.rows; i++) {
        for (int j = 0; j < frame.cols; j++) {
            return_frame.at<uchar>(i, j) = ( frame.at<uchar>(i, j) < threshold )? inverted : 1-inverted;
        }
    }

    return return_frame;
}

Threshold::Threshold(unsigned char t, bool inv) {
    this->threshold = t;
    this->inverted = inv;
}
