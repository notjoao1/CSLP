//
// Created by tiago on 26-09-2023.
//

#include "ImageManipulator.h"

bool ImageManipulator::ReadImage(const string file_name) {
    this->pixel_matrix = imread(file_name, IMREAD_COLOR);
    if(this->pixel_matrix.empty())
    {
        std::cout << "Could not read the image: " << file_name << std::endl;
        return false;
    }
    return true;
}

bool ImageManipulator::WriteImage(string file_name) {
    return imwrite(file_name, this->pixel_matrix);
}
