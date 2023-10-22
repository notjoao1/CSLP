//
// Created by tiago on 13-10-2023.
//

#ifndef GTD_VC_FRAME_H
#define GTD_VC_FRAME_H

#include "opencv2/opencv.hpp"
#include "Channels.h"
#include "ColorSpace.h"
#include <string>


using namespace std;
using namespace cv;

/**
 * @class Frame
 * @brief A class for storing and allowing manipulation of Image Frames.
 */
class Effect;
class Frame {
private:

    Channels channels;
    vector<Effect*>effects;
public:
    /**
     * @brief Adds effect to Frame's effect list.
     * @param effect Effect to be added.
     */
    void addEffect(Effect* effect);
    /**
     * @brief Applies to Frame all effects in Frame's effect list.
     */
    void applyEffects();
    /**
     * @brief Returns Frame Channels.
     * returns Channels of Frame.
     */
    Channels getChannels();
    /**
     * @brief Sets the Color Space of Frame.
     * @param color Color Space to be set.
     */
    void setColorSpace(Color color);
    /**
     * @brief Converts Color Space of Frame.
     * @param dest Final intended Color Space.
     */
    void convertColorSpace(Color dest);
    /**
     * @brief Get frame in Matrix format.
     * @returns Frame in OpenCV's Matrix format.
     */
    Mat getFrame();
    /**
     * @brief Sets Frame Image from Matrix.
     * @param mat Source matrix to be set to Frame.
     */
    void fromMat(Mat mat);
    /**
     * @brief Creates Frame object from Channels object.
     * @param c Channels object to be used as Frame base.
     */
    Frame(Channels c);
};



#endif //GTD_VC_FRAME_H
