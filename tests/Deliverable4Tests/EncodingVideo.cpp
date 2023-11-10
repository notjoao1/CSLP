//
// Created by joao on 09/11/2023.
//

#include "../../src/Encoder.h"

int main2() {
    Encoder e("/home/tiago/Transferências/ducks_take_off_444_720p50.y4m", "/home/tiago/CLionProjects/GTD-VC/tests/Deliverable4Tests/encoded_videoencoded_video.gtd");
    e.encode();
    return 0;
}