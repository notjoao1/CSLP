#ifndef GTD_VC_ENCODER_H
#define GTD_VC_ENCODER_H

#include "BitStream/BitStreamWrite.h"
#include "Encoding/GolombCode.h"
#include "opencv2/imgproc.hpp"
#include "Representation/VideoManipulator.h"
#include "Y4MReader.h"

/**
 * @brief Class for encoding video ( only intra frame ).
 */
class Encoder {
private:
    Y4MReader input_video;
    BitStreamWrite stream_out; /**< Pointer to the BitStreamWrite instance for output stream. */
    int m; /**< Golomb parameter. */
    int quantizationY; /**< Quantization level for the Y luma channel. */
    int quantizationU; /**< Quantization level for the U chroma channel. */
    int quantizationV; /**< Quantization level for the V chroma channel. */
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
    void encodeChannel(const Mat& c, int quantization);

    /**
     * @brief Encodes a single value using Golomb coding.
     * @param v The value to be encoded.
     */
    void encodeValue(unsigned int v);

    /**
     * @brief Generates headers based on Y4M input video headers.
     */
    void generate_headers();

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
     * @param input_file The input file name, should be a Y4M file 4:4:4.
     * @param output_file The output file name.
     * @param quantizationY Level of quantization for the luma channel in lossy encoding.
     * @param quantizationU Level of quantization for the luma channel in lossy encoding.
     * @param quantizationV Level of quantization for the luma channel in lossy encoding.
     */
    Encoder(const string& input_file, const string& output_file, int quantizationY = 0, int quantizationU = 0, int quantizationV = 0);

    /**
     * @brief Main encoding function that encodes the entire video.
     */
    void encode();

};

#endif // GTD_VC_ENCODER_H