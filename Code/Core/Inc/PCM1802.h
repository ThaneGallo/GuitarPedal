/*
 * PCM1802.h
 *
 *  Created on: May 18, 2025
 *      Author: thane
 */

#ifndef SRC_PCM1802_H_
#define SRC_PCM1802_H_

#include "string.h"
#include "stdint.h"
#include "main.h"

#define FSYNC_PIN 0
#define OSR_PIN 0
#define BYPASS_PIN 0
#define PDWN_PIN 0


	void toggle_PCM1802(uint8_t toggle);
	void HPF_bypass_ctrl(uint8_t hpf);
	void oversampling_ctrl(uint8_t osr);

	void setup_PCM1802(uint8_t hpf, uint8_t osr);
	void read_PCM1802();



#endif /* SRC_PCM1802_H_ */
