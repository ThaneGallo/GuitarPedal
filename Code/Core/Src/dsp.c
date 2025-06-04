#include "dsp.h"


void combine_buffers(float* out_buf, float* in_buf, float attenuation, uint16_t size){

    uint16_t i;
    float max_value = 0; // for normalizing

    //check for null
    if (!out_buf) {
         myprintf("combine_buffers ERROR: out_buf is NULL\n");
         return;
     }

     if (!in_buf) {
         myprintf("combine_buffers ERROR: in_buf is NULL\n");
         return;
     }

     if (size == 0) {
         myprintf("combine_buffers WARNING: size is 0\n");
         return;
     }

    //combines buffers and searches for max to renormalize later
    for(i = 0; i < size; i++){

    	myprintf("combine_buffers(): size=%d\n", size);
    	myprintf("out_buf=%p, in_buf=%p\n", out_buf, in_buf);
    	myprintf("out_buf=%d, in_buf=%d\n", out_buf[i], in_buf[i]);

        out_buf[i] =  attenuation * in_buf[i] + out_buf[i];


        if(out_buf[i] > max_value){
            max_value = out_buf[i];
        }

    }

    //re-normalizes from -1 --> 1
     for(i = 0; i < size; i++){

        out_buf[i] /= max_value;

    }


}

void create_delay(delay *delay, float delay_ms){

	uint8_t i;

	myprintf("in_create_delay \n");



	uint8_t num_buf = (uint8_t)(delay_ms / (TIME_FOR_ONE_SAMPLE_MS * HALF_BUF_LEN));

	if (num_buf < 1) {
	    myprintf("Delay is too short");
	    return;
	}

	// Allocate array of float* (buffer pointers)
	delay->delay_buf = malloc(sizeof(float*) * num_buf);
	if (!delay->delay_buf) {
	    myprintf("Not enough space for delay buffer pointers");
	    return;
	}

	// Allocate each individual float buffer
	for (i = 0; i < num_buf; i++) {

	    delay->delay_buf[i] = malloc(sizeof(float) * HALF_BUF_LEN);
	    myprintf("delay_buf[%d] = %p\n", i, delay->delay_buf[i]);

	    if (!delay->delay_buf[i]) {
	        myprintf("Not enough space for buffer %d\n", i);

	        // Free previously allocated buffers
	        for (int j = 0; j < i; j++) {
	            free(delay->delay_buf[j]);
	        }
	        free(delay->delay_buf);
	        return;
	    }

	}


	delay->num_buf = num_buf;
	delay->ms = delay_ms;
	delay->index = 0;
	delay->filled_all = 0;

}


void process_delay(float* new_data, delay *delay, float attenuation){

	if(delay->filled_all == 1){
		//combine old data with new
		combine_buffers(new_data, delay->delay_buf[delay->index], attenuation, HALF_BUF_LEN);

		//copy old data to buffer for next copy
		memcpy(delay->delay_buf[delay->index], new_data, (HALF_BUF_LEN)*sizeof(float));


		delay->index++;


		//reset index to start from first buffer
		if(delay->index >= delay->num_buf){
			delay->index = 0;
		}
		return;
	}
	else{
	memcpy(delay->delay_buf[delay->index], new_data, (HALF_BUF_LEN)*sizeof(float));

	delay->index++;

	if(delay->index >= delay->num_buf){
			delay->index = 0;
			delay->filled_all = 1;
	}
	return;
	}


}



void soft_clip(float *data, float drive, uint16_t size){
//as drive goes up it increases cutoff





}



/**
 * @brief computes filter coefficients for easier application later
 * @param filter pointer to pilter union
 * @param type enum for type
 * @param order order number for attenuation rate
 * @param Q q-factor (if applicable (order > 1))
 * @param freq filter->cutoff frequency point
 */
