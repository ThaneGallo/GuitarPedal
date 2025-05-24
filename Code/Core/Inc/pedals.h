#ifndef DSP_H
#define DSP_H

#include "dsp.h"


// ============================================================
//                 Pedal header
// ============================================================

/*
 * File: pedals.h
 * Description: This header file contains the declarations and 
 *              function prototypes for the pedal simulatior 
 *              functions used in the project.
 * Author: Thane Gallo
 * Date: 3/20/25
 */


// ============================================================
//                      Function Declarations
// ============================================================




//other pedals to be implimented
/*

clip / distortion
equilizer
*/

void delay_pedal();
void gain_pedal();
void wah_pedal();
void frog_pedal();
void distortion_pedal();
void overdrive_pedal();



// ============================================================
//                       Constants & Macros
// ============================================================

typedef struct node{

    uint8_t pedal;
    node* next;

} node;



#define CLEAN 0x00
#define  DELAY 0x01
#define GAIN 0x02
#define WAH 0x04


#endif // PEDALS_H