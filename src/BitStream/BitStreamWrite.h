//
// Created by Kikom on 03/10/2023.
//

#ifndef GTD_VC_BITSTREAMWRITE_H
#define GTD_VC_BITSTREAMWRITE_H
#include "vector"
#include "fstream"
#include "string"


/**
 * @class BitStreamWrite
 * @brief A class for writing bits to a file stream.
 */
class BitStreamWrite{
private:
    unsigned long long small_buffer = 0; /**< Small buffer to store bits temporarily. */
    int small_buffer_pointer = -1; /**< Pointer to the current position in the small buffer. */
    std::vector<unsigned long long> big_buffer; /**< Vector to store a large buffer of bits. */
    const long big_buffer_max_size = 65536; /**< Maximum size of the big buffer. */
    std::fstream file; /**< File stream for writing. */

    /**
     * @brief Refreshes the small buffer by writing by appending it's contents to the big buffer.
     */
    void refresh_small_buffer() ;

    /**
     * @brief Checks whether the small buffer should be refreshed based on the number of bits to be written.
     * @param n The number of bits to be written. n shouldn't be bigger than 64.
     * @return A boolean indicating whether the small buffer should be refreshed.
     */
    bool should_refresh_small_buffer(int n) const ;

    /**
     * @brief Refreshes the big buffer by writing its contents to the file.
     */
    void refresh_big_buffer() ;

    /**
     * @brief Checks whether the big buffer should be refreshed.
     * @return A boolean indicating whether the big buffer should be refreshed.
     */
    bool should_refresh_big_buffer() ;

public:
    /**
     * @brief Constructor for the BitStreamWrite class.
     * @param filename The name of the file to write to.
     */
    explicit BitStreamWrite(const std::string& filename) {
        this->file.open(filename, std::ios::binary | std::ios::out);
    }

    /**
     * @brief Closes the file stream, ensuring that any remaining bits are written to the file.
     */
    void close();

    /**
     * @brief Writes a single bit to the file.
     * @param b The boolean value to be written.
     */
    void write_bit(bool b);

    /**
     * @brief Writes a specified number of bits to the file.
     * @param n The number of bits to be written.
     * @param bits The bits to be written.
     */
    void write(int n, unsigned long long bits);

    /**
     * @brief Write a string to bitStream.
     * @param s The string to write.
     */
    void write(const std::string& s);
};


#endif //GTD_VC_BITSTREAMWRITE_H

