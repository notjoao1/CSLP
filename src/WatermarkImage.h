//
// Created by joao on 28/09/2023.
//

#ifndef GTD_VC_WATERMARKIMAGE_H
#define GTD_VC_WATERMARKIMAGE_H

#include "Effect.h"
#include <string>

using namespace std;

class WatermarkImage : public Effect {
private:
    Mat watermark;
public:
    WatermarkImage(Mat watermark);
    Mat apply(cv::Mat frame) override;
};


#endif //GTD_VC_WATERMARKIMAGE_H
