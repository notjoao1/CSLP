//
// Created by Kikom on 27/09/2023.
//

#ifndef GTD_VC_VIDEOMANIPULATOR_H
#define GTD_VC_VIDEOMANIPULATOR_H

#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


/**
 * @class VideoManipulator
 * @brief Class used to play video files.
 */
class VideoManipulator {
private:
    /**< Path for source video. */
    string source;
public:
    /**
      * @brief Read video from video file.
      * @param filename Path to the source video.
      */
    bool fromFile(string filename);

    /**
      * @brief Play video using OpenCV VideoCapture class. Will play with original framerate.
      */
    void play();
};


#endif //GTD_VC_VIDEOMANIPULATOR_H
