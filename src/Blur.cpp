//
// Created by JPe_D on 10/17/2023.
//

#include "Blur.h"

Blur::Blur() : f(createBlurKernel()) {}

Mat Blur::createBlurKernel() {
    Mat kernel = Mat::ones(3, 3, CV_32F);
    kernel /= sum(kernel);
    return kernel;
}

Frame Blur::apply(Frame frame) {
    return f.apply(frame);
}