void create_filter(filter *filter, enum filter_type type, uint8_t order, float Q, float cutoff)
{
    filter->type = type;
    filter->cutoff = cutoff;
    filter->Q = Q;
    
    
    switch (order)
    {
    case -1:
    	filter->order = -1;
        break;


    case 1:
        
        float tau = 1.0f / (2.0f * M_PI * cutoff);

        switch (type)
        {
        case LOW_PASS_FILTER:
            filter->coeff.first_order.a0 = SAMPLE_RATE / (tau + SAMPLE_RATE);
            filter->coeff.first_order.a1 = 1 - filter->coeff.first_order.a0;

            break;
        case HIGH_PASS_FILTER:
            filter->coeff.first_order.a0 = tau / (tau + SAMPLE_RATE);
            filter->coeff.first_order.a1 = 1 - filter->coeff.first_order.a0;

            break;

        default:
            printf("Unexpected Filter type: %d\n", filter->type);
            break;
        }

        break;

    case 2:


    	//if Q >= .707 it resonates
    	 switch (type)
    	        {
    	 	 float omega = 2 * M_PI * cutoff / SAMPLE_RATE;
    		 float alpha = sinf(omega) / (2.0f * Q);
    		 float cos_omega = cosf(omega);
    		 float a0 = 1 + alpha;

    	 case LOW_PASS_FILTER:
    	     filter->coeff.second_order.b0 = ((1 - cos_omega) / 2.0f) / a0;
    	     filter->coeff.second_order.b1 = (1 - cos_omega) / a0;
    	     filter->coeff.second_order.b2 = filter->coeff.second_order.b0;
    	     filter->coeff.second_order.a1 = (-2 * cos_omega) / a0;
    	     filter->coeff.second_order.a2 = (1 - alpha) / a0;
    	     break;

    	 case HIGH_PASS_FILTER:
    	     filter->coeff.second_order.b0 = ((1 + cos_omega) / 2.0f) / a0;
    	     filter->coeff.second_order.b1 = -(1 + cos_omega) / a0;
    	     filter->coeff.second_order.b2 = filter->coeff.second_order.b0;
    	     filter->coeff.second_order.a1 = (-2 * cos_omega) / a0;
    	     filter->coeff.second_order.a2 = (1 - alpha) / a0;
    	     break;

    	 case BAND_PASS_FILTER:
    	     filter->coeff.second_order.b0 = alpha / a0;
    	     filter->coeff.second_order.b1 = 0;
    	     filter->coeff.second_order.b2 = -alpha / a0;
    	     filter->coeff.second_order.a1 = -2 * cos_omega / a0;
    	     filter->coeff.second_order.a2 = (1 - alpha) / a0;
    	     break;

    	 case BAND_STOP_FILTER:
    	     filter->coeff.second_order.b0 = 1 / a0;
    	     filter->coeff.second_order.b1 = (-2 * cos_omega) / a0;
    	     filter->coeff.second_order.b2 = 1 / a0;
    	     filter->coeff.second_order.a1 = (-2 * cos_omega) / a0;
    	     filter->coeff.second_order.a2 = (1 - alpha) / a0;
    	     break;

    	 default:

    	            printf("Unexpected Filter type: %d\n", filter->type);
    	            break;
    	        }


        float omega = (2 * M_PI * cutoff) / SAMPLE_RATE;
        float alpha = sinf(omega) / (2 * Q);
        float cos_omega = cosf(omega);



        break;

    default:
        printf("Unexpected Filter Order: %d\n", filter->order);
        break;
    }
}


/**
 * @brief filters data in time domain
 * @param data pointer to transformed signal freq response
 * @param filter filter to be used
 * @param size size of signal array
 */
