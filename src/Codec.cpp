//
// Created by joao on 31/10/2023.
//

#include "Codec.h"

void Codec::encode() {

}

void Codec::decode() {

}

Codec::Codec(VideoManipulator v, BitStreamWrite stream) {

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


