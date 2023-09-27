//
// Created by Kikom on 27/09/2023.
//

#ifndef GTD_VC_VIDEOMANIPULATOR_H
#define GTD_VC_VIDEOMANIPULATOR_H

#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class VideoManipulator {
private:
    string source;
public:
    bool fromFile(string filename);
    void play();
};


#endif //GTD_VC_VIDEOMANIPULATOR_H
