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
        src/Encoder.cpp
        src/Y4MWriter.cpp
        src/Encoding/GolombCode.cpp
        #tests/Deliverable4Tests/EncodingVideo.cpp
        #tests/Deliverable4Tests/DecodingVideo.cpp
        #tests/Deliverable5Tests/BlockEncodeVideo.cpp
        #tests/Deliverable5Tests/BlockDecodeVideo.cpp
        src/BlockDecoding.cpp
        src/BlockEncoding.cpp
        src/Y4MReader.cpp
        src/Y4MReader.h
        #tests/TestWrite.cpp
        #tests/testgolomb.cpp
        #tests/Y4MParserTests/Y4MParserTest.cpp
        CLI.cpp
        #tests/Deliverable5Tests/BlockEncodeDecodeFlow.cpp
        #tests/Deliverable4Tests/EncodeDecodeFlow.cpp
)

target_link_libraries(GTD-VC ${OpenCV_LIBS})