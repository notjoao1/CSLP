//
// Created by tiago on 17-10-2023.
//
#include "Channels.h"
#include "ColorSpace.h"

Mat Channels::toMat(){
    Mat res=Mat::zeros(value0.rows,value0.cols,uchar());
    if (this->Colorspace==RGB or this->Colorspace==YUV)
        merge(vector<Mat>{value0,value1,value2},res);
    else{
        Channels temp=ColorSpace::extend(*this,this->Colorspace);
        merge(vector<Mat>{ temp.value0,temp.value1,temp.value2},res);
    }
    return res;
}

void Channels::setColorspace(Color color) {
    Colorspace=color;
};
