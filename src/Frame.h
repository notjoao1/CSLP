//
// Created by tiago on 13-10-2023.
//

#ifndef GTD_VC_FRAME_H
#define GTD_VC_FRAME_H

#include "opencv2/opencv.hpp"
#include "Effect.h"
#include "Channels.h"
#include <string>


using namespace std;
using namespace cv;

class Frame {
private:
    Channels channels;
    vector<Effect*>effects;
public:
    void addEffect(Effect* effect);
    void applyEffects();
    Channels getChannels();
    void setColorSpace(Color color);
    void convertColorSpace(Color dest);
    Mat getFrame();
    void fromMat(Mat& mat);
};



#endif //GTD_VC_FRAME_H
