#pragma once
#ifndef _ENCODER_H
#define _ENCODER_H

#include <stdint.h>

#define ENCODER_KEY GPIO_NUM_15
#define ENCODER_S1 GPIO_NUM_16
#define ENCODER_S2 GPIO_NUM_4

extern int16_t encoder_last_state;
extern int16_t encoder_state;
extern int16_t encoder_count;

void encoder_init();

/*
 * Called in timer interrupt to update the encoder position.
 * Returns true if the encoder position has changed.
 */
bool update_encoder();

#endif // !_ENCODER_H