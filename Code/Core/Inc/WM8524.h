/*
 * WM8524.h
 *
 *  Created on: May 18, 2025
 *      Author: thane
 */

#ifndef SRC_WM8524_H_
#define SRC_WM8524_H_

#include "stdint.h"


#define MUTE_PIN 0
#define AIFMODE_PIN 0
#define BYPASS_PIN 0
#define PDWN_PIN 0


	void toggle_WM8524();
	void Aifmode_ctrl(uint8_t aifmode);
	void send_WM8524();
	void prepare_for_dac(uint16_t* out_data, float* in_data, uint16_t size);


#endif /* SRC_WM8524_H_ */
