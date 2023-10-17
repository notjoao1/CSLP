//
// Created by JPe_D on 10/17/2023.
//

#ifndef GTD_VC_GAUSSIANBLUR_H
#define GTD_VC_GAUSSIANBLUR_H

#include "Filter.h"

/**
 * @class GaussianBlur
 * @brief Class that wraps around filter to apply a specific filter kernel that produces a Gaussian Blur on a frame.
 */
class GaussianBlur : public Effect {
private:

    Filter f;
    /**
      * @brief Creates the filter kernel needed to apply a Gaussian Blur. Uses the OpenCV function
      * getGaussianKernel().
      * @return Odd sized filter kernel.
      */
    static Mat createBlurKernel();

public:
    /**
      * @brief Constructor for the GaussianBlur class. Also creates an instance of Filter with a specific
      * kernel that is created by GaussianBlur::createBlurKernel()
      */
    GaussianBlur();
    /**
      * @brief Applies blur filter kernel to image.
      * @param frame The input frame in which the gaussian blur is applied.
      * @return New frame after applying gaussian blur to input frame.
      */
    Frame apply(Frame frame) override;
};


#endif //GTD_VC_GAUSSIANBLUR_H
