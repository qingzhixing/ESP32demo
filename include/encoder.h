#pragma once
#ifndef _ENCODER_H
#define _ENCODER_H

#include <stdint.h>

#define ENCODER_KEY GPIO_NUM_15
#define ENCODER_S1 GPIO_NUM_16
#define ENCODER_S2 GPIO_NUM_4
#define ENCODER_KEY_PRESSED_LEVEL LOW

typedef void (*EncoderKeyCallback)(void);
/*
 * direction: true for clockwise, false for counterclockwise
 */
typedef void (*EncoderTurnCallback)(bool direction);

void encoder_init();
/*
 * Called in timer interrupt to update the encoder position.
 * Returns true if the encoder position has changed.
 */
bool update_encoder();

// callback will be called in timer interrupt
void set_on_encoder_press(EncoderKeyCallback callback);
// callback will be called in timer interrupt
void set_on_encoder_release(EncoderKeyCallback callback);
// callback will be called in timer interrupt
void set_on_encoder_turn(EncoderTurnCallback callback);
bool is_encoder_pressed();

#endif // !_ENCODER_H