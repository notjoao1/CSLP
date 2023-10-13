//
// Created by Kikom on 03/10/2023.
//

#include "BitStreamRead.h"
#include "iostream"

void BitStreamRead::refresh_small_buffer() {
    if(should_refresh_big_buffer()){
        refresh_big_buffer();
    }
    this->small_buffer = this->big_buffer.at(++big_buffer_pointer);
    this->small_buffer_pointer = 64;
}

bool BitStreamRead::should_refresh_small_buffer(int n) const {
    return this->small_buffer_pointer - n < 0;
}

void BitStreamRead::refresh_big_buffer() {
    if(!this->big_buffer.empty())
        this->last_sb = this->big_buffer.at(this->big_buffer_max_size-1);
    this->big_buffer.clear();
    char* temp[8 * this->big_buffer_max_size];
    this->file.read( (char *) temp, 8 * this->big_buffer_max_size );
    this->big_buffer.assign((unsigned long long*)temp,((unsigned long long*)temp) + this->big_buffer_max_size );
    this->big_buffer_pointer=-1;
}

bool BitStreamRead::should_refresh_big_buffer() const {
    return this->big_buffer_pointer+1 >= this->big_buffer_max_size;
}

bool BitStreamRead::read_bit() {
    if(should_refresh_small_buffer(1)) {
        refresh_small_buffer();
        unsigned long long mask = 0x8000000000000000;
        unsigned long long res = (this->small_buffer & mask) >> 63;
        this->small_buffer_pointer--;
        this->small_buffer<<=1;
        return res;
    }
    unsigned long long mask = 0x8000000000000000;
    unsigned long long res = (this->small_buffer & mask) >> 63;
    this->small_buffer_pointer--;
    this->small_buffer<<=1;
    return res;
}

unsigned long long BitStreamRead::read(int n) {
    if(should_refresh_small_buffer(n)) {
        unsigned long long res=0;
        if(small_buffer_pointer>0){
            res = this->small_buffer;
            res>>=64-n;
            n-=this->small_buffer_pointer;
        }
        refresh_small_buffer();
        signed long long mask2 = 0x8000000000000000;
        mask2>>=(n-1);
        res =  res | ((this->small_buffer & mask2) >> (64-n));
        this->small_buffer_pointer-=n;
        this->small_buffer<<=n;
        return res;
    }
    signed long long mask = 0x8000000000000000;
    mask>>=n-1;
    unsigned long long res = (this->small_buffer & mask) >> (64-n);
    this->small_buffer_pointer-=n;
    this->small_buffer<<=n;
    if(n==64)
        this->small_buffer=0;
    return res;

}

void BitStreamRead::close() {
    this->file.close();
}


void BitStreamRead::push_front(int n,unsigned long long bits) {
    bits<<=64-n;
    bits>>=64-n;
    if(this->small_buffer_pointer+n>64){
        int a = 64-this->small_buffer_pointer;
        bits>>=a;
        bits<<=64-n+a;
        this->small_buffer=bits;
        this->big_buffer_pointer--;
        this->small_buffer_pointer=n-a;
        return;
    }
    this->small_buffer>>=n;
    if(n>63)
        this->small_buffer=0;
    bits<<=64-n+this->small_buffer_pointer;
    this->small_buffer_pointer+=n;
    this->small_buffer = this->small_buffer | bits;

}

void BitStreamRead::back_front(int n) {
    if(this->small_buffer_pointer+n>64){
        if(big_buffer_pointer<1){
            this->small_buffer= this->last_sb << (128-n-this->small_buffer_pointer);
            this->big_buffer_pointer--;
        }else{
            this->small_buffer=this->big_buffer.at(--big_buffer_pointer)<< (128-n-this->small_buffer_pointer);
        }
        this->small_buffer_pointer=n-64+this->small_buffer_pointer;
        return;
    }
    this->small_buffer= this->big_buffer.at(big_buffer_pointer) << (64-this->small_buffer_pointer-n);
    this->small_buffer_pointer+=n;
}

