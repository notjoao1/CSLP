//
// Created by JPe_D on 9/27/2023.
//

#ifndef GTD_VC_EFFECT_H
#define GTD_VC_EFFECT_H

#include "opencv2/opencv.hpp"
#include "../Storage/Frame.h"

using namespace cv;

/**
 * @class Effect
 * @brief Abstract class used to define an interface for effects to apply to an image.
 */
class Effect {
public:
    /**
      * @brief Abstract method to be overwritten by children classes to
      * apply effects to images.
      * @param frame The input frame in which the effect will be applied.
      */
    virtual void apply(Frame* frame) = 0;
};


#endif //GTD_VC_EFFECT_H
