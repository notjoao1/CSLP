//
// Created by JPe_D on 12/21/2023.
//

#include <iostream>
#include <sstream>
#include "Y4MReader.h"
#include <filesystem>


Y4MReader::Y4MReader(const string &input_file) {
    char buffer[65536]; // bigger buffer for less writes/syscalls
    this->input_fd = ifstream(input_file, std::ios::binary);
    input_fd.rdbuf()->pubsetbuf(buffer, 65536);

    if (!input_fd.is_open()) {
        cerr << "Error opening file: " << input_file << endl;
        return;
    }
    parseHeaders(input_file);
}

Y4MReader::~Y4MReader() {
    input_fd.close();
}

void Y4MReader::parseHeaders(const string& input_file) {
    string line;
    getline(input_fd, line);
    vector<string> parts = split_str(line, ' ');

    // header always starts with YUV4MPEG2
    if (parts[0] != "YUV4MPEG2")  {
        throw runtime_error("Y4M headers invalid.");
    }
    // example: W1280 H720
    frame_width = stoi(parts[1].substr(1, 5));
    frame_height = stoi(parts[2].substr(1, 5));

    // number of frames based on file size and header sizes:
    //      TOTAL_FILE_SIZE = initial_header_size + ( FRAME_header_size * num_frames ) + ( W * H * 3 * num_frames )
    //      num_frames = TOTAL_FILE_SIZE / (W * H * 3 + FRAME_header_size)
    // FRAME_header_size is always 6 -> FRAME\n
    number_of_frames = int(filesystem::file_size(input_file) / (frame_width * frame_height * 3 + 6));

    // fps data formatted as such: F<FPS_NUMERATOR>:<FPS_DENOMINATOR>, ex: F50:1 for 50fps
    vector<string> fps_data = split_str(parts[3].substr(1, 10), ':');
    fps_num = stoi(fps_data[0]);
    fps_denom = stoi(fps_data[1]);
}


bool Y4MReader::nextFrame(cv::Mat &f) {
    // read the FRAME header indicator
    std::string frameLine;
    std::getline(input_fd, frameLine);

    if (input_fd.eof())
        return false;

    cv::Mat y = cv::Mat::zeros(frame_height, frame_width, CV_8UC1);
    cv::Mat u = cv::Mat::zeros(frame_height, frame_width, CV_8UC1);
    cv::Mat v = cv::Mat::zeros(frame_height, frame_width, CV_8UC1);

    // read Y, U, V planes in that order
    input_fd.read(reinterpret_cast<char*>(y.data), frame_width * frame_height);
    input_fd.read(reinterpret_cast<char*>(u.data), frame_width * frame_height);
    input_fd.read(reinterpret_cast<char*>(v.data), frame_width * frame_height);

    std::vector<cv::Mat> channels = {y, u, v};
    merge(channels, f);
    return true;
}


// split string by delimiter
vector<string> Y4MReader::split_str(const string &str, char delim) {
    vector<string> split_str;
    stringstream ss(str);
    string curr_str;

    while (getline(ss, curr_str, delim))
        split_str.push_back(curr_str);

    return split_str;
}

int Y4MReader::get_frame_height() {
    return frame_height;
}

int Y4MReader::get_frame_width() {
    return frame_width;
}

int Y4MReader::get_fps_numerator() {
    return fps_num;
}

int Y4MReader::get_fps_denominator() {
    return fps_denom;
}

int Y4MReader::get_number_of_frames() {
    return number_of_frames;
}




