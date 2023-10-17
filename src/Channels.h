//
// Created by tiago on 13-10-2023.
//

#ifndef GTD_VC_CHANNELS_H
#define GTD_VC_CHANNELS_H
#include <utility>

#include "opencv2/opencv.hpp"
#include "Colors.h"
#include "ColorSpace.h"

using namespace std;
using namespace cv;

struct Channels {
    Mat value0;
    Mat value1;
    Mat value2;
    Color Colorspace;
    Channels(Mat v1,Color v4)
            : value0(std::move(v1)), value1(Mat::zeros(1,1,uchar())), value2(Mat::zeros(1,1,uchar())), Colorspace(v4) {
    }
    Channels(Mat v1, Mat v2, Mat v3,Color v4)
            : value0(std::move(v1)), value1(std::move(v2)), value2(std::move(v3)), Colorspace(v4) {
    }
    void setColorspace(Color color);
    Mat toMat();
};


#endif //GTD_VC_CHANNELS_H
