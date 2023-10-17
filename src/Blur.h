//
// Created by JPe_D on 10/17/2023.
//

#ifndef GTD_VC_BLUR_H
#define GTD_VC_BLUR_H

#include "Filter.h"


class Blur : public Effect {
private:
    Filter f;
    static Mat createBlurKernel();

public:
    Blur();
    Frame apply(Frame frame) override;
};


#endif //GTD_VC_BLUR_H
