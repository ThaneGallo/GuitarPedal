#ifndef DSP_H
#define DSP_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complex.h>
#include <math.h>

// ============================================================
//                 Digital Signal Processing Header
// ============================================================

/*
 * File: dsp.h
 * Description: This header file contains the declarations and
 *              function prototypes for the Digital Signal Processing (DSP)
 *              functions used in the project.
 * Author: Thane Gallo
 * Date: 3/8/25
 */



// filters 
 enum filter_type
 {
     LOW_PASS_FILTER,
     HIGH_PASS_FILTER,
     BAND_PASS_FILTER,
	 BAND_STOP_FILTER
 
 };

 
struct first_order_coeff
{
    float a0;
    float a1;
};

struct second_order_coeff
{
    float a0;
    float a1;
    float a2;

    float b0;
    float b1;
    float b2;


    //state memory
    float xn_1;
    float xn_2;
    float yn_1;
    float yn_2;
};


 union filter_coefficients
 {
     struct first_order_coeff first_order;
     struct second_order_coeff second_order;
 };

 typedef struct filter {
    enum filter_type type;
    uint8_t order;
    float cutoff;
    float Q;
    union filter_coefficients coeff;

}filter; 


//delay
typedef struct delay {
   float ms;
   float** delay_buf;
   uint8_t num_buf;
   uint8_t filled_all;
   uint8_t index;

}delay;




// ============================================================
//                      Function Declarations
// ============================================================

// z-transform
//  complex float* z_transform( float *data, uint8_t size);

// fft functions
complex float twiddle_factor(int k, int N, int8_t sign);
complex float *turn_to_imag(float *data, uint16_t size);
complex float *fft(complex float *data, uint16_t size);
complex float *inverse_fft(complex float *data, uint16_t size);


//filter functions
void create_filter(filter *filter, enum filter_type type, uint8_t order, float Q, float cutoff);
void filter_data_iir(float* data, filter *filter, uint16_t size);
void low_pass_filter_freq(complex float *data, filter *filter, uint16_t size);
void high_pass_filter_freq(complex float *data, filter *filter, uint16_t size);
void band_pass_filter_freq(complex float *data, filter *filter, uint16_t size);
void band_stop_filter_freq(complex float *data, filter *filter, uint16_t size);


//delay functions
void create_delay(delay *delay, float delay_ms);
void process_delay(float* new_data, delay *delay, float attenuation);


//distortion/overdrive
void hard_clip(float* data, float amplitude, uint16_t size);
void soft_clip(float* data, float drive, uint16_t size);



// other pedals to be implimented
/*
delay
gain
wah
frog
clip / distortion
equilizer
*/

// misc utilities
float find_average(uint16_t* data, uint16_t size);
void combine_buffers(float* out_buf, float* in_buf, float attenuation, uint16_t size);

// ============================================================
//                       Constants & Macros
// ============================================================

#define IDEAL_FILTER -1
#define SAMPLE_RATE 96000
#define TIME_FOR_ONE_SAMPLE_MS .01
#define ADC_BUF_LEN 8192
#define HALF_BUF_LEN 4096

#endif // DSP_H
