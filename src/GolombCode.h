//
// Created by Kikom on 01/10/2023.
//

#ifndef GTD_VC_GOLOMBCODE_H
#define GTD_VC_GOLOMBCODE_H

#include <vector>
#include "BitStreamRead.h"
#include "BitStreamWrite.h"

class GolombCode {

private:
public:
    static std::vector<bool> encode(int num,int m);
    static int decode_one(int m,std::vector<bool> stream);
    static std::vector<int> decode(int m, const std::vector<bool>& stream , int n);

    static int decodeFrom64bits(unsigned long long i , int m);

    static void encode(int i,int m, BitStreamWrite& stream);
    static void encode(std::vector<int> num_array,int m, BitStreamWrite& stream);
    static int decode_one(int m,BitStreamRead& stream);
    static std::vector<int> decode(int m,BitStreamRead& b,int n);
};


#endif //GTD_VC_GOLOMBCODE_H