void filter_data_iir(float *data, filter *filter, uint16_t size){

	  uint16_t i = 0;



		    switch(filter->order){

		    case 1:

		    	float previous_value = data[0];

		        for (i = 0; i < size; i++)
		        {

		            data[i] = filter->coeff.first_order.a0 * data[i]
					+ filter->coeff.first_order.a1 * previous_value;
		            previous_value = data[i];
		        }

		    	break;

		    case 2:

		    		float x = data[i];

		    	    float y = filter->coeff.second_order.b0 * x
		    	            + filter->coeff.second_order.b1 * filter->coeff.second_order.xn_1
		    	            + filter->coeff.second_order.b2 * filter->coeff.second_order.xn_2
		    	            - filter->coeff.second_order.a1 * filter->coeff.second_order.yn_1
		    	            - filter->coeff.second_order.a2 * filter->coeff.second_order.yn_2;

		    	    data[i] = y;//updates value in array

		    	    // Update state
		    	    filter->coeff.second_order.xn_2 = filter->coeff.second_order.xn_1;
		    	    filter->coeff.second_order.xn_1 = x;
		    	    filter->coeff.second_order.yn_2 = filter->coeff.second_order.yn_1;
		    	    filter->coeff.second_order.yn_1 = y;

		    	break;

		    default:

		    	break;


		    }





	}







 /**
  * @brief uses low pass filter to adjust signal (mimics analog filter) in frequency domain
  * @param data pointer to transformed signal freq response (post fft)
  * @param filter->cutoff desired filter->cutoff frequency
  * @param rolloff desired rate of rolloff (-1 for ideal)
  * @param size size of signal array
  */
 void low_pass_filter_freq(complex float *data, filter *filter, uint16_t size)
 {
     uint8_t i = 0;


    
    
     // in case of ideal filter
     if (filter->order == -1)
     {
         for (i = 0; i < size; i++)
         {
             float freq_bin = ((float)i * SAMPLE_RATE) / size;

             if (freq_bin >= filter->cutoff)
             {
                 data[i] = 0;
             }
         }
     }

     for (i = 0; i < size; i++)
     {
         float freq_bin = ((float)i * SAMPLE_RATE) / size;

         if (freq_bin >= filter->cutoff)
         {
             float amplitude_ratio = pow(10, (-filter->Q * log10f(freq_bin / filter->cutoff)) / 20.0f);
             data[i] = amplitude_ratio * data[i];
         }
     }
 }

 /**
  * @brief uses high pass filter to adjust signal (mimics analog filter)in frequency domain
  * @param data pointer to transformed signal freq response (post fft)
  * @param filter->cutoff desired filter->cutoff frequency
  * @param rolloff desired rate of rolloff (-1 for ideal)
  * @param size size of signal array
  */
 void high_pass_filter_freq(complex float *data, filter *filter, uint16_t size)
 {
     uint8_t i = 0;
     float magnitude_db;

    filter->cutoff = (1 - filter->coeff.first_order.a0) / (filter->coeff.first_order.a0 * 2.0f * M_PI * SAMPLE_RATE);

     // in case of ideal filter
     if (filter->order == -1)
     {
         for (i = 0; i < size; i++)
         {
             float freq_bin = ((float)i * SAMPLE_RATE) / size;

             if (freq_bin <= filter->cutoff)
             {
                 data[i] = 0;
             }
         }
     }

     for (i = 0; i < size; i++)
     {
         float freq_bin = ((float)i * SAMPLE_RATE) / size;

         if (freq_bin <= filter->cutoff)
         {
             float amplitude_ratio = pow(10, (-filter->Q * log10f(filter->cutoff / freq_bin)) / 20.0f);
             data[i] = amplitude_ratio * data[i];
         }
     }
 }

 /**
  * @brief mimics analog band pass filter in frequency domain
  * @param data pointer to transformed signal freq response (post fft)
  * @param upper_cutoff desired filter->cutoff for lpf
  * @param lower_cutoff desired filter->cutoff for hpf
  * @param hpf_rolloff desired rate of upper rolloff (-1 for ideal)
  * @param lpf_rolloff desired rate of lower rolloff (-1 for ideal)
  * @param size size of signal array
  */
 void band_pass_filter_freq(complex float *data, filter *filter, uint16_t size)
 {
     // does not need any special ordering like bsp bc the filters do not interact with one another
     high_pass_filter_freq(data, filter, size);
     low_pass_filter_freq(data, filter, size);
 }

 /**
  * @brief mimics analog band stop filter in frequency domain
  * @param data pointer to transformed signal freq response (post fft)
  * @param upper_cutoff desired filter->cutoff for hpf
  * @param lower_cutoff desired filter->cutoff for lpf
  * @param hpf_rolloff desired rate of lower rolloff (-1 for ideal)
  * @param lpf_rolloff desired rate of higher rolloff (-1 for ideal)
  * @param size size of signal array
  */
 void band_stop_filter_freq(complex float *data, filter *filter, uint16_t size)
 {
     uint8_t i;

     // split then sum
     complex float *low_pass_data = malloc(sizeof(complex float) * size);
     complex float *high_pass_data = malloc(sizeof(complex float) * size);

     if (!low_pass_data || !high_pass_data)
     {
         printf("Low or high pass data is NULL");
         return;
     }

     // copies data to new arrays
     memcpy(low_pass_data, data, sizeof(complex float) * size);
     memcpy(high_pass_data, data, sizeof(complex float) * size);

     low_pass_filter_freq(low_pass_data, filter, size);
     high_pass_filter_freq(high_pass_data, filter, size);

     // thanks to handy dandy superposition i can sum to get filter results
     for (i = 0; i < size; i++)
     {
         data[i] = (low_pass_data[i] + high_pass_data[i]);
     }

     free(low_pass_data);
     free(high_pass_data);
 }

