#ifndef GTD_VC_Y4MWRITER_H
#define GTD_VC_Y4MWRITER_H

#include <string>
#include <fstream>
#include "opencv2/opencv.hpp"

using namespace std;

/**
 * @class Y4MWriter
 * @brief Class for writing video in to Y4M files.
 */
class Y4MWriter {
private:
    std::ofstream outFile; ///< Output file stream for writing Y4M frames.

public:
    /**
     * @brief Constructor for Y4MWriter.
     * @param out_fname Output file name for writing frames into.
     */
    explicit Y4MWriter(const string& out_fname);

    /**
     * @brief Write the Y4M file header with video properties.
     * @param width Width of the video frames.
     * @param height Height of the video frames.
     * @param fps Frames per second of the video.
     */
    void writeHeader(int width, int height, int fps);

    /**
     * @brief Write a single video frame to the Y4M file.
     * @param frame Pointer to the video frame (cv::Mat).
     */
    void writeFrame(const cv::Mat* frame);

    /**
     * @brief Close the output file stream.
     */
    void closeFile();
};

#endif // GTD_VC_Y4MWRITER_H