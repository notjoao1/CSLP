//
// Created by JPe_D on 10/4/2023.
//

#ifndef GTD_VC_FILTER_H
#define GTD_VC_FILTER_H


#include "Effect.h"


//! \brief Class that applies a filter based on a Kernel matrix.
class Filter : public  Effect {
private:
    //!
    Mat kernel;
    Mat convolute(Mat input_frame);
    Mat applyPadding(Mat frame, int padding_size);
public:
    //! Class constructor
    //! @param mat_size
    explicit Filter(Mat kernel);
    Frame apply(Frame frame) override;
};


#endif //GTD_VC_FILTER_H
