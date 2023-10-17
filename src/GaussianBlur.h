//
// Created by JPe_D on 10/17/2023.
//

#ifndef GTD_VC_GAUSSIANBLUR_H
#define GTD_VC_GAUSSIANBLUR_H

#include "Filter.h"

class GaussianBlur : public Effect {
private:
    Filter f;
    static Mat createBlurKernel();

public:
    GaussianBlur();
    Frame apply(Frame frame) override;
};


#endif //GTD_VC_GAUSSIANBLUR_H
