cmake_minimum_required(VERSION 3.16)
project(GTD-VC)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(GTD-VC src/Representation/ImageManipulator.cpp
        src/Representation/VideoManipulator.cpp
        src/BitStream/BitStreamWrite.cpp
        src/BitStream/BitStreamRead.cpp
        src/BitStream/BitStream.cpp
        src/Encoder.cpp
        src/Encoder.h
        src/Encoding/GolombCode.cpp
        tests/Deliverable4Tests/EncodingVideo.cpp
)

target_link_libraries(GTD-VC ${OpenCV_LIBS})