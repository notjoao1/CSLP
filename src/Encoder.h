#ifndef GTD_VC_ENCODER_H
#define GTD_VC_ENCODER_H

#include "BitStream/BitStreamWrite.h"
#include "Encoding/GolombCode.h"
#include "opencv2/imgproc.hpp"
#include "Representation/VideoManipulator.h"

/**
 * @brief Class for encoding video ( only intra frame ).
 */
class Encoder {
private:
    VideoManipulator* video; /**< Pointer to the VideoManipulator instance to read video file. */
    BitStreamWrite* stream_out; /**< Pointer to the BitStreamWrite instance for output stream. */
    int m; /**< Golomb parameter. */

public:
    /**
     * @brief Encodes a single frame.
     * @param f The input frame to be encoded.
     */
    void encodeFrame(const Mat& f);

    /**
     * @brief Encodes a single channel of the input frame.
     * @param c The input channel to be encoded.
     */
    void encodeChannel(const Mat& c);

    /**
     * @brief Encodes a single value using Golomb coding.
     * @param v The value to be encoded.
     */
    void encodeValue(unsigned int v);

    /**
     * @brief Generates headers.
     * @param frame_size The size of the frames in the video.
     */
    void generate_headers(const Size& frame_size);

    /**
     * @brief Performs JPEG-LS encoding on three input bytes.
     * @param a First byte.
     * @param b Second byte.
     * @param c Third byte.
     * @return The output value from JPEG-LS.
     */
    static unsigned char JPEG_LS(unsigned char a, unsigned char b, unsigned char c);

    /**
     * @brief Constructor for the Encoder class.
     * @param in Pointer to the VideoManipulator instance for input video.
     * @param out Pointer to the BitStreamWrite instance for output stream.
     */
    Encoder(VideoManipulator* in, BitStreamWrite* out);

    /**
     * @brief Main encoding function that encodes the entire video.
     */
    void encode();

};

#endif // GTD_VC_ENCODER_H