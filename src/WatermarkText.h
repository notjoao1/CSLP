//
// Created by JPe_D on 9/27/2023.
//

#ifndef GTD_VC_WATERMARKTEXT_H
#define GTD_VC_WATERMARKTEXT_H


#include "Effect.h"
#include <string>

using namespace std;

class WatermarkText : Effect {
private:
    string text;
public:
    WatermarkText(string text);
    Mat apply(cv::Mat frame) override;
};


#endif //GTD_VC_WATERMARKTEXT_H
