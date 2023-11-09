//
// Created by joao on 09/11/2023.
//

#include "../../src/Encoder.h"

int main() {
    Encoder e("tests/Deliverable4Tests/videos/ducks_take_off_444_720p50.y4m", "encoded_video.gtd");
    e.encode();
    return 0;
}