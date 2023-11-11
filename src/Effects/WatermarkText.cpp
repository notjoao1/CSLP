//
// Created by JPe_D on 9/27/2023.
//

#include <iostream>
#include <string>
#include "WatermarkText.h"

using namespace std;

void WatermarkText::apply(Frame* frame) {
    Mat frameMat=frame->getChannels().toMat();
    cv::putText(frameMat, this->text,cv::Point(20, frameMat.rows - 30),cv::FONT_HERSHEY_DUPLEX,2,cv::Scalar(this->color,this->color,this->color),2,false);
    frame->fromMat(frameMat);
}



WatermarkText::WatermarkText(const string& text, TextColor color) {
    this->text = text;
    this->color = color;
}
