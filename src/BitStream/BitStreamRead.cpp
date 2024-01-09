//
// Created by Kikom on 03/10/2023.
//

#include "BitStreamRead.h"
#include "iostream"

void BitStreamRead::refresh_small_buffer() {
    if (back_front_occured) {   // swap their values
        unsigned long long aux = last_sb;
        last_sb = small_buffer;
        small_buffer = aux;
        back_front_occured = false; // reset
        small_buffer_pointer = 64;
        return;
    }
    last_sb = small_buffer;
    this->file.read((char *) &this->small_buffer, 8);
    this->small_buffer_pointer = 64;
}

bool BitStreamRead::should_refresh_small_buffer(int n) const {
    return this->small_buffer_pointer - n < 0;
}

bool BitStreamRead::read_bit() {
    if(should_refresh_small_buffer(1)) {
        refresh_small_buffer();
    }
    unsigned long long mask = 0x8000000000000000;
    mask >>= 64 - small_buffer_pointer;
    unsigned long long res = (this->small_buffer & mask) >> (small_buffer_pointer - 1);
    this->small_buffer_pointer--;
    return res;
}

unsigned long long BitStreamRead::read(int n) {
    if(should_refresh_small_buffer(n)) {
        unsigned long long res=0;
        if(small_buffer_pointer>0){
            res = this->small_buffer;
            res<<=64-small_buffer_pointer;
            res>>=(64-n);
            n-=this->small_buffer_pointer;
        }
        refresh_small_buffer();
        signed long long mask2 = 0x8000000000000000;
        mask2>>=(n-1);
        res =  res | ((this->small_buffer & mask2) >> (64-n));
        this->small_buffer_pointer-=n;
        return res;
    }
    signed long long mask = 0x8000000000000000;
    mask>>=n-1;
    auto ull_mask = static_cast<unsigned long long>(mask) >> (64 - small_buffer_pointer);
    unsigned long long res = (this->small_buffer & ull_mask) >> (small_buffer_pointer - n);
    this->small_buffer_pointer-=n;
    return res;

}

void BitStreamRead::close() {
    this->file.close();
}


void BitStreamRead::back_front(int n) {
    if(this->small_buffer_pointer+n>64){
        this->small_buffer_pointer=n-64+this->small_buffer_pointer;
        back_front_occured = true;
        // swap the two values, the current small_buffer will become
        // the old small_buffer
        unsigned long long aux = last_sb;
        last_sb = small_buffer;
        small_buffer = aux;
        return;
    }
    this->small_buffer_pointer+=n;
}

std::string BitStreamRead::read_string(){
    std::string str;
    char c = read(8);
    while( c != '\0' ){
        str += c ;
        c = read(8);
    }
    return str;
}