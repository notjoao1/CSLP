//
// Created by JPe_D on 10/17/2023.
//

#ifndef GTD_VC_BLUR_H
#define GTD_VC_BLUR_H

#include "Filter.h"

/**
 * @class Blur
 * @brief Class that wraps around filter to apply a specific filter kernel that produces a Blur on a frame.
 */
class Blur : public Effect {
private:
    Filter f;
    /**
      * @brief Creates the filter kernel for a blur filter. Kernel will be normalized and an odd sized matrix.
      * @return Filter kernel.
      */
    static Mat createBlurKernel();

public:
    /**
      * @brief Constructor for the Blur class. Also creates an instance of Filter with a specific kernel
      * that is created by Blur::createBlurKernel()
      */
    Blur();
    /**
      * @brief Applies blur filter kernel to image.
      * @param frame The input frame in which the blur is applied.
      */
    void apply(Frame* frame) override;
};


#endif //GTD_VC_BLUR_H
