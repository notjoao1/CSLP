//
// Created by joao on 28/09/2023.
//

#ifndef GTD_VC_WATERMARKIMAGE_H
#define GTD_VC_WATERMARKIMAGE_H

#include "Effect.h"
#include <string>

using namespace std;

/**
 * @class WatermarkImage
 * @brief Class used to apply a watermark image onto another frame.
 */
class WatermarkImage : public Effect {
private:
    Mat watermark; /**< Watermark image to be applied onto a frame. */
public:
    /**
      * @brief Constructor for WatermarkImage class.
      * @param watermark Matrix representing the watermark image to be applied.
      */
    WatermarkImage(Mat watermark);

    /**
      * @brief Apply watermark image onto input 'frame'.
      * By default, will apply watermark in top corner with 20% size of 'frame'.
      * @param frame Frame in which the watermark image will be applied.
      */
    void apply(Frame* frame) override;
};


#endif //GTD_VC_WATERMARKIMAGE_H
