#include "PCM1802.h"

extern uint8_t process_first_half;
extern uint8_t process_second_half;


	/*
	 * 0 = Power on
	 * 1 = Power down
	 *
	 * */
	void toggle_PCM1802(uint8_t toggle){

		//toggle pdwn
		//high = off
		//low = on
	    if(toggle == 0){
			// HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_SET);   // on
		}
		else if(toggle == 1){
		    // HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_RESET); // off
		}

		else{
			//shouldnt be here


		}

	}

	/*
	 * 0 = 64x samples
	 * 1 = 128x samples
	 *
	 * */
	void HPF_bypass_ctrl(uint8_t hpf){
		    if(hpf == 1){
				// HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_SET);   // on
			}
			else if(hpf == 0){
			    // HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_RESET); // off
			}

			else{
				//shouldnt be here


			}


	}


	/*
	 *
	 *
	 * 0 = no DC component on DOUT
	 * 1 = DC Component on DOUT
	 *
	 * */
	void oversampling_ctrl(uint8_t osr){

		if(osr == 1){
			// HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_SET);   // on
		}
		else if(osr == 0){
		    // HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_RESET); // off
		}

		else{
			//shouldnt be here

		}



	}


	void setup_PCM1802(uint8_t hpf, uint8_t osr){
		HPF_bypass_ctrl(hpf);
		oversampling_ctrl(osr);


	}

	void read_PCM1802(){


	}

	// Called when the **first half** of the DMA buffer is filled
	void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc) {
	    if (hadc->Instance == ADC1) {
	        process_first_half = 1;
	    }
	}

	// Called when the **second half** is filled (full transfer complete)
	void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	    if (hadc->Instance == ADC1) {
	        // Process the second half of the buffer
	    	process_second_half = 1;
	    }
	}
