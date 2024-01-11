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

*Disclaimer: One configuration corresponds to one encoding/statistic cycle of one video with a specific set of parameters: encoding -> decoding -> statistics (Time, CR, PSNR, ...).*

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

![8_PSNR_KP_WCOMP](https://github.com/notjoao1/GTD-VC/assets/97046574/beb11414-d046-42c1-a1c8-9f0a935638f6)


### PSNR / CR

As we can see bellow, the smaller the PSNR (more noise), the greater the compression ratio. This is because the more compressed the video is, the more lossy it is, and consequently the more noise it has.
A lossless video has an infinite PSNR value.

![9_PSNR_CR](https://github.com/notjoao1/GTD-VC/assets/97046574/8d28f5fa-f9ec-4d88-927e-8947c6532d3a)
*Note:* The value on the left (at point (0, 65)) might seem weird. That's because the PSNR is 'inf' when lossless, but in order to represent that value in the plot, we made it 65, to fit the image

### PSNR / Quantization

Quantization Avg. takes the average quantization of the 3 channels. Quantization was represented in number of bits that we lost to quantization - meaning that when a channel has quantization = 1, we are using 7 bits to represent its colors, instead of 8.
As we can see, the higher the quantization, the smaller the PSNR value (video has more noise). This is expected in lossy encoding.

![10_PSNR_QUANTAVG](https://github.com/notjoao1/GTD-VC/assets/97046574/d2b821d7-4e29-458a-9946-dfe0a7c4e1f3)



### Execution Time

![11_TIME_CR](https://github.com/notjoao1/GTD-VC/assets/97046574/ee5e66d6-2c50-40ea-8e02-0682288dabc6)

This plot shows that, the more compressed a video is, the faster it is to write to the disk. The greatest bottleneck of our program is the I/O speed - especially write speed. The more compressed a video is, the less we have to write and the faster the execution is.


![12_TIME_SA](https://github.com/notjoao1/GTD-VC/assets/97046574/5d0ab05a-cf5d-4d18-81d8-c7dc9575f5c6)
As we can see, reducing the search area has an effect on the execution time when a search area is small enough. After a certain threshold, it has no impact on execution time. A lower search area (8) has a small effect on the execution time compared to a slightly bigger search area (16) - about 2 seconds.
Overall, the search area has a small effect on the execution time


# Optimization


To ensure the optimization of our Codec, we've taken the following measures:

## Best-Block Search Optimization

We've used *Four-Step Search (FSS)* as a block-matching algorithm employed in motion estimation for video compression. Initially, the reference block is divided into smaller blocks, and a search window is established. The algorithm starts at the center of the window, evaluating the similarity between the reference block and corresponding blocks in the target image. The search window then moves to the position with the best match, reducing in size for a more focused search. This process iterates until a termination criterion is met, efficiently narrowing down the search space and providing a balance between computational simplicity and motion estimation accuracy.

### Choice

*Why have we choosen this search method?*
The following plots, compare the execution time and PSNR of the different block-matching algorithms. As we can see, Four Step Search provides both great performance and PSNR, while maintining an acceptable complexity level. Although ARPS provides better perfomance and similar PSNR, we didn´t go with it because it's implementation was significantly more complex than FSS.

![imagem](https://github.com/notjoao1/GTD-VC/assets/97362005/ee20d2d8-6fe1-4c94-8313-7edec1dbf855)

![imagem](https://github.com/notjoao1/GTD-VC/assets/97362005/766f3d25-efa3-4c66-a053-24b1055b266d)

These graphics were obtained from the following [source](https://www.mathworks.com/matlabcentral/fileexchange/8761-block-matching-algorithms-for-motion-estimation).


## Perf 

To further optimize our code, we've initially ran it with the perf Tool.
We've obtained the following measurements, running our code with *-O0* flag:

![imagem](https://github.com/notjoao1/GTD-VC/assets/97362005/2bf56384-26d9-42f6-b606-414cc6125d2d)

After taking this into account, we've further optimized our BitStream classes (*Read* and *Writter*).
We made the BitStreamWrite class directly use the ostream file buffer.

Running perf once again, we've obtained the following results:

![imagem](https://github.com/notjoao1/GTD-VC/assets/97362005/fe7965c2-4601-491a-b728-02fe3fb1412f)



## Conclusion
