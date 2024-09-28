#pragma once
#ifndef _ENCODER_H
#define _ENCODER_H

#include <stdint.h>

#define ENCODER_KEY GPIO_NUM_15
#define ENCODER_S1 GPIO_NUM_16
#define ENCODER_S2 GPIO_NUM_4
#define ENCODER_KEY_PRESSED_LEVEL LOW

#define ENCODER_CLOCKWISE true
#define ENCODER_COUNTERCLOCKWISE false

typedef void (*EncoderKeyCallback)(void);
/*
 * direction: true for clockwise, false for counterclockwise
 */
typedef void (*EncoderTurnCallback)(bool direction);

void encoder_init();
/*
 * Called in timer interrupt to update the encoder position.
 */
void encoder_update();

// callback will be called in timer interrupt
void on_encoder_key_pressed(EncoderKeyCallback callback);
// callback will be called in timer interrupt
void on_encoder_key_released(EncoderKeyCallback callback);
// callback will be called in timer interrupt
void on_encoder_turned(EncoderTurnCallback callback);
bool is_encoder_pressed();

// true for clockwise, false for counterclockwise
bool get_encoder_turn_direction();

#endif // !_ENCODER_H