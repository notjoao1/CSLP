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
    VideoCapture cap;
public:
    /**
      * @brief Constructor for VideoManipulator class.
      * @param filename Path to the source video.
      */
    explicit VideoManipulator(const string& filename);

    /**
      * @brief Play video using OpenCV VideoCapture class. Will play with original framerate.
      */
    void play();

    Mat getNextFrame();
    //TODO: add support to write video to file

};


#endif //GTD_VC_VIDEOMANIPULATOR_H
