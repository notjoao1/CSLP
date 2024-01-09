//
// Created by Kikom on 03/10/2023.
//

#include <iostream>
#include "BitStreamWrite.h"

void BitStreamWrite::refresh_small_buffer() {
    this->file.write((char *) &this->small_buffer, 8);
    this->small_buffer_pointer = -1;
    this->small_buffer = 0;
}

bool BitStreamWrite::should_refresh_small_buffer(int n) const {
    return this->small_buffer_pointer + n > 63;
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
    bits<<=64-n;
    bits>>=64-n;
    if(should_refresh_small_buffer(n)) {
        int available = 63-this->small_buffer_pointer;
        if(available>0){
            this->small_buffer<<=available;
            this->small_buffer= this->small_buffer | ( bits >> ( n-available ) );
        }
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
    refresh_small_buffer(); // write small buffer
    this->file.close();
}

void BitStreamWrite::write(const std::string& s) {
    for(char it : s) {
        write(8,it);
    }
    write(8,'\0');
}
