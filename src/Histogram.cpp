//
// Created by JPe_D on 10/14/2023.
//

#include "Histogram.h"
#include "iostream"

using namespace cv;

void Histogram::displayHistograms(const Mat& frame) {
    if (frame.channels() < 3) {
        std::cerr << "ERROR: displayHistograms() - frame.channels() < 3" << std::endl;
        return;
    }
    vector<Mat> channels;
    split(frame, channels);

    Mat b_hist, g_hist, r_hist;
    b_hist = calcColorHist(channels[0]);
    g_hist = calcColorHist(channels[1]);
    r_hist = calcColorHist(channels[2]);

     // create histogram image
    int hist_size = 256;
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/hist_size );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    std::cout << b_hist << std::endl;

    // normalize values to fit within histogram image's height
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    std::cout << b_hist << std::endl;
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
