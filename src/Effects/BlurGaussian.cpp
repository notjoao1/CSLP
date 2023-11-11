//
// Created by JPe_D on 10/17/2023.
//

#include "BlurGaussian.h"

Mat BlurGaussian::createBlurKernel() {
    Mat kernel = cv::getGaussianKernel(3, 1, CV_32F);
    kernel = kernel * kernel.t();
    kernel /= sum(kernel);
    return kernel;
}

BlurGaussian::BlurGaussian() : f(createBlurKernel()) {}

void BlurGaussian::apply(Frame* frame) {
    f.apply(frame);
}
