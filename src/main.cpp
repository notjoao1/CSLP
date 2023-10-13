//1
// Created by joao on 26/09/2023.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "ImageManipulator.h"
#include "VideoManipulator.h"
#include "ColorSpace.h"
int main() {
    VideoManipulator vm;
    Mat image= cv::imread("../resources/image.jpeg");
    Mat test;
    vector<Mat> channels1(3);
    split(image,channels1);
    Channels channels(channels1[0],channels1[1],channels1[2]);
    channels=ColorSpace::convert(channels,"RGB","YUV4_2_2");
    channels=ColorSpace::extend(channels,"YUV4_2_2");

    merge(vector<Mat>{channels.value0,channels.value1,channels.value2},test);

    imshow("Original RGB",image);
    cvtColor(test,test,COLOR_YUV2RGB);
    cvtColor(test,test,COLOR_RGB2BGR);
    imshow("Final YUV", test);
    waitKey();
    cout<<image.type();
    //ColorSpace::YUV4_2_0(image);


    return 0;
}