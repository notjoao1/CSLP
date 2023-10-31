cmake_minimum_required(VERSION 3.16)
project(GTD-VC)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(GTD-VC src/main.cpp
        src/ImageManipulator.cpp
        src/VideoManipulator.cpp
        src/Storage/Channels.cpp
        src/Effects/Effect.h
        src/Storage/Frame.cpp
        src/Color/ColorSpace.cpp
        src/Effects/WatermarkImage.cpp
        src/Effects/WatermarkText.cpp
        src/Effects/Grayscale.cpp
        src/Effects/Filter.cpp
        src/BitStream/BitStreamWrite.cpp
        src/BitStream/BitStreamRead.cpp
        src/BitStream/BitStream.cpp
        src/Effects/Histogram.cpp
        src/Color/Colors.h
        src/Effects/Histogram.cpp
        src/Effects/Threshold.cpp
        src/Effects/Blur.cpp
        src/Effects/BlurGaussian.cpp
)

target_link_libraries(GTD-VC ${OpenCV_LIBS})