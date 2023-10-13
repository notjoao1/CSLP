//
// Created by tiago on 26-09-2023.
//

#ifndef GTD_VC_IMAGEMANIPULATOR_H
#define GTD_VC_IMAGEMANIPULATOR_H

#include "opencv2/opencv.hpp"
#include <string>

using namespace std;
using namespace cv;


class ImageManipulator {
private:
public:
    Mat ReadImage(string file_name);
    bool WriteImage(string file_name, Mat image);
};


#endif //GTD_VC_IMAGEMANIPULATOR_H
