//
// Created by Kikom on 03/10/2023.
//

#ifndef GTD_VC_BITSTREAMREAD_H
#define GTD_VC_BITSTREAMREAD_H
#include "vector"
#include "fstream"
#include "string"

/**
 * @class BitStreamRead
 * @brief A class for reading bits from a file stream.
 */
class BitStreamRead {
private:
    unsigned long long small_buffer = 0; /**< Small buffer to store bits temporarily. */
    int small_buffer_pointer = -1; /**< Pointer to the current position in the small buffer. */
    const long big_buffer_max_size = 65536; /**< Maximum size of the big buffer. */
    std::ifstream file; /**< File stream for reading the bits. */
    unsigned long long last_sb = 0; /**< Value of the previous small buffer. */
    bool back_front_occured = false; /**< Boolean variable to denote if a back_front was called */

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

public:
    /**
     * @brief Constructor for the BitStreamRead class.
     * @param filename The name of the file to be read.
     */
    BitStreamRead(const std::string &filename) {
        char buffer[big_buffer_max_size];
        this->file.open(filename, std::ios_base::binary | std::ios_base::in);
        this->file.rdbuf()->pubsetbuf(buffer, big_buffer_max_size);
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

    /**
     * @brief Read a string from bitStream. Stops when it finds \0
     * @param n size of string.
     */
    std::string read_string();
};

#endif //GTD_VC_BITSTREAMREAD_H