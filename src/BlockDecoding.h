#ifndef GTD_VC_BLOCKDECODING_H
#define GTD_VC_BLOCKDECODING_H

#include <string>
#include "Representation/VideoManipulator.h"
#include "BitStream/BitStreamWrite.h"
#include "Encoding/GolombCode.h"
#include "opencv2/imgproc.hpp"
#include "Decoder.h"
#include "Y4MWriter.h"

/**
 * @brief The BlockDecoding class handles the decoding of video
 */
class BlockDecoding {
public:
    /**
     * @brief Constructor for BlockDecoding.
     * @param input_file The input file path.
     * @param output_file The output file path.
     */
    BlockDecoding(const std::string& input_file, const std::string& output_file);

    /**
     * @brief Initiates the decoding process.
     */
    void decode();
    Y4MWriter output_vid;
private:
    /**
     * @brief Decodes an interframe channel.
     * @param p_channel A pointer to an OpenCV Mat representing a channel of a video frame.
     * @param quantization Quantization used to (lossy) encode this channel. Same quantization
     * level will be used to decode. May be 0, if channel was encoded lossless.
     * @return The decoded interframe channel.
     */
    cv::Mat decodeInterframeChannel(cv::Mat* p_channel, int quantization);

    /**
     * @brief Retrieves a block from a frame.
     * @param original_frame A pointer to the original video frame.
     * @param row The row index specifying the block's position.
     * @param col The column index specifying the block's position.
     * @return The retrieved block.
     */
    cv::Mat getBlock(const cv::Mat* original_frame, int row, int col) const;

    /**
     * @brief Sets a block in a frame.
     * @param original_frame A pointer to the original video frame.
     * @param block A pointer to an OpenCV Mat representing a block.
     * @param row The row index specifying the block's position.
     * @param col The column index specifying the block's position.
     */
    void setBlock(const cv::Mat* original_frame, cv::Mat* block, int row, int col) const;

    Decoder* decoder; ///< A pointer to a Decoder object.
    int width, height, block_size, search_area, keyframe_period, fps_num, fps_denum; ///< Video parameters.
    BitStreamRead stream_in; ///< A BitStreamRead object for reading from a bitstream.
    int m; ///< Golomb parameter.
    int quantizationY; /**< Quantization level for the luma channel. */
    int quantizationU; /**< Quantization level for the U chroma channel. */
    int quantizationV; /**< Quantization level for the V chroma channel. */
    int real_width, real_height; ///< Unpadded width/height

    /**
     * @brief Decodes an interframe using the previous frame.
     * @param previous_frame A pointer to the previous video frame.
     * @return The decoded interframe.
     */
    cv::Mat decodeInterFrame(const cv::Mat* previous_frame);

    /**
     * @brief Reads headers necessary for the decoding process.
     */
    void read_headers();

    /**
     * @brief Decodes a single value using Golomb decoding.
     * @return The decoded value.
     */
    int decodeValue();

    /**
     * @brief Decodes a single frame from the input stream.
     * @return The decoded frame.
     */
    Mat decodeFrame();

    /**
     * @brief Decodes a single channel from the input stream.
     * @param quantization Quantization used to (lossy) encode this channel. Same quantization
     * level will be used to decode. May be 0, if channel was encoded lossless.

     * @return The decoded channel.
     */
    Mat decodeChannel(int quantization);

    /**
     * @brief Performs JPEG-LS encoding on three input bytes.
     * @param a First byte.
     * @param b Second byte.
     * @param c Third byte.
     * @return The output value from JPEG-LS.
     */
    unsigned char JPEG_LS(unsigned char a, unsigned char b, unsigned char c);
};

#endif // GTD_VC_BLOCKDECODING_H
