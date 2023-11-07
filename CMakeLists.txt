cmake_minimum_required(VERSION 3.16)
project(GTD-VC)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(GTD-VC src/Representation/ImageManipulator.cpp
        src/Representation/VideoManipulator.cpp
        src/Storage/Channels.cpp
        src/Effects/Effect.h
        src/Storage/Frame.cpp
        src/Effects/WatermarkImage.cpp
        src/Effects/WatermarkText.cpp
        src/Effects/Grayscale.cpp
        src/Effects/Filter.cpp
        src/BitStream/BitStreamWrite.cpp
        src/BitStream/BitStreamRead.cpp
        src/BitStream/BitStream.cpp
        src/Effects/Histogram.cpp
        src/Effects/Histogram.cpp
        src/Effects/Threshold.cpp
        src/Effects/Blur.cpp
        src/Effects/BlurGaussian.cpp
        src/Codec.cpp
        src/Codec.h
        src/Encoder.cpp
        src/Encoder.h
)

target_link_libraries(GTD-VC ${OpenCV_LIBS})