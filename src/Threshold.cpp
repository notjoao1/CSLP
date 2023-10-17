//
// Created by Kikom on 17/10/2023.
//

#include "Threshold.h"

Frame Threshold::apply(Frame frame) {
    Mat result;

    Mat channels=frame.getChannels().toMat();
    Mat return_frame = Mat::zeros(Size(channels.cols, channels.rows), uchar());
    for(int i = 0; i < channels.rows; i++) {
        for (int j = 0; j < channels.cols; j++) {
            return_frame.at<uchar>(i, j) = ( channels.at<uchar>(i, j) < threshold )? inverted *255: (1-inverted)*255;
        }
    }

    frame.fromMat(return_frame);
    return frame;
}

Threshold::Threshold(unsigned char t, bool inv) {
    this->threshold = t;
    this->inverted = inv;
}
