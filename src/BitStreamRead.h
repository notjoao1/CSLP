//
// Created by Kikom on 03/10/2023.
//

#ifndef GTD_VC_BITSTREAMREAD_H
#define GTD_VC_BITSTREAMREAD_H
#include "vector"
#include "fstream"

class BitStreamRead {
private:
    unsigned long long small_buffer = 0;
    int small_buffer_pointer = -1;
    std::vector<unsigned long long> big_buffer;
    const long big_buffer_max_size = 65536;
    long big_buffer_pointer = big_buffer_max_size;
    std::fstream file;

    void refresh_small_buffer();
    bool should_refresh_small_buffer(int n) const ;
    void refresh_big_buffer() ;
    bool should_refresh_big_buffer() const ;

public:
    explicit BitStreamRead(const std::string& filename) {
        this->file.open(filename , std::ios::binary | std::ios::in  );
    }

    void close();
    bool read_bit();
    unsigned long long read(int n);
};


#endif //GTD_VC_BITSTREAMREAD_H
