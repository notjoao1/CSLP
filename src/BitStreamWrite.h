//
// Created by Kikom on 03/10/2023.
//

#ifndef GTD_VC_BITSTREAMWRITE_H
#define GTD_VC_BITSTREAMWRITE_H
#include "vector"
#include "fstream"

class BitStreamWrite{
private:
    unsigned long long small_buffer = 0;
    int small_buffer_pointer = -1;
    std::vector<unsigned long long> big_buffer;
    const long big_buffer_max_size = 65536;
    std::fstream file;

    void refresh_small_buffer() ;
    bool should_refresh_small_buffer(int n) const ;
    void refresh_big_buffer() ;
    bool should_refresh_big_buffer() ;

public:
    explicit BitStreamWrite(const std::string& filename) {
        this->file.open(filename,std::ios::binary | std::ios::out  );
    }

    void close();
    void write_bit(bool b);
    void write(int n,unsigned long long bits);
};


#endif //GTD_VC_BITSTREAMWRITE_H
