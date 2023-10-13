//
// Created by tiago on 13-10-2023.
//

#include "Frame.h"

#include <utility>
#include "ColorSpace.h"

void Frame::applyEffects() {
    for(Effect* effect:this->effects){
        Mat frame;
        merge(this->channels,frame);
        this->channels=effect->apply(frame);
    }
}

void Frame::addEffect(Effect* effect) {
    this->effects.push_back(effect);

}

void Frame::convertColorSpace(String dest) {
    //WARNING: Check is dest is valid.
    this->ColorSpace = std::move(dest);
}

Mat Frame::getFrame() {
    Mat frame;
    merge(this->channels,frame);
    return frame;
}
