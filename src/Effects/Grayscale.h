//
// Created by joao on 03/10/2023.
//

#ifndef GTD_VC_GRAYSCALE_H
#define GTD_VC_GRAYSCALE_H


#include "Effect.h"
#include "opencv2/imgcodecs.hpp"

using namespace cv;

/**
 * @class Grayscale
 * @brief Class used to apply a grayscale effect to an image
 */
class Grayscale : public Effect {
public:
    /**
      * @brief Change frame's colorspace to Grayscale. Only works for multi-channel frames BGR frames.
      * @param frame The input frame in the effect will be applied.
      */
    void apply(Frame* frame) override;
};


#endif //GTD_VC_GRAYSCALE_H
