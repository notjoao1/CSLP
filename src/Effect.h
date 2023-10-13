//
// Created by JPe_D on 9/27/2023.
//

#ifndef GTD_VC_EFFECT_H
#define GTD_VC_EFFECT_H

#include "opencv2/opencv.hpp"

using namespace cv;

// abstract class for effects to apply to each frame
class Effect {
public:
    virtual Mat apply(Mat frame) = 0;

};


#endif //GTD_VC_EFFECT_H
