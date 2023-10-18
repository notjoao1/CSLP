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

void Blur::apply(Frame* frame) {
    f.apply(frame);
}

