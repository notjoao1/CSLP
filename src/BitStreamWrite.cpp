//
// Created by Kikom on 03/10/2023.
//

#include <iostream>
#include "BitStreamWrite.h"

void BitStreamWrite::refresh_small_buffer() {
    this->big_buffer.push_back(this->small_buffer);
    if(should_refresh_big_buffer())
        refresh_big_buffer();
    this->small_buffer_pointer = -1;
    this->small_buffer = 0;
}

bool BitStreamWrite::should_refresh_small_buffer(int n) const {
    return this->small_buffer_pointer + n > 63;
}

void BitStreamWrite::refresh_big_buffer() {
    file.write((char *) this->big_buffer.data(), 8 * this->big_buffer.size());
    this->big_buffer.clear();
}

bool BitStreamWrite::should_refresh_big_buffer() {
    return this->big_buffer.size() > this->big_buffer_max_size;
}

void BitStreamWrite::write_bit(bool b) {
    if(should_refresh_small_buffer(1)){
        refresh_small_buffer();
        this->small_buffer = b | this->small_buffer;
        this->small_buffer_pointer++;
        return;
    };

    this->small_buffer<<=1;
    this->small_buffer_pointer++;
    this->small_buffer = b | this->small_buffer;
}

void BitStreamWrite::write(int n,unsigned long long bits) {
    if(should_refresh_small_buffer(n)) {
        int available = 63-this->small_buffer_pointer;
        this->small_buffer<<=available;
        this->small_buffer= this->small_buffer | ( bits >> ( n-available ) );
        refresh_small_buffer();
        bits<<= 64 - n + available;
        bits>>= 64 - n + available;
        this->small_buffer = bits | this->small_buffer;
        this->small_buffer_pointer+=n-available;
        return;
    }
    this->small_buffer<<=n;
    this->small_buffer_pointer+=n;
    this->small_buffer = bits | this->small_buffer;
}

void BitStreamWrite::close() {
    this->small_buffer<<=63-this->small_buffer_pointer;
    this->big_buffer.push_back(this->small_buffer);
    refresh_big_buffer();
    this->file.close();
}
