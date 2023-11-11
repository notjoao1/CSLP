//
// Created by joao on 28/09/2023.
//

#include "WatermarkImage.h"

using namespace cv;

WatermarkImage::WatermarkImage(Mat watermark) {
    this->watermark = watermark;
}

void WatermarkImage::apply(Frame* frame) {
    // reduzir o tamanho da watermark para ser 20% da imagem base
    // mantem o aspect ratio da watermark inicial, não da imagem base
    Mat frameMat=frame->getChannels().toMat();
    int new_height = int(frameMat.rows * 0.2);
    int new_width = int(new_height / (double(this->watermark.rows) / double(this->watermark.cols)));

    resize(this->watermark, this->watermark, Size(new_width, new_height));

    // converter watermark e original para 4 channels (adicionar o alpha, para poder fazer a watermark transparente)
    cvtColor(frameMat, frameMat, COLOR_RGB2RGBA);
    cvtColor(this->watermark, this->watermark, COLOR_RGB2RGBA);

    // criar region of interest (zona onde vou meter a watermark)
    Rect roi = Rect(0, 0, new_width, new_height);

    // isto vai "apontar" para a memoria correspondente à region of interest
    Mat original_roi = frameMat(roi);


    // meter a ROI do original e a watermark overlapped, com opacidade reduzida para a watermark
    Mat watermark_overlapped;
    addWeighted(this->watermark, 0.4, original_roi, 0.6, 0.0, watermark_overlapped);

    // adicionar watermark à region of interest
    watermark_overlapped.copyTo(original_roi);
    frame->fromMat(frameMat);
}
