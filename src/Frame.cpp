//
// Created by tiago on 13-10-2023.
//

#include "Frame.h"

#include <utility>

void Frame::applyEffects() {
    for(Effect* effect:this->effects){
        this->channels=effect->apply(this->channels.toMat());
    }
}

void Frame::addEffect(Effect* effect) {
    this->effects.push_back(effect);

}

void Frame::convertColorSpace(Color dest) {
    //WARNING: Check is dest is valid.
    this->channels=ColorSpace::convert(this->channels,this->channels.Colorspace,dest);
}

Mat Frame::getFrame() {
    return this->channels.toMat();
}

void Frame::fromMat(Mat& mat) {
    vector<Mat> cha;
    split(mat,cha);
    this->channels.value0=cha[0];
    this->channels.value1=cha[1];
    this->channels.value2=cha[2];

}

Channels Frame::getChannels() {
    return this->channels;
}

void Frame::setColorSpace(Color color) {
    this->channels.Colorspace=color;
}
