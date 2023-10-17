//
// Created by JPe_D on 10/17/2023.
//

#include "GaussianBlur.h"

Mat GaussianBlur::createBlurKernel() {
    return cv::getGaussianKernel(3, 1, CV_32F);
}

GaussianBlur::GaussianBlur() : f(createBlurKernel()) {}

Frame GaussianBlur::apply(Frame frame) {
    return f.apply(frame);
}
