//
// Created by joao on 03/10/2023.
//

#ifndef GTD_VC_GRAYSCALE_H
#define GTD_VC_GRAYSCALE_H


#include "Effect.h"
#include "opencv2/imgcodecs.hpp"

using namespace cv;

class Grayscale : Effect {
public:
    Mat apply(Mat frame) override;
};


#endif //GTD_VC_GRAYSCALE_H
