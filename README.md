# GTD-VC

This repository holds the source code for GTD-VC, a educational video codec developed in the context of the CSLP (Complementos sobre Linguagens de Programação) class in Universidade de Aveiro.

It includes a script (`scripts/tester.py`) that can be used to run the codec in either encode or decode mode for the source video. 

The encoder only supports [https://wiki.multimedia.cx/index.php/YUV4MPEG2](**.y4m**) video as input, and the decoder's output is also a **.y4m** video.

## Features

- Predictive coding
- Encoding with Golomb Coding
- Highly optimized bit stream reader and writer classes
- Motion-based block interframe encoding
- JPEG-LS based intraframe encoding
- Golomb Coding parameter optimization in real-time
- Optional lossy encoding with bit quantization


## Project Developers
- [Diogo Marto](https://github.com/DiogoMMarto) (108298)
- [Tiago Pereira](https://github.com/uTigas) (108546)
- [João Dourado](https://github.com/notjoao1) (108636)
