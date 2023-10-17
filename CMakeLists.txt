cmake_minimum_required(VERSION 3.16)
project(GTD-VC)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(GTD-VC src/main.cpp
        src/ImageManipulator.cpp
        src/VideoManipulator.cpp
        src/WatermarkImage.cpp
        src/WatermarkText.cpp
        src/Grayscale.cpp
        src/Filter.cpp
        src/BitStreamWrite.cpp
        src/BitStreamRead.cpp
        src/BitStream.cpp
        src/ColorSpace.cpp
        src/Frame.cpp
        src/Histogram.cpp)

target_link_libraries(GTD-VC ${OpenCV_LIBS})