//
// Created by tiago on 26-09-2023.
//

#ifndef GTD_VC_IMAGEMANIPULATOR_H
#define GTD_VC_IMAGEMANIPULATOR_H

#include "opencv2/opencv.hpp"
#include <string>

using namespace std;
using namespace cv;

/**
* @class BitStreamRead
* @brief A class for reading/writings images from/to a file.
*/
class ImageManipulator {
private:
public:
     /**
     * @brief Reads Image from file.
     * @param file_name String defining the path to the to be written file.
     * @returns Matrix read from file.
     */
    Mat ReadImage(string file_name);
     /**
     * @brief Writes Image to file.
     * @param image Image contained in a OpenCV Matrix object.
     * @param file_name String defining the path to the to be written file.
     * @returns True if write has been successful. False otherwise.
     */

    bool WriteImage(string file_name, Mat image);
};


#endif //GTD_VC_IMAGEMANIPULATOR_H
