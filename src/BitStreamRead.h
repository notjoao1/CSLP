//
// Created by Kikom on 03/10/2023.
//

#ifndef GTD_VC_BITSTREAMREAD_H
#define GTD_VC_BITSTREAMREAD_H
#include "vector"
#include "fstream"

/**
 * @class BitStreamRead
 * @brief A class for reading bits from a file stream.
 */
class BitStreamRead {
private:
    unsigned long long small_buffer = 0; /**< Small buffer to store bits temporarily. */
    int small_buffer_pointer = -1; /**< Pointer to the current position in the small buffer. */
    std::vector<unsigned long long> big_buffer; /**< Vector to store a large buffer of bits. */
    const long big_buffer_max_size = 4096*256; /**< Maximum size of the big buffer. */
    long big_buffer_pointer = big_buffer_max_size - 1; /**< Pointer to the current position in the big buffer. */
    std::fstream file; /**< File stream for reading the bits. */

    unsigned long long last_sb = 0; /**< Last small buffer value of the previous big buffer. */

    /**
     * @brief Refreshes the small buffer by reading more bits from the big buffer.
     */
    void refresh_small_buffer();

    /**
     * @brief Checks whether the small buffer should be refreshed based on the number of bits to be read.
     * @param n The number of bits to be read. n shouldn't be bigger than 64.
     * @return A boolean indicating whether the small buffer should be refreshed.
     */
    bool should_refresh_small_buffer(int n) const;

    /**
     * @brief Refreshes the big buffer by reading more bits from the file and putting them on big buffer.
     */
    void refresh_big_buffer();

    /**
     * @brief Checks whether the big buffer should be refreshed.
     * @return A boolean indicating whether the big buffer should be refreshed.
     */
    bool should_refresh_big_buffer() const;

public:
    /**
     * @brief Constructor for the BitStreamRead class.
     * @param filename The name of the file to be read.
     */
    explicit BitStreamRead(const std::string &filename) {
        this->file.open(filename, std::ios::binary | std::ios::in);
    }

    /**
     * @brief Closes the file stream.
     */
    void close();

    /**
     * @brief Reads a single bit from the file.
     * @return A boolean representing the bit read.
     */
    bool read_bit();

    /**
     * @brief Reads a specified number of bits from the file.
     * @param n The number of bits to be read. n shouldn't be bigger than 64.
     * @return An unsigned long long integer representing the bits read.
     */
    unsigned long long read(int n);

    /**
     * @brief Moves the read pointer back by a specified number of bits.
     * @param n The number of bits to move the pointer back. n shouldn't be bigger than 64.
     */
    void back_front(int n);
};

#endif //GTD_VC_BITSTREAMREAD_H
