//
// Created by JPe_D on 11/25/2023.
//

#ifndef GTD_VC_Y4MWRITER_H
#define GTD_VC_Y4MWRITER_H

#include <string>
#include "opencv2/opencv.hpp"

using namespace std;

class Y4MWriter {
private:
    std::ofstream outFile;
public:
    explicit Y4MWriter(const string& out_fname);

    void writeHeader(int width, int height, int fps);

    void writeFrame(const cv::Mat* frame);

    void closeFile();
};


#endif //GTD_VC_Y4MWRITER_H
