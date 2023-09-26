//
// Created by joao on 26/09/2023.
//

#include <iostream>
#include "opencv2/opencv.hpp"
#include "ImageManipulator.h"

int main() {
    ImageManipulator i;
    i.ReadImage("C:\\Users\\leona\\CLionProjects\\GTD-VC\\resources\\Giga_Chad.jpg");
    i.WriteImage("resources/New_Giga_Chad.jpg");
    return 0;
}