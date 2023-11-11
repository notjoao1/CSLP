//
// Created by JPe_D on 10/14/2023.
//

#ifndef GTD_VC_HISTOGRAM_H
#define GTD_VC_HISTOGRAM_H

#include <vector>
#include "opencv2/opencv.hpp"
#include "../Storage/Frame.h"

using namespace std;

/**
 * @class Histogram
 * @brief Class used to do histogram related operations on frames, such as displaying color histograms
 * and equalizing color histograms.
 */
class Histogram {
private:
    /**
      * @brief Calculate histogram for a single channel.
      * @param channel The input channel for which the histogram will be calculated.
      * @return Single channel Mat object with size 256. Represents the distribution
      * of pixel values in a single channel.
      */
    static cv::Mat calcColorHist(const cv::Mat& channel);

    /**
      * @brief Calculate all histograms for member attribute "Mat f". Calculated histograms
      * will be saved in member attribute "vector<Mat> hist_by_channel"
      */
    void calculateAllHistograms();

    /**
      * @brief Calculate Cumulative Distribution Function for given histogram matrix.
      * @param hist Input histogram matrix with 256 values representing the number of
      * occurrences of pixel values in range [0, 255].
      * @return Mat object with 256 values, representing the cumulative distribution
      * function of given input histogram matrix.
      */
    cv::Mat calculateCDF(const cv::Mat& hist) const;

    /**< Total number of pixels in frame used by this class (height * width) */
    int frame_pixels;

    /**< Container that holds a matrix for each channel, representing the distribution of pixel values as an histogram */
    vector<cv::Mat> hist_by_channel;

    /**< Frame for which operations will be applied */
    Mat f;
public:

    /**
      * @brief Histogram class constructor
      * @param f Input frame.
      */
    Histogram(const Mat& f);

    /**
      * @brief Displays histograms for all channels in frame associated to Histogram object.
      */
    void displayHistograms();

    /**
      * @brief Equalizes histogram to improve frame contrast.
      * @return Frame with equalized histograms.
      */
    cv::Mat equalizeHistogram();
};


#endif //GTD_VC_HISTOGRAM_H