//
// Created by Kikom on 17/10/2023.
//

#ifndef GTD_VC_THRESHOLD_H
#define GTD_VC_THRESHOLD_H


#include "Effect.h"

class Threshold: public Effect{
private:
    unsigned char threshold;
    bool inverted;
public:
    Threshold(unsigned char threshold,bool inverted);
    Mat apply(cv::Mat frame) override;
};


#endif //GTD_VC_THRESHOLD_H
