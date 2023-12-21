//
// Created by JPe_D on 12/21/2023.
//

#ifndef GTD_VC_Y4MREADER_H
#define GTD_VC_Y4MREADER_H
#include <string>
#include <vector>
#include <fstream>
#include "opencv2/opencv.hpp"

using namespace std;

class Y4MReader {
private:
    ifstream input_fd;
    int frame_height;
    int frame_width;
    int fps_num, fps_denum;
    static vector<string> split_str(const string& str, char delim);
public:
    explicit Y4MReader(const string& input_file);
    ~Y4MReader();
    void parseHeaders();
    bool nextFrame(cv::Mat& f);
};


#endif //GTD_VC_Y4MREADER_H
