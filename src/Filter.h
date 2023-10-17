//
// Created by JPe_D on 10/4/2023.
//

#ifndef GTD_VC_FILTER_H
#define GTD_VC_FILTER_H


#include "Effect.h"


/**
 * @class Filter
 * @brief Generic filter class that applies given filter kernel as a convolution to input matrix.
 */
 class Filter : public  Effect {
private:
    //! The filter kernel used for convolution. Matrix should be odd sized.
    Mat kernel;
     /**
      * @brief Calculates convoluted matrix based on the kernel given to the Filter class on instantiation.
      * @param input_frame The input frame to be convoluted.
      * @return New frame after applying convolution to input_frame.
      */
    Mat convolute(Mat input_frame);
     /**
      * @brief Applies padding to the input frame in order to perform convolution.
      * It is applied on the left, top, right and bottom parts of frame.
      * @param frame The input frame to be padded.
      * @param padding_size The height and width of padding to be applied.
      * @return The padded frame.
      */
    Mat applyPadding(Mat frame, int padding_size);
public:
     /**
      * @brief Constructor for the Filter class.
      * @param kernel The filter kernel that will be applied for convolution.
      */
    explicit Filter(Mat kernel);
     /**
      * @brief Applies convolution to the input frame using the provided filter kernel on class instantiation.
      * @param frame The input frame to which the convolution is applied.
      * @return The resulting frame after convolution.
      */
    Frame apply(Frame frame) override;
};


#endif //GTD_VC_FILTER_H
