//
// Created by tiago on 13-10-2023.
//

#ifndef GTD_VC_FRAME_H
#define GTD_VC_FRAME_H

#include "opencv2/opencv.hpp"
#include "Effect.h"
#include <string>

using namespace std;
using namespace cv;

class Frame {
private:
    vector<Mat>channels;
    vector<Effect*>effects;
    String ColorSpace;

public:
    void addEffect(Effect* effect);
    void applyEffects();
    void convertColorSpace(String dest);
    Mat getFrame();
};



#endif //GTD_VC_FRAME_H
