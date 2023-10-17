//
// Created by JPe_D on 10/14/2023.
//

#ifndef GTD_VC_HISTOGRAM_H
#define GTD_VC_HISTOGRAM_H

#include <vector>
#include "opencv2/opencv.hpp"

using namespace std;

class Histogram {
private:
    static cv::Mat calcColorHist(const cv::Mat& frame);
public:
    static void displayHistograms(const cv::Mat& frame);
};


#endif //GTD_VC_HISTOGRAM_H
