//
// Created by tiago on 27-09-2023.
//

#ifndef GTD_VC_COLORSPACE_H
#define GTD_VC_COLORSPACE_H
#include "opencv2/opencv.hpp"
#include <string>
#include "Channels.h"

using namespace std;
using namespace cv;

class ColorSpace {
private:
    static Channels YUV4_2_2(Channels image);
    static Channels YUV4_2_0(Channels image);
    static Channels RGBtoYUV(Channels image);
    static Channels YUVtoRGB(Channels image);
public:
    static Channels extend(Channels frame, String type);
    static Channels convert(Channels frame,String src, String dest);

};


#endif //GTD_VC_COLORSPACE_H
