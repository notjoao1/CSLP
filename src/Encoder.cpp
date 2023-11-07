//
// Created by JPe_D on 11/2/2023.
//

#include "Encoder.h"
#include <vector>

Encoder::Encoder(const string &input_file, const string &output_file) : video(input_file), stream_out(output_file) {
    m = 3; // TODO: deixei um valor estático por agora, so para testes
}

// TODO: falta o "video_format"
// TODO: mudar para string, depois quando se encontra um \0, é fixe para ler
void Encoder::generate_headers(const Size& frame_size) {
    stream_out.write(16, frame_size.width); // 2 bytes
    stream_out.write(16, frame_size.height); // 2 bytes
    stream_out.write(8, m); // 1 byte, parametro 'm'
}

// Receives multi-channel Mat
void Encoder::encodeFrame(const Mat& f) {
    std::vector<Mat> channels;
    split(f, channels);
    for (int i = 0; i < f.channels(); ++i) {
        encodeChannel(channels[i]);
    }
}

// Receives single channel Mat
void Encoder::encodeChannel(const Mat& channel) {
    // encode first row and first column directly
    for (int col = 0; col < channel.cols; col++) {
        encodeValue(channel.at<uchar>(1, col));
    }

    for (int row = 1; row < channel.rows; row++) {
        encodeValue(channel.at<uchar>(row, 1));
    }

    int r; // tem de ser int, pois pode ser negativo
    unsigned char a, b, c, p;

    for (int row = 1; row < channel.rows; row++)
        for (int col = 1; col < channel.cols; col++) {
            a = channel.at<uchar>(row, col - 1);
            b = channel.at<uchar>(row - 1, col);
            c = channel.at<uchar>(row - 1, col - 1);
            p = JPEG_LS(a, b, c);
            r = int(channel.at<uchar>(row, col)) - int(p);
            encodeValue(r);
        }

}

void Encoder::encodeValue(int v) {
    golomb.encode(v, this->m);
}

// TODO: talvez dividir em várias funções (encodeFrame, encodeChannel, encodeValue)
void Encoder::encode() {
    Mat curr_frame, curr_channel, channels[3];
    curr_frame = video.getNextFrame();
    generate_headers(curr_frame.size());

    // frame loop
    while (!curr_frame.empty()) {
        encodeFrame(curr_frame);
        curr_frame = video.getNextFrame();
    }
}

// TODO: nao sei se é suposto ter isto como static
static unsigned char JPEG_LS(unsigned char a, unsigned char b, unsigned char c) {
    unsigned char maximum = max(a,b);
    unsigned char minimum = min(a,b);
    if(c >= maximum)
        return minimum;
    else if (c <= minimum)
        return maximum;
    else
        return a + b - c;
}

