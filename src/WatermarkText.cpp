//
// Created by JPe_D on 9/27/2023.
//

#include <iostream>
#include <string>
#include "WatermarkText.h"

using namespace std;

Mat WatermarkText::apply(cv::Mat frame) {
    // todo: custom coordinates, color (?), and fontScale (?)
    putText(frame, this->text,cv::Point(20, frame.rows - 30),cv::FONT_HERSHEY_DUPLEX,2,cv::Scalar(0,0,0),2,false);
    return frame;
}

WatermarkText::WatermarkText(string text) {
    this->text = text;
}
