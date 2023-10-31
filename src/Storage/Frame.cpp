//
// Created by tiago on 13-10-2023.
//

#include "Frame.h"

#include <utility>
#include "../Effects/Effect.h"
void Frame::applyEffects() {
    for(Effect* effect:this->effects){
        effect->apply(this);
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

void Frame::fromMat(Mat mat) {
    vector<Mat> cha;
    split(mat,cha);
    // if mat is grayscale, give empty mat to value1 and value2
    if (cha.size() == 1) {
        this->channels.value0 = cha[0];
        this->channels.value1 = Mat::zeros(1, 1, CV_8UC1);
        this->channels.value2 = Mat::zeros(1, 1, CV_8UC1);
        return;
    }
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

Frame::Frame(Channels c) : channels(c){
    this->channels = std::move(c);
}
