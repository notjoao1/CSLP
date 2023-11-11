//
// Created by JPe_D on 9/27/2023.
//

#ifndef GTD_VC_WATERMARKTEXT_H
#define GTD_VC_WATERMARKTEXT_H


#include "Effect.h"
#include <string>

using namespace std;

/**< Available colors for watermark text */
enum TextColor {
    BLACK = 0,
    WHITE = 255
};

/**
 * @class WatermarkText
 * @brief Class used to apply watermark text onto an image.
 */
class WatermarkText : public Effect {
private:
    /**< Watermark image to be applied onto a frame. */
    string text;

    /**< Color of watermark text. Defined in enum inside of WatermarkText.h */
    TextColor color;
public:

    /**
      * @brief Constructor for WatermarkText class.
      * @param text String watermark to be applied.
      * @param color Color for watermark text.

      */
    WatermarkText(const string& text, TextColor color);

    /**
      * @brief Apply watermark text onto input 'frame'.
      * By default, will apply watermark in bottom corner.
      * @param frame Frame in which the watermark image will be applied.
      */
    void apply(Frame* frame) override;
};


#endif //GTD_VC_WATERMARKTEXT_H
