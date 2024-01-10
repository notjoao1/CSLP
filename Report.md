# CSLP 2023/2024 Project Report

# Features 

 - Predictive Encoding
 - Motion-Based Block-Encoding (Four Step Search + Motion-Detection)
 - Hybrid Encoding (Intra + Inter Frame with Predictive/Motion-Block Encoding)
 - Golomb Encoding of Residuals (with m-parameter estimation)
 - Lossy Encoding (Quantization-based)

*Note: All features were developed aiming the YUV 4:4:4 video format.*

# Methodology

We developed a command-line Codec that supports the features mentioned above. We also created a python-wrapper around the Codec (scripts/tester.py) that allows us to test multiple configurations, in a automated manner, according to the following parameters:
  - Block Size
  - Search Area
  - Keyframe (Interval between Intra frames)
  - Quantization (per Channel)

Using the python tester, we runned *1472* configurations with relevant combinations of the parameters mencioned above, deep-testing the capabilities of our Codec, which allowed us to collect important data with relation to *Compression Ratio (CR)*, *Execution Time (Time)* and *Peak signal-to-noise ratio (PSNR)*.

*!Disclaimer: One configuration corresponds to one encoding/statistic cycle of one video with a specific set of parameters: encoding -> decoding -> statistics (Time, CR, PSNR, ...). *

## Statistics

*Number of configurations:* 1472
*Execution Time:* 19h24m (Single-Thread -> One configuration at a time)
*Computer Specs:*

![imagem](https://github.com/notjoao1/GTD-VC/assets/97362005/e98d2dbe-768c-4926-8e15-ff0a0ad5ca56)

*Command:*

![imagem](https://github.com/notjoao1/GTD-VC/assets/97362005/6518d79a-fc35-408b-a09a-703f58706a7a)
*!Disclaimer: We later executed 32 more configurations with search area of 8, giving the total of 1472 configurations. *

# Results

The collected data is present in a csv file (scripts/resources/data.csv). Lets now analyse data that helps us better understand not only how the different parameters of our Codec work with each other, but mainly how we can set them up for the most efficient execution.
The following plots were created in *Matlab*, with a script we've created (scripts/graficos_CSLP.m)...

### Block Size 

*Block Size* is a parameter of the Motion Block-Encoder that allows us to define the size of the block to be used to encode each Inter Frame (N x N square).
Based on the following plots, we observe that the block size has a relevant impact in the *Compression Ratio (CR)*. 
As the plot suggests, we've determined that an optimal value for the block size is 16. Also worth to mention that block size adds no significant impact to the *Peak signal-to-noise ratio (PSNR)* of videos submitted to *lossy encoding*. 

![1_CR_BS_NOCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/56025313-64de-449b-8b4b-2e7b0934586e)

![2_CR_BS_WCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/dd06a990-6876-40c6-ad41-ba2825994af2)


### Search Area 

*Search Area* is a parameter of the Motion Block-Encoder that allows us to define the 'distance' in which we desire to look for the most simillar block. The most similar the block, the smalller the differences, and the better is the compression.
Based on the plots produced, we've observed that the search area has little impact on both the compression ratio and PSNR, not only in lossy, but also and non-lossy modes. With that in mind, we've choosen the value of 16 for the search area mainly based on *Execution Time (Time)*, but also taking into consideration *CR* and *PSNR*, being this the optimal value between these parameters.

![3_PSNR_SA_WCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/5ef9b1a7-4f22-4882-a6de-69c9560ecc90)
*Note:* the missing data on the PSNR by search area graph is due to the fact that we didn't ran configurations with search area = 8 and 0 < quantization < 4.

![4_CR_SA_NOCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/c8931bb7-0240-40eb-a35f-a8620193daac)

![5_CR_SA_WCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/561851ed-28f3-49f0-bcf4-ae178520e128)



### Key Frame Period

*Key Frame Period* is a parameter of the Hybrid-Encoder that allows us to define the interval between Intra-Frame Codifications. This is extremely important, as Intra-Frame codifications is what guarantees that the differences accumulated on Block-Encoding doesn't grow into something significant.

As we can see in the following 3 plots, independently off the quantization levels used, keyframe period has no effect on neither *PSNR* nor *compression ratio*. For that reason, a keyframe period of *10* is the optimal choice. 


![6_CR_KP_NOCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/c4c0ba99-95b0-4544-9576-df8c6066839e)

![7_CR_KP_WCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/2906b40d-9195-4998-b3bc-5faf1cf2f436)

![8_PSNR_KP_WCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/747df7a1-de1b-4b0d-a213-1a47f63c5c49)


### Ducks Take off 720p50 Motion compensated

| block_size / search_area / keyframe_period | Time (s)  | Space (mB) |
|--------------------------------------------|-----------|------------|
| 4 , 16 , 64                                |   142     |    826     |
| 8 , 16 , 64                                |   62      |    710     |
| 16 , 16 , 64                               |   36      |    676     |
| 8 , 8 , 64                                 |   73      |    705     |

### Ducks Take off 720p50 only JPEG-LS

ENCODER:
    time: 42.27s
    size: 963MB

DECODER:
    time: 43.80s









![9_PSNR_CR](https://github.com/notjoao1/GTD-VC/assets/97046574/a79d5005-2ccc-408d-970c-263ac537c06e)



![10_PSNR_QUANTAVG](https://github.com/notjoao1/GTD-VC/assets/97046574/a7eae49c-71d8-49d8-823b-75a478633f89)


![11_TIME_CR](https://github.com/notjoao1/GTD-VC/assets/97046574/ee5e66d6-2c50-40ea-8e02-0682288dabc6)


![12_TIME_SA](https://github.com/notjoao1/GTD-VC/assets/97046574/5d0ab05a-cf5d-4d18-81d8-c7dc9575f5c6)
