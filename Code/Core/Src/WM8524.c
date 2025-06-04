/*
 * WM8524.c
 *
 *  Created on: May 18, 2025
 *      Author: thane
 */

 #include "WM8524.h"
 #include "main.h"
 

void prepare_for_dac(uint16_t* out_data, float* in_data, uint16_t size){
	uint16_t i;


	for(i = 0; i < size; i++){

			//shifts from -1 --> 1 to -2048 --> 2048
			// then shifts up 2048 to dac range of 0-4096
			out_data[i] =  (uint16_t)((in_data[i] * 2047.5f) + 2047.5f);


		}



}




// 	// Called when the **first half** of the DMA buffer is filled
//	void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc) {
//	    if (hadc->Instance == ADC1) {
//	        process_first_half = 1;
//	    }
//	}
//
//	// Called when the **second half** is filled (full transfer complete)
//	void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
//	    if (hadc->Instance == ADC1) {
//	        // Process the second half of the buffer
//	    	process_second_half = 1;
//	    }
//	}
