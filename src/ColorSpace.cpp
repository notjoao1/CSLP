//

#include "ColorSpace.h"

//
// Created by tiago on 27-09-2023.

Channels ColorSpace::YUV4_2_2(Channels channels){

    Mat U= Mat::zeros(channels.value1.rows, channels.value1.cols / 2 + channels.value1.cols % 2,uchar() );
    Mat V= Mat::zeros(channels.value2.rows, channels.value2.cols / 2 + channels.value2.cols % 2,uchar());

    //convert yuv 4:4:4 into 4:4:2
    for(int row=0;row<channels.value0.rows;row++){
        for(int col=0;col+1<channels.value0.cols;col=col+2){
            U.at<uchar>(row,col/2)=channels.value1.at<uchar>(row,col);
            V.at<uchar>(row,col/2)=channels.value2.at<uchar>(row,col);
        }
    }

    return {channels.value0,U,V};
}
Channels ColorSpace::YUV4_2_0(Channels channels){

    Mat U= Mat::zeros(channels.value1.rows/2+channels.value1.rows % 2, channels.value1.cols / 2 + channels.value1.cols % 2,uchar()  );
    Mat V= Mat::zeros(channels.value2.rows/2+channels.value1.rows % 2, channels.value2.cols / 2 + channels.value2.cols % 2,uchar());

    //convert yuv 4:4:4 into 4:2:0
    for(int row=0;row+1<channels.value0.rows;row=row+2){
        for(int col=0;col+1<channels.value0.cols;col=col+2){
            U.at<uchar>(row/2,col/2)=channels.value1.at<uchar>(row,col);
            V.at<uchar>(row/2,col/2)=channels.value2.at<uchar>(row,col);
        }
    }


    return {channels.value0,U,V};
}

Channels ColorSpace::RGBtoYUV(Channels channels) {
    Mat Y = Mat::zeros(channels.value0.rows, channels.value0.cols,uchar());
    Mat U = Mat::zeros(channels.value0.rows, channels.value0.cols,uchar());
    Mat V = Mat::zeros(channels.value0.rows, channels.value0.cols, uchar());


    for (int row = 0; row < channels.value0.rows; row++) {
        for (int col = 0; col < channels.value0.cols; col++) {
            Y.at<uchar>(row, col) = 0.299 * channels.value2.at<uchar>(row, col) + 0.587 * channels.value1.at<uchar>(row, col) + 0.114 * channels.value0.at<uchar>(row, col);
            U.at<uchar>(row, col) = 128+ 0.492 * (channels.value0.at<uchar>(row, col) - Y.at<uchar>(row, col));
            V.at<uchar>(row, col) = 128+ 0.877 * (channels.value2.at<uchar>(row, col) - Y.at<uchar>(row, col));
        }
    }
    return {Y, U, V};
}


Channels ColorSpace::YUVtoRGB(Channels channels) {
    Mat R = Mat::zeros(channels.value0.rows, channels.value0.cols, uchar());
    Mat G = Mat::zeros(channels.value0.rows, channels.value0.cols, uchar());
    Mat B = Mat::zeros(channels.value0.rows, channels.value0.cols, uchar());
    Mat RGB = Mat::zeros(channels.value0.rows, channels.value0.cols, uchar());

    for (int row = 0; row < channels.value0.rows; row++) {
        for (int col = 0; col < channels.value0.cols; col++) {
            R.at<uchar>(row, col) = channels.value0.at<uchar>(row, col) + 1.140 * channels.value2.at<uchar>(row, col);
            G.at<uchar>(row, col) = channels.value0.at<uchar>(row, col) - 0.395 * channels.value1.at<uchar>(row, col) - 0.581 * channels.value2.at<uchar>(row, col);
            B.at<uchar>(row, col) = channels.value0.at<uchar>(row, col) + 2.032 * channels.value1.at<uchar>(row, col);

        }
    }
    return {R, G, B};

}

Channels ColorSpace::extend(Channels channels,String type) {
    if (type=="YUV4_2_2"){
        //parse again to 4:4:4 with 4:2:2 resolution
        Mat fullV= Mat::zeros(channels.value0.rows, channels.value0.cols,uchar());
        Mat fullU= Mat::zeros(channels.value0.rows, channels.value0.cols,uchar());

        for(int row=0;row<channels.value1.rows-1;row++){
            for(int col=0;col<channels.value1.cols-1;col++){ //TODO check limit condition
                fullU.at<uchar>(row,2*col)=channels.value1.at<uchar>(row,col);
                fullU.at<uchar>(row,2*col+1)=channels.value1.at<uchar>(row,col);
                fullV.at<uchar>(row,2*col)=channels.value2.at<uchar>(row,col);
                fullV.at<uchar>(row,2*col+1)=channels.value2.at<uchar>(row,col);
            }
        }
        return {channels.value0,fullU,fullV};
    }
    else if(type=="YUV4_2_0"){
        //parse again to 4:4:4 with 4:2:0 resolution
        Mat fullV= Mat::zeros(channels.value0.rows, channels.value0.cols,uchar());
        Mat fullU= Mat::zeros(channels.value0.rows, channels.value0.cols,uchar());

        for(int row=0;row<channels.value1.rows-1;row++){
            for(int col=0;col<channels.value1.cols-1;col++){ //TODO check limit condition
                fullU.at<uchar>(2*row,2*col)=channels.value1.at<uchar>(row,col);
                fullU.at<uchar>(2*row,2*col+1)=channels.value1.at<uchar>(row,col);
                fullU.at<uchar>(2*row+1,2*col)=channels.value1.at<uchar>(row,col);
                fullU.at<uchar>(2*row+1,2*col+1)=channels.value1.at<uchar>(row,col);
                fullV.at<uchar>(2*row,2*col)=channels.value2.at<uchar>(row,col);
                fullV.at<uchar>(2*row,2*col+1)=channels.value2.at<uchar>(row,col);
                fullV.at<uchar>(2*row+1,2*col)=channels.value2.at<uchar>(row,col);
                fullV.at<uchar>(2*row+1,2*col+1)=channels.value2.at<uchar>(row,col);
            }
        }
        return  {channels.value0,fullU,fullV};
    }
    return channels;
}

Channels ColorSpace::convert(Channels frame, String src, String dest) {
    if(src=="RGB" and dest=="YUV")
        return RGBtoYUV(frame);
    else if(src=="RGB" and dest=="YUV4_2_2")
        return YUV4_2_2(RGBtoYUV(frame));
    else if(src=="RGB" and dest=="YUV4_2_0")
        return YUV4_2_0(RGBtoYUV(frame));
    else if(src=="YUV" and dest=="RGB")
        return YUVtoRGB(frame);
    else if(src=="YUV4_2_2" and dest=="RGB")
        return YUVtoRGB(extend(frame,"4_2_2"));
    else if(src=="YUV4_2_0" and dest=="RGB")
        return YUVtoRGB(extend(frame,"4_2_0"));
    return frame;
}



