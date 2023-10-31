//
// Created by tiago on 27-09-2023.
//

#ifndef GTD_VC_COLORSPACE_H
#define GTD_VC_COLORSPACE_H
#include "opencv2/opencv.hpp"
#include <string>
#include "../Storage/Channels.h"
#include "Colors.h"

using namespace std;
using namespace cv;
/**
 * @class ColorSpace
 * @brief Class that supports all Color Space operations inside a Channels Object.
 */
class ColorSpace {
private:
    /**
     * @brief Converts Channels Color Space to YUV 4:2:2.
     * @param image Image to be converted, stored in Channels structure.
     * @return Altered Channels Object.
     */
    static Channels toYUV4_2_2(Channels image);
    /**
     * @brief Converts Channels Color Space from YUV 4:4:4 to YUV 4:2:0.
     * @param image Image to be converted, stored in Channels structure.
     * @return Altered Channels Object.
     */
    static Channels toYUV4_2_0(Channels image);
    /**
     * @brief Converts Channels Color Space from RGB to YUV.
     * @param image Image to be converted, stored in Channels structure.
     * @return Altered Channels Object.
     */
    static Channels RGBtoYUV(Channels image);
    /**
     * @brief Converts Channels Color Space from YUV to RGB.
     * @param image Image to be converted, stored in Channels structure.
     * @return Altered Channels Object.
     */
    static Channels YUVtoRGB(Channels image);
public:
    /**
     * @brief Extends a sub-sampled object to full-definition.
     * @param frame frame to be extended, stored in Channels structure.
     * @param type Color Space of frame.
     * @return Altered Channels Object.
     */
    static Channels extend(Channels frame, Color type);
    /**
     * @brief Converts a Channels object from Color Space src to dest.
     * @param frame frame to be extended, stored in Channels structure.
     * @param src Original Color Space of frame.
     * @param dst Intended final Color Space of frame.
     * @return Altered Channels Object.
     */
    static Channels convert(Channels frame,Color src, Color dest);

};


#endif //GTD_VC_COLORSPACE_H
