//1
// Created by joao on 26/09/2023.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "ImageManipulator.h"
#include "VideoManipulator.h"
#include "ColorSpace.h"
#include "Channels.h"
#include "Blur.h"
#include "BlurGaussian.h"
#include "Colors.h"
#include "Grayscale.h"
#include "Histogram.h"
#include "WatermarkImage.h"
#include "WatermarkText.h"

int main() {
    VideoManipulator vm;
    Mat image= cv::imread("resources/bu.PNG");
    Histogram h(image);
    h.displayHistograms();
    Mat equalizedBuh = h.equalizeHistogram();
    WatermarkImage wi(cv::imread("resources/bu.PNG"));
    WatermarkText wt("buh", BLACK);
    vector<Mat> split_buh;
    split(equalizedBuh, split_buh);
    Channels c(split_buh[0], split_buh[1], split_buh[2], BGR);
    Frame f(c);
    f.addEffect(&wi);
    f.addEffect(&wt);
    f.applyEffects();
    imshow("ORIGINAL BUH", image);
    imshow("EQUALIZED & WATERMARKED BUH", f.getChannels().toMat());
    waitKey();
    return 0;

}