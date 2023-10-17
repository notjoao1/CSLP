//
// Created by tiago on 27-09-2023.
//

#ifndef GTD_VC_COLORSPACE_H
#define GTD_VC_COLORSPACE_H
#include "opencv2/opencv.hpp"
#include <string>
#include "Channels.h"
#include "Colors.h"

using namespace std;
using namespace cv;

class ColorSpace {
private:
    static Channels toYUV4_2_2(Channels image);
    static Channels toYUV4_2_0(Channels image);
    static Channels RGBtoYUV(Channels image);
    static Channels YUVtoRGB(Channels image);
public:
    static Channels extend(Channels frame, Color type);
    static Channels convert(Channels frame,Color src, Color dest);

};


#endif //GTD_VC_COLORSPACE_H