/**
 * @brief calculates twiddle factor
 * @param k sample number
 * @param N total number of samples
 * @param sign 1 or -1 depending on fft or ifft
 * @return twiddle factor
 */
complex float twiddle_factor(int k, int N, int8_t sign)
{
    float angle = (sign) * 2.0 * M_PI * k / N;
    return cosf(angle) + I * sinf(angle);
}

/**
 * @brief cooley-tukey FFT divide and conquer
 * @param data digitized audio data
 * @param size size of data array (2^n)
 * @return pointer to transformed array
 */
complex float *fft(complex float *data, uint16_t size)
{

    // base case
    if (size == 1)
    {
        return data;
    }

    else
    {

        complex float *even_data = malloc(sizeof(complex float) * size / 2);
        complex float *odd_data = malloc(sizeof(complex float) * size / 2);

        uint8_t i;

        // moves data into even and odd parts
        for (i = 0; i < size / 2; i++)
        {
            even_data[i] = data[2 * i];
            odd_data[i] = data[2 * i + 1];
        }

        even_data = fft(even_data, size / 2);
        odd_data = fft(odd_data, size / 2);

        // apply twiddle factor and recombine
        for (i = 0; i < size / 2; i++)
        {
            data[i] = even_data[i] + twiddle_factor(i, size, 1) * odd_data[i];
            data[i + size / 2] = even_data[i] - twiddle_factor(i, size, 1) * odd_data[i];
        }

        free(even_data);
        free(odd_data);

        return data;
    }
}

/**
 * @brief inverts fft
 * @param data digitized audio data
 * @param size size of data array (2^n)
 * @return pointer to reverted array
 */
complex float *inverse_fft(complex float *data, uint16_t size)
{

    // base case
    if (size == 1)
    {
        return data;
    }

    else
    {

        complex float *even_data = malloc(sizeof(complex float) * size / 2);
        complex float *odd_data = malloc(sizeof(complex float) * size / 2);

        uint8_t i;

        // moves data into even and odd parts
        for (i = 0; i < size / 2; i++)
        {
            even_data[i] = data[2 * i];
            odd_data[i] = data[2 * i + 1];
        }

        even_data = inverse_fft(even_data, size / 2);
        odd_data = inverse_fft(odd_data, size / 2);

        // apply twiddle factor and recombine
        for (i = 0; i < size / 2; i++)
        {
            data[i] = even_data[i] + twiddle_factor(i, size, -1) * odd_data[i];
            data[i + size / 2] = even_data[i] - twiddle_factor(i, size, -1) * odd_data[i];
        }

        // normallizes
        for (i = 0; i < size; i++)
        {
            data[i] /= (size / 2);
        }

        free(even_data);
        free(odd_data);

        return data;
    }
}
