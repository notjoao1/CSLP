//
// Created by JPe_D on 10/4/2023.
//

#ifndef GTD_VC_FILTER_H
#define GTD_VC_FILTER_H


#include "Effect.h"

class Filter : Effect {
private:
    Mat kernel;
    Mat convolute(Mat input_frame);
    Mat applyPadding(Mat frame, int padding_size);
public:
    explicit Filter(int mat_size);
    Mat apply(cv::Mat frame) override;
};


#endif //GTD_VC_FILTER_H
