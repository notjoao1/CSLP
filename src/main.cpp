//
// Created by joao on 26/09/2023.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "ImageManipulator.h"
#include "VideoManipulator.h"

int main() {
    VideoManipulator vm;
    vm.fromFile("resources/");
    vm.play();
    return 0;
}