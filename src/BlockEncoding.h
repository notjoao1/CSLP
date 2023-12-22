#ifndef GTD_VC_BLOCKENCODING_H
#define GTD_VC_BLOCKENCODING_H

#include <string>
#include "Representation/VideoManipulator.h"
#include "BitStream/BitStreamWrite.h"
#include "Encoding/GolombCode.h"
#include "opencv2/imgproc.hpp"
#include "Encoder.h"

/**
 * @class Encoder
 * @brief Class for video encoding.
 */
class BlockEncoding {
public:
    /**
     * @brief Constructor for Enconder.
     * @param input_file Input video file path.
     * @param output_file Output encoded video file path.
     * @param block_size Size of the encoding block for motion estimation.
     * @param search_area Size of the search area for motion estimation.
     * @param keyframe_period Number of frames between intra frames.
     */
    BlockEncoding(const std::string& input_file, const std::string& output_file, int block_size = 16, int search_area = 16, int keyframe_period = 10);

    /**
     * @brief Main function to perform video encoding.
     */
    void encode();

private:
    int block_size, search_area, keyframe_period; ///< Encoding parameters.
    Y4MReader input_video; ///< Y4M Parser to get input frames from.
    BitStreamWrite stream_out; ///< Bitstream writer for output.
    GolombCode golomb; ///< Golomb coding object.
    int m; ///< Golomb parameter.

    /**
     * @brief Encode an inter-frame (motion-compensated) video frame.
     * @param f Current frame.
     * @param p Previous frame for motion estimation.
     */
    void encodeInterFrame(const Mat& f, const Mat& p);

    /**
     * @brief Encode an intra-frame (keyframe) video frame.
     * @param f Current frame.
     */
    void encodeIntraFrame(const Mat& f);

    /**
     * @brief Encode a single unsigned integer value using Golomb coding.
     * @param v Value to be encoded.
     */
    void encodeValue(unsigned int v);

    /**
     * @brief Encode the difference between two macroblocks.
     * @param block Error block to be encoded.
     */
    void encodeBlockDifference(const Mat& block);

    /**
     * @brief Generate headers for the encoded video based on input video headers.
     */
    void generate_headers();

    /**
     * @brief Extract a block from a given frame.
     * @param original_frame Original video frame.
     * @param row Row index of the block.
     * @param col Column index of the block.
     * @return Extracted block.
     */
    Mat getBlock(const Mat& original_frame, int row, int col) const;

    /**
     * @brief Search for the best-matching block in the previous frame. Uses Four Step Search Algorithm
     * @param prev_frame Previous video frame.
     * @param curr_block Current block to be matched.
     * @param y Row index of the block.
     * @param x Column index of the block.
     * @param rows Number of rows in the search area.
     * @param cols Number of columns in the search area.
     * @return Tuple with the best-matching block and the (x, y) vector.
     */
    std::tuple<Mat, int, int> searchBestBlock(const Mat& prev_frame, const Mat& curr_block, int y, int x, int rows, int cols);

    /**
     * @brief Perform JPEG-LS compression on three bytes.
     * @param a First byte.
     * @param b Second byte.
     * @param c Third byte.
     * @return Compressed byte.
     */
    static unsigned char JPEG_LS(unsigned char a, unsigned char b, unsigned char c);

    /**
     * @brief Pad a given frame to handle border cases.
     * @param frame Original frame to be padded.
     * @return Padded frame.
     */
    Mat pad(const Mat& frame) const;

    /**
     * @brief Encode the interframe channel (e.g., color channels).
     * @param c_channel Current channel.
     * @param p_channel Previous channel for motion estimation.
     */
    void encodeInterframeChannel(const Mat& c_channel, const Mat& p_channel);

    /**
     * @brief Calculate the Mean Absolute Difference (MAD) between two image blocks.
     * @param block1 First block.
     * @param block2 Second block.
     * @return MAD value.
     */
    int calculateMAD(const Mat& block1, const Mat& block2) const;
};

#endif // GTD_VC_BLOCKENCODING_H