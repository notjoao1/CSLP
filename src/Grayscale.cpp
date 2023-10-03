//
// Created by joao on 03/10/2023.
//

#include "Grayscale.h"
#include "opencv2/imgcodecs.hpp"
#include <iostream>

using namespace cv;

// todo: testar isto para YUV, RGBA, etc etc
Mat Grayscale::apply(Mat frame) {
    Mat channel[3];
    split(frame, channel);

    // criar uma mat com zeros, apenas 1 channel (de unsigned chars) para representar a imagem em grayscale
    Mat return_frame = Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1);

    // escrever na matrix return_frame com base na transformação
    // RGB -> Y' (referencia: https://en.wikipedia.org/wiki/Y%E2%80%B2UV)
    double weight_r = 0.299, weight_b = 0.114, weight_g = 1 - weight_r - weight_b;
    uchar curr_r, curr_g, curr_b;
    for(int i = 0; i < frame.rows; i++) {
        for (int j = 0; j < frame.cols; j++) {
            curr_r = channel[0].at<uchar>(i, j);
            curr_g = channel[1].at<uchar>(i, j);
            curr_b = channel[2].at<uchar>(i, j);
            return_frame.at<uchar>(i, j) = weight_r * curr_r + weight_g * curr_g + weight_b * curr_b;
        }
    }

    std::cout << "finished reading image" << std::endl;
    return return_frame;
}
