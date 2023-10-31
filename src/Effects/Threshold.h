//
// Created by Kikom on 17/10/2023.
//

#ifndef GTD_VC_THRESHOLD_H
#define GTD_VC_THRESHOLD_H


#include "Effect.h"

/**
 * @class Threshold
 * @brief Class used apply threshold based segmentation on an image.
 */
class Threshold: public Effect{
private:
    unsigned char threshold; /**< Threshold for pixel values. */

    /**< Boolean variable to define the way 'threshold' will be applied in the algorithm.
     * If false, pixel values lower than 'threshold' will be interpreted as black (0) and
     * values higher will be interpreted as white (255). If true, the opposite will occur. */
    bool inverted;
public:

    /**
      * @brief Constructor for Threshold class.
      * @param threshold Threshold for pixel values
      * @param inverted Invert the pixel output values during application of algorithm
      */
    Threshold(unsigned char threshold,bool inverted);

    /**
      * @brief Apply image segmentation algorithm based on threshold with given values.
      */
    void apply(Frame* frame) override;
};


#endif //GTD_VC_THRESHOLD_H
