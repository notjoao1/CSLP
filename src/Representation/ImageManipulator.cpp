//
// Created by tiago on 26-09-2023.
//

#include "ImageManipulator.h"

Mat ImageManipulator::ReadImage(const string file_name) {
    Mat image=imread(file_name, IMREAD_COLOR);
    if(image.empty())
    {
        std::cout << "Could not read the image: " << file_name << std::endl;
        return Mat();
    }
    return image;
}

bool ImageManipulator::WriteImage(string file_name, Mat image) {
    return imwrite(file_name, image);
}
