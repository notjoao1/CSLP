//
// Created by JPe_D on 10/4/2023.
//

#include "Filter.h"

Mat Filter::apply(cv::Mat frame) {
    Mat output = convolute(frame);
    return output;
}

Filter::Filter(int mat_size) {
    kernel = Mat::ones(Size(mat_size, mat_size), CV_32F);
    // normalize kernel matrix
    kernel /= (sum(kernel)[0]);
}


Mat Filter::convolute(Mat frame) {
    int padding_size = (kernel.cols - 1)/2;
    Mat frame_with_padding = applyPadding(frame, padding_size);

    // create channels in which we will save the values resulting from the convolution of each channel
    int original_channels = frame.channels();
    Mat channels[original_channels];
    for (int i = 0; i < original_channels; i++)
        channels[i] = Mat::zeros(Size(frame.cols, frame.rows), CV_32F);

    Rect curr_roi;
    Mat sub_matrix, mult_result;
    Mat sub_channels[original_channels];
    float sum;
    for (int row = 0; row < frame_with_padding.rows - kernel.rows + 1; row++) {
        for (int col = 0; col < frame_with_padding.cols - kernel.cols + 1; col++) {
            curr_roi = Rect(col, row, kernel.cols, kernel.rows);
            sub_matrix = frame_with_padding(curr_roi);
            split(sub_matrix, sub_channels);

            for (int curr_ch = 0; curr_ch < sub_matrix.channels(); curr_ch++)
            {
                sub_channels[curr_ch].convertTo(sub_channels[curr_ch], CV_32F, 1.0/255.0); // guarantee both matrices have same type
                sum = 0;
                 for (int i = 0; i < kernel.rows; i++)
                         for (int j = 0; j < kernel.cols; j++)
                             sum += sub_channels[curr_ch].at<float>(i, j) *
                                    kernel.at<float>(kernel.rows - i - 1, kernel.cols - j - 1);  //  flipped kernel

                 channels[curr_ch].at<float>(row, col) = sum;

            }

        }
    }
    Mat convoluted_frame;
    merge(channels, original_channels, convoluted_frame);

    // reconvert to uchar with 255x scaling (since floats were represented as 0-1)
    // todo: all these conversions probably lose quality, maybe fix it
    convoluted_frame.convertTo(convoluted_frame, CV_8UC(original_channels), 255);

    return convoluted_frame;
}

Mat Filter::applyPadding(Mat frame, int padding_size) {
    // apply padding to input frame for convolution (extra pixels will be the color black)
    Mat frame_with_padding;

    std::cout << "padding_size: " << padding_size << std::endl;

    // add padding size * 2 to the width and height (left, right, top and bottom padding)
    frame_with_padding = Mat::zeros(Size(frame.cols + padding_size * 2, frame.rows + padding_size * 2), CV_8UC(frame.channels()));

    // region of interest to apply original frame into the "frame_with_padding" mat,
    // leaving padded pixels as 0
    Rect roi(padding_size, padding_size, frame.cols, frame.rows);

    frame.copyTo(frame_with_padding(roi));

    return frame_with_padding;
}
