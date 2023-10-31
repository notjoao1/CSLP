//
// Created by Kikom on 01/10/2023.
//

#ifndef GTD_VC_GOLOMBCODE_H
#define GTD_VC_GOLOMBCODE_H

#include <vector>
#include "../BitStream/BitStreamRead.h"
#include "../BitStream/BitStreamWrite.h"

/**
 * @class GolombCode
 * @brief A class for encoding and decoding Golomb codes.
 */
class GolombCode {

private:
public:
    /**
     * @brief Encodes an integer into a Golomb code with a specified parameter.
     * @param num The integer to be encoded.
     * @param m The parameter for Golomb coding.
     * @return A vector of booleans(bits) representing the encoded Golomb code.
     */
    static std::vector<bool> encode(int num, int m);

    /**
     * @brief Decodes one integer from a Golomb-encoded bit stream using a specified parameter.
     * @param m The parameter for Golomb coding.
     * @param stream The Golomb-encoded bit stream.
     * @return The decoded integer.
     */
    static int decode_one(int m, std::vector<bool> stream);

    /**
     * @brief Decodes a sequence of integers from a Golomb-encoded bit stream using a specified parameter.
     * @param m The parameter for Golomb coding.
     * @param stream The Golomb-encoded bit stream.
     * @param n The number of integers to decode.
     * @return A vector of decoded integers.
     */
    static std::vector<int> decode(int m, const std::vector<bool> &stream, int n);

    /**
     * @brief Decodes an integer from a 64-bit value using a specified parameter.
     * @param i The 64-bit value to be decoded.
     * @param m The parameter for Golomb coding.
     * @return The decoded integer.
     */
    static int decodeFrom64bits(unsigned long long i, int m);

    /**
     * @brief Encodes an integer into a Golomb code with a specified parameter and writes it to a BitStreamWrite object.
     * @param i The integer to be encoded.
     * @param m The parameter for Golomb coding.
     * @param stream The BitStreamWrite object for writing the encoded Golomb code.
     */
    static void encode(int i, int m, BitStreamWrite &stream);

    /**
     * @brief Encodes a vector of integers into Golomb codes with a specified parameter and writes them to a BitStreamWrite object.
     * @param num_array The vector of integers to be encoded.
     * @param m The parameter for Golomb coding.
     * @param stream The BitStreamWrite object for writing the encoded Golomb codes.
     */
    static void encode(std::vector<int> num_array, int m, BitStreamWrite &stream);

    /**
     * @brief Decodes one integer from a Golomb-encoded bit stream using a specified parameter from a BitStreamRead object.
     * @param m The parameter for Golomb coding.
     * @param stream The BitStreamRead object containing the Golomb-encoded bit stream.
     * @return The decoded integer.
     */
    static int decode_one(int m, BitStreamRead &stream);

    /**
     * @brief Decodes a sequence of integers from a Golomb-encoded bit stream using a specified parameter from a BitStreamRead object.
     * @param m The parameter for Golomb coding.
     * @param b The BitStreamRead object containing the Golomb-encoded bit stream.
     * @param n The number of integers to decode.
     * @return A vector of decoded integers.
     */
    static std::vector<int> decode(int m, BitStreamRead &b, int n);
};

#endif //GTD_VC_GOLOMBCODE_H
