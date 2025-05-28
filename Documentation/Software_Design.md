# Software Design

## Table of Contents
* [Development](#Development)
* [How-To](#How-To)
* [Roadbumps](#Roadbumps)
* [Conclusion / Future Design Changes](#Conclusion--Future-Design-cChanges)

# Development 
## Filters
Originally I had intended to have a frequency based filter which would just take cutoffs and desired rollofs and would compute each adjusted value as the set of samples was passed through. This turned to be very slow and did not process quickly enough. This led to the development of time based filters through using an IIR or infinite impulse response filter so it would require no FFTs and would just use simple addition and subtraction. As this type of filter is a general form based on the desired order it would allow for any of the basic filter types:

* Low Pass (1st, 2nd order)
* High Pass (1st, 2nd order)
* Band Pass (2nd order)
* Band Stop (2nd order)

This would attenuate the frequency components of the signal and would alter the sound. A good example would be that if you were to create a band=stop around 60Hz you would be able to increase sound quality as it removes transmission line noise.

Resonance can be achieved within these filters given the order is 2 and the Q > .707 (.707 is the maximally flat filter response) and as Q increases the system oscillates and rings and will become unstable so a reccomeneded Q is to be between 0 and 1.

## Delay 
The next implimented effect was the delay effect which would effectively add an echo every time interval as decided by the user. This would require memory from the system to properly "remember" the audio sample and echo it later. As the sample buffers would be filled every 10ish milliseconds this would require a very large amount of memory for larger delays. So temporarily (will be looked into later) the delay is to be limited. 

## Gain


# How-To

First a DC Block (fucntions as high pass filter) funcition is to be called to prime the data for processing moving 0-4096 to -1 to 1.

## Digital Filtering
All filters supported by the project begin with the below function:
 
create_filter(filter *filter, enum filter_type type, uint8_t order, float Q, float cutoff)
  
This takes a pointer to the filter struct and calculates all of the coefficients necessary for the IIR based on the desired cutoff, order, and Q factor for the sharpness of the filter (above .707 starts resonance around the cutoff)

Then after the filter is made you simply use filter_data_iir(float *data, filter *filter, uint8_t size) which processes the data before it gets sent to the dac_buffer for playback.


## Gain and Distortion
There are two main types of distortion currently supported, soft and hard clipping which perform the following effect.

### Hard Clipping : Harsh

void hard_clip(float* data, float amplitude, uint16_t size);

Clips to a set of thresholds so that all values above an upper threshold get moved down and all below the lower threshold get moves down. In the above implimentation it uses a set amplitude from the center and clips accordingly.

### Soft Clipping : Warm sounding distortion 

void soft_clip(float* data, float drive, uint16_t size);

Has a smoother clipping around the threshold and this specific implimentation uses tanh() to perform the clipping and uses a varible drive to change the strength of the clipping.


# Roadbumps

## To Float or not to float 
The first main roadblock I came to was what format to use for my calculations. The first step into this throught process is that the first step of the chain would be the stm-ADC which gives me a 12 bit number (16 bits) which would mean I would have to convert regardless so my decision is between the fixed point or floating point values. Within my reasearch it appears that floating point values have a higher range and therefore more precision which would mean there is less distortion between caclulations. Thankfully my MCU has FPU support so this was a no brainer.


## Normalization and Beginning DSP Effect Chains
Since my hardware is limited in its accuracy I am thankfully able to utilize more complex software to make up for this. Specifically my input signal is not centered at Vref/2 Which would distort when effects were applied so I applied a DC-Blocking high-pass Filter first to move the data from around 0-4096 to -2048-2048 then moved to -1 to 1 to maximize float precision although this would mean the data is not out of range for the DAC (same range as ADC) this makes it easier to apply processing.

This conversion would be made into a secondary buffer of floats so that block-algorithims such as FFT would be able to be processed without many conversions every sample. 

After the desired filters and effects were added renormalization would need to happen moving from float back into uint16 as well as the midpoint but this is even easier as you can center the data to half of the bitwidth of the sample to guarentee it maximizes output range.



# Conclusion / Future Design Changes

PCM1740E/2K appears to be much better but would cost me nearly 500x time amount of the other option
