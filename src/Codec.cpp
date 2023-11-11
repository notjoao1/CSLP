//
// Created by joao on 31/10/2023.
//

#include "Codec.h"
#include <string>


// TODO: meter o input_file no
Codec::Codec(const std::string& input_file, const std::string& output_file) : v(), stream(output_file) {
    Codec::readStream=BitStreamWrite(output_file);
    Codec::writeStream=BitStreamRead(input_file);

}

void Codec::encodeVideo() {

}

void Codec::decodeVideo() {

}

void Codec::encodeFrame() {

}

void Codec::decodeFrame() {

}
void Codec::encodeChannel() {

}

void Codec::decodeChannel() {

}

static unsigned char JPEG_LS(unsigned char a,unsigned char b,unsigned char c,unsigned char x){
    unsigned char maximum=max(a,b);
    unsigned char minimum=min(a,b);
    if(c>=maximum)
        return minimum;
    else if (c<=minimum)
            return maximum;
        else
            return a+b-c;

}


