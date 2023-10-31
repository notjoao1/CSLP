//
// Created by Kikom on 27/09/2023.
//

#include "VideoManipulator.h"

bool VideoManipulator::fromFile(string filename){

    VideoCapture cap;
    int apiID = cv::CAP_ANY;
    cap.open(filename, apiID);
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open file\n";
    }

    this->source = filename;
}

void VideoManipulator::play(){
    Mat frame;
    VideoCapture cap;

    int apiID = cv::CAP_ANY;

    if(this->source.empty()){
        cerr << "Please open a file\n";
        return;
    }
    cap.open(this->source, apiID);

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
