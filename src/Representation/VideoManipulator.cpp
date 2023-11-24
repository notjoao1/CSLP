//
// Created by Kikom on 27/09/2023.
//

#include <fstream>
#include "VideoManipulator.h"

void VideoManipulator::play(){
    Mat frame;

    // get frame rate of video
    double fps = cap.get(CAP_PROP_FPS);

    //--- GRAB AND WRITE LOOP
    cout << "Start grabbing" << endl
         << "Press any key to terminate" << endl;
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", frame);
        if (waitKey((int) 1000/fps) >= 0)
            break;
    }
}

VideoManipulator::VideoManipulator(const string& filename) : cap(filename),filename(filename){
}
void VideoManipulator::writeHeader(int width, int height, int fps) {
    // Open the Y4M file for writing
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open the file for writing." << std::endl;
        return;
    }
    // Write Y4M header
    outFile << "YUV4MPEG2 W" << width << " H" << height << " F" << fps << ":1 Ip A1:1 C420" << std::endl;

    // Close the file
    outFile.close();
}
void VideoManipulator::writeFrame(const Mat* frame) {


    int width = frame->cols;
    int height = frame->rows;

    // Open the Y4M file for writing
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open the file for writing." << std::endl;
        return;
    }
    // Write Y4M frame
    for (int i = 0; i < height; ++i) {
        outFile.write(reinterpret_cast<const char*>(frame->ptr(i)), width * 3); // YUV444 has 3 channels
    }

    // Write frame separator
    outFile << "FRAME" << std::endl;

    // Close the file
    outFile.close();
}

Mat VideoManipulator::getNextFrame() {
    Mat frame;
    cap >> frame;
    return frame;
}

int VideoManipulator::getFPS(){
    return cap.get(CAP_PROP_FPS);
}
