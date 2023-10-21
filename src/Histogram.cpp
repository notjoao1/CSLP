//
// Created by JPe_D on 10/14/2023.
//

#include "Histogram.h"
#include "iostream"

using namespace cv;

void Histogram::displayHistograms() {
    // if histogram values haven't been calculated, calculate them
    if (hist_by_channel.empty())
        calculateAllHistograms();
    if (f.channels() < 3) {
        std::cerr << "ERROR: displayHistograms() - frame.channels() < 3" << std::endl;
        return;
    }

    Mat b_hist, g_hist, r_hist;

    // create histogram image
    int hist_size = 256;
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/hist_size );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

    // normalize values to fit within histogram image's height
    normalize(hist_by_channel[0], b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(hist_by_channel[1], g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(hist_by_channel[2], r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < hist_size; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0 );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0 );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0 );
    }
    imshow("Color Histogram", histImage );
    waitKey();

}


Mat Histogram::calcColorHist(const Mat& channel) {
    Mat output_mat = Mat::zeros(256, 1, CV_32FC1);

    uchar curr_pixel;
    for (int i = 0; i < channel.rows; ++i)
        for (int j = 0; j < channel.cols; ++j)
        {
            curr_pixel = channel.at<uchar>(i, j);
            output_mat.at<float>(curr_pixel,0)++;
        }

    return output_mat;
}

cv::Mat Histogram::equalizeHistogram() {
    // if histograms haven't been calculated, calculate them
    if (hist_by_channel.empty())
        calculateAllHistograms();
    Mat channels[f.channels()];
    split(f, channels);

    vector<Mat> equalized_channels;
    Mat curr_cdf, curr_channel, new_channel;
    for (int i = 0; i < hist_by_channel.size(); ++i) {
        curr_cdf = calculateCDF(hist_by_channel.at(i));
        // normalize CDF to values in [0, 255]
        curr_cdf *= 255;
        curr_channel = channels[i];
        new_channel = Mat(curr_channel.rows, curr_channel.cols, CV_8UC1);
        for (int j = 0; j < curr_channel.rows; ++j) {
            for (int k = 0; k < curr_channel.cols; ++k) {
                new_channel.at<uchar>(j, k) = round(curr_cdf.at<float>(curr_channel.at<uchar>(j, k)));
            }

        }
        equalized_channels.push_back(new_channel);
    }
    Mat output_mat;
    merge(equalized_channels, output_mat);
    return output_mat;
}

cv::Mat Histogram::calculateCDF(const cv::Mat& hist) const {
    Mat cdf = Mat::zeros(256, 1, CV_32FC1);
    // calculate first value
    cdf.at<float>(0) = hist.at<float>(0) / float(frame_pixels);
    // cumulative sum function
    for (int i = 1; i < hist.rows; ++i) {
        cdf.at<float>(i) = cdf.at<float>(i-1) + (hist.at<float>(i) / float(frame_pixels));
    }
    return cdf;
}

Histogram::Histogram(const Mat& f) {
    this->f = f;
    this->frame_pixels = f.rows * f.cols;
}

void Histogram::calculateAllHistograms() {
    vector<Mat> channels;
    split(f, channels);

    for (const Mat& channel: channels) {
        hist_by_channel.push_back(calcColorHist(channel));
    }
}
