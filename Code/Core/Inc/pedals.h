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




//pedal_init
void delay_init(float** delay_buf, float delay_ms);




//pedal
void delay_pedal();
void filter_pedal();
void gain_pedal();
void wah_pedal();
void frog_pedal();
void distortion_pedal();
void overdrive_pedal();



// ============================================================
//                       Constants & Macros
// ============================================================

//typedef struct node{
//
//    struct pedal;
//    node* next;
//
//} node;
//
////
////struct delay_pedal
////{
////    float delay_ms;
////    float** delay_buf;
////    uint8_t filter_index;
////};
//
//
//
//
//typedef struct pedal{
//    enum pedal_type type;
//
//
//    union pedals
//    {
//
//        struct delay_pedal delay;
//        filter filter;
//
//    };
//
//} pedal;
//


enum pedal_type{
    CLEAN,
    FILTER,
    DELAY,
    WAH
};


#endif // PEDALS_H
