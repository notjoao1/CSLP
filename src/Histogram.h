//
// Created by JPe_D on 10/14/2023.
//

#ifndef GTD_VC_HISTOGRAM_H
#define GTD_VC_HISTOGRAM_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "Frame.h"

using namespace std;

class Histogram {
private:
    static cv::Mat calcColorHist(const cv::Mat& frame);
    void calculateAllHistograms();
    cv::Mat calculateCDF(const cv::Mat& hist) const;
    int frame_pixels;
    vector<cv::Mat> hist_by_channel;
    Mat f;
public:
    Histogram(const Mat& f);
    void displayHistograms();
    cv::Mat equalizeHistogram();
};


#endif //GTD_VC_HISTOGRAM_H