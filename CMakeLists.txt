cmake_minimum_required(VERSION 3.16)
project(GTD-VC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -O3)

find_package(OpenCV REQUIRED)

add_executable(GTD-VC src/Representation/ImageManipulator.cpp
        src/Representation/VideoManipulator.cpp
        src/BitStream/BitStreamWrite.cpp
        src/BitStream/BitStreamRead.cpp
        src/BitStream/BitStream.cpp
        src/Decoder.cpp
        src/Decoder.h
        src/Encoder.cpp
        src/Encoder.h
        src/Encoding/GolombCode.cpp
        tests/Deliverable4Tests/EncodingVideo.cpp
        tests/Deliverable4Tests/DecodingVideo.cpp
        tests/Deliverable4Tests/BitStreamGolombPredictorTests.cpp
        src/BlockDecoding.cpp


)

target_link_libraries(GTD-VC ${OpenCV_LIBS})