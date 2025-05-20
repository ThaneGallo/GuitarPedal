/*
 * WM8524.c
 *
 *  Created on: May 18, 2025
 *      Author: thane
 */

 #include "WM8524.h"
 #include "main.h"
 

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
