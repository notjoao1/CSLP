//
// Created by JPe_D on 11/2/2023.
//

#include "Encoder.h"

Encoder::Encoder(const string &input_file, const string &output_file) : video(input_file), stream_out(output_file) {
    m = 3; // TODO: deixei um valor estático por agora, so para testes
}

// TODO: falta o "video_format"
void Encoder::generate_headers(const Size& frame_size) {
    stream_out.write(16, frame_size.width); // 2 bytes
    stream_out.write(16, frame_size.height); // 2 bytes
    stream_out.write(8, m); // 1 byte, parametro 'm'
}

// TODO: talvez dividir em várias funções (encodeFrame, encodeChannel, encodeValue)
void Encoder::encode() {
    Mat curr_frame, curr_channel, channels[3];
    curr_frame = video.getNextFrame();
    generate_headers(curr_frame.size());

    unsigned char a, b, c, r, p;
    while (!curr_frame.empty()) {
        split(curr_frame, channels);
        for (int i = 0; i < curr_frame.channels(); ++i) {
            curr_channel = channels[i];
            for (int j = 0; j < curr_frame.rows; ++j) {
                for (int k = 0; k < curr_frame.cols; ++k) {
                    if (j - 1 < 0 && k - 1 >= 0) {  // left border edge case
                        b = curr_channel.at<uchar>(j, k - 1);
                        a = b, c = b; // propagar b para 'a' e 'c'
                        p = JPEG_LS(curr_channel.at<uchar>(j, k), a, b, c);
                        r = curr_channel.at<uchar>(j, k) - p; // TODO: se r for negativo?
                    } else if (k - 1 < 0 && j - 1 >= 0) {   // upper border edge case

                    }
                }
            }
        }

    }
}

static unsigned char JPEG_LS(unsigned char a, unsigned char b, unsigned char c, unsigned char x) {
    unsigned char maximum = max(a,b);
    unsigned char minimum = min(a,b);
    if(c >= maximum)
        return minimum;
    else if (c <= minimum)
        return maximum;
    else
        return a + b - c;
}

