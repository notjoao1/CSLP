//
// Created by JPe_D on 10/13/2023.
//
#include <iostream>
#include "opencv2/opencv.hpp"
#include "../src/ImageManipulator.h"
#include "../src/VideoManipulator.h"
#include "../src/ColorSpace.h"
#include "../src/Channels.h"

int main() {

    VideoManipulator vm;
    Mat image= cv::imread("../resources/image.jpeg");
    Mat test;
    vector<Mat> channels1(3);
    split(image,channels1);
    Channels channels(channels1[0],channels1[1],channels1[2],RGB);
    channels=ColorSpace::convert(channels,RGB,YUV);
    channels=ColorSpace::extend(channels,YUV);
    merge(vector<Mat>{channels.value0,channels.value1,channels.value2},test);
    imshow("Original RGB",image);
    cvtColor(test,test,COLOR_YUV2RGB);
    imshow("Final YUV", test);
    waitKey();
    cout<<image.type();
    //ColorSpace::YUV4_2_0(image);


    return 0;

}
}